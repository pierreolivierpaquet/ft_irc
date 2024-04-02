/******************************************************************************/
/*                                                                            */
/*                                    IRC                                     */
/*                                                                            */
/******************************************************************************/

# include	"main.hpp"

void	mode(Server &ircserv, Clients &client, std::vector< std::string > param ) {
	Channel *channel = NULL;
	//	CHECK IF THE USER CAN EXECUTE A MODE CHANGE (is operator)
	if (param.size() < 3) {
		// send() ERR_NEEDMOREPARAMS
			std::string temp(":127.0.0.1 " + client.getPort() + " " + std::to_string( ERR_NEEDMOREPARAMS ) + " " + client.getNickName() + " :Need more parameters\r\n");
			send( client.getFd(), temp.c_str(), temp.size(), 0 );
			return ;
	} else if ( ircserv.getChannel(param.at(1), &channel) == false ) {
		std::string temp(":127.0.0.1 " + client.getPort() + " " + std::to_string( ERR_NOSUCHCHANNEL ) + " " + client.getNickName() + " :No such channel\r\n");
		send( client.getFd(), temp.c_str(), temp.size(), 0 );
		return ;
	} else if ( param.at(2).size() > 1 &&
				(param.at(2).find_first_of( CHMOD_CHAR ) != 0 ||
				param.at(2).find_first_not_of( static_cast<std::string>(CHMOD_CHAR) + MODE_CHAR ) != NOT_FOUND )) {
		// +/- not found at thew beginning of token OR character not permitted found
		std::cout << "MODE BAD TOKEN DELETE THIS" << std::endl;
		return ;
	}

	short set;
	if (param.at(2).find( "+" ) == 0) {
		static_cast< void >( ircserv );
		set = +1;
	} else {
		set = -1;
	}

	std::string mode = "";
	char c;
	if (param.size() >= 4) {
		mode = param.at(2);
		c = mode.at( mode.find_first_of( MODE_CHAR ) );
		channel->ModeOption( set, c, param ) ;
	}


	// Locate the right channel.
	/*	channel.mode( (*it) * set )	*/
	return ;
}