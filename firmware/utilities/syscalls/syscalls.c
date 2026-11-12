/**
  ******************************************************************************
  * @file      syscalls.c
  * @brief     Minimal System calls file
  *
  *            For more information about which c-functions
  *            need which of these lowlevel functions
  *            please consult the Newlib libc-manual
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes */
#include <sys/stat.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>
#include <sys/times.h>

/* functions prototype */
void initialise_monitor_handles(void);
int _getpid(void);
int _kill(int pid, int sig);
void _exit(int status);
__attribute__((weak)) int _read(int file, char *ptr, int len);
__attribute__((weak)) int _write(int file, char *ptr, int len);
int _close(int file);
int _fstat(int file, struct stat *st);
int _isatty(int file);
int _lseek(int file, int ptr, int dir);
int _open(char *path, int flags, ...);
int _wait(int *status);
int _unlink(char *name);
int _times(struct tms *buf);
int _stat(char *file, struct stat *st);
int _link(char *old, char *new);
int _fork(void);
int _execve(char *name, char **argv, char **env);

/* External function */
extern int __io_putchar(int ch) __attribute__((weak));
extern int __io_getchar(void) __attribute__((weak));

/* Local Variables */
char *__env[1] = { 0 };
char **environ = __env;

/**
  * @defgroup SYS_CALLS Syscalls Interface (newlib/newlib-nano)
  * @brief Minimal POSIX-like stubs required by GCC newlib on bare-metal.
  * @{
  */

/**
  * @brief Initialize semihosting monitor handles (optional).
  * @details Empty by default; used when semihosting is enabled.
  */
void initialise_monitor_handles(void)
{
}

/**
  * @brief Return the current (fake) process ID for bare-metal runtime.
  * @return Always returns 1.
  * @note newlib is allowed to query _getpid() for signals/stdio bookkeeping.
  */
int _getpid(void)
{
  return 1;
}

/**
  * @brief Send a signal to a process (stub).
  * @param pid Target process id.
  * @param sig Signal number.
  * @return Always -1 on bare-metal; sets errno=EINVAL.
  * @note Required by newlib to complete _exit() and signal stubs.
  */
int _kill(int pid, int sig)
{
  (void)pid;
  (void)sig;
  errno = EINVAL;
  return -1;
}

/**
  * @brief Terminate the program (no OS to return to).
  * @param status Exit status code.
  * @details Calls _kill(status,-1) then loops forever.
  * @note GCC/newlib calls this from exit(). A reset can be triggered here if desired.
  */
void _exit(int status)
{
  _kill(status, -1);
  while (1) {}    /* Make sure we hang here */
}

/**
  * @brief Read from a file descriptor into a buffer.
  * @param file File descriptor (0=stdin expected).
  * @param ptr  Destination buffer.
  * @param len  Number of bytes requested.
  * @return Number of bytes read (len in this stub).
  * @note newlib uses _read() for scanf/getchar; wired to __io_getchar().
  */
__attribute__((weak)) int _read(int file, char *ptr, int len)
{
  (void)file;
  int DataIdx;

  for (DataIdx = 0; DataIdx < len; DataIdx++)
  {
    *ptr++ = __io_getchar();
  }

  return len;
}

/**
  * @brief Write buffer to a file descriptor.
  * @param file File descriptor (1=stdout, 2=stderr).
  * @param ptr  Source buffer.
  * @param len  Number of bytes to write.
  * @return Number of bytes written (len in this stub).
  * @note newlib uses _write() for printf/fputs; wired to __io_putchar().
  */
__attribute__((weak)) int _write(int file, char *ptr, int len)
{
  (void)file;
  int DataIdx;

  for (DataIdx = 0; DataIdx < len; DataIdx++)
  {
    __io_putchar(*ptr++);
  }
  return len;
}

/**
  * @brief Close a file descriptor (stub).
  * @param file File descriptor.
  * @return Always -1.
  */
int _close(int file)
{
  (void)file;
  return -1;
}

/**
  * @brief Get file status.
  * @param file File descriptor.
  * @param st   Status structure.
  * @return 0 on success; sets st_mode=S_IFCHR to indicate a char device.
  * @note newlib expects S_IFCHR for stdio streams.
  */
int _fstat(int file, struct stat *st)
{
  (void)file;
  st->st_mode = S_IFCHR;
  return 0;
}

/**
  * @brief Test if file descriptor is a TTY.
  * @param file File descriptor.
  * @return 1 (true) for stdio char devices.
  */
int _isatty(int file)
{
  (void)file;
  return 1;
}

/**
  * @brief Reposition file offset (stub).
  * @param file File descriptor.
  * @param ptr  Offset.
  * @param dir  Whence (SEEK_SET, etc.).
  * @return 0 in this stub.
  */
int _lseek(int file, int ptr, int dir)
{
  (void)file;
  (void)ptr;
  (void)dir;
  return 0;
}

/**
  * @brief Open a file (stub).
  * @param path Path string.
  * @param flags Open flags.
  * @return Always -1.
  */
int _open(char *path, int flags, ...)
{
  (void)path;
  (void)flags;
  /* Pretend like we always fail */
  return -1;
}

/**
  * @brief Wait for child process (stub).
  * @param status Status pointer.
  * @return -1; sets errno=ECHILD.
  */
int _wait(int *status)
{
  (void)status;
  errno = ECHILD;
  return -1;
}

/**
  * @brief Unlink a file (stub).
  * @param name Path name.
  * @return -1; sets errno=ENOENT.
  */
int _unlink(char *name)
{
  (void)name;
  errno = ENOENT;
  return -1;
}

/**
  * @brief Get process times (stub).
  * @param buf Pointer to tms structure.
  * @return Always -1.
  */
int _times(struct tms *buf)
{
  (void)buf;
  return -1;
}

/**
  * @brief Get file status.
  * @param file File descriptor.
  * @param st   Status structure.
  * @return 0 on success; sets st_mode=S_IFCHR to indicate a char device.
  * @note newlib expects S_IFCHR for stdio streams.
  */
int _stat(char *file, struct stat *st)
{
  (void)file;
  st->st_mode = S_IFCHR;
  return 0;
}

/**
  * @brief Create a link to a file (stub).
  * @param old Old path name.
  * @param new New path name.
  * @return -1; sets errno=EMLINK.
  */
int _link(char *old, char *new)
{
  (void)old;
  (void)new;
  errno = EMLINK;
  return -1;
}

/**
  * @brief Create a new process (stub).
  * @return -1; sets errno=EAGAIN.
  */
int _fork(void)
{
  errno = EAGAIN;
  return -1;
}

/**
  * @brief Execute a program (stub).
  * @param name Program name.
  * @param argv Argument vector.
  * @param env  Environment vector.
  * @return -1; sets errno=ENOMEM.
  */
int _execve(char *name, char **argv, char **env)
{
  (void)name;
  (void)argv;
  (void)env;
  errno = ENOMEM;
  return -1;
}

/**
  * @}
  */
