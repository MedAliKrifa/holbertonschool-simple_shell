#include <stdio.h>
#include "shell.h"

void print_1(void)
{
    fprintf(stderr, "$ ");
}
void print_2(void)
{
    fprintf(stderr, "> ");
}
char *read_cmd(void)
{
    char buf[1024];
    char *ptr = NULL;
    char ptrlen = 0;
    while (fgets(buf, 1024, stdin))
    {
        int buflen = strlen(buf);
        if (!ptr)
        {
            ptr = malloc(buflen + 1);
        }
        else
        {
            char *ptr2 = realloc(ptr, ptrlen + buflen + 1);

            if (ptr2)
            {
                ptr = ptr2;
            }
            else
            {
                free(ptr);
                ptr = NULL;
            }
        }
        if (!ptr)
        {
            fprintf(stderr, "failed to allocate buffer:%s\n", strerror(errno));
            return NULL;
        }
        strcpy(ptr + ptrlen, buf);
        if (buf[buflen - 1] == '\n')
        {
            if (buflen == 1 || buf[buflen - 2] != '\\')
            {
                return ptr;
            }
            ptr[ptrlen + buflen - 2] = '\0';
            buflen -= 2;
            print_2();
        }
        ptrlen += buflen;
    }
    return ptr;
}