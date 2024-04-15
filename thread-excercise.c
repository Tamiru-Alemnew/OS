#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

int counter=0;
void *thread_task(){
    for(int i=0;i<10;i++){
        printf("\n Thread Global counter = %d", counter);
        counter++;
        printf("\n Thread Local counter i= %d , my ID=%lu", i, pthread_self());
        sleep(1);
        }
        printf("\n");
    return 0;
}

int main() {
    pthread_t my_thread_desc;
    int my_thread_status;

    my_thread_status=pthread_create(&my_thread_desc, NULL, thread_task, NULL);
    
    if(my_thread_status==0) {
        printf("Thread created successfully. \n");
    }else{
        printf("Unable to create thread \n");
    }

    for(int i=0;i<10;i++) {
        printf("\n Main global counter = %d", counter);
        counter++;
        printf("\n Main local counter i= %d, my ID=%lu", i, pthread_self());
        sleep(1);
    }

    printf("\n");
    
    return 0;
}