#ifndef _WIMLIB_CAPTURE_H
#define _WIMLIB_CAPTURE_H

#include "wimlib.h"
#include "wimlib/inode_table.h"
#include "wimlib/list.h"
#include "wimlib/security.h"
#include "wimlib/util.h"

struct wim_lookup_table;
struct wim_dentry;
struct wim_inode;

/* Common parameters to implementations of building an in-memory dentry tree
 * from an on-disk directory structure. */
struct add_image_params {
	/* Pointer to the lookup table of the WIM.  */
	struct wim_lookup_table *lookup_table;

	/* List of streams that have been added so far, but without their SHA1
	 * message digests being calculated (as a shortcut).  */
	struct list_head *unhashed_streams;

	/* Hash table of inodes that have been captured for this tree so far. */
	struct wim_inode_table inode_table;

	/* The set of security descriptors that have been captured for this
	 * image so far. */
	struct wim_sd_set sd_set;

	/* Pointer to the capture configuration, which indicates whether any
	 * files should be excluded from capture or not. */
	struct wimlib_capture_config *config;

	/* Flags that affect the capture operation (WIMLIB_ADD_FLAG_*) */
	int add_flags;

	/* Extra argument; set to point to a pointer to the ntfs_volume for
	 * libntfs-3g capture.  */
	void *extra_arg;

	u64 capture_root_ino;
	u64 capture_root_dev;

	/* If non-NULL, the user-supplied progress function. */
	wimlib_progress_func_t progress_func;

	/* Progress data.  */
	union wimlib_progress_info progress;
};


/* capture_common.c */

extern void
do_capture_progress(struct add_image_params *params, int status,
		    const struct wim_inode *inode);

extern bool
exclude_path(const tchar *path, size_t path_len,
	     const struct wimlib_capture_config *config,
	     bool exclude_prefix);

extern struct wimlib_capture_config *
copy_capture_config(const struct wimlib_capture_config *config);

extern int
copy_and_canonicalize_capture_config(const struct wimlib_capture_config *config,
				     struct wimlib_capture_config **config_copy_ret);

extern void
free_capture_config(struct wimlib_capture_config *config);


#ifdef WITH_NTFS_3G
/* ntfs-3g_capture.c */
extern int
build_dentry_tree_ntfs(struct wim_dentry **root_p,
		       const tchar *device,
		       struct add_image_params *params);
#endif

#ifdef __WIN32__
/* win32_capture.c */
extern int
win32_build_dentry_tree(struct wim_dentry **root_ret,
			const tchar *root_disk_path,
			struct add_image_params *params);
#else
/* unix_capture.c */
extern int
unix_build_dentry_tree(struct wim_dentry **root_ret,
		       const tchar *root_disk_path,
		       struct add_image_params *params);
#endif

#define WIMLIB_ADD_FLAG_ROOT	0x80000000

#endif /* _WIMLIB_CAPTURE_H */
