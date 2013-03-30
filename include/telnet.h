#ifndef _TELNET_H_
#define _TELNET_H_

#include <telnet_cmds.h>
#include <telnet_log.h>
#include <telnet_misc.h>
#include <telnet_nvt.h>
#include <telnet_options.h>


extern void telnet_parse_data (telnet_nvt* state,
			       unsigned char* cmd_start, int* p_cmd_size,
			       const unsigned char* buffer, int size);

extern int telnet_parse_a_cmd (telnet_nvt* state, const unsigned char* buffer, int size);

#endif/*_TELNET_H_*/
