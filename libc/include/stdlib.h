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

#ifndef _STDLIB_H_
#define _STDLIB_H_

#include <wonderful.h>
#include <stddef.h>

int abs(int j) __attribute__((const));
long int labs(long int j) __attribute__((const));
long long int llabs(long long int j) __attribute__((const));

int atoi(const char __far* s) __attribute__((pure));
long atol(const char __far* s) __attribute__((pure));

typedef struct {
	int quot;
	int rem;
} div_t;
div_t div(int numer, int denom) __attribute__((const));

typedef struct {
	long int quot;
	long int rem;
} ldiv_t;
ldiv_t ldiv(long int numer, long int denom) __attribute__((const));

typedef struct {
	long long int quot;
	long long int rem;
} lldiv_t;
lldiv_t lldiv(long long int numer, long long int denom) __attribute__((const));

#define RAND_MAX 32767
int rand(void);
void srand(unsigned int seed);

void __far* bsearch(const void __far* key, const void __far* base, size_t nmemb, size_t size, int (*compar)(const void __far*, const void __far*));
void qsort(void __far* base, size_t nmemb, size_t size, int (*compar)(const void __far*, const void __far*));

void *malloc(size_t size) __attribute__((malloc));
void free(void *ptr);
void free_sized(void *ptr, size_t size);
void *realloc(void *ptr, size_t size);
void* calloc(size_t nelem, size_t elsize) __attribute__((malloc));

__attribute__((noreturn))
void abort(void);

__attribute__((noreturn))
void exit(int code);

#endif /* _STDLIB_H_ */
