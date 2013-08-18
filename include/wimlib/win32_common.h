#ifndef _WIMLIB_WIN32_COMMON_H
#define _WIMLIB_WIN32_COMMON_H

#include <windows.h>
#ifdef ERROR
#  undef ERROR
#endif

#include "wimlib/types.h"
#include "wimlib/win32.h"

extern void
set_errno_from_GetLastError(void);

extern void
set_errno_from_win32_error(DWORD err);

#ifdef WITH_NTDLL
extern void
set_errno_from_nt_status(DWORD status);
#endif

extern bool
win32_path_is_root_of_drive(const wchar_t *path);

extern int
win32_get_vol_flags(const wchar_t *path, unsigned *vol_flags_ret,
		    bool *supports_SetFileShortName_ret);

extern HANDLE
win32_open_existing_file(const wchar_t *path, DWORD dwDesiredAccess);

extern HANDLE
win32_open_file_data_only(const wchar_t *path);

/* Vista and later */
extern HANDLE (WINAPI *win32func_FindFirstStreamW)(LPCWSTR lpFileName,
						   STREAM_INFO_LEVELS InfoLevel,
						   LPVOID lpFindStreamData,
						   DWORD dwFlags);

/* Vista and later */
extern BOOL (WINAPI *win32func_FindNextStreamW)(HANDLE hFindStream,
						LPVOID lpFindStreamData);

/* Vista and later */
extern BOOL (WINAPI *win32func_CreateSymbolicLinkW)(const wchar_t *lpSymlinkFileName,
						    const wchar_t *lpTargetFileName,
						    DWORD dwFlags);

extern bool
windows_version_is_at_least(unsigned major, unsigned minor);

#define running_on_windows_xp_or_later() \
			windows_version_is_at_least(5, 1)

#define running_on_windows_vista_or_later() \
			windows_version_is_at_least(6, 0)

#define running_on_windows_7_or_later() \
			windows_version_is_at_least(6, 1)



#endif /* _WIMLIB_WIN32_COMMON_H */
