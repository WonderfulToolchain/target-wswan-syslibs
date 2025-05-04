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

#include <stddef.h>
#include "stdlib.h"

// https://github.com/DevSolar/pdclib/blob/master/functions/stdlib/bsearch.c

void __far* bsearch(const void __far* key, const void __far* base, size_t nmemb, size_t size, int (*compar)(const void __far*, const void __far*)) {
    const void __far* pivot;
    int rc;
    size_t corr;

    while ( nmemb )
    {
        /* algorithm needs -1 correction if remaining elements are an even number. */
        corr = nmemb % 2;
        nmemb /= 2;
        pivot = ( const char __far* )base + ( nmemb * size );
        rc = compar( key, pivot );

        if ( rc > 0 )
        {
            base = ( const char __far* )pivot + size;
            /* applying correction */
            nmemb -= ( 1 - corr );
        }
        else if ( rc == 0 )
        {
            return ( void __far* )pivot;
        }
    }

    return NULL;
}
