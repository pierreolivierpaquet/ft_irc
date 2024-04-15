#include "main.hpp"

void quit( Server &ircserv, Clients &client, std::vector< std::string > param) {
	t_map_Channel &channelsList = ircserv.getChannelsList();
	t_map_Channel::iterator it;
	std::vector <std::string> vecChan;

	for (it = channelsList.begin(); it != channelsList.end(); it++) {
		if (it->second.findClient(client.getNickName()) != -1) {
			vecChan.push_back(it->second.getName());
		}
	}

	for (size_t i = 0; i < vecChan.size(); i++) {
		std::vector< std::string > chanParam;
		chanParam.push_back("PART");
		chanParam.push_back(vecChan.at(i));
		if (param.size() > 1) {
			chanParam.push_back(param.at(1));
		}
		part(ircserv, client, chanParam);
	}

	client.quit();
}
