#include "main.hpp"

void quit( Server &ircserv, Clients &client, std::vector< std::string > param) {
	t_map_Channel &channelsList = ircserv.getChannelsList();
	t_map_Channel::iterator it;
	(void)param;
	for (it = channelsList.begin(); it != channelsList.end(); it++) {
		if (it->second.findClient(client.getNickName()) != -1) {
			std::vector< std::string > chanParam;
			chanParam.push_back("QUIT");
			chanParam.push_back(it->second.getName());
			part(ircserv, client, chanParam);
		}
	}

	ircserv.clearClient(client.getFd());
	close(client.getFd());
		std::cout << "Client quit" << std::endl;
}