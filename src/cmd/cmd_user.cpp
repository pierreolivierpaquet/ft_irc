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
			std::cout << "Can't set user: not authenticated/registered." << std::endl;
			// close( client.getFd() );				// To disconnect immediatetly
			// ircserv.clearClient( client.getFd() );	// To disconnect immediatetly
			throw( ERR_NOTREGISTERED );
		}
		return ;
	}
	if( client.isAuthenticatedAs( DEFAULT_AUTH | USER_AUTH ) ) {
		std::cout << "Can't set user: already authenticated/registered." << std::endl;
		throw( ERR_ALREADYREGISTERED );
		return ;
	}
	if ( param.size() < 5) throw ERR_NEEDMOREPARAMS;
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
	if (client.isAuthenticatedAs( FULL_AUTH ) &&
		client.isAuthenticatedAs( WELCOMED_AUTH ) == false) {
		sendMessageLogging(client);
		client.setRegistration( WELCOMED_AUTH );
	}
	return ;
}
