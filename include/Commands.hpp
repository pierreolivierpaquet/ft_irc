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

void	pass( Server &ircserv, Clients &client, std::vector< std::string > param );
void	user( Server &ircserv, Clients &client, std::vector< std::string > param );
void	nick( Server &ircserv, Clients &client, std::vector< std::string > param );

#endif	/*	COMMANDS_HPP_	*/
