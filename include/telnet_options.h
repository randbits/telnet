/*
 *	The Telnet Option Codes
 *	
 *	NOTE: 1. alll command start with TELNET_OPT_*
 */

#ifndef _TELNET_OPTIONS_H_
#define	_TELNET_OPTIONS_H_

typedef struct telnet_option telnet_option;
struct telnet_option
{
    unsigned char  option_code; //option code. one byte.
    const char*    option_name; //option name: e.g. "TELNET_OPT_"
    const char*	   option_desc; //option description: e.g. "" 
};

/*rfc857.txt
 *	TELNET ECHO OPTION
 */
#define TELNET_OPT_ECHO			1
/*rfc858.txt
 *	TELNET SUPPRESS GO AHEAD OPTION
 */
#define TELNET_OPT_SUPPRESS_GO_AHEAD	3
/*rfc1073.txt
 *	Telnet Window Size Option
 */
#define TELNET_OPT_NAWS			31


/*
 *	Public APIs
 */

extern const char* telnet_option_get_name (unsigned char option_code);
extern const char* telnet_option_get_desc (unsigned char option_code);

#endif /*_TELNET_OPTIONS_H_*/
