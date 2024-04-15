#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 20

int buffer[BUFFER_SIZE]; // shared buffer
int count = 0; // shared count

pthread_mutex_t mutex;
pthread_cond_t cond_producer;
pthread_cond_t cond_consumer;

void *producer(void *param) {
    int item;

    while(1) {
        // produce an item
        item = rand() % 100;

        pthread_mutex_lock(&mutex);

        if(count == BUFFER_SIZE) {
            pthread_cond_wait(&cond_producer, &mutex);
        }

        // add item to buffer
        buffer[count] = item;
        count++;

        if(count == 1) {
            pthread_cond_signal(&cond_consumer);
        };

        pthread_mutex_unlock(&mutex);

        printf("Producer produced %d\n", item);
        sleep(1);
    }
}

void *consumer(void *param) {
    int item;

    while(1) {
        pthread_mutex_lock(&mutex);

        if(count == 0) {
            pthread_cond_wait(&cond_consumer, &mutex);
        }

        // remove item from buffer
        item = buffer[count-1];
        count--;

        if(count == BUFFER_SIZE - 1) {
            pthread_cond_signal(&cond_producer);
        }

        pthread_mutex_unlock(&mutex);

        printf("Consumer consumed %d\n", item);
        sleep(1);
    }
}

int main() {
    pthread_t producer_thread, consumer_thread;

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond_producer, NULL);
    pthread_cond_init(&cond_consumer, NULL);

    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond_producer);
    pthread_cond_destroy(&cond_consumer);

    return 0;
}