

#include <telnet.h>

TELNET_EXPORT
void
telnet_nvt_set_sock_fd (telnet_nvt* state, int fd)
{
    state->socket_fd = fd;
}

TELNET_EXPORT
void 
telnet_cmd_do_option (telnet_nvt* state, unsigned char option_code)
{
    //a naive implementation now
    unsigned char cmd_buffer[3];
    cmd_buffer[0] = TELNET_IAC;
    cmd_buffer[1] = TELNET_CMD_DO;
    cmd_buffer[2] = option_code;

    telnet_log_cmd_end ();
    telnet_log_cmd_begin (TELNET_LOG_CMD_SEND);
    telnet_log_cmd (cmd_buffer[0]);
    telnet_log_cmd (cmd_buffer[1]);
    telnet_log_option (cmd_buffer[2]);

    write (state->socket_fd, cmd_buffer, 3);
}
