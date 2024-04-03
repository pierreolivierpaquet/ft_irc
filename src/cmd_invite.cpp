/******************************************************************************/
/*                                                                            */
/*                                    IRC                                     */
/*                                                                            */
/******************************************************************************/

#include	"main.hpp"

# define RPL_INVITING 341

void	invite( Server &ircserv, Clients &client, std::vector< std::string > param ) {
	std::string str = getSendID(client) + " INVITE " + param.at(1) + " " + param.at(2) + "\r\n";
	Channel *channel = NULL;
	Clients *target;

	if (param.size() < 3) {
		std::string temp(":127.0.0.1 " + client.getPort() + " " + std::to_string( ERR_NEEDMOREPARAMS ) + " " + client.getNickName() + " :Need more parameters\r\n");
		send( client.getFd(), temp.c_str(), temp.size(), 0 );
		return ;
	}

	target = ircserv.getClientWithName(param.at(1));
	if (target == NULL) {
		std::string temp(":127.0.0.1 " + client.getPort() + " " + std::to_string( ERR_NOSUCHNICK ) + " " + client.getNickName() + " :No such nickname\r\n");
		send( client.getFd(), temp.c_str(), temp.size(), 0 );
		return ;
	}

	if (ircserv.getChannel(param.at(2), &channel) == false)
		send(target->getFd(), str.c_str(), str.length(), 0);
	else if (channel->isMode(INVITE_MODE) == true) {
		if (channel->findOperator(client.getFd()) == channel->getOper().end()) {
			std::string temp(":127.0.0.1 " + client.getPort() + " " + std::to_string( ERR_CHANOPRIVSNEEDED ) + " " + client.getNickName() + " :You're not channel operator\r\n");
			send( client.getFd(), temp.c_str(), temp.size(), 0 );
			return ;
		}
		send(target->getFd(), str.c_str(), str.length(), 0);
		channel->addWhiteList(*target);
	} else {
		if (channel->findClient(client.getNickName()) == -1) {
			std::string temp(":127.0.0.1 " + client.getPort() + " " + std::to_string( ERR_NOTONCHANNEL ) + " " + client.getNickName() + " :User not on channel\r\n");
			send( client.getFd(), temp.c_str(), temp.size(), 0 );
			return ;
		}
		send(target->getFd(), str.c_str(), str.length(), 0);
		channel->addWhiteList(*target);
	}
}
