#ifndef _SYS_SYSCALLS_H
#define _SYS_SYSCALLS_H

#ifndef NULL
#define NULL 0
#endif

typedef long long long_int; /* should be 64 bits long */

extern int _lseek(int, long_int, int);
extern char *_read(int, char *, int);
extern char *_write(int, char *, int);
extern int _open(const char *, int, ...);
extern void _close(int);
extern int _isatty(int);
extern int _unlink(const char *);
extern int _link(const char *, const char *);
extern int _stat(const char *, char *);
extern int _fstat(int fd, char *buf);

#endif
