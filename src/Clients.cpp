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

/// @brief Default constructor.
Clients::Clients( void ) {

	return;
}

/// @brief Default destructor.
Clients::~Clients( void ) {

	return ;
}
