#include "log.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 5 // Số lượng luồng

// Hàm thực thi của mỗi luồng
void *thread_function(void *arg) {
    int thread_id = *(int *)arg;

    for (int i = 0; i < 5; i++) {
        log_log(LOG_LVL_DEBUG, "Thread %d: Debug message %d", thread_id, i);
        log_log(LOG_LVL_WARN, "Thread %d: Warning message %d", thread_id, i);
        log_log(LOG_LVL_ERROR, "Thread %d: Error message %d", thread_id, i);
    }

    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];


    log_config_t config = {
        .log_config_level = LOG_LVL_DEBUG, 
        .log_config_type = LOG_FILE,
        .log_config_file = "multithread_log.log" 
    };

    log_init(&config);

    log_debug("=== Multi-threaded logging test started ===");

    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        if (pthread_create(&threads[i], NULL, thread_function, &thread_ids[i]) != 0) {
            perror("Failed to create thread");
            return EXIT_FAILURE;
        }
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }


    log_debug("=== Multi-threaded logging test completed ===\n");
    return 0;
}