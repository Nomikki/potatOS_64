#ifndef UTILS_LOG_H
#define UTILS_LOG_H

#include <configs.h>
#include <klib/stdio.h>

extern char *getFileName(const char *path);

#ifdef DEBUG

#define klog(fmt, ...) kprintf("%u:%s:%s: " fmt, __LINE__, getFileName(__FILE__), __FUNCTION__, ##__VA_ARGS__)

#else
#define klog(fmt, ...) kprintf(fmt, ##__VA_ARGS__)
#endif

extern void log(char *str);

#endif // UTILS_LOG_H