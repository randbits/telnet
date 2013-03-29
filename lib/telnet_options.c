/*
 *
 */

#include <telnet_options.h>
#include <telnet_misc.h>

#define TELNET_OPT_MIN_CODE	0	//the min option code
#define TELNET_OPT_MAX_CODE	255
#define TELNET_OPT_IS_VALID(option_code) \
    (((option_code)>=TELNET_OPT_MIN_CODE)&& \
     ((option_code)<=TELNET_OPT_MAX_CODE))

static telnet_option _telnet_options_table[] = {
    [3] = {//3
	.option_code = TELNET_OPT_SUPPRESS_GO_AHEAD, 
	.option_name = "SUPPRESS-GO-AHEAD",
	.option_desc = "Suppress Go Ahead",
    },
};

TELNET_EXPORT
const char*
telnet_option_get_name (unsigned char option_code)
{
    if (TELNET_OPT_IS_VALID(option_code))
	return _telnet_options_table[option_code-TELNET_OPT_MIN_CODE].option_name;
    else
	return NULL;
}

TELNET_EXPORT
const char*
telnet_option_get_desc (unsigned char option_code)
{
    if (TELNET_OPT_IS_VALID(option_code))
	return _telnet_options_table[option_code-TELNET_OPT_MIN_CODE].option_desc;
    else
	return NULL;
}

