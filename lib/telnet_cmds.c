/*
 *	
 */

#include <telnet_cmds.h>
#include <telnet_misc.h>

static telnet_cmd _telnet_cmds_table[] = {
    [0] = {//240
	.cmd_code = TELNET_CMD_SE, 
	.cmd_name = "SE",
	.cmd_desc = "Subnegotiation End",
    },
    [1] = {//241
	.cmd_code = TELNET_CMD_NOP,
	.cmd_name = "NOP",
	.cmd_desc = "No Operation",
    },
    [2] = {//242
	.cmd_code = TELNET_CMD_DM,
	.cmd_name = "DM",
	.cmd_desc = "Data Mark",
    },
    [3] = {//243
	.cmd_code = TELNET_CMD_BRK,
	.cmd_name = "BRK",
	.cmd_desc = "NVT Break",
    },
    [4] = {//244
	.cmd_code = TELNET_CMD_IP,
	.cmd_name = "IP",
	.cmd_desc = "Interrupt Process",
    },
    [5] = {//245
	.cmd_code = TELNET_CMD_AO,
	.cmd_name = "AO",
	.cmd_desc = "Abort Output",
    },
    [6] = {//246
	.cmd_code = TELNET_CMD_AYT,
	.cmd_name = "AYT",
	.cmd_desc = "Are You There",
    },
    [7] = {//247
	.cmd_code = TELNET_CMD_EC,
	.cmd_name = "EC",
	.cmd_desc = "Erase Character",
    },
    [8] = {//248
	.cmd_code = TELNET_CMD_EL,
	.cmd_name = "EL",
	.cmd_desc = "Erase Line",
    },
    [9] = {//249
	.cmd_code = TELNET_CMD_GA,
	.cmd_name = "GA",
	.cmd_desc = "Go Ahead",
    },
    [10] = {//250
	.cmd_code = TELNET_CMD_SB,
	.cmd_name = "SB",
	.cmd_desc = "Subnegotiation Begin",
    },
    [11] = {//251
	.cmd_code = TELNET_CMD_WILL,
	.cmd_name = "WILL",
	.cmd_desc = "Will",
    },
    [12] = {//252
	.cmd_code = TELNET_CMD_WONT,
	.cmd_name = "WONT",
	.cmd_desc = "Will not",
    },
    [13] = {//253
	.cmd_code = TELNET_CMD_DO,
	.cmd_name = "DO",
	.cmd_desc = "Do",
    },
    [14] = {//254
	.cmd_code = TELNET_CMD_DONT,
	.cmd_name = "DONT",
	.cmd_desc = "Do not",
    },
    [15] = {//255
	.cmd_code = TELNET_IAC,
	.cmd_name = "IAC",
	.cmd_desc = "Interprete As Command",
    }
};
/*
 *	@cmd_code: the command code
 *	@return: the corresponding command name 
 *		 or NULL if cmd_code is not a valid 
 *		 command code.
 */
TELNET_EXPORT
const char*
telnet_cmd_get_name (unsigned char cmd_code)
{
    if (TELNET_CMD_IS_VALID(cmd_code))
	return _telnet_cmds_table[cmd_code-TELNET_CMD_MIN_CODE].cmd_name;
    else
	return NULL;
}

TELNET_EXPORT
const char*
telnet_cmd_get_desc (unsigned char cmd_code)
{
    if (TELNET_CMD_IS_VALID(cmd_code))
	return _telnet_cmds_table[cmd_code-TELNET_CMD_MIN_CODE].cmd_desc;
    else
	return NULL;
}

