/******************************************************************************/
/*                                                                            */
/*                                    IRC                                     */
/*                                                                            */
/******************************************************************************/

# include "Commands.hpp"

void	sendMessageLogging(Clients &client) {
	std::string str1 = ":127.0.0.1 001 " + client.getNickName() + " :Welcome to the machine.\r\n";
	std::string str2 = ":127.0.0.1 002 " + client.getNickName() + " :Your host is ft_irc, running version 0.1.\r\n";
	std::string str3 = ":127.0.0.1 003 " + client.getNickName() + " :This server was created now!\r\n";
	std::string str4 = ":127.0.0.1 004 " + client.getNickName() + " :127.0.0.1 ft_irc0.1 * itkol.\r\n";

	send(client.getFd(), str1.c_str(), str1.length(), 0);
	send(client.getFd(), str2.c_str(), str2.length(), 0);
	send(client.getFd(), str3.c_str(), str3.length(), 0);
	send(client.getFd(), str4.c_str(), str4.length(), 0);
}


std::string getSendID( Clients &client ) {
	return ( ":" + client.getNickName() + "!" + client.getRealName() + "@127.0.0.1:" + client.getPort() );
}

void	execute( Server &ircserv, Clients &client_data ) {
	size_t						cr_lf = 0;
	std::string					input;
	std::vector< std::string >	tmp_split;

	input = client_data.getInputBuffer();
	cr_lf = input.find( CR_LF );
	while (cr_lf != NOT_FOUND) {
		tmp_split = cmd::split( input.substr( 0, cr_lf ) );
		/*
			tmp_split >> TOKENIZE + EXECUTION HERE
		*/
		//
		if (tmp_split.at(0).compare( "PASS" ) == 0) {
			pass( ircserv, client_data, tmp_split );
		} else if ( tmp_split.at( 0 ).compare( "NICK" ) == 0 ) {
			nick( ircserv, client_data, tmp_split );
		} else if (tmp_split.at(0).compare( "USER" ) == 0) {
			user( ircserv, client_data, tmp_split );
		} else if (tmp_split.at(0).compare( "JOIN" ) == 0) {
			channel( ircserv, client_data, tmp_split );
		} else if (tmp_split.at(0).compare( "PRIVMSG" ) == 0) {
			privmsg( ircserv, client_data, tmp_split );
		} else if (tmp_split.at(0).compare( "PART" ) == 0) {
			part( ircserv, client_data, tmp_split );
		}
		//
		input = input.substr( cr_lf + 2 ); // '+ 2' Since CR_LF was found.
		cr_lf = input.find( CR_LF );
	}
	client_data.trimInputBuffer(); // DONT CLEAR, BUT TRIM UNTIL \r\n to avoid losing data
	return ;
}
