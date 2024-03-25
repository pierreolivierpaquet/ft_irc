/******************************************************************************/
/*                                                                            */
/*                                    IRC                                     */
/*                                                                            */
/******************************************************************************/

#include	"Server.hpp"

/// @brief	Sets the static signal variable to false.
bool Server::_sig = false;

/// @brief Validates the minimum arguments requirements for Server initialization.
void	Server::checkParameters( int ac ) {
	if (ac < 3) {
		throw( std::runtime_error( BLD_RED ERR_MSG WHI MISSING_PARAM ) );
	} else if ( ac > 3 ) {
		throw( std::runtime_error( BLD_RED ERR_MSG WHI EXCEEDING_PARAM ) );
	}
	return ( static_cast< void >( ac ) );
}

void	Server::signalHandle( int num ) {
	static_cast< void >( num );
	this->_sig = true;
	return ;
}

void	Server::setPort( std::string portnum ) {
	int	set_port = std::atoi( portnum.c_str() );
	if (set_port > 49151 || set_port < 1024) {
		throw( std::runtime_error(BLD_RED ERR_MSG WHI INVALID_PORT) );
	}
	this->_port = static_cast< in_port_t >( set_port );
	return ;
}

void Server::clearClient( int fd ) {
	for (size_t i = 0; i < _fds.size(); i++) {
		if (_fds[i].fd == fd) {
			_fds.erase(_fds.begin() + i);
			break;
		}
	}
	for (size_t i = 0; i < _clients.size(); i++) {
		if (_clients[i].getFd() == fd) {
			_clients.erase(_clients.begin() + i);
			break;
		}
	}
}

Clients	*Server::getClient( int fd) {
	for ( size_t i = 0; i < this->_clients.size(); i++) {
		if ( this->_clients[ i ].getFd() == fd ) {
			return ( &this->_clients[ i ] );
		}
	}
	return ( NULL );
}

void	Server::setPassword( std::string passwd ) {
	this->_passwd = passwd;
	return ;
}

void	Server::setSocket( void ) {
	int	option_value = 1;
	t_pollfd	poll;	// Used for monitoring file descriptors I/O events.
	t_sockaddr_in add;	// Contains important information about server address.
	memset(&add, 0, sizeof(add));

	add.sin_family = AF_INET;
	add.sin_addr.s_addr = INADDR_ANY;
	add.sin_port = htons(_port);

	this->_sock_fd = socket(	AF_INET,		// https://stackoverflow.com/questions/1593946/what-is-af-inet-and-why-do-i-need-it
								SOCK_STREAM,	// https://stackoverflow.com/questions/5815675/what-is-sock-dgram-and-sock-stream
								0 );
	if (this->_sock_fd < 0) {
		std::cout << "Error sock_fd" << std::endl; //	THROW ERROR MANAGEMENT
	} else if (setsockopt(	this->_sock_fd,
							SOL_SOCKET,	// socket level: https://stackoverflow.com/questions/21515946/what-is-sol-socket-used-for
							SO_REUSEADDR,	// 
							&option_value,
							sizeof(option_value) )) {
		std::cout << "Error setsock" << std::endl;//	THROW ERROR MANAGEMENT
	} else if (fcntl(	this->_sock_fd,
						F_SETFL,	// Sets flag
						O_NONBLOCK ) < 0) {
		std::cout << "Error fcntl" << std::endl;//	THROW ERROR MANAGEMENT
	} else if (	bind(this->_sock_fd,
				reinterpret_cast< struct sockaddr * >( &add ),
				sizeof(add) ) == -1) {
		std::cout << "Error bind" << std::endl;// THROW ERROR MANAGEMENT
	} else if (listen(this->_sock_fd, SOMAXCONN) < 0) {
		std::cout << "Error listen" << std::endl;// THROW ERROR MANAGEMENT
	}
	poll.fd = this->_sock_fd;
	poll.events = POLLIN;
	poll.revents = 0;
	this->_fds.push_back( poll );
	return ;
}

void Server::acceptNewClient( void ) {
	Clients newClient;
	t_sockaddr_in clientAdd;
	t_pollfd newPoll;
	socklen_t len = sizeof(clientAdd);

	memset( &newClient, 0, sizeof(newClient));

	int incofd = accept(_sock_fd, reinterpret_cast< struct sockaddr * >( &clientAdd) , &len);
	if (incofd == -1) {
		std::cout << "Accept() failed!" << std::endl;
		return;
	}

	if (fcntl(incofd, F_SETFL, O_NONBLOCK) == -1) {
		std::cout << "fctnl() failed!" << std::endl;
		return;
	}

	newPoll.fd = incofd;
	newPoll.events = POLLIN;
	newPoll.revents = 0;

	newClient.setFd(incofd);
	newClient.setIpAdd(inet_ntoa((clientAdd.sin_addr)));
	_clients.push_back(newClient);
	_fds.push_back(newPoll);

	std::cout << "Client connected!" << std::endl;
}

void Server::receiveNewData( int fd ) {
	char buff[1024]; // buffer to receive the data
	memset(buff, 0, sizeof(buff)); // set the buffer to 0

	Clients	*tmp_client = this->getClient( fd );	// Retrieves the right client to store it's buffer
	ssize_t bytes = recv(fd, buff, sizeof(buff) - 1, 0); // receive the actual data

	if (bytes <= 0) { // checks if the client disconnected
		std::cout << "Client disconnected" << std::endl;
		clearClient(fd);
		close(fd);
	} else {
		tmp_client->setInputBuffer( buff );
		if (tmp_client->getInputBuffer().find_first_of( CR_LF ) == NOT_FOUND) {
			return ;
		}
		buff[bytes] = '\0';
		std::cout << "client : " << fd << " data : " << buff << std::endl;
		// here is for the parsing of the data
	}
}

void Server::serverInit( std::string portnum, std::string passwd ) {
	setPort( portnum ); // sets the port
	setPassword( passwd );
	setSocket(); // create a new socket

	std::cout << "Server connected" << std::endl;

	while (Server::_sig == false) { // main runtime loop of the program
		if (	(poll(&_fds[0], _fds.size(), -1)) == -1 &&
				Server::_sig == false ) // checks for events
			throw(std::runtime_error("poll() failed"));

		for (size_t i = 0; i < _fds.size(); i++) {
			if (_fds[i].revents & POLLIN) { // checks  if there is data to read
				if (_fds[i].fd == _sock_fd)
					acceptNewClient();
				else
					receiveNewData(_fds[i].fd);
			}
		}
	}
	//function to close all the fds
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
