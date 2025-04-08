#include "log.h"
#include <stdio.h>
#include <stdlib.h>

// Custom callback function for logging
void custom_callback(LogEvent *ev)
{
    // Format and write the log message with a custom prefix
    fprintf(ev->udata, "CUSTOM CALLBACK: [%s] %s:%d: ", log_level_string(ev->level), ev->file, ev->line);
    vfprintf(ev->udata, ev->fmt, ev->ap);
    fprintf(ev->udata, "\n");
}

int main()
{
    // 1. Set the minimum log level to DEBUG
    log_set_level(LOG_TRACE);
    // 2. Log messages to stdout
    printf("=== Testing logging to stdout ===\n");
    log_trace("This is a TRACE %d message.", 1000);
    log_log(LOG_TRACE, __FILE__, __LINE__, "This is a TRACE message.");
    log_log(LOG_DEBUG, __FILE__, __LINE__, "This is a DEBUG message.");
    log_log(LOG_INFO, __FILE__, __LINE__, "This is an INFO message.");
    log_log(LOG_WARN, __FILE__, __LINE__, "This is a WARN message.");
    log_log(LOG_ERROR, __FILE__, __LINE__, "This is an ERROR message.");
    log_log(LOG_FATAL, __FILE__, __LINE__, "This is a FATAL message.");

    // 3. Log messages to a file
    printf("\n=== Testing logging to a file ===\n");
    FILE *log_file = fopen("logfile.txt", "w");
    if (!log_file)
    {
        // Print an error message if the file cannot be opened
        perror("Unable to open logfile.txt");
        return EXIT_FAILURE;
    }
    // Add the file as a logging destination
    log_add_fp(log_file, LOG_DEBUG);
    log_log(LOG_DEBUG, __FILE__, __LINE__, "This is a DEBUG message written to the file.");
    log_log(LOG_ERROR, __FILE__, __LINE__, "This is an ERROR message written to the file.");
    fclose(log_file); // Close the file after logging

    // 4. Add a custom callback for logging
    printf("\n=== Testing custom callback ===\n");
    log_add_callback(custom_callback, stderr, LOG_INFO);
    log_log(LOG_INFO, __FILE__, __LINE__, "This is an INFO message with a custom callback.");
    log_log(LOG_FATAL, __FILE__, __LINE__, "This is a FATAL message with a custom callback.");

    // 5. Test quiet mode (disable logging to stdout)
    printf("\n=== Testing quiet mode ===\n");
    log_set_quiet(true); // Enable quiet mode
    log_log(LOG_WARN, __FILE__, __LINE__, "This message will not appear on stdout.");
    log_set_quiet(false); // Disable quiet mode
    log_log(LOG_WARN, __FILE__, __LINE__, "This message will appear on stdout.");

    printf("\n=== End of tests ===\n");
    return 0;
}