/******************************************************************************/
/*                                                                            */
/*                                    IRC                                     */
/*                                                                            */
/******************************************************************************/

#ifndef		COMMANDS_HPP_
# define	COMMANDS_HPP_

# include	"main.hpp"
# define RPL_NOTOPIC	331
# define RPL_TOPIC		332
# define RPL_TOPICTIME	333


/// @note Forward declaration.
class Server;

///	------------------------------------------------------------------- @section

void	execute( Server &ircserv, Clients &client_data );

void	pass( Server &ircserv, Clients &client, std::vector< std::string > param );
void	user( Server &ircserv, Clients &client, std::vector< std::string > param );
void	nick( Server &ircserv, Clients &client, std::vector< std::string > param );
void	sendMessage(Clients client);

#endif	/*	COMMANDS_HPP_	*/
