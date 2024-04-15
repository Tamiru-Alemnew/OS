#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
int counter=0;

void *even_number(){
       for (int i =0 ; i < 10; i ++){
        if (counter % 2 == 1){
            counter++;
            printf("\n even thread counter =%d", counter);
        }
       
        sleep(1);
    } 

    printf("\n");
    return 0; 
        
}
void *odd_number(){
     
    for (int i =0 ; i < 10; i ++){
        if (counter % 2 == 0){
            counter++;
            printf("\n odd thread counter =%d", counter);
        }
       
        sleep(1);
    } 

    printf("\n");
    return 0; 
}


int main() {
    pthread_t even_thread , odd_thread;
    int my_odd_thread_status;
    int my_even_thread_status;

    my_even_thread_status = pthread_create(&even_thread, NULL, even_number, NULL);
    my_odd_thread_status=pthread_create(&odd_thread, NULL, odd_number, NULL);

    if(my_even_thread_status==0 && my_odd_thread_status == 0) {
        printf("Thread created successfully. \n");
    }else{
        printf("Unable to create thread \n");
    }

    for(int i=0;i<10;i++) {
        printf("\n Main global counter = %d", counter);
        counter++;
        sleep(1);
    }

    printf("\n");
    
    return 0;
}