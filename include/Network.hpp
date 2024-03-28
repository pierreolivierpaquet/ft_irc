/******************************************************************************/
/*                                                                            */
/*                                    IRC                                     */
/*                                                                            */
/******************************************************************************/

#ifndef		NETWORK_HPP_
# define	NETWORK_HPP_

///	------------------------------------------------------------------- @section HEADER.S

# include	"main.hpp"

/*	socket(), getsockname(), setsockopt(), bind(), connect(), listen(),
	accept(), recv(), send() */
# include	<sys/socket.h>

/*	close(), gethostname(), lseek() */
# include	<unistd.h>

/*	fcntl() */
# include	<sys/types.h>
# include	<fcntl.h>

/*	poll() */
# include	<sys/time.h>
# include	<sys/msg.h>
# include	<poll.h>

/*	getprotobyname(), getaddrinfo(), getprotobyname(), freeaddrinfo() */
# include	<netdb.h>

/*	fstat() */
# include	<sys/stat.h>

/*	sigaction(), signal() */
# include	<csignal>

/*	inet_ntoa(), inet_addr(), htons(), htonl(), ntohs(), ntohl() */
# include	<arpa/inet.h>

///	------------------------------------------------------------------- @section MACRO.S



///	------------------------------------------------------------------- @section TYPEDEF.S

typedef	struct pollfd	t_pollfd;

#endif	/*	NETWORK_HPP_	*/
