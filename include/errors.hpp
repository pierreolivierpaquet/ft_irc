/******************************************************************************/
/*                                                                            */
/*                                    IRC                                     */
/*                                                                            */
/******************************************************************************/

#ifndef		ERRORS_HPP_
# define	ERRORS_HPP_

# include	"main.hpp"

///	------------------------------------------------------------------- @section MACRO.S

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

/// @link ERR REPLIES: https://www.irchelp.org/protocol/rfc/chapter6.html

# define	ERR_NOTREGISTERED			451
# define	ERR_NEEDMOREPARAMS			461
# define	ERR_ALREADYREGISTERED		462 // If a client tries to sent the PASS command after connection registration has been completed
# define	ERR_PASSWDMISMATCH			464

# define	ERR_NOSUCHNICK				401
# define	ERR_NOSUCHCHANNEL			403
# define	ERR_NOTEXTTOSEND			412
# define	ERR_USERNOTINCHANNEL		441
# define	ERR_NOTONCHANNEL			442
# define	ERR_USERONCHANNEL			443
# define	ERR_BADCHANMASK				476
# define	ERR_CHANOPRIVSNEEDED		482

# define	ERR_NONICKNAMEGIVEN			431
# define	ERR_ERRONEUSNICKNAME		432
# define	ERR_NICKNAMEINUSE			433
# define	ERR_NICKCOLLISION			436 // Same as ERR_NICKNAMEINUSE ??

# endif	/*	ERRORS_HPP_	*/
