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
}

std::string	Clients::getInputBuffer( void ) {
	return ( this->_input_buffer );
}

void	Clients::clearInputBuffer( void ) {
	this->_input_buffer.clear();
}

<<<<<<< HEAD
/// @brief Default constructor.
Clients::Clients( void ): _fd(-1) {

=======
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
>>>>>>> 29d4649d936e1c6388d7be45a7e643d1d9d68898
}

/// @brief Default destructor.
Clients::~Clients( void ) {

}
