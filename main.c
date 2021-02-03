/* DavydovMA 2013040600 {
 */

#define		SOFT_NAME	"Shredir"
#define		SOFT_VERSION	"19.07"
#define		SOFT_COPYRIGHT	"Copyright 1990-2019"
#define		SOFT_AUTHOR	"DavydovMA"
#define		SOFT_URL	"http://domain"
#define		SOFT_EMAIL	"dev-c@domain"

#include	"main_head.c"
#include	"main_copying.c"
#include	"main_help.c"

#include	<dirent.h>
#include	<errno.h>
#include	<signal.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<sys/stat.h>
#include	<time.h>
#include	<unistd.h>

#define		RM_FILE		"20130406.!.06042013"
#define		RM_FILE_LENGTH	19


/* ------------- ---- ------
 * function:    sys_remove {
 * rem:         remove
 * date:        2019-07-30
 * in:
 *  vc_path     path to destination
 * out:
 */
void sys_remove( const char *vc_path ) {
/* ------------- ---- ------
 * Block: Variable
 */
	char		*vc_path_new;
	int		vi_count;
/* ------------- ---- ------
 * Block: Start
 */
if ( flag.verbose != 0 ) {
	printf( " remove\t: [%s]\n", vc_path );
}
	vi_count = strlen( vc_path );						/* NEW_NAME { */
	while( vc_path[ vi_count ] != '/' ) {
		vi_count--;
	}
	vc_path_new = ( char * ) malloc( vi_count + 1 + RM_FILE_LENGTH + 1 );	/* malloc-4 */
	if ( vc_path_new != 0 ) {	/* malloc-4 */
		( char * ) memcpy( vc_path_new, vc_path, vi_count + 1 );
		( char * ) memcpy( vc_path_new + vi_count + 1, RM_FILE, RM_FILE_LENGTH );
		vc_path_new[ vi_count + 1 + RM_FILE_LENGTH ] = '\0';		/* } NEW_NAME */
		if ( rename( vc_path, vc_path_new ) == 0 ) {	/* RENAME { */
if ( flag.verbose != 0 ) {
	printf( " rmnew\t: [%s]\n", vc_path_new );
}
		} else {
printf( " error\t: [%s] - %s (rmnew)\n", vc_path, strerror( errno ) );
		}						/* } RENAME */
if ( flag.verbose != 0 ) {					/* REMOVE ( */
	printf( " rm\t: [%s] - ["RM_FILE"]\n", vc_path );
}
		if ( remove( vc_path_new ) == 0 ) {
if ( flag.verbose != 0 ) {
	printf( " rm\t: [%s] - ok\n", vc_path );
}
		} else {
printf( " error\t: [%s] - %s (rm)\n", vc_path, strerror( errno ) );
		}					/* } REMOVE */
		free( vc_path_new );	/* malloc-4 */
	} else {			/* malloc-4 */
printf( " error\t: [%s] - %s (malloc-4)\n", vc_path, strerror( errno ) );
	}				/* malloc-4 */
}	/* } sys_remove */
/* ------------- ---- ------
 * function:    sys_shred {
 * rem:         shred
 * date:        2019-07-30
 * in:
 *  vc_path     path to destination
 * out:
 */
