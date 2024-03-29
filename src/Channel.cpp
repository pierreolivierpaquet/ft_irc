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

void	Channel::setMode( u_int16_t mask ) {
	this->_mode |= mask;
	return ;
}

u_int16_t	Channel::getMode( void ) const {
	return ( this->_mode );
}

bool	Channel::isMode( u_int16_t mode ) const {
	u_int16_t	status = this->getMode() & mode;
	return ( status == mode );
}

Channel::Channel( std::string name): _name(name) {}

Channel::~Channel( void ) {}
