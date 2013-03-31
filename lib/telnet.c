/*
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <assert.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>	

#include <telnet.h>

/*
 *	@cmd_start [in, out]: because a command sequence can be separated into two 
 *			      consecutive reads. so we need a buffer @cmd_start to
 *	                      store the incomplete command sequence in the previous
 *			      reads and we also use it as the output the incomplete
 *			      command sequence in this read. 
 *	@p_cmd_size [in, out]:  designates the size of the valide portion of @cmd_start.
 *	@buffer [in]: the data of the current read.
 *	@size [in]: the data of the current read.
 */
TELNET_EXPORT
void 
telnet_parse_data (telnet_nvt* state, 
		   unsigned char* cmd_buffer, int* p_cmd_size,
		   const unsigned char* buffer, int size)
{
    int cmd_size = 0;//the size of the incomplete command sequence buffer @cmd_buffer
    int tmp_size = 0;//the size of the complete comamnd sequence

    cmd_size = *p_cmd_size;
    //1. handling incomplete command from @cmd_buffer
    if (cmd_size > 0)
    {
	assert (cmd_buffer[0] == TELNET_IAC);
	memcpy (&cmd_buffer[cmd_size], buffer, TELNET_MAX_CMD_LEN-cmd_size);
	tmp_size = telnet_parse_a_cmd (state, cmd_buffer, TELNET_MAX_CMD_LEN);
    }
    //start parsing from buffer[tmp_size - cmd_size]
    int current_index;
    current_index = tmp_size - cmd_size;
    for (; current_index < size;)
    {
	if (buffer[current_index] == TELNET_IAC)
	{
	    tmp_size = telnet_parse_a_cmd (state, &buffer[current_index], size - current_index);
	    current_index += tmp_size;
	}
	else // ordinary data
	{
	    fprintf (stdout, "%c", buffer[current_index]);
	    current_index ++;
	}
    }
    //outpu incomplete command sequence.
    if (current_index > size) //we have in
    {
	cmd_size = size - (current_index - tmp_size);
	*p_cmd_size = cmd_size;
	memset (cmd_buffer, 0, TELNET_MAX_CMD_LEN);
	memcpy (cmd_buffer, &buffer[current_index-tmp_size], cmd_size);
    }
    else if (tmp_size == 1) // the buffer[size-1]==TELNET_IAC
    {
	*p_cmd_size = 1;
	memset (cmd_buffer, 0, TELNET_MAX_CMD_LEN);
	cmd_buffer[0] = TELNET_IAC;
    }
}

/*TODO:
 *	@state  : track NVT state and supported options.
 *	@buffer : buffer can be a complete or incomplete command sequence
 *	@size   : size of @buffer.
 *	@return : 1) 1 : if @buffer contains only TELNET_IAC. must be incomplete.
 *		  2) 2 : if 
 *		  3) 3 :
 *		  4) >3:
 *		  the size of the first command sequence.(can be incomplete)
 */
TELNET_EXPORT
int 
telnet_parse_a_cmd (telnet_nvt* state, const unsigned char* buffer, int size)
{
    assert (size > 0);
    assert (buffer[0] == TELNET_IAC);

    int cmd_size = 1;//buffer must start with TELNET_IAC.
    int partial = 1; //0: complete, 1; incomplete command sequence

    telnet_log_cmd_begin (TELNET_LOG_CMD_RECV);
    telnet_log_cmd (buffer[0]);
    if (size > 1)
    {
	telnet_log_cmd (buffer[1]);
	switch (buffer[1])  //command code
	{
	//IAC <cmd> <option>
	case TELNET_CMD_WILL:
	    {
		cmd_size = 3;
		if (size >= 3)
		{
		    partial = 0;
		    telnet_log_option (buffer[2]);
		    telnet_cmd_do_option (state, buffer[2]);
		}
	    }
	    break;
	case TELNET_CMD_WONT:
	    {
		cmd_size = 3;
		if (size >= 3)
		{
		    partial = 0;
		    telnet_log_option (buffer[2]);
		}
	    }
	    break;
	case TELNET_CMD_DO:
	    {
		cmd_size = 3;
		if (size >= 3)
		{
		    partial = 0;
		    telnet_log_option (buffer[2]);
		}
	    }
	    break;
	case TELNET_CMD_DONT:
	    {
		cmd_size = 3;
		if (size >= 3)
		{
		    partial = 0;
		    telnet_log_option (buffer[2]);
		}
		//telnet_nvt_set_option (state, buffer[2]);
	    }
	    break;
	//IAC SB <option> <parameters> IAC SE
	case TELNET_CMD_SB:
	    break;
	//IAC IAC
	//case TELNET_IAC:
	//    break;
	//IAC <cmd>:
	case TELNET_CMD_NOP:
	case TELNET_CMD_DM:
	case TELNET_CMD_BRK:
	case TELNET_CMD_IP:
	case TELNET_CMD_AO:
	case TELNET_CMD_AYT:
	case TELNET_CMD_EC:
	case TELNET_CMD_EL:
	case TELNET_CMD_GA:
	    {
		partial = 0;
		cmd_size = 2;
	    }
	    break;
	default:
	    break;
	}
    }

    if (partial)
	telnet_log_cmd_invalidate ();
    else 
	telnet_log_cmd_end ();

    return cmd_size;
}
