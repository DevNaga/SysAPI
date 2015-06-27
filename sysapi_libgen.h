#ifndef __SYSAPI_LIBGEN_H__
#define __SYSAPI_LIBGEN_H__

#define UNUSED __attribute__((unused))
#define MUST_CHECK_RETURN __attribute__((warn_unused_result))
// broken is used only with the APIs that are
// exposed to the users
#define BROKEN __attribute__((visibility ("hidden")))

#define HIDDEN __attribute__((visibility ("hidden")))

#endif

