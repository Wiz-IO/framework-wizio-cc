#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <driverlib/uart.h>
static uint32_t u_base = 0;

#define PRINTF printf

void retarget_uart(uint32_t base)
{
    u_base = base;
    extern void __sinit(struct _reent *);
    __sinit(_GLOBAL_REENT);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
    setvbuf(stdin, NULL, _IONBF, 0);
}

/* NEWLIB SYSCALLS */

void *_sbrk(intptr_t increment) { return (void *)-1; }

void _exit(int status)
{
    while (1)
    {
    }
}

void abort(void)
{
    PRINTF("[ABORT]\n");
    while (1)
        ;
}

void _kill(int pid, int sig) { return; }

int _getpid(void) { return -1; }

int _isatty(int fd) { return (unsigned int)fd <= STDERR_FILENO; }

_off_t _lseek_r(struct _reent *r, int fd, _off_t where, int whence) { return -EINVAL; }

int _fstat_r(struct _reent *r, int fd, struct stat *st) { return -EINVAL; }

int _close_r(struct _reent *r, int fd) { return -EINVAL; }

int _open_r(struct _reent *r, const char *path, int flags, int mode) { return -EINVAL; }

_ssize_t _read_r(struct _reent *r, int fd, void *buf, size_t len) { return -EINVAL; }

_ssize_t _write_r(struct _reent *r, int fd, const void *buf, size_t len)
{
    int err = -EINVAL;
    char *p = (char *)buf;
    if (fd > -1 && buf && len)
    {
        if (u_base && _isatty(fd))
        {
            char* c = buf;
            err = len;
            while (len--)
                UARTCharPut(u_base, *c++);
        }
    }
    errno = (err < 0) ? -err : 0;
    return err;
}

////////////////////////////////////////////////////////////////////////////////////////////

extern char *utoa(unsigned int value, char *buffer, int radix);
inline char *ltoa(long value, char *result, int base) { return utoa(value, result, base); }
inline char *ultoa(unsigned long value, char *result, int base) { return utoa(value, result, base); }