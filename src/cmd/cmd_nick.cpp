/******************************************************************************/
/*                                                                            */
/*                                    IRC                                     */
/*                                                                            */
/******************************************************************************/

#include	"main.hpp"

static	void	updateChannels( std::string new_nickname, int client_fd, Server &ircserver ) {
	std::map<std::string, Channel >::iterator	it = ircserver.getChannelsList().begin();
	std::map<std::string, Channel >::iterator	ite = ircserver.getChannelsList().end();

	if (ircserver.getChannelsList().size() != 0) {
		for (; it != ite; ++it) {
			if (it->second.getClientList().find( client_fd ) != it->second.getClientList().end() ) {
				for (	std::map<int, Clients >::iterator it_client = it->second.getClientList().begin();
						it_client != it->second.getClientList().end(); it_client++) {
					if (it_client->first == client_fd) {
							it_client->second.setNickName( new_nickname );
					}
				}
			}
		}
	}
}

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

	updateChannels( client.getNickName(), client.getFd(), ircserv ); // test

	return ;
}
