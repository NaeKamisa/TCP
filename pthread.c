#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 

int i = 0;

void thread_test(){
    while (1)
    {
        /* code */
    sleep(1);
    printf("ceci est un test %d\n",i);
    i++;
    sleep(1);
    }
    
    return NULL;
}

int main(){
    pthread_t thread_id;
        /* code */
    printf("start of thread\n");
    pthread_create(&thread_id,NULL,thread_test,NULL);
    pthread_join(thread_id,NULL);
    printf("end of thread\n");
    while (1)
    {
    }
    
    return 0;

}