/******************************************************************************/
/*                                                                            */
/*                                    IRC                                     */
/*                                                                            */
/******************************************************************************/

#ifndef		SERVER_HPP_
# define	SERVER_HPP_

# include	"main.hpp"

/// @note Forward declaration.
class Clients;
class Channel;

///	------------------------------------------------------------------- @section MACRO.S

# define	CR_LF			"\r\n" // Carriage return - Line feed (page 6 - Internet Relay Chat: Client Protocol)
# define	NOT_FOUND		std::string::npos

# ifndef	PASSWORD_LENGHT
#  define	PASSWORD_LENGHT	9
# endif	/*	PASSWORD_LENGHT	*/

# define	NICKNAME_CHAR	"abcdefghijklmnopqrstuvwxyz0123456789.ABCDEFGHIJKLMNOPQRSTUVWXYZ"

///	------------------------------------------------------------------- @section TYPEDEF.S

typedef std::vector< Clients >		t_vec_Clients;
typedef std::vector< t_pollfd >		t_vec_pollfd;
typedef std::map<std::string, Channel> t_map_Channel;

typedef	struct sockaddr_in t_sockaddr_in;

///	------------------------------------------------------------------- @section CLASS.ES

class	Server {
	private:
		static bool				_sig;			//	Program signal.
		static const u_int8_t	_password_lenght;	// MAX lenght of nickname

		std::string		_passwd;		//	Password
		in_port_t		_port;			//	0 to 65353
		int				_sock_fd;		//	return from socket() call.
		t_vec_Clients 	_clients;		//	Client vector; keep track of all the clients, manage their requests.
		t_vec_pollfd	_fds;			//	struct pollfd vector.
		t_map_Channel	_channelList; 	// map containing all the channel in the server.

	public:
		Server( void );
		~Server( void );
		// Server( const Server &rhs );	//	Coplien form requisite
		// Server &operator=( const Server &rhs );	//	Coplien form requisite
		static	void checkParameters( int ac );

		void	setPort( std::string portnum );
		void	signalHandle( int num );
		void	setSocket();
		void	serverInit( std::string portnum, std::string passwd );
		void	acceptNewClient( void );
		void	receiveNewData( int fd );
		void	clearClient( int fd );

		Clients	*getClient( int fd );
		void	setPassword( std::string passwd );
		int		checkPassword( std::string rhs ) const;

		int	addChannel( std::string name );
		Channel & getChannel( std::string name );
		bool	checkAvailableNickName( std::string needle );

};	/*	Server	*/

namespace	serv {
	t_pollfd	newPoll( int socket_fd );
};	/*	serv	*/

#endif	/*	SERVER_HPP_	*/
