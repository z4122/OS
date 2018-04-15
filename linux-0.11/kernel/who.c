#include <linux/kernel.h>
#include <asm/segment.h>
#include <unistd.h>
#include <errno.h>

#define name_len 23

char my_name[name_len] = "lyb";

int sys_iam(const char* name)
{
    int i = 0,j = 0;
    while(get_fs_byte(&name[i])!='\0')
    {
        i++;
    }

    if(i>23)  
        return -EINVAL;

    for(;j<i;j++)
    {
        my_name[j] = get_fs_byte(&name[j]);
    }
    my_name[j] = '\0';
    return i;
}

int sys_whoami(char* name,unsigned int size)
{
    int i = 0,j = 0;
    while(my_name[i]!='\0')
    {
        i++;
    }

    if(size<i)
        return -EINVAL;

    for(;j<i;j++)
    {
        put_fs_byte(my_name[j],&name[i]);
    }
    name[j] = '\0';
    return i;
}
