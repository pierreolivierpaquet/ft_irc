/******************************************************************************/
/*                                                                            */
/*                                    IRC                                     */
/*                                                                            */
/******************************************************************************/

#include	"main.hpp"

void	topic( Server &ircserv, Clients &client, std::vector< std::string > param ) {
	if (param.size() < 2) {
		std::string temp(":127.0.0.1 " + client.getPort() + " " + std::to_string( ERR_NEEDMOREPARAMS ) + " " + client.getNickName() + " :Need more parameters\r\n");
		send( client.getFd(), temp.c_str(), temp.size(), 0 );
		return ;
	}
	Channel*	targetChannel = NULL;

	if(!ircserv.getChannel(param.at(1), &targetChannel)) {
		std::string temp(":127.0.0.1 " + client.getPort() + " " + std::to_string( ERR_NOSUCHCHANNEL ) + " " + client.getNickName() + " :No such channel\r\n");
		send( client.getFd(), temp.c_str(), temp.size(), 0 );
		return ;
	}

	if (param.size() == 3) {
		if (targetChannel->findClient(client.getNickName()) != -1) {
			if ( targetChannel->isMode(TOPIC_MODE) && targetChannel->findOperator(client.getFd()) == targetChannel->getOper().end()) {
				std::string temp(":127.0.0.1 " + client.getPort() + " " + std::to_string( ERR_CHANOPRIVSNEEDED ) + " " + client.getNickName() + " :You're not channel operator\r\n");
				send( client.getFd(), temp.c_str(), temp.size(), 0 );
				return;
			}
			targetChannel->setTopic(param.at(2)); // send message back to users??????
		} else {
			std::string temp(":127.0.0.1 " + client.getPort() + " " + std::to_string( ERR_NOTONCHANNEL ) + " " + client.getNickName() + " :Not on channel\r\n");
			send( client.getFd(), temp.c_str(), temp.size(), 0 );
			return ;
		}
	} else if (param.size() == 2) {
		std::string str2 = ":127.0.0.1 332 " + client.getNickName() + " " + param.at(1) + " " + targetChannel->getTopic() + "\r\n";
		send(client.getFd(), str2.c_str(), str2.length(), 0);
	}
}
