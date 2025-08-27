

#ifndef KHEAP_H
#define KHEAP_H

#define BLOCK_TABLE_ENTRY_TAKEN 0x01
#define BLOCK_TABLE_ENTRY_FREE 0x00

#define BLOCK_HAS_NEXT 0b10000000
#define BLOCK_IS_FIRST 0b01000000

typedef unsigned char PAGE_ENTRY;

struct entry_table
{
    PAGE_ENTRY *entries;
    unsigned int total_entries;
};

struct pool
{
    struct entry_table *pages_entry_table;
    void *pool_start_address;
};

void init_pool();

void *allocate_pages(unsigned int size);
void free_pages(void *ptr);

#endif