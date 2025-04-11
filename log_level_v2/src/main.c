#include "log.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

pthread_mutex_t log_mutex;

// Lock function to be used with LogLockFn
void log_lock_function(bool lock, void *udata)
{
    if (lock)
    {
        pthread_mutex_lock(&log_mutex); // Lock the mutex
    }
    else
    {
        pthread_mutex_unlock(&log_mutex); // Unlock the mutex
    }
}

int main()
{
    // Initialize the mutex
    if (pthread_mutex_init(&log_mutex, NULL) != 0)
    {
        perror("Mutex initialization failed");
        return EXIT_FAILURE;
    }

    // Set the lock function for thread safety
    log_set_lock(log_lock_function, NULL);

    // Set the minimum log level
    log_set_level(LOG_INFO);

    // Example of multi-threaded logging
    printf("=== Testing multi-threaded logging ===\n");

    // Simulate logging from multiple threads (example code here)
    log_info("This is an INFO message from the main thread.");
    log_warn("This is a WARN message from the main thread.");

    // Destroy the mutex
    pthread_mutex_destroy(&log_mutex);

    printf("=== End of test ===\n");
    return 0;
}