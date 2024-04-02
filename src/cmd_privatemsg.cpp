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

	if (param.size() < 3) {
		std::string temp(":127.0.0.1 " + client.getPort() + " " + std::to_string( ERR_NEEDMOREPARAMS ) + " " + client.getNickName() + " :Need more parameters\r\n");
		send( client.getFd(), temp.c_str(), temp.size(), 0 );
		return ;
	}

	if (param.at(1).find("#") == 0) {
		if (ircserv.getChannel(param.at(1), &channel) == false) {
			std::string temp(":127.0.0.1 " + client.getPort() + " " + std::to_string( ERR_NOSUCHCHANNEL ) + " " + client.getNickName() + " :No such channel\r\n");
			send( client.getFd(), temp.c_str(), temp.size(), 0 );
			return ;
		}
		for (it = channel->getClientList().begin(); it != channel->getClientList().end(); ++it) {
			if (it->first != client.getFd()) {
				send_str = param.at(1) + " :" + param.at(2) + "\r\n";
				sendPrivateMessage(getSendID(client), send_str, it->first);
			}
		}
	} else if (ircserv.getClientWithName(param.at(1)) == NULL) {
		std::string temp(":127.0.0.1 " + client.getPort() + " " + std::to_string( ERR_NOSUCHNICK ) + " " + client.getNickName() + " :No such nickname\r\n");
		send( client.getFd(), temp.c_str(), temp.size(), 0 );
		return ;
	}
	send_str = param.at(1) + " :" + param.at(2) + "\r\n";
	sendPrivateMessage(getSendID(client), send_str.c_str(), ircserv.getClientWithName(param.at(1))->getFd());
}
