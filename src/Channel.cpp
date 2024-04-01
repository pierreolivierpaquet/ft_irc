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

/// @brief Modifies the channel mode itself.
void	Channel::ChanMode( char mode ) {
	switch ( mode ) {
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

void	Channel::ModeOption( short set, char mode, std::vector< std::string > param ) {
	if (mode == 'i') {
		this->ChanMode( set * mode );
	} else if (mode == 't') {
		this->ChanMode( set * mode );
	} else if ( mode == 'k' ) {
		if (param.size() < 4) {
			std::cout << "SEND() ERR_NEEDMOREPARAM - DELETE THIS" << std::endl;
			return ;
		}
		if (set < 0) {
			if (this->_key == param.at( 3 )) {
				this->_key.clear();
				this->ChanMode( set * mode );
			} else {
				std::cout << "SEND() ERR CANT DEACTIVATE KEY BECAUSE NOT SAME AS PROVIDED DELETE THIS" << std::endl;
			}
		} else {
			this->_key = param.at( 3 );
			this->ChanMode( set * mode );
		}
	} else if ( mode == 'o' ) {
		if (param.size() < 4) {
		std::cout << "SEND() ERR_NEEDMOREPARAM - DELETE THIS" << std::endl;
		return ;
		}
		int client_fd = this->findClient( param.at( 3 ) );
		if (client_fd < 0) {
			std::cout << "SEND() OPERATOR NOT FOUND - DELETE THIS" << std::endl;
			return ;
		}
		if (set < 0) {
			this->_operList.erase( this->findOperator( client_fd ) );
			if (this->_operList.size() == 0) {
				this->ChanMode( set * mode );
			}
		} else {
			this->_operList.push_back( client_fd );
			this->ChanMode( set * mode );
		}
	} else if ( mode == 'l' ) {
		if (set > 0) {
			if ( param.size() < 4 ) {
				std::cout << "SEND() ERR_NEEDMOREPARAM - DELETE THIS" << std::endl;
			}
			this->_clients_limit = std::atoi( param.at( 3 ).c_str() );
			this->ChanMode( set * mode );
		} else {
			this->_clients_limit = 0;
			this->ChanMode( set * mode );
		}
	}
	return ;
}

int	Channel::findClient( std::string name ) const {
	std::map< int, Clients >::const_iterator it = this->_clientList.begin();
	std::map< int, Clients >::const_iterator ite = this->_clientList.end();
	for (; it != ite; it++) {
		if (it->second.getNickName().compare( name ) == 0) {
			return ( it->first );
		}
	}
	return ( -1 );
}

std::vector< int >::const_iterator	Channel::findOperator( int client_fd ) const {
	std::vector< int >::const_iterator it = this->_operList.begin();
	std::vector< int >::const_iterator ite = this->_operList.end();
	for (; it != ite; it++) {
		if (*it == client_fd) {
			return ( it );
		}
	}
	return ( it );
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

std::map<int, Clients> & Channel::getClientList( void ) {
	return (_clientList);
}

void Channel::setOper( Clients & client ) {
	_operList.push_back(client.getFd());
}

std::vector<int> & Channel::getOper( void ) {
	return (_operList);
}

Channel::Channel( std::string name) :
	_name(name),
	_mode( DEFAULT_MODE ) {}

Channel::~Channel( void ) {}
