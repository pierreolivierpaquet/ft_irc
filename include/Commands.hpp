/******************************************************************************/
/*                                                                            */
/*                                    IRC                                     */
/*                                                                            */
/******************************************************************************/

#ifndef		COMMANDS_HPP_
# define	COMMANDS_HPP_

# include	"main.hpp"

/// @note Forward declaration.
class Server;

///	------------------------------------------------------------------- @section

void	execute( Server &ircserv, Clients &client_data );
void	sendMessageLogging(Clients &client);

void	pass( Server &ircserv, Clients &client, std::vector< std::string > param );
void	user( Server &ircserv, Clients &client, std::vector< std::string > param );
void	nick( Server &ircserv, Clients &client, std::vector< std::string > param );
void	channel( Server &ircserv, Clients &client, std::vector< std::string > param );
void	channelJoin( Server &ircserv, Clients &client, std::vector< std::string > param );
void	privatemsg( std::string sendID, std::string message, int fd );
void	privmsg( Server &ircserv, Clients &client, std::vector< std::string > param );

std::string		getSend( Clients &client );

#endif	/*	COMMANDS_HPP_	*/

