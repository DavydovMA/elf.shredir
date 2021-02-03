/* DavydovMA 2013040600 {
 * file:	main_help.c
 */

#include	<stdio.h>


/* ------------- ---- ------
 * function:	f_help {
 * rem:		show help
 * date:	2019-07-23
 * in:
 * out:
 */
void f_help( void ) {

	printf( "\nUsage:\t%s <options>\n"
		"Common options:\n"
		"\t-h|--help\t\t: this help\n"
		"\t-v|--verbose\t\t: verbose mode\n"
		"\t-i|--iterdef\t\t: enable iteration (3); default=(1)\n"
		"\t-n|--nowait\t\t: no wait Ctrl_C\n"
		"\t-y|--yes\t\t: confirm YES to execute\n"
		"\t-u|--user\t\t: don't check on root\n"
		"\t-l|--link\t\t: follow link; default=(link as file)\n"
		"\t-p|--path <path>\t: path to directory or file\n"
		"\n",
		file_elf
		);

}	/* } f_help */


/* } DavydovMA 2019072400 */
