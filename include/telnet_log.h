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
    TELNET_LOG_LEVEL_DEBUG,
} TelnetLogLevel;

extern void telnet_log (const char* component, TelnetLogLevel level, 
			const char* format, ...);

#endif/*_TELNET_LOG_H_*/
