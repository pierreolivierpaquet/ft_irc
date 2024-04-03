/******************************************************************************/
/*                                                                            */
/*                                    IRC                                     */
/*                                                                            */
/******************************************************************************/

# include	"main.hpp"

/// @brief Determines if the mode is ENABLING or DISABLING a channel mode.
static short	mode_set( std::string parameter ) {
	short	set = 0;

	return ( (parameter.find( "+" ) == 0) ? set + 1 : set - 1 );
}

/// @brief Extracts the correct mode identifier. (MODE_CHAR)
static char	mode_id( std::string parameter ) {
	size_t	index = std::string::npos;

	index = parameter.find_first_of( MODE_CHAR );
	return ( parameter.at( index ) );
}

/// @brief SETS/UNSETS the channel <param[1]> to the specified MODE identifier.
void	mode(Server &ircserv, Clients &client, std::vector< std::string > param ) {
	Channel *channel = NULL;

	if (param.size() < 3) throw ERR_NEEDMOREPARAMS;

	if ( ircserv.getChannel(param.at(1), &channel) == false ) throw ERR_NOSUCHCHANNEL; 
	if (channel->findOperator(client.getFd()) == channel->getOper().end()) {
		std::cout << "SEND() NOT OPERATOR DELETE THIS" << std::endl;
		throw ERR_NOPRIVILEGES;
	}
	if ( param.at(2).size() >= 1 &&
				(param.at(2).find_first_of( CHMOD_CHAR ) != 0 ||
				param.at(2).find_first_of( MODE_CHAR ) == NOT_FOUND ||
				param.at(2).find_first_not_of( static_cast< std::string >(CHMOD_CHAR) + MODE_CHAR ) != NOT_FOUND )) {
		std::string temp(":127.0.0.1 " + client.getPort() + " " + std::to_string( ERR_UNKNOWNMODE ) + " " + client.getNickName() + " :Unknown mode char to me for " + param.at(1) + "\r\n");
		send( client.getFd(), temp.c_str(), temp.size(), 0 );
		std::cout << "MODE BAD TOKEN DELETE THIS" << std::endl;
		return ;
	}

	if (param.size() >= 3) {
		channel->ModeOption(	mode_set( param.at( 2 ) ),
								mode_id( param.at( 2 ) ),
								param ) ;
	}

	return ;
}