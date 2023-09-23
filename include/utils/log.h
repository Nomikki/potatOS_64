#ifndef UTILS_LOG_H
#define UTILS_LOG_H

#include <klib/stdio.h>



#ifdef DEBUG

char *getFileName(const char *path) {
    const char *filename = path;
    const char *ptr = path;

    while (*ptr) {
        if (*ptr == '/' || *ptr == '\\') {
            filename = ptr + 1;
        }
        ptr++;
    }
    return (char *)filename;
}

#define klog(fmt, ...) kprintf("%u:%s:%s-> " fmt, __LINE__, getFileName(__FILE__), __FUNCTION__, ##__VA_ARGS__)
#else
#define klog(fmt, ...) kprintf(fmt, ##__VA_ARGS__)
#endif

extern void log(char *str);

#endif // UTILS_LOG_H