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

#include <stddef.h>
#include <stdint.h>
#include "errno.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"

// Simple best fit-based allocator implementation.
#define MALLOC_BEST_FIT

typedef struct {
	uint16_t size;
} alloc_header_t;

#define SIZE_MASK 0x7FFF
#define BLOCK_ALLOCATED 0x8000
#define INVALID ((void*)-1)

static void* alloc_start = INVALID;

#define BLOCK_AFTER(block, len) ((alloc_header_t*) (((uint8_t*) (block)) + sizeof(alloc_header_t) + (len)))
#define NEXT_BLOCK(block) BLOCK_AFTER(block, ((block)->size & SIZE_MASK))

void *malloc(size_t size) {
	if (size <= 0)
		return NULL;

	// word align all allocations
	size = (size + 1) & ~1;

	void *alloc_end = sbrk(0);

	alloc_header_t *block = alloc_start;
	alloc_header_t *best_block = INVALID;
	uint16_t best_block_size = 65535;
	if (block != INVALID) {
		while (1) {
			alloc_header_t *next_block = NEXT_BLOCK(block);

			if (!(block->size & BLOCK_ALLOCATED)) {
				// check if there's a following free block
				if ((void*)next_block < alloc_end) {
					if (!(next_block->size & BLOCK_ALLOCATED)) {
						// if neither block is allocated, merge
						block->size = block->size + next_block->size + sizeof(alloc_header_t);
						continue;
					}
				}

				// block not allocated, consider as allocation candidate
	#ifdef MALLOC_BEST_FIT
				if (block->size == size) {
					// perfect fit
					best_block = block;
					break;
				} else if (block->size > size && block->size < best_block_size) {
					// better fit
					best_block = block;
					best_block_size = block->size;
				}
	#else
				if (block->size >= size) {
					best_block = block;
					break;
				}
	#endif
			}

			// advance to next block
			if ((void*)next_block >= alloc_end || next_block == INVALID)
				break;
			block = next_block;
		}
	}

	// failed to find candidate?
	if (best_block == INVALID) {
		// allocate room for new block

		// is last block not allocated?
		if ((void*)block < alloc_end && !(block->size & BLOCK_ALLOCATED)) {
			// expand last block
			if (sbrk(size - block->size) == INVALID) {
				errno = ENOMEM;
				return NULL;
			}
		} else {
			block = sbrk(sizeof(alloc_header_t) + size);
			if (block == INVALID) {
				errno = ENOMEM;
				return NULL;
			}
			if (alloc_start == INVALID) {
				alloc_start = block;
			}
		}

		// initialize new block
		block->size = BLOCK_ALLOCATED | size;
	} else {
		block = best_block;
		// big enough to allocate next empty block?
		if (block->size > (size + sizeof(alloc_header_t))) {
			alloc_header_t *following_block = BLOCK_AFTER(block, size);
			following_block->size = block->size - size - sizeof(alloc_header_t);
			block->size = size | BLOCK_ALLOCATED;
		} else {
			// if not, re-use entire block as is
			block->size |= BLOCK_ALLOCATED;
		}
	}

	return ((void*) block) + sizeof(alloc_header_t);
}

void free(void *ptr) {
	alloc_header_t *block = (alloc_header_t*) (ptr - 2);
	block->size &= ~BLOCK_ALLOCATED;
}

void free_sized(void *ptr, size_t size) {
	free(ptr);
}

void *realloc(void *ptr, size_t size) {
	alloc_header_t *block = (alloc_header_t*) (ptr - 2);

	// word align all allocations
	size = (size + 1) & ~1;

	// can we fit data in the existing block?
	uint16_t block_size = block->size & SIZE_MASK;

	// check for any following free blocks
	void *alloc_end = sbrk(0);
	while (1) {
		alloc_header_t *next_block = BLOCK_AFTER(block, block_size);

		if ((void*)next_block < alloc_end) {
			if (!(next_block->size & BLOCK_ALLOCATED)) {
				block_size += next_block->size + sizeof(alloc_header_t);
				continue;
			}
		}

		break;
	}

	if (size <= block_size) {
		if (size <= (block_size - sizeof(alloc_header_t))) {
			// split block
			alloc_header_t *following_block = BLOCK_AFTER(block, size);
			following_block->size = block_size - size - sizeof(alloc_header_t);
			block_size = size;
		}
		block->size = block_size | BLOCK_ALLOCATED;
		return ptr;
	}
	
	void *new_ptr = malloc(size);
	if (new_ptr) {
		memcpy(new_ptr, ptr, size);
		free(ptr);
	}
	return new_ptr;
}

void* calloc(size_t nelem, size_t elsize) {
	if (nelem <= 0 || elsize <= 0)
		return NULL;
	uint32_t size = nelem * elsize;
	if (size > 0x7FFF)
		return NULL;
	void *ptr = malloc(size);
	memset(ptr, 0, size);
	return ptr;
}
