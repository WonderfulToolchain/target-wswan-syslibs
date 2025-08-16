/**
 * wonderful ia16 libc
 *
 * To the extent possible under law, the person who associated CC0 with
 * wonderful ia16 libc has waived all copyright and related or neighboring rights
 * to wonderful ia16 libc.
 *
 * You should have received a copy of the CC0 legalcode along with this
 * work.  If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
 */

#ifndef _STDIO_H_
#define _STDIO_H_

#include <wonderful.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

#define EOF -1
#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

struct wf_file_t;
struct wf_fileops_t {
    int (*get)(struct wf_file_t*);
    int (*put)(uint8_t, struct wf_file_t*);
    int (*close)(struct wf_file_t*);
};

typedef struct wf_file_t {
    union {
        uint32_t h;
        void __far *p;
    } handle;
    const struct wf_fileops_t __far *ops;
} FILE;

extern FILE* stdin;
extern FILE* stdout;
extern FILE* stderr;

int fgetc(FILE *stream);
int fputc(int c, FILE *stream);
int getc(FILE *stream);
int getchar(void);
int putc(int c, FILE *stream);
int putchar(int c);
int puts(const char __far* s);

int printf(const char __far* format, ...);
int sprintf(char __far* s, const char __far* format, ...);
int snprintf(char __far* s, size_t n, const char __far* format, ...);
int vprintf(const char __far* format, va_list arg);
int vsprintf(char __far* s, const char __far* format, va_list arg);
int vsnprintf(char __far* s, size_t n, const char __far* format, va_list arg);

#endif /* _STDIO_H_ */
