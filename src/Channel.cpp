/******************************************************************************/
/*                                                                            */
/*                                    IRC                                     */
/*                                                                            */
/******************************************************************************/

#include "Channel.hpp"

int Channel::addClient( Clients client ) {
	std::map<int, Clients>::iterator it;

	for (it = _clientList.begin(); it != _clientList.end(); ++it) {
		if (it->first == client.getFd())
			return (1);
	}

	_clientList.insert(std::make_pair(client.getFd(), client));
	return (0);
}

std::string Channel::getName( void ) {
	return (_name);
}

std::map<int, Clients> & Channel::getClientList( void ) {
	return (_clientList);
}

void Channel::setOper( Clients & client ) {
	_operList.push_back(client.getFd());
}

std::vector<int> & Channel::getOper( void ) {
	return (_operList);
}

Channel::Channel( std::string name): _name(name) {}

Channel::~Channel( void ) {}
