/*
 *
 */

#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#include <telnet.h>
#include <telnet_log.h>
#include <telnet_misc.h>

#define TELNET_LOG_CMD_RECV_MARK	"<-"
#define TELNET_LOG_CMD_SEND_MARK	"->"

static TelnetLogCmdToggle log_cmd_toggle = TELNET_LOG_CMD_OFF;
static TelnetLogCmdDirection log_cmd_direction = TELNET_LOG_CMD_RECV;

static unsigned char log_cmd_seq[TELNET_MAX_CMD_LEN]; //a builder for complete command sequence.

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
	    return "Message";
	case TELNET_LOG_LEVEL_INFO:
	    return "Info";
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

TELNET_EXPORT
void
telnet_toggle_log_cmd (TelnetLogCmdToggle value)
{
    log_cmd_toggle = value;
}

TELNET_EXPORT
void
telnet_log_cmd (unsigned char cmd_code)
{
    if (log_cmd_toggle == TELNET_LOG_CMD_ON)
    {
	const char* cmd_name = telnet_cmd_get_name (cmd_code);
	if (cmd_name != NULL)
	{
	    sprintf (log_cmd_seq, "%s %s", log_cmd_seq, cmd_name);
	}
    }
}

TELNET_EXPORT
void
telnet_log_option (unsigned char option_code)
{
    if (log_cmd_toggle == TELNET_LOG_CMD_ON)
    {
	const char* option_name = telnet_option_get_name (option_code);
	if (option_name != NULL)
	{
	    sprintf (log_cmd_seq, "%s %s", log_cmd_seq, option_name);
	}
    }
}

TELNET_EXPORT
void
telnet_log_cmd_begin (TelnetLogCmdDirection direction)
{
    if (log_cmd_toggle == TELNET_LOG_CMD_ON)
    {
	memset (log_cmd_seq, 0, sizeof (log_cmd_seq));
	log_cmd_direction = direction;
	switch (direction)
	{
	    case TELNET_LOG_CMD_RECV:
		sprintf (log_cmd_seq, "%s ", TELNET_LOG_CMD_RECV_MARK);
		break;
	    case TELNET_LOG_CMD_SEND:
		sprintf (log_cmd_seq, "%s ", TELNET_LOG_CMD_SEND_MARK);
		break;
	    default:
		break;
	}
    }
}

TELNET_EXPORT
void
telnet_log_cmd_end ()
{
    if (log_cmd_toggle == TELNET_LOG_CMD_ON)
    {
	fprintf (stdout, "%s\n", log_cmd_seq);
    }
}

TELNET_EXPORT
void
telnet_log_cmd_invalidate ()
{
    memset (log_cmd_seq, 0, sizeof (log_cmd_seq));
}
