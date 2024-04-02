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

	if (param.at(1).find("#") == 0) {
		for (it = ircserv.getChannel(param.at(1)).getClientList().begin(); it != ircserv.getChannel(param.at(1)).getClientList().end(); ++it) {
			if (it->first != client.getFd()) {
				send_str = param.at(1) + " :" + param.at(2) + "\r\n";
				sendPrivateMessage(getSendID(client), send_str, it->first);
			}
				
		}
	} else if (ircserv.getClientWithName(param.at(1)) != NULL) { // privmsg working but not with multiple target.
		send_str = param.at(1) + " :" + param.at(2) + "\r\n";
		sendPrivateMessage(getSendID(client), send_str.c_str(), ircserv.getClientWithName(param.at(1))->getFd());
	} else
		std::cout << "Destination non existant!" << std::endl;
}
