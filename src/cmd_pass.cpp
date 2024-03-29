/******************************************************************************/
/*                                                                            */
/*                                    IRC                                     */
/*                                                                            */
/******************************************************************************/

#include	"main.hpp"

/// @brief 
/// @param
/// @link https://dd.ircdocs.horse/refs/commands/pass
void	pass( Server &ircserv, Clients &client, std::vector< std::string > param ) {
	if ( client.isAuthenticatedAs( DEFAULT_AUTH | PASS_AUTH ) ) {
			std::string temp(":127.0.0.1 " + client.getPort() + " " + std::to_string( ERR_ALREADYREGISTERED ) + " " + client.getNickName() + " :Already registered\r\n");
			send( client.getFd(), temp.c_str(), temp.size(), 0 );
		std::cout << "ALREADY REGISTERED DELETE THIS" << std::endl;
		return ;
	}
	if ( param.size() < 2 && ircserv.checkPassword( EMPTY_STR ) == 0 ) {
		client.setRegistration( PASS_AUTH );
	} else if (param.size() < 2) {
			std::string temp(":127.0.0.1 " + client.getPort() + " " + std::to_string( ERR_NEEDMOREPARAMS ) + " " + client.getNickName() + " :Need more parameters\r\n");
			send( client.getFd(), temp.c_str(), temp.size(), 0 );
	}
	if (ircserv.checkPassword( param.at( 1 ) ) == 0) {
		client.setRegistration( PASS_AUTH );
	} else {
			std::string temp(":127.0.0.1 " + client.getPort() + " " + std::to_string( ERR_PASSWDMISMATCH ) + " " + client.getNickName() + " :Password mismatch\r\n");
			send( client.getFd(), temp.c_str(), temp.size(), 0 );
	}

	return;
}
