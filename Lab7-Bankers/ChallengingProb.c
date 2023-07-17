#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    pthread_mutex_t rope_mutex;
    pthread_mutex_t east_mutex;
    pthread_mutex_t west_mutex;
    int east_count;
    int west_count;
} Canyon;

void* baboon_cross(void* arg) {
    Canyon* canyon = (Canyon*)arg;
    int direction = rand() % 2;  // Randomly choose direction (0 for east, 1 for west)

    if (direction == 0) {  // Eastward baboon
        pthread_mutex_lock(&canyon->east_mutex);
        canyon->east_count++;

        if (canyon->east_count == 1) {
            pthread_mutex_lock(&canyon->rope_mutex);
        }

        pthread_mutex_unlock(&canyon->east_mutex);

        printf("Baboon moving eastward is crossing the canyon\n");

        pthread_mutex_lock(&canyon->east_mutex);
        canyon->east_count--;

        if (canyon->east_count == 0) {
            pthread_mutex_unlock(&canyon->rope_mutex);
        }

        pthread_mutex_unlock(&canyon->east_mutex);
    } else {  // Westward baboon
        pthread_mutex_lock(&canyon->west_mutex);
        canyon->west_count++;

        if (canyon->west_count == 1) {
            pthread_mutex_lock(&canyon->rope_mutex);
        }

        pthread_mutex_unlock(&canyon->west_mutex);

        printf("Baboon moving westward is crossing the canyon\n");

        pthread_mutex_lock(&canyon->west_mutex);
        canyon->west_count--;

        if (canyon->west_count == 0) {
            pthread_mutex_unlock(&canyon->rope_mutex);
        }

        pthread_mutex_unlock(&canyon->west_mutex);
    }

    pthread_exit(NULL);
}

int main() {
    srand(time(NULL));
    Canyon canyon;
    pthread_t baboon_threads[10];  // Replace with desired number of baboons

    pthread_mutex_init(&canyon.rope_mutex, NULL);
    pthread_mutex_init(&canyon.east_mutex, NULL);
    pthread_mutex_init(&canyon.west_mutex, NULL);
    canyon.east_count = 0;
    canyon.west_count = 0;

    for (int i = 0; i < 10; i++) {
        pthread_create(&baboon_threads[i], NULL, baboon_cross, (void*)&canyon);
    }

    for (int i = 0; i < 10; i++) {
        pthread_join(baboon_threads[i], NULL);
    }

    pthread_mutex_destroy(&canyon.rope_mutex);
    pthread_mutex_destroy(&canyon.east_mutex);
    pthread_mutex_destroy(&canyon.west_mutex);

    return 0;
}