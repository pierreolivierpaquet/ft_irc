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

void sendError(const int& errorCode, Clients& client, std::vector< std::string >& param) {
	std::string errMsg (":127.0.0.1 " + client.getPort() + " " + std::to_string(errorCode) + " " + client.getNickName() + " :");
	switch (errorCode) {
		case ERR_CHANNELISFULL:
			errMsg += "Channel is full";
			break;
		case ERR_NEEDMOREPARAMS:
			errMsg += "Need more parameters";
			break;
		case ERR_BADCHANNELKEY:
			errMsg += "Bad channel key";
			break;
		case ERR_INVITEONLYCHAN:
			errMsg += "This is an invite only channel";
			break;
		case ERR_USERONCHANNEL:
			errMsg += "User already in channel";
			break;
		case ERR_NOTONCHANNEL:
			errMsg += "Not on channel";
			break;
		case ERR_NOSUCHNICK:
			errMsg += "No such nickname";
			break;
		case ERR_CHANOPRIVSNEEDED:
			errMsg += "You're not channel operator";
			break;
		case ERR_NOSUCHCHANNEL:
			errMsg += "No such channel";
			break;
		case ERR_USERNOTINCHANNEL:
			errMsg += "User not in channel";
			break;
		case ERR_NOPRIVILEGES:
			errMsg += "Permission Denied - You're not an IRC operator";
			break;
		case ERR_NONICKNAMEGIVEN:
			errMsg += "No nickname given";
			break;
		case ERR_NICKNAMEINUSE:
			errMsg += "Nickname already in use";
			break;
		case ERR_ERRONEUSNICKNAME:
			errMsg += "Erroneous nickname";
			break;
		case ERR_ALREADYREGISTERED:
			errMsg += "Already registered";
			break;
		case ERR_PASSWDMISMATCH:
			errMsg += "Password mismatch";
			break;
		case ERR_UNKNOWNCOMMAND:
			errMsg += "Unknown command";
			break;
		case ERR_UNKNOWNMODE:
			errMsg += "Unknown mode char to me for " + param.at(1);
			break;
		case ERR_KEYSET:
			errMsg += "Channel key already set";
			break;
		case ERR_NOTREGISTERED:
			errMsg += "Not registered";
			break;
		default:
			errMsg += "Undefined error message";
	}
	errMsg += CR_LF;
	send( client.getFd(), errMsg.c_str(), errMsg.size(), 0 );
}

void	execute( Server &ircserv, Clients &client_data ) {
	size_t						cr_lf = 0;
	std::string					input;
	std::vector< std::string >	tmp_split;

	input = client_data.getInputBuffer();
	cr_lf = input.find( CR_LF );
	while (cr_lf != NOT_FOUND) {
		tmp_split = cmd::split( client_data, input.substr( 0, cr_lf ) );
		try {
			if (tmp_split.at(0).compare( "PASS" ) == 0) {
				pass( ircserv, client_data, tmp_split );
			} else if (tmp_split.at(0).compare( "NICK" ) == 0 ) {
				nick( ircserv, client_data, tmp_split );
			} else if (tmp_split.at(0).compare( "USER" ) == 0) {
				user( ircserv, client_data, tmp_split );
			} else if (tmp_split.at(0).compare( "JOIN" ) == 0) {
				channel( ircserv, client_data, tmp_split );
			} else if (tmp_split.at(0).compare( "PRIVMSG" ) == 0) {
				privmsg( ircserv, client_data, tmp_split );
			} else if (tmp_split.at(0).compare( "PART" ) == 0) {
				part( ircserv, client_data, tmp_split );
			} else if (tmp_split.at(0).compare( "MODE" ) == 0) {
				mode( ircserv, client_data, tmp_split );
			} else if (tmp_split.at(0).compare( "INVITE" ) == 0) {
				invite( ircserv, client_data, tmp_split );
			} else if (tmp_split.at(0).compare( "TOPIC" ) == 0) {
				topic( ircserv, client_data, tmp_split );
			} else if (tmp_split.at(0).compare( "KICK" ) == 0) {
				kick( ircserv, client_data, tmp_split );
			} else if (tmp_split.at(0).compare( "QUIT" ) == 0) {
				quit( ircserv, client_data, tmp_split );
			} else if (tmp_split.at(0).compare( "PONG" ) == 0) {} else throw ERR_UNKNOWNCOMMAND;
		} catch (int& errorCode) {
			sendError(errorCode, client_data, tmp_split);
		}
		input = input.substr( cr_lf + 2 );
		cr_lf = input.find( CR_LF );
	}
	client_data.trimInputBuffer();
	return ;
}
