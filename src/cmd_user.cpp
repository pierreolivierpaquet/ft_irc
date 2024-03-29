/******************************************************************************/
/*                                                                            */
/*                                    IRC                                     */
/*                                                                            */
/******************************************************************************/

#include "main.hpp"

/// @link https://dd.ircdocs.horse/refs/commands/user
void	user( Server &ircserv, Clients &client, std::vector< std::string > param ) {
	if ( client.isAuthenticatedAs( DEFAULT_AUTH | PASS_AUTH ) == false ) {
		if (client.validateServerPassword( ircserv ) == false) {
			// send() ERR_NOTREGISTERED
		}
		return ;
	}
	if( client.isAuthenticatedAs( DEFAULT_AUTH | USER_AUTH ) ) {
		// send() ERR_ALREADYREGISTERED
		std::cout << "ALREADY REGISTERED DELETE THIS" << std::endl;
		return ;
	}
	if ( param.size() < 5) {
		// send() ERR_
	}
	client.setUserName( param.at( 1 ) );
	client.setRealName( param.back() );
	std::vector< std::string >::const_iterator ite = param.end();
	std::vector< std::string >::const_iterator it = param.begin();
	ite--;
	for (; ite != it; ite--) {
		if (ite->compare( "*" ) == 0) {
			break ;
		}
	}
	ite++;
	client.setRealName( *ite );
	client.setRegistration( USER_AUTH );
	return ;
}
