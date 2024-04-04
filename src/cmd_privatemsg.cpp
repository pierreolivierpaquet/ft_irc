/******************************************************************************/
/*                                                                            */
/*                                    IRC                                     */
/*                                                                            */
/******************************************************************************/

#include "Commands.hpp"

void sendPrivateMessage(std::string sendID, std::string message, int fd) {
	sendID += " PRIVMSG " + message;
	send(fd, sendID.c_str(), sendID.length(), 0);
}

void privmsg( Server &ircserv, Clients &client, std::vector< std::string > param ) {
	std::map<int, Clients>::iterator it;
	std::string send_str;
	Channel *channel = NULL;

	if (param.size() < 3) throw ERR_NEEDMOREPARAMS;
	if (param.at(1).find("#") == 0) {
		if (ircserv.getChannel(param.at(1), &channel) == false) throw ERR_NOSUCHCHANNEL;
		else if (channel->findClient(client.getNickName()) == -1) throw ERR_NOTONCHANNEL;
		for (it = channel->getClientList().begin(); it != channel->getClientList().end(); ++it) {
			if (it->first != client.getFd()) {
				send_str = param.at(1) + " :" + param.at(2) + "\r\n";
				sendPrivateMessage(getSendID(client), send_str, it->first);
			}
		}
	} else if (ircserv.getClientWithName(param.at(1)) == NULL) {
		throw ERR_NOSUCHNICK;
	} else {
		send_str = param.at(1) + " :" + param.at(2) + "\r\n";
		sendPrivateMessage(getSendID(client), send_str.c_str(), ircserv.getClientWithName(param.at(1))->getFd());
	}
	return ;
}
