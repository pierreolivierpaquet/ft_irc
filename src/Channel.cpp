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

void	Channel::mode( char mode ) {
	switch (mode) {
		case ( 'i' * -1 ) : this->unsetMode( ~INVITE_MODE );	break;
		case ( 't' * -1 ) : this->unsetMode( ~TOPIC_MODE );		break;
		case ( 'k' * -1 ) : this->unsetMode( ~KEY_MODE );		break;
		case ( 'o' * -1 ) : this->unsetMode( ~OPERATOR_MODE );	break;
		case ( 'l' * -1 ) : this->unsetMode( ~LIMIT_MODE );		break;
		case ( 'i' ) : this->setMode( INVITE_MODE );			break;
		case ( 't' ) : this->setMode( TOPIC_MODE );				break;
		case ( 'k' ) : this->setMode( KEY_MODE );				break;
		case ( 'o' ) : this->setMode( OPERATOR_MODE );			break;
		case ( 'l' ) : this->setMode( LIMIT_MODE );				break;
		default:
			break;
	}
	return ;
}

void	Channel::setMode( u_int16_t mask ) {
	this->_mode |= mask;
	return ;
}

void	Channel::unsetMode( u_int16_t mask ) {
	this->_mode &= mask;
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
