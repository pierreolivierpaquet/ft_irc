/******************************************************************************/
/*                                                                            */
/*                                    IRC                                     */
/*                                                                            */
/******************************************************************************/

#include "Commands.hpp"

void channelJoin( Channel *channel, Clients &client, std::vector< std::string > param ) {
	std::map<int, Clients>::iterator it;
	std::string str = getSendID(client) + " JOIN " + param.at(1) + "\r\n";

	for (it = channel->getClientList().begin(); it != channel->getClientList().end(); ++it) {
		send(it->first, str.c_str(), str.length(), 0);
	}
}

static void makeUserListSend(Channel *channel, Clients &client, int channelExist) {
	std::map<int, Clients>::iterator it;
	std::vector<int>::iterator it1;
	std::string str;

	if (channelExist == 0) {
		str = ":127.0.0.1 353 " + client.getNickName() + " = " + channel->getName() + " :@" + client.getNickName() +  "\r\n";
	} else {
		str = ":127.0.0.1 353 " + client.getNickName() + " = " + channel->getName() + " :";
		for (it = channel->getClientList().begin(); it != channel->getClientList().end(); ++it) {
			for (it1 = channel->getOper().begin(); it1 != channel->getOper().end(); ++it1) {
				if (*it1 == it->second.getFd())
					str += "@";
			}
			str += it->second.getNickName() + " ";
		}
		str += "\r\n";
	}
	send(client.getFd(), str.c_str(), str.length(), 0);
}

static bool parseJoinRequest(Channel *channel, Clients &client, std::vector<std::string> param) {
	if (channel->isMode(LIMIT_MODE) == true) {
		if (channel->checkLimit() == true) {
			std::string temp(":127.0.0.1 " + client.getPort() + " " + std::to_string( ERR_CHANNELISFULL ) + " " + client.getNickName() + " :Channel is full\r\n");
			send( client.getFd(), temp.c_str(), temp.size(), 0 );
			return (false);
		}
	} else if (channel->isMode(KEY_MODE) == true) {
		if (param.size() < 3) {
			std::string temp(":127.0.0.1 " + client.getPort() + " " + std::to_string( ERR_NEEDMOREPARAMS ) + " " + client.getNickName() + " :Need more parameters\r\n");
			send( client.getFd(), temp.c_str(), temp.size(), 0 );
			return (false);
		} else if (channel->checkKey(param.at(2)) == false) {
			std::string temp(":127.0.0.1 " + client.getPort() + " " + std::to_string( ERR_BADCHANNELKEY ) + " " + client.getNickName() + " :Bad channel key\r\n");
			send( client.getFd(), temp.c_str(), temp.size(), 0 );
			return (false);
		}
	} else if (channel->isMode(INVITE_MODE) == true) {
		if (channel->isInvited(client) == false) {
			std::string temp(":127.0.0.1 " + client.getPort() + " " + std::to_string( ERR_INVITEONLYCHAN ) + " " + client.getNickName() + " :This is an invite only channel\r\n");
			send( client.getFd(), temp.c_str(), temp.size(), 0 );
			return (false);
		} else
			channel->deleteWhiteList(client);
	}
	return (true);
}

void channel( Server &ircserv, Clients &client, std::vector< std::string > param ) {
	int channelExist = 0;
	std::string str4 = ":127.0.0.1 366 " + client.getNickName() + " " + param.at(1) + " :END if /NAMES list.\r\n";
	Channel *channel = NULL;

	if (param.at(1).find("#") != 0){
		std::cout << "Error: Bad channel format!" << std::endl;
		return ;
	}

	channelExist = ircserv.addChannel(param.at(1));
	ircserv.getChannel(param.at(1), &channel);

	if (parseJoinRequest(channel, client, param) == false)
		return ;

	if (channelExist == 0)
		channel->setOper(client);
		
	if (channel->addClient(client) == 1) {
		std::string temp(":127.0.0.1 " + client.getPort() + " " + std::to_string( ERR_USERONCHANNEL ) + " " + client.getNickName() + " :already in channel\r\n");
		send( client.getFd(), temp.c_str(), temp.size(), 0 );
		return ;
	}

	channelJoin(channel, client, param);

	std::string str2 = ":127.0.0.1 332 " + client.getNickName() + " " + param.at(1) + " " + channel->getTopic() + "\r\n";
    send(client.getFd(), str2.c_str(), str2.length(), 0);
	makeUserListSend(channel, client, channelExist);
    send(client.getFd(), str4.c_str(), str4.length(), 0);
}
