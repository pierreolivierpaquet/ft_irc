/******************************************************************************/
/*                                                                            */
/*                                    IRC                                     */
/*                                                                            */
/******************************************************************************/

#include <cstring>
#include <cstdlib>
#include <sstream>
#include "Server.hpp"

/// @brief	Sets the static signal variable to false.
bool Server::_sig = false;
const u_int8_t	Server::_password_lenght = PASSWORD_LENGHT;

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
	static_cast<void>(num);
	_sig = true;
	return ;
}

void	Server::setPort( std::string portnum ) {
	int	set_port = atoi( portnum.c_str() );
	if (set_port < 1024 || set_port > 49151 ) {
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

Clients *Server::getClientWithName( std::string name ) {
	for ( size_t i = 0; i < this->_clients.size(); i++) {
		if ( this->_clients[ i ].getNickName() == name ) {
			return ( &this->_clients[ i ] );
		}
	}
	return ( NULL );
}

t_map_Channel	&Server::getChannelsList( void ) {
	return _channelList;
}

void	Server::setPassword( std::string passwd ) {
	this->_passwd = passwd;
	return ;
}

int	Server::checkPassword( std::string rhs ) const {
	return ( this->_passwd.compare( rhs ) );
}

void	Server::setSocket( void ) {
	int				option_value = 1;
	t_pollfd		poll;	// Used for monitoring file descriptors I/O events.
	t_sockaddr_in	add;	// Contains important information about server address.
	memset(&add, 0, sizeof(add));

	add.sin_family = AF_INET;
	add.sin_addr.s_addr = INADDR_ANY;
	add.sin_port = htons(_port);

	this->_sock_fd = socket(	AF_INET,		// https://stackoverflow.com/questions/1593946/what-is-af-inet-and-why-do-i-need-it
								SOCK_STREAM,	// https://stackoverflow.com/questions/5815675/what-is-sock-dgram-and-sock-stream
								0 );
	if (this->_sock_fd < 0) {
		throw( std::runtime_error( BLD_RED ERR_MSG WHI ERR_SOCK_FD ) );
	} else if (setsockopt(	this->_sock_fd,
							SOL_SOCKET,	// socket level: https://stackoverflow.com/questions/21515946/what-is-sol-socket-used-for
							SO_REUSEADDR,
							&option_value,
							sizeof(option_value) )) {
		throw( std::runtime_error( BLD_RED ERR_MSG WHI ERR_SETSOCKOPT ) );
	} else if (fcntl(	this->_sock_fd,
						F_SETFL,
						O_NONBLOCK ) < 0) {
		throw( std::runtime_error( BLD_RED ERR_MSG WHI ERR_FCNTL ) );
	} else if (	bind(this->_sock_fd,
				reinterpret_cast< struct sockaddr * >( &add ),
				sizeof(add) ) == -1) {
		throw( std::runtime_error( BLD_RED ERR_MSG WHI ERR_BIND ) );
	} else if (listen(this->_sock_fd, SOMAXCONN) < 0) {
		throw( std::runtime_error( BLD_RED ERR_MSG WHI ERR_LISTEN ) );
	}
	poll = serv::newPoll( this->_sock_fd );
	this->_fds.push_back( poll );
	return ;
}

void Server::acceptNewClient( void ) {
	Clients newClient;
	t_sockaddr_in clientAdd;
	t_pollfd newPoll;
	socklen_t len = sizeof(clientAdd);
	std::stringstream ss;

	int incofd = accept(_sock_fd, reinterpret_cast< struct sockaddr * >( &clientAdd) , &len);
	if (incofd == -1) {
		std::cout << "Accept() failed!" << std::endl;
		return;
	}

	if (fcntl(incofd, F_SETFL, O_NONBLOCK) == -1) {
		std::cout << "fctnl() failed!" << std::endl;
		return;
	}
	newPoll = serv::newPoll( incofd );

	newClient.setFd(incofd);
	newClient.setIpAdd(inet_ntoa((clientAdd.sin_addr)));
	ss << clientAdd.sin_port;
	newClient.setPort(ss.str());
	_clients.push_back(newClient);
	_fds.push_back(newPoll);

	std::cout << "Client connected!" << std::endl;
}

void Server::receiveNewData( int fd ) {
	char buff[ 1024 ]; // buffer to receive the data
	memset(buff, 0, sizeof(buff)); // set the buffer to 0
	std::vector<std::string> vec_quit;
	vec_quit.push_back("QUIT");
	vec_quit.push_back("Leaving...");

	Clients	*client_data = this->getClient( fd );	// Retrieves the right client to store it's buffer
	ssize_t bytes = recv(fd, buff, sizeof(buff) - 1, 0); // receive the actual data

	if (bytes <= 0) { // checks if the client disconnected
		if (!client_data->getPendingQuit())
			quit(*this, *client_data, vec_quit);
		close(fd);
		clearClient(fd);
		std::cout << "Client disconnected" << std::endl;
	} else {
		client_data->setInputBuffer( buff );
		if (client_data->getInputBuffer().find_first_of( CR_LF ) == NOT_FOUND) {
			return ;
		}
		buff[ bytes ] = '\0';
		execute( *this , *client_data );
		if (client_data->getPendingQuit()) {
			close(client_data->getFd());
			clearClient(client_data->getFd());
			std::cout << "Client quit" << std::endl;
		}
	}
}

bool	Server::checkAvailableNickName( std::string needle ) {
	t_vec_Clients::iterator it = this->_clients.begin();
	t_vec_Clients::iterator ite = this->_clients.end();

	needle = needle.substr(0, 9);

	for (; it != ite; it++) {
		if (it->getNickName().compare( needle ) == 0){
			return ( false );
		}
	}
	return ( true );
}

std::vector< int >	Server::getConcernedClients( Clients &client ) {
	std::vector< int > concerned_clients;
	std::vector< int > concerned_clients2;
	int	client_fd = client.getFd();
	bool found = false;
	std::map<std::string, Channel >::iterator	it = this->_channelList.begin();
	std::map<std::string, Channel >::iterator	ite = this->_channelList.end();
	std::vector<int>::iterator itvec;

	if (this->_channelList.size() != 0) {
		for (; it != ite; ++it) {
			if (it->second.getClientList().find( client_fd ) != it->second.getClientList().end() ) {
				for (	std::map<int, Clients >::iterator it_client = it->second.getClientList().begin();
						it_client != it->second.getClientList().end(); it_client++) {
					if (it_client->first != client_fd &&
						std::find( concerned_clients.begin(), concerned_clients.end(), it_client->first ) == concerned_clients.end()) {
							concerned_clients.push_back( it_client->first );
					}
				}
			}
		}
	}

	if (client.getPrivmsgTarget().size() != 0) {
		for (size_t i = 0; i < client.getPrivmsgTarget().size(); i++) {
			for (itvec = concerned_clients.begin(); itvec != concerned_clients.end(); ++itvec) {
				if (client.getPrivmsgTarget().at(i) == *itvec)
					found = true;
			}
			if (found == false)
				concerned_clients2.push_back(client.getPrivmsgTarget().at(i));
			found = false;
		}

		for (size_t i = 0; i < concerned_clients2.size(); i++) {
			concerned_clients.push_back(concerned_clients2[i]);
		}
	}

	return ( concerned_clients );
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

	for (size_t i = 0; i < _fds.size(); i++) {
		close(_fds[i].fd);
	}

}

bool Server::getChannel( std::string name , Channel **channel) {
	t_map_Channel::iterator it;

	for (it = _channelList.begin(); it != _channelList.end(); ++it) {
		if (it->first == name) {
			*channel = &it->second;
			return (true);
		}
	}
	return (false);
}

int Server::addChannel( std::string name ) {
	std::map<std::string, Channel>::iterator it;

	for (it = _channelList.begin(); it != _channelList.end(); ++it) {
		if (it->first == name)
			return (1);
	}

	Channel newChannel(name);
	_channelList.insert(std::make_pair(name, newChannel));
	return (0);
}

void Server::deleteChannel( std::string name ) {
	t_map_Channel::iterator it;

	for (it = _channelList.begin(); it != _channelList.end(); ++it) {
		if (it->first == name) {
			_channelList.erase(name);
			break;
		}
	}
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

/// @brief Creates and fills a new poll_fd.
t_pollfd	serv::newPoll( int socket_fd) {
	t_pollfd	new_poll;
	new_poll.fd =		socket_fd;
	new_poll.events =	POLLIN;
	new_poll.revents =	0;
	return ( new_poll );
}
