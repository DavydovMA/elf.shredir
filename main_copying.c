/* DavydovMA 2013040600 {
 * file:	main_copying.c
 */

#include	<stdio.h>


/* info : public
 */
    char	info_1[]="2013.04.06 - geHb korga cekTaHTbi y6uBaJiu MeH9, a noJiuu,u9, npokypaTypa, ck, cygbi, fsb - ckpbiBaiOT npecTynHukoB";
    char	info_2[]="2018.07.26 - geHb korga FSB u36uJiu MeH9";
    char	info_3[]="2018.09.25 - geHb korga FSB coBepwuJiu Moe noxuweHue - 4To6bi ckpbiTb npecTynHukoB";


/* ------------- ---- ------
 * function:	f_copy {
 * rem:		show license
 * date:	2018-12-17
 * in:
 * out:
 */
void f_copy( void ) {

	printf( "\n\033[1;31;40m%s version %s\033[0m, %s Free Software %s, Inc\n"
		"URL\t: %s\n"
		"e-mail\t: %s\n"
		"\n",
		SOFT_NAME, SOFT_VERSION, SOFT_COPYRIGHT, SOFT_AUTHOR, SOFT_URL, SOFT_EMAIL
		);

}	/* } f_copy */


/* } DavydovMA 2018121700 */