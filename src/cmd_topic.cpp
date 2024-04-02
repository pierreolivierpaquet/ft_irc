/******************************************************************************/
/*                                                                            */
/*                                    IRC                                     */
/*                                                                            */
/******************************************************************************/

#include	"main.hpp"

void	topic( Server &ircserv, Clients &client, std::vector< std::string > param ) {
	if (param.size() < 2) return;
	Channel targetChannel = ircserv.getChannel(param.at(1));

	if (param.size() == 3) {
		targetChannel.setTopic(param.at(2));
	} else if (param.size() == 2) {
		std::string str2 = ":127.0.0.1 332 " + client.getNickName() + " " + param.at(1) + " " + targetChannel.getTopic() + "\r\n";
		send(client.getFd(), str2.c_str(), str2.length(), 0);
	}
}
