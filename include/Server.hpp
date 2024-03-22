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



///	--------------------------------------------------------- @section TYPEDEF.S

typedef std::vector< Clients >		t_vec_Clients;
typedef std::vector< t_pollfd >		t_vec_pollfd;

typedef	struct sockaddr_in t_sockaddr_in;

///	---------------------------------------------------------- @section CLASS.ES

class	Server {
	private:
		static bool		_sig;		//	Program signal.
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
		void	serverInit( std::string portnum );
		void	acceptNewClient( void );
		void	receiveNewData( int fd );
		void	clearClient( int fd );

};	/*	Server	*/

#endif	/*	SERVER_HPP_	*/
