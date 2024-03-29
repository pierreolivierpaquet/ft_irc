/******************************************************************************/
/*                                                                            */
/*                                    IRC                                     */
/*                                                                            */
/******************************************************************************/

#include	"main.hpp"

void	topic( Server &ircserv, Clients &client, std::vector< std::string > param ) {
	if (param.size() < 2) return;

	(void)client;
	Channel targetChannel = ircserv.getChannel(param.at(1));
	targetChannel.setTopic(param.at(2));
	std::cout << BLD_RED << targetChannel.getTopic() << WHI << std::endl;
}
