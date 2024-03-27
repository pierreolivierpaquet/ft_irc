/******************************************************************************/
/*                                                                            */
/*                                    IRC                                     */
/*                                                                            */
/******************************************************************************/

#include	"Clients.hpp"

/// @brief Getter for fd.
int Clients::getFd( void ) {
	return (_fd);
}

/// @brief Setter for fd of the client.
/// @param fd Client fd.
void Clients::setFd( int fd ) {
	_fd = fd;
}

/// @brief Setter for IP address of the client.
/// @param ipadd Client IP address.
void Clients::setIpAdd( std::string ipadd ) {
	_IPadd = ipadd;
}

void	Clients::setInputBuffer( std::string buffer) {
	this->_input_buffer.append( buffer );
	return ;
}

std::string	Clients::getInputBuffer( void ) {
	return ( this->_input_buffer );
}

void	Clients::clearInputBuffer( void ) {
	this->_input_buffer.clear();
	return ;
}

void	Clients::setMode( u_int16_t mode ) {
	this->_mode = mode;
	return ;
}

u_int16_t	Clients::getRegistration( void ) const {
	return ( this->_registered );
}

void	Clients::setRegistration( u_int16_t mask ) {
	this->_registered |= mask;
	return ;
}

void	Clients::setNickName( std::string nickname ) {
	this->_nickname = nickname;
	return ;
}

std::string	Clients::getNickName( void ) const {
	return ( this->_nickname );
}


void	Clients::setUserName( std::string username ) {
	this->_username = username;
	return ;
}

void	Clients::setRealName( std::string realname ) {
	this->_realname = realname;
	return ;
}

std::string Clients::getPort( void ) {
	return (_port);
}

void Clients::setPort( std::string port ) {
	_port = port;
}

/// @brief Default constructor.
Clients::Clients( void ) :
	_fd( 0 ),
	_IPadd( EMPTY_STR ),
	_input_buffer( EMPTY_STR ),
	_registered( 1 ),
	_username( EMPTY_STR ),
	_nickname( EMPTY_STR ),
	_realname( EMPTY_STR ),
	_mode( 0 ) {
	return;
}

/// @brief Default destructor.
Clients::~Clients( void ) {

	return ;
}
