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
#include <string.h>

// https://github.com/DevSolar/pdclib/blob/master/functions/_PDCLIB/_PDCLIB_strtok.c

char __far* strtok_s(char __far* s1, size_t __far* s1max, const char __far* s2, char __far* __far* ptr)
{
    const char __far* p = s2;

    if ( s1max == NULL || s2 == NULL || ptr == NULL || ( s1 == NULL && *ptr == NULL ) || *s1max > SIZE_MAX )
    {
        return NULL;
    }

    if ( s1 != NULL )
    {
        /* new string */
        *ptr = s1;
    }
    else
    {
        /* old string continued */
        if ( *ptr == NULL )
        {
            /* No old string, no new string, nothing to do */
            return NULL;
        }

        s1 = *ptr;
    }

    /* skip leading s2 characters */
    while ( *p && *s1 )
    {
        if ( *s1 == *p )
        {
            /* found separator; skip and start over */
            if ( *s1max == 0 )
            {
                return NULL;
            }

            ++s1;
            --( *s1max );
            p = s2;
            continue;
        }

        ++p;
    }

    if ( ! *s1 )
    {
        /* no more to parse */
        *ptr = s1;
        return NULL;
    }

    /* skipping non-s2 characters */
    *ptr = s1;

    while ( **ptr )
    {
        p = s2;

        while ( *p )
        {
            if ( **ptr == *p++ )
            {
                /* found separator; overwrite with '\0', position *ptr, return */
                if ( *s1max == 0 )
                {
                    return NULL;
                }

                --( *s1max );
                *( ( *ptr )++ ) = '\0';
                return s1;
            }
        }

        if ( *s1max == 0 )
        {
            return NULL;
        }

        --( *s1max );
        ++( *ptr );
    }

    /* parsed to end of string */
    return s1;
}

char __far* strtok(char __far* s1, const char __far* s2)
{
    static char __far* tmp = NULL;
    static size_t max;

    if ( s1 != NULL )
    {
        /* new string */
        tmp = s1;
        max = strlen( tmp );
    }

    return strtok_s( s1, &max, s2, &tmp );
}
