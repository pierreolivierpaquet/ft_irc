/******************************************************************************/
/*                                                                            */
/*                                    IRC                                     */
/*                                                                            */
/******************************************************************************/

#include "Commands.hpp"

void	part( Server &ircserv, Clients &client, std::vector< std::string > param ) {
	std::string send_str = getSendID(client) + " PART " + param.at(1);
	std::map<int, Clients>::iterator it;
	Channel *channel = NULL;

	if (ircserv.getChannel(param.at(1), &channel) == false) throw ERR_NOSUCHCHANNEL;
	if (channel->findClient(client.getNickName()) == -1) throw ERR_NOTONCHANNEL;

	if (param.size() > 2) {
		send_str += " :" + param.at(2);
	}
	send_str += "\r\n";

	for (it = channel->getClientList().begin(); it != channel->getClientList().end(); ++it) {
		send(it->first, send_str.c_str(), send_str.length(), 0);
	}

	channel->deleteClient(client);
	channel->deleteOper(client);

	if (channel->getClientList().size() == 0)
		ircserv.deleteChannel(channel->getName());
}
