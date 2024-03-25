/******************************************************************************/
/*                                                                            */
/*                                    IRC                                     */
/*                                                                            */
/******************************************************************************/

#include "Channel.hpp"

void Channel::addClient( Clients client ) {
	std::map<int, Clients>::iterator it;

	for (it = _clientList.begin(); it != _clientList.end(); ++it) {
		if (it->first == client.getFd()) {
			std::cout << "Client already in the channel!" << std::endl;
			return;
		}
	}
	
	_clientList.insert(std::make_pair(client.getFd(), client));
}

std::string Channel::getName( void ) {
	return (_name);
}

Channel::Channel( std::string name): _name(name) {}

Channel::~Channel( void ) {}
