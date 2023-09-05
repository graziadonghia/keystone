// #ifdef USE_LINUX_SYSCALL
#ifndef _LINUX_WRAP_H_
#define _LINUX_WRAP_H_

#include <bits/types/sigset_t.h>
#include <stddef.h>
#include <stdint.h>

/* Identifier for system-wide realtime clock.  */
# define CLOCK_REALTIME			0
/* Monotonic system-wide clock.  */
# define CLOCK_MONOTONIC		1
/* High-resolution timer from the CPU.  */
# define CLOCK_PROCESS_CPUTIME_ID	2
/* Thread-specific CPU-time clock.  */
# define CLOCK_THREAD_CPUTIME_ID	3
/* Monotonic system-wide clock, not adjusted for frequency scaling.  */
# define CLOCK_MONOTONIC_RAW		4
/* Identifier for system-wide realtime clock, updated only on ticks.  */
# define CLOCK_REALTIME_COARSE		5
/* Monotonic system-wide clock, updated only on ticks.  */
# define CLOCK_MONOTONIC_COARSE		6
/* Monotonic system-wide clock that includes time spent in suspension.  */
# define CLOCK_BOOTTIME			7
/* Like CLOCK_REALTIME but also wakes suspended system.  */
# define CLOCK_REALTIME_ALARM		8
/* Like CLOCK_BOOTTIME but also wakes suspended system.  */
# define CLOCK_BOOTTIME_ALARM		9
/* Like CLOCK_REALTIME but in International Atomic Time.  */
# define CLOCK_TAI			11

struct timespec;

uintptr_t linux_uname(void* buf);
uintptr_t linux_clock_gettime(__clockid_t clock, struct timespec *tp);
uintptr_t linux_rt_sigprocmask(int how, const sigset_t *set, sigset_t *oldset);
uintptr_t linux_getrandom(void *buf, size_t buflen, unsigned int flags);
uintptr_t linux_getpid();
uintptr_t linux_set_tid_address(int* tidptr);
uintptr_t linux_RET_ZERO_wrap(unsigned long which);
uintptr_t linux_RET_BAD_wrap(unsigned long which);
uintptr_t syscall_munmap(void *addr, size_t length);
uintptr_t syscall_mmap(void *addr, size_t length, int prot, int flags,
                  int fd, __off_t offset);
uintptr_t syscall_brk(void* addr);
#endif /* _LINUX_WRAP_H_ */
// #endif /* USE_LINUX_SYSCALL */
