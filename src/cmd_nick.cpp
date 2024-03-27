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
	if (param.size() < 2) {
		// send() ERR_NONICKNAMEGIVEN
	} else if (ircserv.checkAvailableNickName( param.at( 1 ) ) == false) {
		// send() ERR_NICKNAMEINUSE
	} else if (param.at( 1 ).find_first_not_of( NICKNAME_CHAR ) != NOT_FOUND) {
		// send() ERR_ERRONEUSNICKNAME
		std::cout << "BAD CHAR DELETE THIS" << std::endl;
	} else {
		client.setNickName( param.at( 1 ).substr(0, 9) );
		client.setRegistration( 0b0100 );
	}
	if (client.getRegistration() != 0b1111) {
		// Silently accept nick name
		//	send() 
	} else { 
		// send() 
	}
	return ;
}
