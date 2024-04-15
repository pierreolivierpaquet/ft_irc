/******************************************************************************/
/*                                                                            */
/*                                    IRC                                     */
/*                                                                            */
/******************************************************************************/

#include "Commands.hpp"

typedef std::vector< std::pair<std::string, std::string> > t_vec_pair;

void channelJoin( Channel *channel, Clients &client, std::string name ) {
	std::map<int, Clients>::iterator it;
	std::string str = getSendID(client) + " JOIN " + name + "\r\n";

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
	std::string str4 = ":127.0.0.1 366 " + client.getNickName() + " " + channel->getName() + " :END if /NAMES list.\r\n";
	send(client.getFd(), str4.c_str(), str4.length(), 0);
}

static bool parseJoinRequest(Channel *channel, Clients &client, std::vector<std::string> param, std::string key) {
	if (channel->isMode(LIMIT_MODE) == true) {
		if (channel->checkLimit() == true) return (sendError(ERR_CHANNELISFULL, client, param), false);
	} else if (channel->isMode(KEY_MODE) == true) {
		if (key == "") return (sendError(ERR_NEEDMOREPARAMS, client, param), false);
		else if (channel->checkKey(key) == false) return (sendError(ERR_BADCHANNELKEY, client, param), false);
	} else if (channel->isMode(INVITE_MODE) == true) {
		if (channel->isInvited(client) == false) return (sendError(ERR_INVITEONLYCHAN, client, param), false);
		channel->deleteWhiteList(client);
	}
	return (true);
}

static t_vec_pair	splitNames(std::string names, std::string key) {
	t_vec_pair			tokens;
	std::stringstream	str_names(names);
	std::stringstream	str_key(key);
	std::string			token_name;
	std::string			token_key;

	while (std::getline(str_names, token_name, ',')) {
		if (token_name.find("#") != 0) {
			std::cout << "Error: Bad channel format!" << std::endl;
			std::getline(str_key, token_key, ',');
			continue ;
		}
		if (!std::getline(str_key, token_key, ','))
			token_key = "";
		
		tokens.push_back(std::make_pair(token_name, token_key));
	}
	
	return (tokens);
}

void channel( Server &ircserv, Clients &client, std::vector< std::string > param ) {
	int channelExist = 0;

	Channel *channel = NULL;
	t_vec_pair tokens;

	if (param.size() < 3)
		tokens = splitNames(param.at(1), "");
	else
		tokens = splitNames(param.at(1), param.at(2));

	for (size_t i = 0; i < tokens.size(); i++) {
		channelExist = ircserv.addChannel(tokens.at(i).first);
		ircserv.getChannel(tokens.at(i).first, &channel);

		if (!parseJoinRequest(channel, client, param, tokens.at(i).second))
			continue ;

		if (channelExist == 0)
			channel->setOper(client);

		if (channel->addClient(client) == 1) throw ERR_USERONCHANNEL;

		channelJoin(channel, client, channel->getName());

		std::string str2 = ":127.0.0.1 332 " + client.getNickName() + " " + channel->getName() + " " + channel->getTopic() + "\r\n";
		send(client.getFd(), str2.c_str(), str2.length(), 0);
		makeUserListSend(channel, client, channelExist);
		// std::string str4 = ":127.0.0.1 366 " + client.getNickName() + " " + channel->getName() + " :END if /NAMES list.\r\n";
		// send(client.getFd(), str4.c_str(), str4.length(), 0);
	}
}
