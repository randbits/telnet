/*
 *	The Telnet Command Codes
 *	
 *	NOTE: 1. alll command start with TELNET_CMD_*
 */

#ifndef _TELNET_CMDS_H_
#define _TELNET_CMDS_H_

typedef struct telnet_cmd telnet_cmd;
struct telnet_cmd
{
    unsigned char  cmd_code; //command code. one byte.
    const char*    cmd_name; //command name: e.g. "TELNET_CMD_SE"
    const char*	   cmd_desc; //command description: e.g. "subnegotiation End" 
};

/*
 *rfc854.txt : p13~p14 TELNET COMMAND STRUCTURE
 *there'are two kinds of commands:
 *1. two bytes sequence
 *
 *	IAC <cmd> 
 *
 * cmd : command code 241~249
 *2. tree bytes sequence (for option negotiation)
 * 
 *	IAC <cmd> <option>
 *
 * cmd : command code 251-254
 * opt : option code (see various rfcs) 
 * NOTE: 1. command types.
 *	    WILL: Sender wants to do something
 *	    WONT: Sender doesn't want to do something
 *	    DO  : Sender wants the other end to do something
 *	    DONT: Sender wants the other not to do something
 *	 2. command type and their responses
 *	    Sender_sent Receiver_responds
 *	  1)WILL	DO		 
 *	    The sender would like to use a certain facility if the receiver
 *	    can handle it. Option is now in effect.
 *	  2)WILL	DONT
 *	    Receiver says it cannot support the option. Option is not in effect
 *	  3)DO		WILL
 *	    The sender says it can handle traffic from the sender if the sender 
 *	    wishes to use a certain option. Option is now in effect.
 *	  4)DO		WONT
 *	    Receiver says it cannot support the option. Option is not in effect.
 *	  5)WONT	DONT
 *	    Option is disabled. DONT is the only valid responses.
 *	  6)DONT	WONT
 *	    Option is disabled. WONT is the only valid responses.
 *
 *3. more bytes (for subnegotiation)
 *
 *	IAC SB <option> <parameters>  IAC SE
 *
 * cmd : command code 240, 250
 * option and parameters: see various rfc definitions.
 */
#define TELNET_IAC	255	//Interpret As Command

/*
 *rfc854.txt : p13~p14 TELNET COMMAND STRUCTURE
 *The following are the defined TELNET commands.  
 *Note that these codes and code sequences have the indicated meaning only when
 *immediately preceded by an IAC.
 */
//	NAME            CODE    MEANING
#define TELNET_CMD_SE	240	//SE: End of subnegotiation parameters.
#define TELNET_CMD_NOP	241	//NOP: No operation.
#define TELNET_CMD_DM   242	//Data Mark: The data stream portion of a Synch. 
                                //	This should always be accompanied by a 
				//	TCP Urgent notification.
#define TELNET_CMD_BRK  243	//Break:  NVT character BRK.
#define TELNET_CMD_IP	244	//Interrupt Process:  The function IP.
#define TELNET_CMD_AO	245	//Abort output:  The function AO.
#define TELNET_CMD_AYT	246	//Are You There: The function AYT.
#define TELNET_CMD_EC	247	//Erase character: The function EC.
#define TELNET_CMD_EL	248	//Erase Line: The function EL.
#define TELNET_CMD_GA	249	//Go ahead:  The GA signal.
#define TELNET_CMD_SB	250	//SB: Indicates that what follows is 
				//    subnegotiation of the indicated option.

#define TELNET_CMD_WILL	251	//WILL (option code): Indicates the desire to 
				//	begin performing, or confirmation that 
				//	you are now performing, the indicated 
				//	option.
#define TELNET_CMD_WONT	252	//WON'T (option code): Indicates the refusal 
				//	to perform, or continue performing, 
				//	the indicated option.
#define TELNET_CMD_DO	253	//DO (option code): Indicates the request that
				//	the other party perform, or confirmation
				//	that you are expecting the other party 
				//	to perform, the indicated option.
#define TELNET_CMD_DONT	254	//DON'T (option code): Indicates the demand that
				//	the other party stop performing,
                                //      or confirmation that you are no longer 
				//      expecting the other party to perform, 
				//      the indicated option.

/*the data IAC should escaped by IAC */
//#define TELNET_IAC	255	//IAC:  Data Byte 255.

/*
 *	Public APIs
 */
#define TELNET_MAX_CMD_LEN	64 //the max command sequence len (may be not reasonable).

#define TELNET_CMD_MIN_CODE	240	//the min command code
#define TELNET_CMD_MAX_CODE	255
#define TELNET_CMD_IS_VALID(cmd_code) \
    (((cmd_code)>=TELNET_CMD_MIN_CODE)&& \
     ((cmd_code)<=TELNET_CMD_MAX_CODE))

extern const char* telnet_cmd_get_name (unsigned char cmd_code);
extern const char* telnet_cmd_get_desc (unsigned char cmd_code);

#endif /*_TELNET_CMDS_H_*/
