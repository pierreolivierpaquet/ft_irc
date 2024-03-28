/******************************************************************************/
/*                                                                            */
/*                                    IRC                                     */
/*                                                                            */
/******************************************************************************/

#include "main.hpp"

/// @link https://dd.ircdocs.horse/refs/commands/user
void	user( Server &ircserv, Clients &client, std::vector< std::string > param ) {
	
	static_cast< void >( ircserv );

	if ((client.getRegistration() & 0b0010) != 0b0010) {
		// send() ERR_NOTREGISTERED
		std::cout << "NOT REGISTERED (password) DELETE THIS" << std::endl;
		return ;
	}
	if ((client.getRegistration() & 0b1000 ) == 0b1000) {
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
	--ite;
	client.setMode( std::atoi( (--ite)->c_str() ) ); // Eventually transfers to bitfield
	client.setRegistration( 0b1000 );
	if (client.getRegistration() == 0b1111)
		sendMessageLogging(client);
	return ;
}
