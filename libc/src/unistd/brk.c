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

#include <stdint.h>
#include <wonderful.h>
#include "errno.h"
#include "unistd.h"

#ifdef __WONDERFUL_WWITCH__
// This points to the heap start pointer in the process's PCB.
#define brk_addr (*((void**) 0x005E))

int brk(void *addr) {
    if (((uint16_t) addr) < 0x0060) {
        errno = ENOMEM;
        return -1;
    }
    brk_addr = addr;
    return 0;
}
#else
extern uint8_t __wf_heap_start;
extern uint8_t __wf_heap_top;
static void *brk_addr = &__wf_heap_start;

int brk(void *addr) {
    if (addr < (void*)&__wf_heap_start || addr >= (void*)&__wf_heap_top) {
        errno = ENOMEM;
        return -1;
    }
    brk_addr = addr;
    return 0;
}
#endif

void *sbrk(intptr_t incr) {
    if (!incr)
        return brk_addr;

    void *old_addr = brk_addr;
    return brk((void*) brk_addr + incr) ? (void*)-1 : old_addr;
}
