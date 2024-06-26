/******************************************************************************/
/*                                                                            */
/*                                    IRC                                     */
/*                                                                            */
/******************************************************************************/

#include "Channel.hpp"

int Channel::addClient( Clients & client ) {
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

/// @brief Broadcasts a message to all the clients within the channel.
void	Channel::_broadcast( std::string message ) const {
	std::map < int, Clients >::const_iterator it;
	std::map< int, Clients >::const_iterator ite = this->_clientList.end();

	for (it = this->_clientList.begin(); it != ite; it++) {
		send(	it->first,
				static_cast< const void * >(message.c_str()),
				message.length(),
				0 );
	}
	return ;
}

/// @brief Modifies the channel mode bit (flag).
void	Channel::_ChanMode( char mode ) {
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

void Channel::_mode_topic( Clients &client, short set, char mode, std::vector< std::string > param ) {
	static_cast< void >( param );
	this->_ChanMode( set * mode );

	std::stringstream ss;
	ss << ":" << client.getNickName() << " MODE " << this->getName() << " " << (( set > 0 ) ? "+" : "-") << mode << CR_LF;
	this->_broadcast( ss.str() );
	return;
}

void Channel::_mode_invite( Clients &client, short set, char mode, std::vector< std::string > param ) {
	static_cast< void >( param );
	this->_ChanMode( set * mode );

	std::stringstream ss;
	ss << ":" << client.getNickName() << " MODE " << this->getName() << " " << (( set > 0 ) ? "+" : "-") << mode << CR_LF;
	this->_broadcast( ss.str() );
	return ;
}

void Channel::_mode_key( Clients &client, short set, char mode, std::vector< std::string > param ) {
	if (param.size() < 4) {
		std::cout << "Can't set/unset channel's key: need more parameter(s)." << std::endl;
		throw( ERR_NEEDMOREPARAMS );
		return ;
	}
	if (set < 0) {
		if (this->_key == param.at( 3 )) {
			this->_key.clear();
			this->_ChanMode( set * mode );
		} else {
			std::cout << "Can't deactivate channel's key: provided key is not the same as current." << std::endl;
			throw( ERR_BADCHANNELKEY );
		}
	} else if (this->isMode( KEY_MODE ) == true) {
		std::cout << "Can't add key: already set." << std::endl;
		throw( ERR_KEYSET );
	} else {
		this->_key = param.at( 3 );
		this->_ChanMode( set * mode );
	}
	std::stringstream ss;
	ss << ":" << client.getNickName() << " MODE " << this->getName() << " " << (( set > 0 ) ? "+" : "-") << mode << CR_LF;
	this->_broadcast( ss.str() );
	return ;
}

void	Channel::_mode_operator( Clients &client, short set, char mode, std::vector< std::string > param ) {
	static_cast< void >( client );
	if (param.size() < 4) {
	std::cout << "Can't add/remove channel operator: no nickname given/missing parameter(s)." << std::endl;
	throw( ERR_NONICKNAMEGIVEN );
	return ;
	}
	int client_fd = this->findClient( param.at( 3 ) );
	if (client_fd < 0) {
		std::cout << "Can't add/remove channel operator: mentionned user not in channel." << std::endl;
		throw( ERR_USERNOTINCHANNEL );
		return ;
	}
	if (set < 0) {
		this->_operList.erase( this->findOperator( client_fd ) );
		if (this->_operList.size() == 0) {
			this->_ChanMode( set * mode );
		}
	} else {
		this->_operList.push_back( client_fd );
		this->_ChanMode( set * mode );
	}
	std::stringstream ss;
	ss << ":" << client.getNickName() << " MODE " << this->getName() << " " << (( set > 0 ) ? "+" : "-") << mode << " " << param.at(3) << CR_LF;
	this->_broadcast( ss.str() );
	return ;
}

void	Channel::_mode_limit( Clients &client, short set, char mode, std::vector< std::string > param  ) {
	static_cast< void >( client );
	if (set > 0) {
		if ( param.size() < 4 ) {
			std::cout << "Can't add channel limit: missing parameter(s)." << std::endl;
			throw( ERR_NEEDMOREPARAMS );
		}
		this->_clients_limit = std::atoi( param.at( 3 ).c_str() );
		this->_ChanMode( set * mode );
	} else {
		this->_clients_limit = 0;
		this->_ChanMode( set * mode );
	}
	std::stringstream ss;
	ss << ":" << client.getNickName() << " MODE " << this->getName() << " " << (( set > 0 ) ? "+" : "-") << mode << CR_LF;
	this->_broadcast( ss.str() );
	return ;
}

void	Channel::ModeOption( Clients &client, short set, char mode, std::vector< std::string > param ) {
	switch ( mode )
	{
		case ( 's' ) :
		case ( 'n' ) : std::cout << "{s;n} channel modes not supported." << std::endl; break;
		case ( 'i' ) : ( this->*_mode_func[ INV ] )( client, set, mode, param ); break;
		case ( 't' ) : ( this->*_mode_func[ TOP ] )( client, set, mode, param ); break;
		case ( 'k' ) : ( this->*_mode_func[ KEY ] )( client, set, mode, param ); break;
		case ( 'o' ) : ( this->*_mode_func[ OPS ] )( client, set, mode, param ); break;
		case ( 'l' ) : ( this->*_mode_func[ LIM ] )( client, set, mode, param ); break;
		default : break;
	}
	return ;
}

int	Channel::findClient( std::string name ) {
	std::map< int, Clients >::iterator it = this->_clientList.begin();
	std::map< int, Clients >::iterator ite = this->_clientList.end();
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

void	Channel::setTopic(const std::string& topic) {
	if (topic.size() == 0) return;
	_topic = topic;
}

std::string	Channel::getTopic( void ) const {
	return _topic;
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

void Channel::deleteClient( Clients client) {
	std::map<int, Clients>::iterator it;

	for (it = _clientList.begin(); it != _clientList.end(); ++it) {
		if (it->first == client.getFd()) {
			_clientList.erase(client.getFd());
			break;
		}
	}
}

void Channel::deleteOper( Clients client ) {
	std::vector<int>::iterator it;

	for (it = _operList.begin(); it != _operList.end(); ++it) {
		if (*it == client.getFd()) {
			_operList.erase(it);
			break;
		}
	}
}

void	Channel::_modefuncmapping( void ) {
	this->_mode_func[ INV ] = &Channel::_mode_invite;
	this->_mode_func[ TOP ] = &Channel::_mode_topic;
	this->_mode_func[ KEY ] = &Channel::_mode_key;
	this->_mode_func[ OPS ] = &Channel::_mode_operator;
	this->_mode_func[ LIM ] = &Channel::_mode_limit;
	return ;
}

void Channel::addWhiteList( Clients & client ) {
	std::vector<std::string>::iterator it;

	for (it = _whiteList.begin(); it != _whiteList.end(); ++it) {
		if (*it == client.getNickName())
			return ;
	}

	_whiteList.push_back(client.getNickName());
	return ;
}

void Channel::deleteWhiteList( Clients & client ) {
	std::vector<std::string>::iterator it;

	for (it = _whiteList.begin(); it != _whiteList.end(); ++it) {
		if (*it == client.getNickName()) {
			_whiteList.erase(it);
			return ;
		}
	}
}

bool Channel::isInvited( Clients & client ) {
	std::vector<std::string>::iterator it;

	for (it = _whiteList.begin(); it != _whiteList.end(); ++it) {
		if (*it == client.getNickName())
			return (true);
	}
	return (false);
}

bool Channel::checkKey( std::string key ) {
	if (key == _key)
		return (true);
	return (false);
}

bool Channel::checkLimit( void ) {
	if (_clientList.size() == _clients_limit)
		return (true);
	return (false);
}

Channel::Channel( std::string name) :
	_name(name),
	_topic( ":Channel topic!" ),
	_mode( DEFAULT_MODE | TOPIC_MODE ) {
	this->_modefuncmapping();
}

Channel::~Channel( void ) {}
