/******************************************************************************/
/*                                                                            */
/*                                    IRC                                     */
/*                                                                            */
/******************************************************************************/

#include "Commands.hpp"

void channelJoin( Channel &channel, Clients &client, std::vector< std::string > param ) {
	std::map<int, Clients>::iterator it;
	std::string str = getSend(client) + " JOIN " + param.at(1) + "\r\n";

	for (it = channel.getClientList().begin(); it != channel.getClientList().end(); ++it) {
		if (it->first != client.getFd())
			send(it->first, str.c_str(), str.length(), 0);
	}
}

void channel( Server &ircserv, Clients &client, std::vector< std::string > param ) {
	int channelExist = 0;
	std::string str1 = getSend(client) + " JOIN " + param.at(1) + "\r\n";
	//std::string str2 = ":127.0.0.1 332 " + client.getNickName() + " " + param.at(1) + " :Miscellaneous shit.\r\n";
	std::string str3;
	std::string str4 = ":127.0.0.1 366 " + client.getNickName() + " " + param.at(1) + " :END if /NAMES list.\r\n";
	std::map<int, Clients>::iterator it;
	std::vector<int>::iterator it1;

	if (ircserv.addChannel(param.at(1)) == 1) {
		channelExist = 1;
	} else
		ircserv.getChannel(param.at(1)).setOper(client);
		

	if (ircserv.getChannel(param.at(1)).addClient(client) == 1) {
		std::cout << "User already in the channel!" << std::endl;
		return ;
	}

	channelJoin(ircserv.getChannel(param.at(1)), client, param);
	send(client.getFd(), str1.c_str(), str1.length(), 0);

	std::string str2 = ":127.0.0.1 332 " + client.getNickName() + " " + param.at(1) + " " + ircserv.getChannel(param.at(1)).getTopic() + "\r\n";
    send(client.getFd(), str2.c_str(), str2.length(), 0);
	if (channelExist == 0) {
		str3 = ":127.0.0.1 353 " + client.getNickName() + " = " + param.at(1) + " :@" + client.getNickName() +  "\r\n";
	} else {
		str3 = ":127.0.0.1 353 " + client.getNickName() + " = " + param.at(1) + " :";
		for (it = ircserv.getChannel(param.at(1)).getClientList().begin(); it != ircserv.getChannel(param.at(1)).getClientList().end(); ++it) {
			for (it1 = ircserv.getChannel(param.at(1)).getOper().begin(); it1 != ircserv.getChannel(param.at(1)).getOper().end(); ++it1) {
				if (*it1 == it->second.getFd())
					str3 += "@";
			}
			str3 += it->second.getNickName() + " ";
		}
		str3 += "\r\n";
	}
	send(client.getFd(), str3.c_str(), str3.length(), 0);
    send(client.getFd(), str4.c_str(), str4.length(), 0);
}
