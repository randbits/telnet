#ifndef _TELNET_NVT_H_
#define	_TELNET_NVT_H_

typedef struct telnet_nvt telnet_nvt;
struct telnet_nvt
{
    int socket_fd;	//socket fd.
};

//rfc854.txt
/*required*/
#define TELNET_NVT_ASCII_NUL	0	//No Operationally
#define TELNET_NVT_ASCII_LF	10	//Moves the printer to the next print line,
					//keepin the same horizontal position.
#define TELNET_NVT_ASCII_CR	13	//Moves the printer to the left margin of the
					//current line.
/*optional*/
#define TELNET_NVT_ASCII_BEL	7	//produces an audible or visible signal (which 
					//does NOT move the print head).
#define	TELNET_NVT_ASCII_BS	8	//Movets the print head one character position 
					//towards the left margin.
#define TELNET_NVT_ASCII_HT	9	//horizontal tab
#define TELNET_NVT_ASCII_VT	11	//Vertical tab
#define TELNET_NVT_ASCII_FF	12	//form feed


extern void telnet_nvt_set_sock_fd (telnet_nvt* state, int fd);
extern void telnet_cmd_do_option (telnet_nvt* state, unsigned char option_code);

#endif/*_TELNET_NVT_H_*/
