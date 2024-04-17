/******************************************************************************/
/*                                                                            */
/*                                    IRC                                     */
/*                                                                            */
/******************************************************************************/

#include	"main.hpp"

void	invite( Server &ircserv, Clients &client, std::vector< std::string > param ) {
	Channel *channel = NULL;
	Clients *target;
	std::string str( EMPTY_STR );

	if (param.size() < 3) throw ERR_NEEDMOREPARAMS;
	str = getSendID(client) + " INVITE " + param.at(1) + " " + param.at(2) + "\r\n";

	target = ircserv.getClientWithName(param.at(1));
	if (target == NULL) throw ERR_NOSUCHNICK; 
	if (ircserv.getChannel(param.at(2), &channel) == false)
		send(target->getFd(), str.c_str(), str.length(), 0);
	else if (channel->isMode(INVITE_MODE) == true) {
		if (channel->findOperator(client.getFd()) == channel->getOper().end()) throw ERR_CHANOPRIVSNEEDED;
		channel->addWhiteList(*target);
		send(target->getFd(), str.c_str(), str.length(), 0);
	} else {
		if (channel->findClient(client.getNickName()) == -1) throw ERR_NOTONCHANNEL;
		channel->addWhiteList(*target);
		send(target->getFd(), str.c_str(), str.length(), 0);
	}
}
