/******************************************************************************/
/*                                                                            */
/*                                    IRC                                     */
/*                                                                            */
/******************************************************************************/

#ifndef		ERRORS_HPP_
# define	ERRORS_HPP_

# include	"main.hpp"

///	----------------------------------------------------------- @section MACRO.S

# define	ERR				"error"
# define	ERR_MSG			"error: "

# define	MISSING_PARAM	"specify <password> and <port>."
# define	EXCEEDING_PARAM	"too many arguments."
# define	INVALID_PORT	"invalid port number."

# define	ERR_SOCK_FD		"socket(): creating socket"
# define	ERR_SETSOCKOPT	"setsockopt(): setting socket option(s)."
# define	ERR_FCNTL		"fcntl(): setting flag."
# define	ERR_BIND		"bind(): binding socket with address."
# define	ERR_LISTEN		"listen(): listening to specified port."

# endif	/*	ERRORS_HPP_	*/
