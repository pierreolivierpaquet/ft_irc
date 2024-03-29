/******************************************************************************/
/*                                                                            */
/*                                    IRC                                     */
/*                                                                            */
/******************************************************************************/

# include	"main.hpp"

void	mode(Server &ircserv, Clients &client, std::vector< std::string > param ) {
	//	CHECK IF THE USER CAN EXECUTE A MODE CHANGE (is operator)
	if (param.size() < 3) {
		// send() ERR_NEEDMOREPARAMS
			std::string temp(":127.0.0.1 " + client.getPort() + " " + std::to_string( ERR_NEEDMOREPARAMS ) + " " + client.getNickName() + " :Need more parameters\r\n");
			send( client.getFd(), temp.c_str(), temp.size(), 0 );
			return ;
	} else if ( param.at(1).find("#") == NOT_FOUND) {
		std::cout << "MODE MISSING CHANNEL NAME DELETE THIS" << std::endl;
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
		set = +1;
	} else {
		set = -1;
	}
	// Locate the right channel.
	//	Iterate throught the string, and for each letter, send to Mode member func of channel
	/*	channel.mode( (*it) * set )	*/
	return ;
}