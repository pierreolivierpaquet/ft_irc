/******************************************************************************/
/*                                                                            */
/*                                    IRC                                     */
/*                                                                            */
/******************************************************************************/

#include	"main.hpp"

void	sendMessage(Clients client) {
	std::string str1 = ":127.0.0.1 001 " + client.getNickName() + " :Welcome to the test\r\n";
	std::string str2 = ":127.0.0.1 002 " + client.getNickName() + " :Your host is ft_irc, running version 0.1\r\n";
	std::string str3 = ":127.0.0.1 003 " + client.getNickName() + " :This server was created now!\r\n";
	std::string str4 = ":127.0.0.1 004 " + client.getNickName() + " :127.0.0.1 ft_irc0.1 * itkol\r\n";

	send(client.getFd(), str1.c_str(), str1.length(), 0);
	send(client.getFd(), str2.c_str(), str2.length(), 0);
	send(client.getFd(), str3.c_str(), str3.length(), 0);	
	send(client.getFd(), str4.c_str(), str4.length(), 0);
}

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
		sendMessage(client);
	} else {
		// send() ERR_NEEDMOREPARAM
	}
	if (ircserv.checkPassword( param.at( 1 ) ) == 0) {
		client.setRegistration( 0b0010 );
		
	} else {
		// send() ERR_PASSMISMATCH
	}
	
	return;
}
