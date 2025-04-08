/*
 *******************************************************************************
 * @file       log.h
 * @author     Luu Ngoc Anh
 * @date       04/04/2025
 * @brief      Logging utility with support for levels, file and line info, 
 *             and customizable output.
 *******************************************************************************
 */

 #ifndef __LOG_H__
 #define __LOG_H__
 
 #include <stdio.h>
 #include <stdarg.h>
 #include <stdbool.h>
 #include <time.h>
 
 #define LOG_USE_COLOR  // Enable colored output (can be customized)
 
 /**
  * @brief Struct containing information about a log event.
  */
 typedef struct
 {
     va_list ap;           /**< Argument list for formatted output */
     const char *fmt;      /**< Format string */
     const char *file;     /**< File name where log is called */
     struct tm *time;      /**< Time of the log event */
     void *udata;          /**< User data passed to the callback */
     int line;             /**< Line number in source file */
     int level;            /**< Log level (TRACE, DEBUG, etc.) */
 } LogEvent;
 
 /**
  * @brief Enumeration of log levels.
  */
 typedef enum
 {
     LOG_TRACE,
     LOG_DEBUG,
     LOG_INFO,
     LOG_WARN,
     LOG_ERROR,
     LOG_FATAL
 } LogLevel;
 
 /**
  * @brief Callback function for handling log output.
  */
 typedef void (*LogCallback)(LogEvent *ev);
 
 /**
  * @brief Function pointer for thread locking mechanism.
  */
 typedef void (*LogLockFn)(bool lock, void *udata);
 
 /* Logging macros for different levels */
 #define log_trace(...) log_log(LOG_TRACE, __FILE__, __LINE__, __VA_ARGS__)
 #define log_debug(...) log_log(LOG_DEBUG, __FILE__, __LINE__, __VA_ARGS__)
 #define log_info(...)  log_log(LOG_INFO,  __FILE__, __LINE__, __VA_ARGS__)
 #define log_warn(...)  log_log(LOG_WARN,  __FILE__, __LINE__, __VA_ARGS__)
 #define log_error(...) log_log(LOG_ERROR, __FILE__, __LINE__, __VA_ARGS__)
 #define log_fatal(...) log_log(LOG_FATAL, __FILE__, __LINE__, __VA_ARGS__)
 
 /**
  * @brief Get the string representation of a log level.
  * @param level Log level enum
  * @return Name of the log level as a string
  */
 const char *log_level_string(int level);
 
 /**
  * @brief Set a locking function for thread safety.
  * @param fn Lock/unlock function
  * @param udata User data passed to lock function
  */
 void log_set_lock(LogLockFn fn, void *udata);
 
 /**
  * @brief Set the minimum log level to display.
  * @param level Only log events >= level will be processed
  */
 void log_set_level(int level);
 
 /**
  * @brief Enable or disable all logging output.
  * @param enable If true, logging is silenced
  */
 void log_set_quiet(bool enable);
 
 /**
  * @brief Add a callback function for log events.
  * @param fn Callback function
  * @param udata User data passed to callback
  * @param level Minimum log level for this callback
  * @return 0 on success, -1 on failure
  */
 int log_add_callback(LogCallback fn, void *udata, int level);
 
 /**
  * @brief Add a FILE* output stream (e.g., stderr or a file).
  * @param fp File pointer to write logs
  * @param level Minimum log level for this output
  * @return 0 on success, -1 on failure
  */
 int log_add_fp(FILE *fp, int level);
 
 /**
  * @brief Main logging function used internally by macros.
  * @param level Log level
  * @param file Source file name
  * @param line Line number in file
  * @param fmt Format string (printf-style)
  * @param ... Variable arguments
  */
 void log_log(LogLevel level, const char *file, int line, const char *fmt, ...);
 
 #endif
 
 /********************************* END OF FILE ********************************/
 /******************************************************************************/
 