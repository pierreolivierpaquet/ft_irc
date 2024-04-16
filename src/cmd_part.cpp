/******************************************************************************/
/*                                                                            */
/*                                    IRC                                     */
/*                                                                            */
/******************************************************************************/

#include "Commands.hpp"

static std::vector<std::string>	splitNames(std::string names) {
	std::vector<std::string>	tokens;
	std::stringstream			str_names(names);
	std::string					token_name;

	while (std::getline(str_names, token_name, ',')) {
		if (token_name.find("#") != 0) {
			std::cout << "Error: Bad channel format!" << std::endl;
			continue ;
		}

		tokens.push_back(token_name);
	}

	return (tokens);
}

void	part( Server &ircserv, Clients &client, std::vector< std::string > param ) {
	std::string send_str;
	std::map<int, Clients>::iterator it;
	Channel *channel = NULL;
	std::vector<std::string> tokens;

	tokens = splitNames(param.at(1));

	for (size_t i = 0; i < tokens.size(); i++) {
		if (ircserv.getChannel(tokens.at(i), &channel) == false) {
			sendError(ERR_NOSUCHCHANNEL, client, param);
			continue;
		}

		if (channel->findClient(client.getNickName()) == -1) {
			sendError(ERR_NOTONCHANNEL, client, param);
			continue;
		}

		send_str = getSendID(client) + " PART " + channel->getName();

		if (param.size() > 2) {
			send_str += " " + param.at(2);
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
}