void sys_shred( const char *vc_path ) {
/* ------------- ---- ------
 * Block: Variable
 */
	char		vc_sys[]	= "shred -u ";		/* "/usr/bin/shred -u " */
	char		vc_sys_n[]	= "-n 1 ";
	char		vc_sys_v[]	= "-v ";
	char		vc_sys_f[]	= "-f \"";
	char		*vc_sys_new;
	int		vl_sys;
	int		vl_sys_n;
	int		vl_sys_v;
	int		vl_sys_f;
	int		vl_path;
	int		vi_index;
	int		vi_quot;
	int		vi_quot_off;
/* ------------- ---- ------
 * Block: Start
 */
	vl_path = strlen( vc_path );
	vi_quot = 0;
	for ( vi_index = 0; vi_index < vl_path; vi_index++ ) {
		if ( vc_path[ vi_index ] == '\"' ) {
			vi_quot++;
		}
	}
	vl_sys   = strlen( vc_sys );
if ( flag.iterdef != 0 ) {
	vl_sys_n = 0;
} else {
	vl_sys_n = strlen( vc_sys_n );
}
if ( flag.verbose != 0 ) {
	printf( "{\n" );
	vl_sys_v = strlen( vc_sys_v );
} else {
	vl_sys_v = 0;
}
	vl_sys_f = strlen( vc_sys_f );
	vc_sys_new = ( char * ) malloc( vl_sys + vl_sys_n + vl_sys_v + vl_sys_f + vl_path + vi_quot + 1 + 1 );	/* malloc-3 */
	if ( vc_sys_new != 0 ) {	/* malloc-3 */
/* [shred..] */	( char * ) memcpy( vc_sys_new,					vc_sys,		vl_sys );
/* [-n 1 ]   */	( char * ) memcpy( vc_sys_new + vl_sys,				vc_sys_n,	vl_sys_n );
/* [-v ]     */	( char * ) memcpy( vc_sys_new + vl_sys + vl_sys_n, 		vc_sys_v,	vl_sys_v );
/* [-f \"]   */	( char * ) memcpy( vc_sys_new + vl_sys + vl_sys_n + vl_sys_v,	vc_sys_f,	vl_sys_f );
		vi_quot_off = 0;
		for ( vi_index = 0; vi_index < vl_path; vi_index++ ) {
			if ( vc_path[ vi_index ] == '\"' ) {
/* [\"] */		( char * ) memcpy( vc_sys_new + vl_sys + vl_sys_n + vl_sys_v + vl_sys_f + vi_index + vi_quot_off, "\\\"", 2 );
				vi_quot_off++;
			} else {
/* [CHAR] */		( char * ) memcpy( vc_sys_new + vl_sys + vl_sys_n + vl_sys_v + vl_sys_f + vi_index + vi_quot_off, &vc_path[ vi_index ], 1 );
			}
		}
		( char * ) memcpy( vc_sys_new + vl_sys + vl_sys_n + vl_sys_v + vl_sys_f + vl_path + vi_quot, "\"", 1 );	/* copy ["]	*/
		vc_sys_new[ vl_sys + vl_sys_n + vl_sys_v + vl_sys_f + vl_path + vi_quot + 1 ] = '\0';			/* copy [\0]	*/
//*D printf( "D: [%s]\n", vc_sys_new );
		if ( system( vc_sys_new ) != -1 ) {	/* RUN: shred */
if ( flag.verbose != 0 ) {
	printf( "}\n shred\t: [%s] - ok\n", vc_path );
}
		} else {
printf( "}\n error\t: [%s] - %s (shred)\n", vc_path, strerror( errno ) );
		}
		free( vc_sys_new );	/* malloc-3 */
	} else {			/* malloc-3 */
printf( "}\n error\t: [%s] - %s (malloc-3)\n", vc_path, strerror( errno ) );
	}				/* malloc-3 */
}	/* } sys_shred */
/* ------------- ---- ------
 * function:    path_recursive {
 * rem:         recursive
 * date:        2019-07-30
 * in:
 *  vc_path     path to destination
 * out:
 */
