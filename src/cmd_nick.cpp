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

	if ( client.isAuthenticatedAs( DEFAULT_AUTH | PASS_AUTH ) == false ) {
		if (client.validateServerPassword( ircserv ) == false) {
			std::cout << "Can't set nickame: not registered." << std::endl;
			close( client.getFd() );
			ircserv.clearClient( client.getFd() );
			throw( ERR_NOTREGISTERED );
			return ;
		}
	}

	if (param.size() < 2) throw ERR_NONICKNAMEGIVEN;

	if (ircserv.checkAvailableNickName( param.at( 1 ) ) == false) {
		throw ERR_NICKNAMEINUSE;
	} else if (param.at( 1 ).find_first_not_of( NICKNAME_CHAR ) != NOT_FOUND) {
		throw ERR_ERRONEUSNICKNAME;
	} else {
		client.setNickName( param.at( 1 ).substr(0, 9) );
		client.setRegistration( NICK_AUTH );
	}

	if (client.isAuthenticatedAs( FULL_AUTH ) &&
		client.isAuthenticatedAs( WELCOMED_AUTH ) == false) {
		sendMessageLogging(client);
		client.setRegistration( WELCOMED_AUTH );
	}

	std::vector<int> advise_client = ircserv.getConcernedClients( client );
	std::string str2 = ":" + client.getNickNamePrev() + "!" + client.getRealName() + "@127.0.0.1:" + client.getPort() + " NICK :" + client.getNickName() + "\r\n";
	for (std::vector<int>::iterator it = advise_client.begin(); it != advise_client.end(); it++) {
		send(*it, str2.c_str(), str2.length(), 0);
	}
	send(client.getFd(), str2.c_str(), str2.length(), 0);

	return ;
}
