#include <sys/types.h>
#include <sys/stat.h>

#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <stdarg.h>
#include <unistd.h>

#include <string.h>

#include "trace-marker.h"

#ifdef ENABLE_TRACING

static int tracefd = -1;

#ifdef USE_DIRECT_WRITE
/*
 * The write function may be hooked via LD_PRELOAD. We should make a direct call here.
 *
 */
#define __NR_write 1
static ssize_t direct_write(int fd, const void *buf, size_t size)
{
    ssize_t ret;
    asm volatile
    (
        "syscall"
        : "=a" (ret)
        : "0"(__NR_write), "D"(fd), "S"(buf), "d"(size)
        : "cc", "rcx", "r11", "memory"
    );
    return ret;
}

static inline int trace_write(int fd, const void *buf, size_t size)
{
	return direct_write(fd, buf, size);
}

#else
static inline int trace_write(int fd, const void *buf, size_t size)
{
	return write(fd, buf, size);
}

#endif

int trace_marker_init(void)
{
	if (tracefd == -1) {
		tracefd = open("/sys/kernel/debug/tracing/trace_marker",
				O_WRONLY);
		if (tracefd == -1) {
			return errno;
		}
	}
	
	return 0;
}

int trace_printk(const char *fmt, ...)
{
	va_list argp;
	int len;
	char buffer[1024];

	/*
	 * Since we do not allow this to ever be closed once it was successfully
	 * opened, we do not need to worry about synchronization here.
	 */
	if (tracefd == -1) {
		return -EINVAL;
	}

	va_start(argp, fmt);
	len = vsnprintf(buffer, sizeof(buffer), fmt, argp);
	va_end(argp);

	if (len > 0) {
		int written;
		written = trace_write(tracefd, buffer, len - 1);
		if (written != (len - 1)) {
			return -EIO;
		}
	} else {
		return -EIO;
	}

	return 0;
}

static inline size_t trace_strlen(const char *str)
{
	size_t i;
	for (i = 0; *str != '\0'; ++i, ++str);
	return i;
}

int trace_puts(const char *str)
{
	size_t written;
	size_t len;
	/*
	 * Since we do not allow this to ever be closed once it was successfully
	 * opened, we do not need to worry about synchronization here.
	 */
	if (tracefd == -1) {
		return -EINVAL;
	}

	len = trace_strlen(str);
	written = trace_write(tracefd, str, len);
	if (len != written) {
		return -EFAULT;
	}

	return 0;
}
#endif /* ENABLE_TRACING */
