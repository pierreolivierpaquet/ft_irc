/******************************************************************************/
/*                                                                            */
/*                                    IRC                                     */
/*                                                                            */
/******************************************************************************/

#include	"main.hpp"

/// @brief 
/// @param ircserv 
/// @param client 
/// @param param 
/// @link https://dd.ircdocs.horse/refs/commands/nick
void	nick( Server &ircserv, Clients &client, std::vector< std::string > param ) {
	if ( client.isAuthenticatedAs(DEFAULT_AUTH | PASS_AUTH) == false ) {
		if (client.validateServerPassword( ircserv ) == false) {
			std::cout << "NEED TO KICK OUT/ CLOSE CLIENT FD" << std::endl;
			return ;
		}
	}
	if (param.size() < 2) {
		// send() ERR_NONICKNAMEGIVEN
			std::string temp(":127.0.0.1 " + client.getPort() + " " + std::to_string( ERR_NONICKNAMEGIVEN ) + " " + client.getNickName() + " :No nickname given\r\n");
			send( client.getFd(), temp.c_str(), temp.size(), 0 );
			return ;
	} else if (ircserv.checkAvailableNickName( param.at( 1 ) ) == false) {
		// send() ERR_NICKNAMEINUSE
			std::string temp(":127.0.0.1 " + client.getPort() + " " + std::to_string( ERR_NICKNAMEINUSE ) + " " + client.getNickName() + " :Nickname already in use\r\n");
			send( client.getFd(), temp.c_str(), temp.size(), 0 );
			return ;
	} else if (param.at( 1 ).find_first_not_of( NICKNAME_CHAR ) != NOT_FOUND) {
		// send() ERR_ERRONEUSNICKNAME
			std::string temp(":127.0.0.1 " + client.getPort() + " " + std::to_string( ERR_ERRONEUSNICKNAME ) + " " + client.getNickName() + " :Erroneous nickname\r\n");
			send( client.getFd(), temp.c_str(), temp.size(), 0 );
			return ;
	} else {
		client.setNickName( param.at( 1 ).substr(0, 9) );
		client.setRegistration( NICK_AUTH );
	}
	if (client.isAuthenticatedAs( FULL_AUTH )) { 
		// send() 
			std::string temp(":127.0.0.1 " + client.getPort() + " NICK " + param.at( 1 ) + "\r\n");
			send( client.getFd(), temp.c_str(), temp.size(), 0 );
	}
	return ;
}
