/******************************************************************************/
/*                                                                            */
/*                                    IRC                                     */
/*                                                                            */
/******************************************************************************/

#ifndef		SERVER_HPP_
# define	SERVER_HPP_

# include	"main.hpp"

/// @brief Forward declaration.
class Clients;

///	----------------------------------------------------------- @section MACRO.S

# define	CR_LF		"\r\n" // Carriage return - Line feed
# define	NOT_FOUND	std::string::npos

///	--------------------------------------------------------- @section TYPEDEF.S

typedef std::vector< Clients >		t_vec_Clients;
typedef std::vector< t_pollfd >		t_vec_pollfd;

typedef	struct sockaddr_in t_sockaddr_in;

///	---------------------------------------------------------- @section CLASS.ES

class	Server {
	private:
		static bool		_sig;		//	Program signal.
		std::string		_passwd;	//	Password
		in_port_t		_port;		//	0 to 65353
		int				_sock_fd;	//	return from socket() call.
		t_vec_Clients 	_clients;	//	Client vector; keep track of all the clients, manage their requests.
		t_vec_pollfd	_fds;		//	struct pollfd vector.

	public:
		Server( void );
		~Server( void );
		// Server( const Server &rhs );	//	Coplien form requisite
		// Server &operator=( const Server &rhs );	//	Coplien form requisite

		void	setPort( std::string portnum );
		void	signalHandle( int num );
		void	setSocket();
		void	serverInit( std::string portnum, std::string passwd );
		void	acceptNewClient( void );
		void	receiveNewData( int fd );
		void	clearClient( int fd );

		Clients	*getClient( int fd );
		void	setPassword( std::string passwd );

		static	void checkParameters( int ac );

};	/*	Server	*/

#endif	/*	SERVER_HPP_	*/
