#ifndef _WIMLIB_WIN32_H
#define _WIMLIB_WIN32_H

#include "wimlib_internal.h"
#include <direct.h>
#include <windef.h>

extern int
win32_build_dentry_tree(struct wim_dentry **root_ret,
			const tchar *root_disk_path,
			struct add_image_params *params);

extern int
win32_get_file_and_vol_ids(const wchar_t *path, u64 *ino_ret, u64 *dev_ret);

extern int
win32_read_file(const tchar *filename, HANDLE handle,
		u64 offset, size_t size, void *buf);

extern int
read_win32_file_prefix(const struct wim_lookup_table_entry *lte,
		       u64 size,
		       consume_data_callback_t cb,
		       void *ctx_or_buf,
		       int _ignored_flags);

extern int
read_win32_encrypted_file_prefix(const struct wim_lookup_table_entry *lte,
				 u64 size,
				 consume_data_callback_t cb,
				 void *ctx_or_buf,
				 int _ignored_flags);

#define FNM_PATHNAME 0x1
#define FNM_NOESCAPE 0x2
#define FNM_NOMATCH 1
extern int
fnmatch(const tchar *pattern, const tchar *string, int flags);

extern int
win32_do_apply_dentry(const tchar *output_path,
		      size_t output_path_nbytes,
		      struct wim_dentry *dentry,
		      struct apply_args *args);

extern int
win32_do_apply_dentry_timestamps(const tchar *output_path,
				 size_t output_path_nbytes,
				 const struct wim_dentry *dentry,
				 const struct apply_args *args);

extern int
fsync(int fd);

extern unsigned
win32_get_number_of_processors();

extern tchar *
realpath(const tchar *path, tchar *resolved_path);

typedef enum {
	CODESET
} nl_item;

extern int
win32_rename_replacement(const tchar *oldpath, const tchar *newpath);

extern int
win32_truncate_replacement(const tchar *path, off_t size);

extern void
win32_global_init();

extern void
win32_global_cleanup();

extern int
win32_strerror_r_replacement(int errnum, tchar *buf, size_t buflen);

extern ssize_t
win32_pread(int fd, void *buf, size_t count, off_t offset);

extern ssize_t
win32_pwrite(int fd, const void *buf, size_t count, off_t offset);

extern ssize_t
win32_writev(int fd, const struct iovec *iov, int iovcnt);

#endif /* _WIMLIB_WIN32_H */
