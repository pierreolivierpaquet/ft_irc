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

void	Clients::trimInputBuffer( void ) {
	this->_input_buffer = this->_input_buffer.substr( this->_input_buffer.rfind( CR_LF ) + 2, std::string::npos );
	return ;
}

u_int16_t	Clients::getRegistration( void ) const {
	return ( this->_registered );
}

void	Clients::setRegistration( u_int16_t mask ) {
	this->_registered |= mask;
	return ;
}

bool	Clients::passwordAuthenticated( void ) const {
	u_int16_t	status = this->getRegistration() & PASS_AUTH;
	return ( status == PASS_AUTH );
}

bool	Clients::userAuthenticated( void ) const {
	u_int16_t	status = this->getRegistration() & USER_AUTH;
	return ( status == USER_AUTH );
}

bool	Clients::authenticated( void ) const {
	u_int16_t	auth_status = this->getRegistration() & FULL_AUTH;
	return ( auth_status == FULL_AUTH );
}

bool	Clients::validateServerPassword( const Server &ircserv ) {
	if (ircserv.checkPassword( EMPTY_STR ) != 0) {
			std::cout << "NEED TO KICK OUT/ CLOSE CLIENT FD" << std::endl;
			return ( false );
		} else {
			this->setRegistration( PASS_AUTH );
		}
	return ( true );
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
	_realname( EMPTY_STR ) {
	return;
}

/// @brief Default destructor.
Clients::~Clients( void ) {

	return ;
}
