/******************************************************************************/
/*                                                                            */
/*                                    IRC                                     */
/*                                                                            */
/******************************************************************************/

#include	"main.hpp"

void channelKick( Channel *channel, Clients &client, std::vector< std::string > param ) {
	std::map<int, Clients>::iterator it;
	std::string str = getSendID(client) + " KICK " + param.at(1) + ' ' + param.at(2) + ' ' + " :";

	if (param.size() > 3)
		str += param.at(3) + "\r\n";
	else
		str += client.getNickName() + "\r\n";

	for (it = channel->getClientList().begin(); it != channel->getClientList().end(); ++it) {
		send(it->first, str.c_str(), str.length(), 0);
	}
}

void	kick( Server &ircserv, Clients &client, std::vector< std::string > param ) {
	if (param.size() < 3) {
		std::string temp(":127.0.0.1 " + client.getPort() + " " + std::to_string( ERR_NEEDMOREPARAMS ) + " " + client.getNickName() + " :Need more parameters\r\n");
		send( client.getFd(), temp.c_str(), temp.size(), 0 );
		return ;
	}

	Channel *targetChannel;

	if (!ircserv.getChannel(param.at(1), &targetChannel)) {
		std::string temp(":127.0.0.1 " + client.getPort() + " " + std::to_string( ERR_NOSUCHCHANNEL ) + " " + client.getNickName() + " :No such channel\r\n");
		send( client.getFd(), temp.c_str(), temp.size(), 0 );
		return ;
	}

	if (targetChannel->findClient(client.getNickName()) != -1) {
		if ( targetChannel->findOperator(client.getFd()) == targetChannel->getOper().end()) {
			std::string temp(":127.0.0.1 " + client.getPort() + " " + std::to_string( ERR_CHANOPRIVSNEEDED ) + " " + client.getNickName() + " :You're not channel operator\r\n");
			send( client.getFd(), temp.c_str(), temp.size(), 0 );
			return;
		}
		Clients *targetClient;

		targetClient = ircserv.getClientWithName(param.at(2));
		if (!targetClient) {
			std::string temp(":127.0.0.1 " + client.getPort() + " " + std::to_string( ERR_NOSUCHNICK ) + " " + client.getNickName() + " :No such nickname\r\n");
			send( client.getFd(), temp.c_str(), temp.size(), 0 );
			return;
		}
		if (targetChannel->findClient(param.at(2)) == -1) {
			std::string temp(":127.0.0.1 " + client.getPort() + " " + std::to_string( ERR_USERNOTINCHANNEL ) + " " + client.getNickName() + " :User not in channel\r\n");
			send( client.getFd(), temp.c_str(), temp.size(), 0 );
			return;
		}
		channelKick(targetChannel, client, param);
	}
}
