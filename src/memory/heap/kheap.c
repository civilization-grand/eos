#include "kheap.h"
#include "config.h"
#include "status.h"
#include "memory.h"
#include <stdbool.h>

struct entry_table page_entries;
struct pool memory_pool;

/*------------------Utility functions-------------------------------------------*/
unsigned int get_entry_type(PAGE_ENTRY entry)
{
    return entry & 0x0f;
}

int pool_get_start_block(unsigned int total_blocks)
{
    struct entry_table *table = &memory_pool.pages_entry_table[0];

    int block_count = 0;
    int block_start = -1;

    for (unsigned int i = 0; i < table->total_entries; i++)
    {
        if (get_entry_type(table->entries[i]) != BLOCK_TABLE_ENTRY_FREE)
        {
            block_count = 0;
            block_start = -1;
            continue;
        }

        if (block_start == -1)
        {
            block_start = i;
        }

        block_count++;
        if ((unsigned int)block_count == total_blocks)
        {
            break;
        }
    }

    if (block_start == -1)
    {
        return -ENOMEM;
    }

    return block_start;
}

unsigned int align_value_to_upper(unsigned int size)
{
    /*
    if (size <= POOL_BLOCK_SIZE)
    {
        return size;
    }
    */

    if ((size % POOL_BLOCK_SIZE) == 0)
    {
        return size;
    }

    size = (size - (size % POOL_BLOCK_SIZE));
    size += POOL_BLOCK_SIZE;
    return size;
}

void *block_to_address(int start_block)
{
    void *address = memory_pool.pool_start_address + (start_block * POOL_BLOCK_SIZE);

    if (address)
    {
        /* nothin */
    }

    return address;
}

int address_to_block(void *address)
{
    return ((int)(address - memory_pool.pool_start_address)) / POOL_BLOCK_SIZE;
}

void mark_blocks_taken(int start_block, int blocks_to_allocate)
{
    int end_block = (start_block + blocks_to_allocate) - 1;

    PAGE_ENTRY entry = BLOCK_TABLE_ENTRY_TAKEN | BLOCK_IS_FIRST;
    if (blocks_to_allocate > 1)
    {
        entry |= BLOCK_HAS_NEXT;
    }

    for (int i = start_block; i <= end_block; i++)
    {
        memory_pool.pages_entry_table->entries[i] = entry;
        entry = BLOCK_TABLE_ENTRY_TAKEN;
        if (i != (end_block - 1))
        {
            entry |= BLOCK_HAS_NEXT;
        }
    }
}

void *allocate_blocks(unsigned int blocks_to_allocate)
{
    void *address;

    int start_block = pool_get_start_block(blocks_to_allocate);
    if (start_block < 0)
    {
        goto out;
    }

    address = block_to_address(start_block);

    mark_blocks_taken(start_block, (int)blocks_to_allocate);

out:
    return address;
}

void mark_blocks_free(int start_block)
{
    struct entry_table *table = memory_pool.pages_entry_table;
    for (int i = start_block; i < (int)table->total_entries; i++)
    {
        PAGE_ENTRY entry = table->entries[i];
        table->entries[i] = BLOCK_TABLE_ENTRY_FREE;
        if (!(entry & BLOCK_HAS_NEXT))
        {
            break;
        }
    }
}
/*------------------Utility functions-------------------------------------------*/

/*Memory Pool initialization*/

void init_pool()
{

    page_entries.entries = (PAGE_ENTRY *)PAGES_ENTRY_TABLE;
    page_entries.total_entries = POOL_SIZE_BYTES / POOL_BLOCK_SIZE;

    memset(&memory_pool, 0, sizeof(struct pool));

    memory_pool.pool_start_address = (void *)POOL_ADDRESS;
    memory_pool.pages_entry_table = &page_entries;

    memset(page_entries.entries, 0, sizeof(PAGE_ENTRY) * page_entries.total_entries);
}

/*The interface functions*/
void *allocate_pages(unsigned int size)
{
    unsigned int aligned_size = align_value_to_upper(size);
    unsigned int blocks_to_allocate = aligned_size / POOL_BLOCK_SIZE;

    void *allocate = allocate_blocks(blocks_to_allocate);

    if (allocate)
    {
        /*nothin*/
    }

    return allocate;
}

void free_pages(void *ptr)
{
    mark_blocks_free(address_to_block((void *)ptr));
    ptr = 0x0; // ptr = null;
}