void path_recursive( const char *vc_path ) {
/* ------------- ---- ------
 * Block: Variable
 */
	struct	stat	*vs_stat;
	char		*vc_path_new;
	int		vi_count;
/* ------------- ---- ------
 * Block: Start
 */
if ( flag.verbose != 0 ) {
	printf( " source\t: [%s]\n", vc_path );
}
	vs_stat = ( struct stat * ) malloc( sizeof( struct stat ) );	/* malloc-1 */
	if ( vs_stat != 0 ) {		/* malloc-1 */
		if ( (( flag.link == 0 ) && !( lstat( vc_path, vs_stat ) )) || (( flag.link == 1 ) && !( stat(  vc_path, vs_stat ) )) ) {	/* TYPE */
			if ( S_ISDIR( vs_stat->st_mode ) != 0 ) {       	/* DIR: begin {*/
//*D				printf( " mode\t: [%s] - DIR\n", vc_path );
				/* DIR - check first name RM_FILE */
				vi_count = strlen( vc_path );			/* DIR RM_FILE */
				vc_path_new = ( char * ) malloc( vi_count + 1 + RM_FILE_LENGTH + 1 );	/* malloc-5 */
				if ( vc_path_new != 0 ) {	/* malloc-5 */

					( char * ) memcpy( vc_path_new, vc_path, vi_count );
					( char * ) memcpy( vc_path_new + vi_count, "/", 1 );
					( char * ) memcpy( vc_path_new + vi_count + 1, RM_FILE, RM_FILE_LENGTH );
					vc_path_new[ vi_count + 1 + RM_FILE_LENGTH ] = '\0';
					path_recursive( vc_path_new );	/* RUN recursive */
					free( vc_path_new );	/* malloc-5 */
				} else {			/* malloc-5 */
printf( " error\t: [%s] - %s (malloc-5)\n", vc_path, strerror( errno ) );
				}				/* malloc-5 */
				/* DIR - list files */
				DIR *dp;						/* From: " The GNU C Library Reference Manual" */
				struct dirent *ep;					/* From: " The GNU C Library Reference Manual" */
				dp = opendir( vc_path );				/* From: " The GNU C Library Reference Manual" */
				if ( dp != NULL ) {					/* From: " The GNU C Library Reference Manual" */
					while ( ep = readdir(dp) ) {			/* From: " The GNU C Library Reference Manual" */
						if ( strcmp( ".", ep->d_name ) && strcmp( "..", ep->d_name ) ) {
							vi_count = strlen( vc_path );	/* force */
							vc_path_new = ( char * ) malloc( vi_count + 1 + strlen( ep->d_name ) + 1 );	/* malloc-2 */
							if ( vc_path_new != 0 ) {	/* malloc-2 */
								( char * ) memcpy( vc_path_new, vc_path, vi_count );
								( char * ) memcpy( vc_path_new + vi_count, "/", 1 );
								( char * ) memcpy( vc_path_new + vi_count + 1, ep->d_name, strlen( ep->d_name ) );
								vc_path_new[ vi_count + 1 + strlen( ep->d_name ) ] = '\0';
								path_recursive( vc_path_new );	/* RUN recursive */
								free( vc_path_new );	/* malloc-2 */
							} else {			/* malloc-2 */
printf( " error\t: [%s] - %s (malloc-2)\n", vc_path, strerror( errno ) );
							}				/* malloc-2 */
//*D						} else {	[ . ] [ .. ]
//*D							printf( "[%s] - NO\n", ep->d_name );
						}
					}						/* From: " The GNU C Library Reference Manual" */
					(void) closedir(dp);				/* From: " The GNU C Library Reference Manual" */
				} else {						/* From: " The GNU C Library Reference Manual" */
printf( " error\t: [%s] - %s (dstrem)\n", vc_path, strerror( errno ) );
				}							/* From: " The GNU C Library Reference Manual" */
				;
if ( flag.verbose != 0 ) {
	printf( " dir\t: [%s]\n", vc_path );
}
				sys_remove( vc_path );
				;						/* } DIR: end */
//*D			} else if ( S_ISCHR(  vs_stat->st_mode ) != 0 ) {
//*D				printf( " skip\t: [%s] - CHR\n", vc_path );
//*D			} else if ( S_ISBLK(  vs_stat->st_mode ) != 0 ) {
//*D				printf( " skip\t: [%s] - BLK\n", vc_path );
			} else if ( S_ISREG(  vs_stat->st_mode ) != 0 ) {	/* FILE: begin { */
//*D				printf( " mode\t: [%s] - REG\n", vc_path );
if ( flag.verbose != 0 ) {
	printf( " file\t: [%s]\n", vc_path );
}
				sys_shred( vc_path );
				;						/* } FILE: end */
			} else if ( S_ISFIFO( vs_stat->st_mode ) != 0 ) {	/* FIFO: begin { */
if ( flag.verbose != 0 ) {
	printf( " fifo\t: [%s]\n", vc_path );
}
				sys_remove( vc_path );
				;						/* } FIFO: end */
			} else if ( S_ISLNK( vs_stat->st_mode ) != 0 ) {	/* LINK:  begin { */
if ( flag.verbose != 0 ) {
	printf( " link\t: [%s]\n", vc_path );
}
				sys_remove( vc_path );
				;						/* } LINK: end */
			} else if ( S_ISSOCK( vs_stat->st_mode ) != 0 ) {	/* SOCK: begin { */
if ( flag.verbose != 0 ) {
	printf( " sock\t: [%s]\n", vc_path );
}
				sys_remove( vc_path );
				;						/* } SOCK: end */
			}
		} else {	/* TYPE */
printf( " error\t: [%s] - %s (type)\n", vc_path, strerror( errno ) );
//OFF//if ( flag.verbose != 0 ) {
//OFF//		printf( " unknow\t: [%s]\n", vc_path );
//OFF//}
//OFF//			sys_remove( vc_path );					/* UNKNOW */
		}		/* TYPE */
		free( vs_stat );	/* malloc-1 */
	} else {			/* malloc-1 */
printf( " error\t: [%s] - %s (malloc-1)\n", vc_path, strerror( errno ) );
	}				/* malloc-1 */
/* ------------- ---- ------
 * Block: Exit
 */
}	/* } path_recursive */

/* ------------- ---- ------ *
 * function:    main {
 * rem:         main function
 * date:        2019-07-23
 * in:
 *  vc_path     path to destination
 * out:
 */
