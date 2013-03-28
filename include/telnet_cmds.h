/*
 *	The Telnet Command Codes
 *	
 *	NOTE: 1. alll command start with TELNET_CMD_*
 */

#ifndef _TELNET_CMDS_H_
#define _TELNET_CMDS_H_

/*
 *rfc854.txt : p13~p14 TELNET COMMAND STRUCTURE
 *there'are two kinds of commands:
 *1. two bytes sequence
 * +-----+-----+
 * | IAC | CMD |
 * +-----+-----+
 * cmd : command code
 *2. tree bytes sequence (for option negotiation)
 * +-----+-----+-----+
 * | IAC | CMD | OPT |
 * +-----+-----+-----+
 * cmd : command code
 * opt : option code  
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

#endif /*_TELNET_CMDS_H_*/
