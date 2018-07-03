#ifndef __TRACE_MARKER_H__
#define __TRACE_MARKER_H__

#ifdef ENABLE_TRACING
int trace_marker_init(void);
int trace_printk(const char *fmt, ...);
#else
static inline int trace_marker_init(void) { return 0; }
static inline int trace_printk(const char *fmt, ...) { return 0; }
#endif /* ENABLE_TRACING */

#endif /* __TRACE_MARKER_H__ */

