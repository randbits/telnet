/*
 *	
 */

#include <telnet_cmds.h>
#include <telnet_misc.h>

#define TELNET_CMD_MIN_CODE	240	//the min command code

static telnet_cmd _telnet_cmds_table[] = {
    {//240
	.cmd_code = TELNET_CMD_SE, 
	.cmd_name = "TELNET_CMD_SE",
	.cmd_desc = "Subnegotiation End",
    },
    {//241
	.cmd_code = TELNET_CMD_NOP,
	.cmd_name = "TELNET_CMD_NOP",
	.cmd_desc = "No Operation",
    },
    {//242
	.cmd_code = TELNET_CMD_DM,
	.cmd_name = "TELNET_CMD_DM",
	.cmd_desc = "Data Mark",
    },
    {//243
	.cmd_code = TELNET_CMD_BRK,
	.cmd_name = "TELNET_CMD_BRK",
	.cmd_desc = "NVT Break",
    },
    {//244
	.cmd_code = TELNET_CMD_IP,
	.cmd_name = "TELNET_CMD_IP",
	.cmd_desc = "Interrupt Process",
    },
    {//245
	.cmd_code = TELNET_CMD_AO,
	.cmd_name = "TELNET_CMD_AO",
	.cmd_desc = "Abort Output",
    },
    {//246
	.cmd_code = TELNET_CMD_AYT,
	.cmd_name = "TELNET_CMD_AYT",
	.cmd_desc = "Are You There",
    },
    {//247
	.cmd_code = TELNET_CMD_EC,
	.cmd_name = "TELNET_CMD_EC",
	.cmd_desc = "Erase Character",
    },
    {//248
	.cmd_code = TELNET_CMD_EL,
	.cmd_name = "TELNET_CMD_EL",
	.cmd_desc = "Erase Line",
    },
    {//249
	.cmd_code = TELNET_CMD_GA,
	.cmd_name = "TELNET_CMD_GA",
	.cmd_desc = "Go Ahead",
    },
    {//250
	.cmd_code = TELNET_CMD_SB,
	.cmd_name = "TELNET_CMD_SB",
	.cmd_desc = "Subnegotiation Begin",
    },
    {//251
	.cmd_code = TELNET_CMD_WILL,
	.cmd_name = "TELNET_CMD_WILL",
	.cmd_desc = "Will",
    },
    {//252
	.cmd_code = TELNET_CMD_WONT,
	.cmd_name = "TELNET_CMD_WONT",
	.cmd_desc = "Will not",
    },
    {//253
	.cmd_code = TELNET_CMD_DO,
	.cmd_name = "TELNET_CMD_DO",
	.cmd_desc = "Do",
    },
    {//254
	.cmd_code = TELNET_CMD_DONT,
	.cmd_name = "TELNET_CMD_DONT",
	.cmd_desc = "Do not",
    },
    {//255
	.cmd_code = TELNET_IAC,
	.cmd_name = "TELNET_IAC",
	.cmd_desc = "Interprete As Command",
    }
//   {//Invalid
//	.cmd_code = TELNET_INVALID,
//	.cmd_name = "TELNET_INVALID",
//	.cmd_desc = "Invalid Telnet Command",
//   }
};

TELNET_EXPORT
const char*
telnet_cmd_get_name (unsigned char cmd_code)
{
    return _telnet_cmds_table[cmd_code-TELNET_CMD_MIN_CODE].cmd_name;
}

TELNET_EXPORT
const char*
telnet_cmd_get_desc (unsigned char cmd_code)
{
    return _telnet_cmds_table[cmd_code-TELNET_CMD_MIN_CODE].cmd_desc;
}
