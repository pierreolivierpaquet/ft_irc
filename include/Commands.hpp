/******************************************************************************/
/*                                                                            */
/*                                    IRC                                     */
/*                                                                            */
/******************************************************************************/

#ifndef		COMMANDS_HPP_
# define	COMMANDS_HPP_

# include	"main.hpp"
# define	RPL_NOTOPIC			331
# define	RPL_TOPIC			332
# define	RPL_TOPICTIME		333

# define	RPL_CHANNELMODEIS	324

/// @note Forward declaration.
class Server;

///	------------------------------------------------------------------- @section

void	execute( Server &ircserv, Clients &client_data );
void	sendMessageLogging(Clients &client);
void	sendError(const int& errorCode, Clients& client, std::vector< std::string >& param);

void	pass( Server &ircserv, Clients &client, std::vector< std::string > param );
void	user( Server &ircserv, Clients &client, std::vector< std::string > param );
void	nick( Server &ircserv, Clients &client, std::vector< std::string > param );
void	kick( Server &ircserv, Clients &client, std::vector< std::string > param );
void	mode( Server &ircserv, Clients &client, std::vector< std::string > param );
void	topic( Server &ircserv, Clients &client, std::vector< std::string > param );
void	channel( Server &ircserv, Clients &client, std::vector< std::string > param );
void	channelJoin( Server &ircserv, Clients &client, std::string name );
void	sendPrivateMessage( std::string sendID, std::string message, int fd );
void	privmsg( Server &ircserv, Clients &client, std::vector< std::string > param );
void	part( Server &ircserv, Clients &client, std::vector< std::string > param );
void	invite( Server &ircserv, Clients &client, std::vector< std::string > param );
void	quit( Server &ircserv, Clients &client, std::vector< std::string > param );

std::string		getSendID( Clients &client );

#endif	/*	COMMANDS_HPP_	*/

