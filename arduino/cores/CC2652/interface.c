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
#include <driverlib/uart.h>
#include <driverlib/prcm.h>

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

void powerOn(uint32_t domain, uint32_t periph, bool sleep, bool deep_sleep)
{
    if (domain)
    {
        PRCMPowerDomainOn(domain);
        while (PRCMPowerDomainsAllOn(domain) != PRCM_DOMAIN_POWER_ON)
            ;
    }
    if (periph)
    {
        PRCMPeripheralRunEnable(periph);
        if (sleep)
            PRCMPeripheralSleepEnable(periph);
        if (deep_sleep)
            PRCMPeripheralDeepSleepEnable(periph);
        PRCMLoadSet();
        while (!PRCMLoadGet())
            ;
    }
}

void powerOff(uint32_t domain, uint32_t periph)
{
    if (periph)
    {
        PRCMPeripheralRunDisable(periph);
        PRCMPeripheralSleepDisable(periph);
        PRCMPeripheralDeepSleepDisable(periph);
        PRCMLoadSet();
        while (!PRCMLoadGet())
            ;
    }

    if (domain)
    {
        PRCMPowerDomainOff(domain);
        while (PRCMPowerDomainsAllOff(domain) != PRCM_DOMAIN_POWER_ON)
            ;
    }
}

//////////////////////////////////////////////////////////////////////////
#include <driverlib/trng.h>
int rand(void) // need powerOff()
{
    bool once = true;
    if (once)
    {
        powerOn(PRCM_DOMAIN_PERIPH, PRCM_PERIPH_TRNG, false, false);
        TRNGConfigure(1 << 6, 1 << 8, 1); // min samp num: 2^6, max samp num: 2^8, cycles per sample 16
        TRNGEnable();
    }
    return TRNGNumberGet(TRNG_LOW_WORD);
}

void srand(unsigned __seed) {}