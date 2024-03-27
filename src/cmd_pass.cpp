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
	if ((client.getRegistration() & 0b0010) == 0b0010) {
		// send() ERR_ALREADYREGISTERED
		std::cout << "ALREADY REGISTERED DELETE THIS" << std::endl;
		return ;
	}
	if ( param.size() < 2 && ircserv.checkPassword( EMPTY_STR ) == 0 ) {
		client.setRegistration( 0b0010 );
	} else {
		// send() ERR_NEEDMOREPARAM
	}
	if (ircserv.checkPassword( param.at( 1 ) ) == 0) {
		client.setRegistration( 0b0010 );
		//send() 001
	} else {
		// send() ERR_PASSMISMATCH
	}
	
	return;
}
