#define __LIBRARY__

#include<linux/kernel.h>
#include<unistd.h>
#include<asm/segment.h>
#include<asm/system.h>

sem_t* sys_semopen(const char* name,unsigned int value)
{
    char* buf = (char*)malloc(sizeof(char)*10);
    int i = 0,j = 0;
    while(get_fs_byte(&name[i])!='\0')
        i++;
   
    for(j = 0;j<i;j++)
        buf[j] = get_fs_byte(&name[j]);
    sem_t *sem = (sem_t*)malloc(sizeof(sem_t));
    sem->name = buf;
    sem->value = value;
    
    printk("semopen,name:%s value:%d\n",sem->name,sem->value);
    return sem;
}

//i_queue *queue_index = queue_init(10);

int sys_semwait(sem_t* sem)
{
    cli();
    while(!sem->value)
        sleep_on(&sem->wait);
    sem->value--;
    sti();
   // printk("semwait\n");
    return 0;
}

int sys_sempost(sem_t* sem)
{
    cli();//close interrupter
    if(!sem->value)
        wake_up(sem->wait);
    sem->value++;
    sti();//open interrupter
    return 0;
}

int sys_semunlink(const char* sem)
{
    return 0;
}
