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

// https://github.com/DevSolar/pdclib/blob/master/functions/stdlib/qsort.c

/* This implementation is taken from Paul Edward's PDPCLIB.

   Original code is credited to Raymond Gardner, Englewood CO.
   Minor mods are credited to Paul Edwards.
   Some reformatting and simplification done by Martin Baute.
   All code is still Public Domain.
*/

// TODO: Could probably be optimized by writing it in ASM.
static inline void memswp(char __far* i, char __far* j, size_t size) {
    char c;
    while (size--) {
        c = *i;
        *(i++) = *j;
        *(j++) = c;
    }
}

/* For small sets, insertion sort is faster than quicksort.
   T is the threshold below which insertion sort will be used.
   Must be 3 or larger.
*/
#define T 7

/* Macros for handling the QSort stack */
#ifdef __IA16_CALLCVT_NO_ASSUME_SS_DATA
#define PREPARE_STACK char __far* stack[STACKSIZE]; char __far* __seg_ss* stackptr = stack
#else
#define PREPARE_STACK char __far* stack[STACKSIZE]; char __far* * stackptr = stack
#endif
#define PUSH( base, limit ) stackptr[0] = base; stackptr[1] = limit; stackptr += 2
#define POP( base, limit ) stackptr -= 2; base = stackptr[0]; limit = stackptr[1]
/* TODO: Stack usage is log2( nmemb ) (minus what T shaves off the worst case).
         Worst-case nmemb is platform dependent.
*/
#define STACKSIZE 16

void qsort(void __far* base, size_t nmemb, size_t size, int (*compar)(const void __far*, const void __far*)) {
    char __far* i;
    char __far* j;
    size_t thresh = T * size;
    char __far* base_          = ( char __far* )base;
    char __far* limit          = base_ + nmemb * size;
    PREPARE_STACK;

    for ( ;; )
    {
        if ( ( size_t )( limit - base_ ) > thresh ) /* QSort for more than T elements. */
        {
            /* We work from second to last - first will be pivot element. */
            i = base_ + size;
            j = limit - size;
            /* We swap first with middle element, then sort that with second
               and last element so that eventually first element is the median
               of the three - avoiding pathological pivots.
               TODO: Instead of middle element, chose one randomly.
            */
            memswp( ( ( ( ( size_t )( limit - base_ ) ) / size ) / 2 ) * size + base_, base_, size );

            if ( compar( i, j ) > 0 )
            {
                memswp( i, j, size );
            }

            if ( compar( base_, j ) > 0 )
            {
                memswp( base_, j, size );
            }

            if ( compar( i, base_ ) > 0 )
            {
                memswp( i, base_, size );
            }

            /* Now we have the median for pivot element, entering main Quicksort. */
            for ( ;; )
            {
                do
                {
                    /* move i right until *i >= pivot */
                    i += size;
                } while ( compar( i, base_ ) < 0 );

                do
                {
                    /* move j left until *j <= pivot */
                    j -= size;
                } while ( compar( j, base_ ) > 0 );

                if ( i > j )
                {
                    /* break loop if pointers crossed */
                    break;
                }

                /* else swap elements, keep scanning */
                memswp( i, j, size );
            }

            /* move pivot into correct place */
            memswp( base_, j, size );

            /* larger subfile base / limit to stack, sort smaller */
            if ( j - base_ > limit - i )
            {
                /* left is larger */
                PUSH( base_, j );
                base_ = i;
            }
            else
            {
                /* right is larger */
                PUSH( i, limit );
                limit = j;
            }
        }
        else /* insertion sort for less than T elements              */
        {
            for ( j = base_, i = j + size; i < limit; j = i, i += size )
            {
                for ( ; compar( j, j + size ) > 0; j -= size )
                {
                    memswp( j, j + size, size );

                    if ( j == base_ )
                    {
                        break;
                    }
                }
            }

            if ( stackptr != stack )           /* if any entries on stack  */
            {
                POP( base_, limit );
            }
            else                       /* else stack empty, done   */
            {
                break;
            }
        }
    }
}
