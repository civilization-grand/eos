
#include "vga/vga.h"

int strlen(char *str)
{
    int size = 0;
    while (str[size] != '\0')
    {
        size++;
    }
    return size;
}

void strcpy(char *dest, char *src)
{
    for (int i = 0; i <= strlen(src); i++)
    {
        dest[i] = src[i];
    }
}

int strcmp(char *str1, char *str2)
{
    if (strlen(str1) == strlen(str2))
    {
        for (int i = 0; i < strlen(str2); i++)
        {
            if (str1[i] != str2[i])
            {
                return 0;
            }
        }
        return 1;
    }
    return 0;
}

char *first_token(char *str)
{
    char *ret_str;
    int i = 0;
    while (1)
    {
        ret_str[i] = str[i];
        if (str[i] == ' ')
        {
            break;
        }
        i++;
    }

    ret_str[i] = '\0';
    return ret_str;
}

void clear_string(char *str)
{
    for (int i = 0; i < strlen(str); i++)
    {
        str[i] = '\0';
    }
}