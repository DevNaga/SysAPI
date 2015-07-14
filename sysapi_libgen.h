#ifndef __SYSAPI_LIBGEN_H__
#define __SYSAPI_LIBGEN_H__

// These macros are used only if the code is
// in the critical performance oritented paths
// unless these macros unnecessarily complicate the code 
// and make it hard to read
#define LIKELY __builtin_expect(!!(x), 1)
#define UNLIKELY __builtin_expect(!!(x), 0)

#define UNUSED __attribute__((unused))
#define MUST_CHECK_RETURN __attribute__((warn_unused_result))
// broken is used only with the APIs that are
// exposed to the users
#define BROKEN __attribute__((visibility ("hidden")))

#define HIDDEN __attribute__((visibility ("hidden")))

#define _LIBINIT_ __attribute__((constructor))
#define _LIBEXIT_ __attribute__((destructor))

#define LIBSYSAPI_DEBUG

#ifdef LIBSYSAPI_DEBUG
#define sysapi_err(...)               sysapi_log_err("libsysapi:  ",  __VA_ARGS__)
#define sysapi_warn(...)              sysapi_log_warn("libsysapi:  ", __VA_ARGS__)
#define sysapi_info(...)              sysapi_log_info("libsysapi:  ", __VA_ARGS__)
#define sysapi_norm(...)              sysapi_log_norm("libsysapi:  ", __VA_ARGS__)
#else
#define sysapi_err(...)               (void)0
#define sysapi_warn(...)              (void)0
#define sysapi_info(...)              (void)0
#define sysapi_norm(...)              (void)0
#endif

#define sysapi_alloc_err(...)         sysapi_log_err("libsysapi:  ", \
		                                  "%s-> %s:%u allocation error\n", \
		                                  __FILE__, __func__, __LINE__)
#endif

