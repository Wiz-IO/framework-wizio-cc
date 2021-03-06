////////////////////////////////////////////////////////////////////////////////////////
//
//      2021 Georgi Angelov
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
////////////////////////////////////////////////////////////////////////////////////////

#include "interface.h"

/* NEWLIB SYSCALLS */

void *_sbrk(intptr_t increment)
{
    return (void *)-1;
}

void _exit(int status)
{
    while (1)
    {
    }
}

// abort()
void _kill(int pid, int sig) { return; }

int _getpid(void) { return -1; }

int _isatty(int fd)
{
    return (unsigned int)fd <= STDERR_FILENO;
}

_off_t _lseek_r(struct _reent *r, int fd, _off_t where, int whence)
{
    int err = -EINVAL;
    errno = (err < 0) ? -err : 0;
    return err;
}

int _fstat_r(struct _reent *r, int fd, struct stat *st)
{
    int err = -EINVAL;
    errno = (err < 0) ? -err : 0;
    return err;
}

int _close_r(struct _reent *r, int fd)
{
    int err = -EINVAL;
    if (fd > STDERR_FILENO)
    {
    }
    errno = (err < 0) ? -err : 0;
    return err;
}

int _open_r(struct _reent *r, const char *path, int flags, int mode)
{
    int err = -EINVAL;
    errno = (err < 0) ? -err : 0;
    return err;
}

_ssize_t _write_r(struct _reent *r, int fd, const void *buf, size_t len)
{
    int err = -EINVAL;
    if (fd > -1 && buf && len)
    {
        if (_isatty(fd))
        {
            if (stdout->_cookie && stdout->_write)
                return stdout->_write(r, stdout->_cookie, buf, len); // arduino
        }
    }
    errno = (err < 0) ? -err : 0;
    return err;
}

_ssize_t _read_r(struct _reent *r, int fd, void *buf, size_t len)
{
    int err = -EINVAL;
#if 0 // not support yet
    if (fd > -1 && buf && len)
    {
        if (fd == STDIN_FILENO)
        {
            if (stdin->_cookie && stdin->_read)
                return stdin->_read(r, stdin->_cookie, buf, len); // arduino
        }
    }
#endif
    errno = (err < 0) ? -err : 0;
    return err;
}

///////////////////////////////////////////////////////////////////////////////////////////

static int null_write_r(struct _reent *r, void *p, const char *b, int s) { return -1; }
static int null_read_r(struct _reent *r, void *p, char *b, int s) { return -1; }
drv_t stdio_null_drv = {
    .ctx = NULL,
    .write_r = null_write_r,
    .read_r = null_read_r,
};

void stdio_retarget(drv_t *p)
{
    if (p == NULL)
        p = &stdio_null_drv;

    stdout->_cookie = p;
    stdout->_write = p->write_r;
    stdout->_read = p->read_r;
    setvbuf(stdout, NULL, _IONBF, 0);

    stderr->_cookie = p;
    stderr->_write = p->write_r;
    stderr->_read = p->read_r;
    setvbuf(stderr, NULL, _IONBF, 0);

    stdin->_cookie = p;
    stdin->_write = p->write_r;
    stdin->_read = p->read_r;
    setvbuf(stdin, NULL, _IONBF, 0);
}

///////////////////////////////////////////////////////////////////////////////////////////

int rand(void)
{
    int res = millis();
#if 1
    {
        if (0 == HWREGBITW(TRNG_BASE + TRNG_O_CTL, TRNG_CTL_TRNG_EN_BITN))
        {
            TRNGConfigure(1 << 6, 1 << 8, 1); // min samp num: 2^6, max samp num: 2^8, cycles per sample 16
            TRNGEnable();
        }
        res += TRNGNumberGet(TRNG_LOW_WORD);
    }
#endif
    return res;
}

void srand(unsigned __seed) {}

///////////////////////////////////////////////////////////////////////////////////////////

uint8_t disableFlashCache(void)
{
    uint8_t mode = VIMSModeGet(VIMS_BASE);
    VIMSLineBufDisable(VIMS_BASE);
    if (mode != VIMS_MODE_DISABLED)
    {
        VIMSModeSet(VIMS_BASE, VIMS_MODE_DISABLED);
        while (VIMSModeGet(VIMS_BASE) != VIMS_MODE_DISABLED)
            ;
    }

    return (mode);
}

void restoreFlashCache(uint8_t mode)
{
    if (mode != VIMS_MODE_DISABLED)
    {
        VIMSModeSet(VIMS_BASE, VIMS_MODE_ENABLED);
    }
    VIMSLineBufEnable(VIMS_BASE);
}