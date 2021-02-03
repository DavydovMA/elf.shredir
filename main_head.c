/* DavydovMA 2013040600 {
 * file:	main_head.c
 */

#include	<stdio.h>
#include	<signal.h>


struct {
	unsigned int	verbose	: 1;	/* flag verbose  : 0=off; 1=on; -v --verbose */
	unsigned int	yes	: 1;	/* flag yes      : 0=off; 1=on; -y --yes     */
	unsigned int	nowait	: 1;	/* flag nowait   : 0=off; 1=on; -n --nowait  */
	unsigned int	iterdef	: 1;	/* flag iterdef  : 0=off; 1=on; -i --iterdef */
	unsigned int	user	: 1;	/* flag user     : 0=off; 1=on; -u --user    */
	unsigned int	link	: 1;	/* flag link     : 0=off; 1=on; -l --link    */
} flag;

	char		*file_elf	= NULL;


/* } DavydovMA 2019072300 */