int main( int argc, char *argv[] ) {
/* ------------- ---- ------
 * Block: Variable
 */
	int	vi_sh_path;			/* PATH - number of shell parametr */
	int	vi_count;
	char	*vc_path;
	time_t	mAd_time_b;
	time_t	mAd_time_e;

/* show : license */
        f_copy();
        sleep(1);
        file_elf = argv[0];

/* find : --help -h */
	for ( int vi_count = 0; vi_count < argc; vi_count++ ) {
		if ( ( ! strcmp( "-h", argv[ vi_count ] ) ) || ( ! strcmp( "--help", argv[ vi_count ] ) ) ) {
			f_help();
			exit( 0 );
			break;
		}
	}
/* find : --yes -y */
	flag.yes	= 0;
	for ( vi_count = 0; vi_count < argc; vi_count++ ) {
		if ( ( ! strcmp( "-y", argv[ vi_count ] ) ) || ( ! strcmp( "--yes", argv[ vi_count ] ) ) ) {
			printf( " yes\t: [%s]\n", argv[ vi_count ] );
			flag.yes	= 1;
			break;
		}
	}
/* find : --nowait -n */
	flag.nowait	= 0;
	for ( vi_count = 0; vi_count < argc; vi_count++ ) {
		if ( ( ! strcmp( "-n", argv[ vi_count ] ) ) || ( ! strcmp( "--nowait", argv[ vi_count ] ) ) ) {
			printf( " nowait\t: [%s]\n", argv[ vi_count ] );
			flag.nowait	= 1;
			break;
		}
	}
/* find : --verbose -v */
	flag.verbose	= 0;
	for ( vi_count = 0; vi_count < argc; vi_count++ ) {
		if ( ( ! strcmp( "-v", argv[ vi_count ] ) ) || ( ! strcmp( "--verbose", argv[ vi_count ] ) ) ) {
			printf( " verbose: [%s]\n", argv[ vi_count ] );
			flag.verbose	= 1;
			break;
		}
	}
/* find : --iterdef -i */
	flag.iterdef	= 0;
	for ( vi_count = 0; vi_count < argc; vi_count++ ) {
		if ( ( ! strcmp( "-i", argv[ vi_count ] ) ) || ( ! strcmp( "--iterdef", argv[ vi_count ] ) ) ) {
			printf( " iterdef: [%s]\n", argv[ vi_count ] );
			flag.iterdef	= 1;
			break;
		}
	}
/* find : --user -u */
	flag.user	= 0;
	for ( vi_count = 0; vi_count < argc; vi_count++ ) {
		if ( ( ! strcmp( "-u", argv[ vi_count ] ) ) || ( ! strcmp( "--user", argv[ vi_count ] ) ) ) {
			printf( " user\t: [%s]\n", argv[ vi_count ] );
			flag.user	= 1;
			break;
		}
	}
/* find : --link -l */
	flag.link	= 0;
	for ( vi_count = 0; vi_count < argc; vi_count++ ) {
		if ( ( ! strcmp( "-l", argv[ vi_count ] ) ) || ( ! strcmp( "--link", argv[ vi_count ] ) ) ) {
			printf( " link\t: [%s]\n", argv[ vi_count ] );
			flag.link	= 1;
			break;
		}
	}
/* find : Find PATH in shell  */
	vi_sh_path = 0;
	for ( vi_count = 0; vi_count < argc; vi_count++ ) {
		if ( ( ! strcmp( "-p", argv[ vi_count ] ) ) || ( ! strcmp( "--path", argv[ vi_count ] ) ) ) {
			vi_sh_path = vi_count + 1;
			printf( " found\t: [%s]\n", argv[ vi_sh_path ] );
			break;
		}
	}

/* check root access  */
	if ( getuid() == 0 ) {
		printf( " access\t: root\n" );
	} else if ( flag.user == 1 ) {
		printf( " access\t: not-root [%d]\n", getuid() );
	} else {
		printf( " access\t: need root!\n" );
		f_help();
		goto m_exit;
	}

/* RUN */
	if ( ( flag.yes != 0 ) && ( vi_sh_path != 0 ) && ( vi_sh_path < argc ) ){
/* WARNINT TimeOut { */
		printf( "\033[1;33;40m-------------------------\033[0m\n"
			"\033[1;31;40m! ! ! W A R N I N G ! ! !\033[0m\n"
			"\033[1;33;40m-------------------------\n"
			"\033[0m" );
		time( &mAd_time_b );
		mAd_time_e = mAd_time_b;
		while ( ( mAd_time_e - mAd_time_b < 15 ) && ( flag.nowait == 0 ) ) {
			printf( "\033[1;33;40mwait Ctrl+C %2d sec...\033[0m\r", 15 - ( mAd_time_e - mAd_time_b ) );
			time( &mAd_time_e );
		}
		printf( "                     \r" );
/* } WARNING TimeOut */
		vi_count = strlen( argv[ vi_sh_path ] );
		if ( ! strcmp( "/",  ( argv[ vi_sh_path ] + vi_count - 1 ) ) ) {
			vi_count--;
		}
		vc_path = ( char * ) malloc( vi_count + 1 );	/* malloc-0 */
		if ( vc_path != 0 ) {		/* malloc-0 */
			signal( SIGHUP,    SIG_IGN );   /* 01 : termination, report that the user’s terminal is disconnected */
			signal( SIGINT,    SIG_IGN );   /* 02 : termination, when the user types ctrl+c */
			signal( SIGQUIT,   SIG_IGN );   /* 03 : termination, core dump */
			signal( SIGILL,    SIG_IGN );   /* 04 : error, illegal instruction */
			signal( SIGTRAP,   SIG_IGN );   /* 05 : error, breakpoint instruction */
			signal( SIGABRT,   SIG_IGN );   /* 06 : error, calling abort  */
			signal( SIGBUS,    SIG_IGN );   /* 07 : error, invalid pointer is dereferenced */
			signal( SIGFPE,    SIG_IGN );   /* 08 : error, fatal arithmetic error */
//*off			signal( SIGKILL,   SIG_IGN );   /* 09 : termination, cannot be handled or ignored */
//*off			signal( SIGUSR1,   SIG_IGN );   /* 10 : miscellaneous, for you to use any way you want */
			signal( SIGSEGV,   SIG_IGN );   /* 11 : error, read or write outside the memory */
//*off			signal( SIGUSR2,   SIG_IGN );   /* 12 : miscellaneous, for you to use any way you want */
			signal( SIGPIPE,   SIG_IGN );   /* 13 : operation error, broken pipe */
			signal( SIGALRM,   SIG_IGN );   /* 14 : alarm, indicates expiration of a timer that measures real or clock time */
			signal( SIGTERM,   SIG_IGN );   /* 15 : termination, cause program termination */
			signal( SIGSTKFLT, SIG_IGN );   /* 16 : */
			signal( SIGCHLD,   SIG_IGN );   /* 17 : job, to a parent process whenever one of its child processes terminates or stops.*/
			signal( SIGCONT,   SIG_IGN );   /* 18 : job, make it continue */
			signal( SIGSTOP,   SIG_IGN );   /* 19 : job, stops the process */
			signal( SIGTSTP,   SIG_IGN );   /* 20 : job, interactive stop signal */
			signal( SIGTTIN,   SIG_IGN );   /* 21 : job, process in a background job tries to read from the terminal */
			signal( SIGTTOU,   SIG_IGN );   /* 22 : job, in a background job attempts to write to the terminal or set its modes*/
			signal( SIGURG,    SIG_IGN );   /* 23 : asynchronous i/o, when “urgent” or out-of-band data arrives on a socket */
			signal( SIGXCPU,   SIG_IGN );   /* 24 : operation error, CPU time limit exceeded */
			signal( SIGXFSZ,   SIG_IGN );   /* 25 : operation error, file size limit exceeded */
			signal( SIGVTALRM, SIG_IGN );   /* 26 : alarm, indicates expiration of a timer that measures CPU time */
			signal( SIGPROF,   SIG_IGN );   /* 27 : alarm, indicates expiration of a timer that measures both CPU time */
//*off			signal( SIGWINCH,  SIG_IGN );   /* 28 : miscellaneous, window size change */
			signal( SIGIO,     SIG_IGN );   /* 29 : asynchronous i/o, sent when a file descriptor is ready */
			signal( SIGPWR,    SIG_IGN );   /* 30 : */
			signal( SIGSYS,    SIG_IGN );   /* 31 : error, bad system call */
//*off			34-49 SIGRTMIN...+NN
//*off			50-64 SIGRTMAX...-NN
			( char * ) memcpy( vc_path, argv[ vi_sh_path ], vi_count );
			vc_path[ vi_count ] = '\0';
			path_recursive( vc_path );	/* RUN recursive */
			free( vc_path );	/* malloc-0 */
		} else {			/* malloc-0 */
printf( " error\t: [%s] - %s (malloc-0)\n", argv[ vi_sh_path ], strerror( errno ) );
		}				/* malloc-0 */
		;
	} else {
		f_help();
	}

m_exit:
	printf( " exit\t: bay.\n" );
}	/* } main */


/* } DavydovMA 2019073000 */
