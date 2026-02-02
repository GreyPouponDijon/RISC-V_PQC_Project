#include <stdio.h>
#include <stdint.h>

#include "nrf.h"

#if FEATURE_UARTE_ENABLED
#include "uarte.h"
#endif

#if defined(__GNUC__) && !defined(__SES_ARM)

#if defined(__PICOLIBC__)
FILE *const stdout = 0;
#endif

/*void *__dso_handle = 0;*/
/*#define QUICKPRINT*/
#if FEATURE_UARTE_ENABLED
int _write(int file, const char * p_char, int len)
{
    (void)file;
    volatile unsigned int* uarte_txd_p = (unsigned int*) (CONFIG_HW_UARTE_INSTANCE + 0x51c);
    volatile unsigned int* uarte_task_tx_p = (unsigned int*) (CONFIG_HW_UARTE_INSTANCE + 0xb90);
#ifdef QUICKPRINT
    *uarte_task_tx_p = 1;
#endif    
    for (int i = 0; i < len; i++) {
      #ifdef QUICKPRINT
      *uarte_txd_p = (uint32_t)*p_char++;
      #else
      (void)hal_uarte_char_write((uint8_t)*p_char++);
      #endif


    }

    return len;
}

int _read(int file, char * p_char, int len) {
    (void)file;
    (void)len;
    hal_uarte_char_read((uint8_t *)p_char);
    return 1;
}
#elif FEATURE_SEMIHOSTING_ENABLED
int _write(int file, const char * p_char, int len)
{
  volatile unsigned char *trace_p = (unsigned char*) 0x4F9A5000;
    (void)file;
    (void)p_char;
    (void)len;
    /* for (int i = 0; i < len; i++) { */
    /*     (void)hal_uarte_char_write((uint8_t)*p_char++); */
    /* } */
    //#define TRACE (volatile (*(unsigned char *)0x4F9A5000))
    for (int i = 0; i < 10; i++) {
      //(void)hal_uarte_char_write((uint8_t)*p_char++);
      //TRACE = (uint8_t)*p_char++;
        *trace_p = (uint8_t)*p_char++;
        
    }

    //TRACE = p_char;
    
    __asm("MOVS r0, 0x04");
    __asm("BKPT 0xab");

    return len;
}

int _read(int file, char * p_char, int len) {
    (void)file;
    (void)p_char;
    (void)len;
    return 0;
   
}

#elif FEATURE_SIM_PRINT_ENABLED
//extern int _sim_printk(int);
int _write(int file, const char * p_char, int len)
{
    (void)file;
    (void)p_char;
    asm volatile("srai x0, x0, 5");
    return len;
}

int _read(int file, char * p_char, int len) {
    (void)file;
    (void)p_char;
    (void)len;
    return 1;
}
#elif (defined(__GNUC__) && (__GNUC__ == 9 && __GNUC_MINOR__ == 3)) || defined(__riscv)

int _write(int file, const char * p_char, int len) {
    (void)file;
    (void)p_char;
    (void)len;
    return len;
}

int _read(int file, char * p_char, int len) {
    (void)file;
    (void)p_char;
    (void)len;
    return 0;
}
#endif

int _open_r(struct _reent *ptr,
		    const char *file, int flags, int mode) {
    (void)ptr;
    (void)file;
    (void)flags;
    (void)mode;
    return 0;
}

#include <errno.h>
#include <sys/stat.h>
#include <sys/times.h>
//#include <sys/unistd.h>

//#undef errno
//extern int errno;

/*
 environ
 A pointer to a list of environment variables and their values.
 For a minimal environment, this empty list is adequate:
 */
char *__env[1] = { 0 };
char **environ = __env;

#ifdef FEATURE_SEMIHOSTING_ENABLED
void _exit(int status) {
    (void)status;   // Remove unused parameter warning
  __ASM("MOVS r0, 0x1a");
  __ASM("BKPT 0xab");
}
#else
#ifndef SIM
void _exit(int status) {
    (void)status;   // Remove unused parameter warning
//    _write(1, "exit", 4);
    while (1) {
        ;
    }
}
#endif
#endif
int _close(int file) {
    (void)file;   // Remove unused parameter warning
    return -1;
}
/*
 execve
 Transfer control to a new process. Minimal implementation (for a system without processes):
 */
