/*
 *
 */

#include <stdio.h>
#include <stdargs.h>

#include <telnet_misc.h>

static const char*
log_level_to_str (TelnetLogLevel level)
{
    switch (level)
    {
	case TELNET_LOG_LEVEL_ERROR:
	    return "Error";
	case TELNET_LOG_LEVEL_CRITICAL:
	    return "Critical";
	case TELNET_LOG_LEVEL_WARNING:
	    return "Warning";
	case TELNET_LOG_LEVEL_MESSAGE:
	    return "Message;
	case TELNET_LOG_LEVEL_INFO:
	    return "Info;
	case TELNET_LOG_LEVEL_DEBUG:
	    return "Debug";
	default:
	    break;
    }
    return "Invalid";
}

TELNET_EXPORT
void
telnet_log (const char* component, TelnetLogLevel level, const char* format, ...)
{
    char message[2048];
    va_list args;

    va_start (args, format);
    vsnprintf (message, 2048, format, args);
    fprintf (stderr, "%s (%s): %s\n",
	     component, log_level_to_str (level), message);
    va_end (args);
}
