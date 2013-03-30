/*
 *	Logging facility borrowed from Glib
 *	see gmessages.c/h
 */

#ifndef _TELNET_LOG_H_
#define _TELNET_LOG_H_


typedef enum
{
    TELNET_LOG_LEVEL_ERROR,
    TELNET_LOG_LEVEL_CRITICAL,
    TELNET_LOG_LEVEL_WARNING,
    TELNET_LOG_LEVEL_MESSAGE,
    TELNET_LOG_LEVEL_INFO,
    TELNET_LOG_LEVEL_DEBUG
} TelnetLogLevel;

typedef enum
{
    TELNET_LOG_CMD_RECV,
    TELNET_LOG_CMD_SEND
} TelnetLogCmdDirection;

typedef enum
{
    TELNET_LOG_CMD_ON,
    TELNET_LOG_CMD_OFF
} TelnetLogCmdToggle;

extern void telnet_log (const char* component, TelnetLogLevel level, 
			const char* format, ...);

extern void telnet_toggle_log_cmd (TelnetLogCmdToggle value);
extern void telnet_log_cmd_begin (TelnetLogCmdDirection direction);
extern void telnet_log_cmd (unsigned char cmd_code);
extern void telnet_log_option (unsigned char option_code);
extern void telnet_log_cmd_end ();
extern void telnet_log_cmd_invalidate ();

#endif/*_TELNET_LOG_H_*/
