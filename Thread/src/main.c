#include <stdio.h>
#include<pthread.h>

void *my_thread_function(void *arg)
{
    printf("Hello arg: %s!\n", (char *)arg);
    return arg;
}

int main()
{
    pthread_t  thread_id;
    pthread_t  thread_id2;
    char a[100] = {0};
    memset(a, 0, sizeof(a));
    pthread_create(&thread_id, NULL, my_thread_function, "ngocanh");
    pthread_create(&thread_id2, NULL, my_thread_function, "ngocanh2");

    pthread_join(thread_id, &a);
    printf("Thread 1 returned: %s\n", &a);
    pthread_join(thread_id2, &a);
    printf("Thread 2 returned: %s\n", &a);
    return 0;
}