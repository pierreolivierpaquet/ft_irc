/******************************************************************************/
/*                                                                            */
/*                                    IRC                                     */
/*                                                                            */
/******************************************************************************/

#include	"Server.hpp"

/// @brief	Sets the static signal variable to false.
bool Server::_sig = false;

void	Server::signalHandle( int num ) {
	static_cast< void >( num );
	this->_sig = true;
	return ;
}

void	Server::setPort( std::string portnum ) {
	int	set_port = std::atoi( portnum.c_str() );
	if (set_port > 65535 || set_port < 1024) {
		throw( std::runtime_error(ERR_MSG "invalid port number.") );
	}
	this->_port = static_cast< in_port_t >( set_port );
	return ;
}

void	Server::setSocketAddress( void ) {
	this->_sockaddr_in.sin_family = AF_INET; // Specifies that it's an internet connection.
	this->_sockaddr_in.sin_port = htons( this->_port ); // big-endian format.
	this->_sockaddr_in.sin_addr.s_addr = INADDR_ANY; // or loopback 127.0.0.1 ?
	return ;
}

void	Server::setSocket( void ) {
	int	option_value = 1;
	t_pollfd	poll;

	this->_sock_fd = socket( AF_INET, SOCK_STREAM, 0 );
	if (this->_sock_fd < 0) {
		//	THROW ERROR MANAGEMENT
	} else if (setsockopt(	this->_sock_fd,
							SOL_SOCKET,
							SO_REUSEADDR,
							&option_value,
							sizeof(option_value) )) {
		//	THROW ERROR MANAGEMENT
	} else if (fcntl(	this->_sock_fd,
						F_SETFL,
						O_NONBLOCK ) < 0) {
		//	THROW ERROR MANAGEMENT
	} else if (	bind(this->_sock_fd,
				reinterpret_cast< struct sockaddr * >( &this->_sockaddr_in ),
				sizeof(this->_sockaddr_in) ) < 0) {
		// THROW ERROR MANAGEMENT
	} else if (listen(this->_sock_fd, SOMAXCONN) < 0) {
		// THROW ERROR MANAGEMENT
	}
	poll.fd = this->_sock_fd;
	poll.events = POLLIN;
	poll.revents = 0;
	this->_fds.push_back( poll );
	return ;
}

/// @brief Default constructor.
Server::Server( void ) :
	_port( 0 ),
	_sock_fd( std::numeric_limits< int >::min() ) {
	return;
}

/// @brief Default destructor.
Server::~Server( void ) {

	return ;
}