int _execve(char *name, char **argv, char **env) {
    (void)name;   // Remove unused parameter warning
    (void)argv;   // Remove unused parameter warning
    (void)env;   // Remove unused parameter warning
    errno = ENOMEM;
    return -1;
}
/*
 fork
 Create a new process. Minimal implementation (for a system without processes):
 */

int _fork(void) {
    errno = EAGAIN;
    return -1;
}
/*
 fstat
 Status of an open file. For consistency with other minimal implementations in these examples,
 all files are regarded as character special devices.
 The `sys/stat.h' header file required is distributed in the `include' subdirectory for this C library.
 */
int _fstat(int file, struct stat *st) {
    (void)file;   // Remove unused parameter warning
    st->st_mode = S_IFCHR;
    return 0;
}

/*
 getpid
 Process-ID; this is sometimes used to generate strings unlikely to conflict with other processes. Minimal implementation, for a system without processes:
 */

int _getpid(void) {
    return 1;
}

/*
 isatty
 Query whether output stream is a terminal. For consistency with the other minimal implementations,
 */
int _isatty(int file) {
    switch (file){
      //case STDOUT_FILENO:
      //case STDERR_FILENO:
      //case STDIN_FILENO:
      //return 1;
    default:
        //errno = ENOTTY;
        errno = EBADF;
        //return 0;
    }
}


/*
 kill
 Send a signal. Minimal implementation:
 */
int _kill(int pid, int sig) {
    (void)pid;   // Remove unused parameter warning
    (void)sig;   // Remove unused parameter warning
    errno = EINVAL;
    return (-1);
}

/*
 link
 Establish a new name for an existing file. Minimal implementation:
 */

int _link(char *old, char *new) {
    (void)old;   // Remove unused parameter warning
    (void)new;   // Remove unused parameter warning
    errno = EMLINK;
    return -1;
}

/*
 lseek
 Set position in a file. Minimal implementation:
 */
int _lseek(int file, int ptr, int dir) {
    (void)file;   // Remove unused parameter warning
    (void)ptr;   // Remove unused parameter warning
    (void)dir;   // Remove unused parameter warning
    return 0;
}

/*
 sbrk
 Increase program data space.
 Malloc and related functions depend on this
 */

#if defined(__riscv)
static inline uint32_t __get_MSP(void)
{
  uint32_t result;

  __ASM volatile ("mv %0, sp" : "=r" (result) );
  return(result);
}
#endif


caddr_t _sbrk(int incr) {

    extern char __HeapBase; // Defined by the linker
    static char *heap_end;
    char *prev_heap_end;

    if (heap_end == 0) {
        heap_end = &__HeapBase;
    }
    prev_heap_end = heap_end;

     char * stack = (char*) __get_MSP();
     if (heap_end + incr >  stack)
     {
//         _write (STDERR_FILENO, "Heap and stack collision\n", 25);
         errno = ENOMEM;
         return  (caddr_t) -1;
         //abort ();
     }

    heap_end += incr;
    return (caddr_t) prev_heap_end;

}

/*
caddr_t _sbrk(int32_t incr)
{
    extern char   __HeapBase; // Set by linker.
    static char * heap_end;
    char *        prev_heap_end;
    if (heap_end == 0) {
        heap_end = &__HeapBase;
    }

    prev_heap_end = heap_end;
    heap_end += incr;

    printf("_sbrk: Growing memory pool by %ld bytes. New span is 0x%lX-0x%lX (%ld bytes)\n",
        incr,
        (uint32_t)(&__HeapBase),
        (uint32_t)(heap_end),
        (uint32_t)(heap_end) - (uint32_t)(&__HeapBase));

    return (caddr_t) prev_heap_end;
}
*/
/*
 stat
 Status of a file (by name). Minimal implementation:
 int    _EXFUN(stat,( const char *__path, struct stat *__sbuf ));
 */

int _stat(const char *filepath, struct stat *st) {
    (void)filepath;   // Remove unused parameter warning
    st->st_mode = S_IFCHR;
    return 0;
}

/*
 times
 Timing information for current process. Minimal implementation:
 */

clock_t _times(struct tms *buf) {
    (void)buf;   // Remove unused parameter warning
    return -1;
}

/*
 unlink
 Remove a file's directory entry. Minimal implementation:
 */
int _unlink(char *name) {
    (void)name;   // Remove unused parameter warning
    errno = ENOENT;
    return -1;
}

/*
 wait
 Wait for a child process. Minimal implementation:
 */
int _wait(int *status) {
    (void)status;   // Remove unused parameter warning
    errno = ECHILD;
    return -1;
}

#endif
