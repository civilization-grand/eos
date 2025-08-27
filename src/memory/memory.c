
#include "memory.h"

void *memset(void *ptr, int value, unsigned int size)
{
    char *temp_ptr = (char *)ptr;
    for (unsigned int i = 0; i < size; i++)
    {
        temp_ptr[i] = value;
    }

    return ptr;
}