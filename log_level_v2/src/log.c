#include "log.h"

#define MAX_CALLBACKS 32 // Maximum number of log output callbacks

/**
 * @brief Struct to hold a log callback, its user data, and level filter.
 */
typedef struct
{
    LogCallback fn; /**< Callback function */
    void *udata;    /**< User-defined data */
    int level;      /**< Minimum level this callback will handle */
} Callback;

/**
 * @brief Global logger state.
 */
static struct
{
    void *udata;                       /**< User-defined data for lock function */
    LogLockFn lock;                    /**< Lock function for thread safety */
    int level;                         /**< Minimum level to log */
    bool quiet;                        /**< If true, suppresses stdout logging */
    Callback callbacks[MAX_CALLBACKS]; /**< Registered log callbacks */
} L;

/**
 * @brief String representations of log levels.
 */
static const char *level_strings[] = {
    "TRACE", "DEBUG", "INFO", "WARN", "ERROR", "FATAL"};

/**
 * @brief ANSI color codes for each log level (if enabled).
 */
#ifdef LOG_USE_COLOR
static const char *level_colors[] = {
    "\033[0;37m", // TRACE - light gray
    "\033[0;34m", // DEBUG - blue
    "\033[0;32m", // INFO - green
    "\033[0;33m", // WARN - yellow
    "\033[0;31m", // ERROR - red
    "\033[1;31m"  // FATAL - bright red
};
#else
static const char *level_colors[] = {
    "", "", "", "", "", ""};
#endif

/**
 * @brief Default callback to print logs to stdout.
 * @param ev Pointer to log event data
 */
static void stdout_callback(LogEvent *ev)
{
    char buf[16];
    buf[strftime(buf, sizeof(buf), "%H:%M:%S", ev->time)] = '\0';

#ifdef LOG_USE_COLOR
    fprintf(
        ev->udata, "%s %s%-5s\033[0m \033[90m%s:%d:\033[0m ",
        buf, level_colors[ev->level], level_strings[ev->level],
        ev->file, ev->line);
#else
    fprintf(
        ev->udata, "%s %-5s %s:%d: ",
        buf, level_strings[ev->level], ev->file, ev->line);
#endif

    vfprintf(ev->udata, ev->fmt, ev->ap);
    fprintf(ev->udata, "\n");
    fflush(ev->udata);
}

/**
 * @brief Callback for writing logs to a file.
 * @param ev Pointer to log event data
 */
static void file_callback(LogEvent *ev)
{
    char buf[64];
    buf[strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", ev->time)] = '\0';
    fprintf(
        ev->udata, "%s %-5s %s:%d: ",
        buf, level_strings[ev->level], ev->file, ev->line);
    vfprintf(ev->udata, ev->fmt, ev->ap);
    fprintf(ev->udata, "\n");
    fflush(ev->udata);
}

/**
 * @brief Acquire logger lock (if defined).
 */
static void lock(void)
{
    if (L.lock)
    {
        L.lock(true, L.udata);
    }
}

/**
 * @brief Release logger lock (if defined).
 */
static void unlock(void)
{
    if (L.lock)
    {
        L.lock(false, L.udata);
    }
}

const char *log_level_string(int level)
{
    return level_strings[level];
}

void log_set_lock(LogLockFn fn, void *udata)
{
    L.lock = fn;
    L.udata = udata;
}

void log_set_level(int level)
{
    L.level = level;
}

void log_set_quiet(bool enable)
{
    L.quiet = enable;
}

/**
 * @brief Register a new log callback.
 * @param fn Callback function
 * @param udata User data for the callback
 * @param level Minimum log level for this callback
 * @return 0 on success, -1 if callback limit exceeded
 */
int log_add_callback(LogCallback fn, void *udata, int level)
{
    int i;
    for (i = 0; i < MAX_CALLBACKS; i++)
    {
        if (!L.callbacks[i].fn)
        {
            L.callbacks[i] = (Callback){fn, udata, level};
            return 0;
        }
    }
    return -1;
}

/**
 * @brief Initialize log event with current time and user data.
 * @param ev Pointer to log event
 * @param udata User data to assign
 */
static void init_event(LogEvent *ev, void *udata)
{
    if (!ev->time)
    {
        time_t t = time(NULL);
        ev->time = localtime(&t);
    }
    ev->udata = udata;
}

/**
 * @brief Add a file pointer as a logging target.
 * @param fp File to write logs to
 * @param level Minimum level for this output
 * @return 0 on success, -1 on failure
 */
int log_add_fp(FILE *fp, int level)
{
    return log_add_callback(file_callback, fp, level);
}

/**
 * @brief Main logging function called by log macros.
 * @param level Log level of the message
 * @param file Source file name
 * @param line Line number
 * @param fmt Format string
 * @param ... Additional arguments
 */
void log_log(LogLevel level, const char *file, int line, const char *fmt, ...)
{
    LogEvent ev = {
        .fmt = fmt,
        .file = file,
        .line = line,
        .level = level};

    lock();

    // Log to stdout if not quiet and level is sufficient
    if (!L.quiet && level >= L.level)
    {
        va_start(ev.ap, fmt);
        init_event(&ev, stdout);
        stdout_callback(&ev);
        va_end(ev.ap);
    }


    

    // Log to each registered callback
    int i;
    for (i = 0; i < MAX_CALLBACKS && L.callbacks[i].fn; i++)
    {
        if (level >= L.callbacks[i].level)
        {
            va_start(ev.ap, fmt);
            init_event(&ev, L.callbacks[i].udata);
            L.callbacks[i].fn(&ev);
            va_end(ev.ap);
        }
    }

    unlock();
}
