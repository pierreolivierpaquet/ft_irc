/******************************************************************************/
/*                                                                            */
/*                                    IRC                                     */
/*                                                                            */
/******************************************************************************/

#include	"main.hpp"

static void channelTopic( Channel *channel, Clients &client, std::vector< std::string > param ) {
	std::map<int, Clients>::iterator it;
	std::string str = getSendID(client) + " TOPIC " + param.at(1) + ' ' + param.at(2) + "\r\n";

	for (it = channel->getClientList().begin(); it != channel->getClientList().end(); ++it) {
		send(it->first, str.c_str(), str.length(), 0);
	}
}


void	topic( Server &ircserv, Clients &client, std::vector< std::string > param ) {
	if (param.size() < 2) throw ERR_NEEDMOREPARAMS;
	Channel*	targetChannel = NULL;

	if(!ircserv.getChannel(param.at(1), &targetChannel)) throw ERR_NOSUCHCHANNEL; 
	if (param.size() == 3) {
		if (targetChannel->findClient(client.getNickName()) != -1) {
			if ( targetChannel->isMode( TOPIC_MODE ) && targetChannel->findOperator(client.getFd()) == targetChannel->getOper().end()) throw ERR_CHANOPRIVSNEEDED;
			targetChannel->setTopic(param.at(2));
			channelTopic(targetChannel, client, param);
		} else throw ERR_NOTONCHANNEL;
	} else if (param.size() == 2) {
		std::string str2 = ":127.0.0.1 332 " + client.getNickName() + " " + param.at(1) + " " + targetChannel->getTopic() + "\r\n";
		send(client.getFd(), str2.c_str(), str2.length(), 0);
	}
}
