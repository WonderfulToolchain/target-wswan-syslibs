/**
 * wonderful-i8086 libc
 *
 * To the extent possible under law, the person who associated CC0 with
 * wonderful-i8086 libc has waived all copyright and related or neighboring rights
 * to wonderful-i8086 libc.
 *
 * You should have received a copy of the CC0 legalcode along with this
 * work.  If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
 */

#ifndef _STDLIB_H_
#define _STDLIB_H_

#include <wonderful.h>
#include <stddef.h>

int abs(int j);
long int labs(long int j);
long long int llabs(long long int j);

int atoi(const char __far* s);
long atol(const char __far* s);

typedef struct {
	int quot;
	int rem;
} div_t;
div_t div(int numer, int denom);

typedef struct {
	long int quot;
	long int rem;
} ldiv_t;
ldiv_t ldiv(long int numer, long int denom);

typedef struct {
	long long int quot;
	long long int rem;
} lldiv_t;
lldiv_t lldiv(long long int numer, long long int denom);

#define RAND_MAX 32767
int rand(void);
void srand(unsigned int seed);

void __far* bsearch(const void __far* key, const void __far* base, size_t nmemb, size_t size, int (*compar)(const void __far*, const void __far*));
void qsort(void __far* base, size_t nmemb, size_t size, int (*compar)(const void __far*, const void __far*));

void *malloc(size_t size);
void free(void *ptr);
void free_sized(void *ptr, size_t size);
void *realloc(void *ptr, size_t size);
void* calloc(size_t nelem, size_t elsize);

#endif /* _STDLIB_H_ */
