/******************************************************************************/
/*                                                                            */
/*                                    IRC                                     */
/*                                                                            */
/******************************************************************************/

#include "Commands.hpp"

void	part( Server &ircserv, Clients &client, std::vector< std::string > param ) {
	std::string send_str = getSendID(client) + " PART " + param.at(1);
	std::map<int, Clients>::iterator it;
	Channel &channel = ircserv.getChannel(param.at(1));

	if (param.size() > 2) {
		send_str += " :" + param.at(2);
	}
	send_str += "\r\n";

	for (it = channel.getClientList().begin(); it != channel.getClientList().end(); ++it) {
		send(it->first, send_str.c_str(), send_str.length(), 0);
	}
	// not working 
	channel.deleteClient(client);
	//
}
