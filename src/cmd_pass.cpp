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
		std::cout << "Can't validate password: already registered." << std::endl;
		throw ERR_ALREADYREGISTERED;
	}
	if ( param.size() < 2 && ircserv.checkPassword( EMPTY_STR ) == 0 ) {
		client.setRegistration( PASS_AUTH );
	} else if (param.size() < 2) throw ERR_NEEDMOREPARAMS;
	if (ircserv.checkPassword( param.at( 1 ) ) == 0) {
		client.setRegistration( PASS_AUTH );
	} else throw ERR_PASSWDMISMATCH;
	return;
}
