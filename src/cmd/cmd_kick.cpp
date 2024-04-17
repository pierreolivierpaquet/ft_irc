/******************************************************************************/
/*                                                                            */
/*                                    IRC                                     */
/*                                                                            */
/******************************************************************************/

#include	"main.hpp"

void channelKick( Channel *channel, Clients &client, std::vector< std::string > param ) {
	std::map<int, Clients >::iterator it;
	std::string str = getSendID(client) + " KICK " + param.at(1) + ' ' + param.at(2) + ' ' + " :";

	if (param.size() > 3)
		str += param.at(3) + "\r\n";
	else
		str += client.getNickName() + "\r\n";

	for (it = channel->getClientList().begin(); it != channel->getClientList().end(); ++it) {
		send(it->first, str.c_str(), str.length(), 0);
	}
}

void	kick( Server &ircserv, Clients &client, std::vector< std::string > param ) {
	if (param.size() < 3) throw ERR_NEEDMOREPARAMS;

	Channel *targetChannel;

	if (!ircserv.getChannel(param.at(1), &targetChannel)) throw ERR_NOSUCHCHANNEL;

	if (targetChannel->findClient(client.getNickName()) != -1) {
		if ( targetChannel->findOperator(client.getFd()) == targetChannel->getOper().end()) throw ERR_CHANOPRIVSNEEDED;
		Clients *targetClient;

		targetClient = ircserv.getClientWithName(param.at(2));
		if (!targetClient) throw ERR_NOSUCHNICK;
		if (targetChannel->findClient(param.at(2)) == -1) throw ERR_USERNOTINCHANNEL;
		channelKick(targetChannel, client, param);
		targetChannel->deleteClient(*targetClient);
		targetChannel->deleteOper(*targetClient);
	}
}
