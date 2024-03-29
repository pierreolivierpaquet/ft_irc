/******************************************************************************/
/*                                                                            */
/*                                    IRC                                     */
/*                                                                            */
/******************************************************************************/

#ifndef		CLIENTS_HPP_
# define	CLIENTS_HPP_

# include	"main.hpp"

/// Forward class declaration.
class Server;

///	----------------------------------------------------------- @section MACRO.S

# define	PASS_AUTH		0b0010
# define	NICK_AUTH		0b0100
# define	USER_AUTH		0b1000
# define	FULL_AUTH		0b1111

///	--------------------------------------------------------- @section TYPEDEF.S



///	---------------------------------------------------------- @section CLASS.ES

class	Clients {
	private:
		int _fd;
		std::string _IPadd;
		std::string	_input_buffer;	// Stores the input from client
		u_int16_t	_registered;	// Bitfield to monitor registration process. 
		std::string	_username;
		std::string	_nickname;
		std::string	_realname;
		std::string _port;

	public:
		Clients( void );
		~Clients( void );
		// Client( const Client &rhs );	//	Coplien form requisite
		// Client &operator=( const Client &rhs );	//	Coplien form requisite

		int		getFd( void );
		void	setFd( int fd );
		std::string getPort( void );
		void 	setPort( std::string port );
		void	setIpAdd( std::string ipadd);
		void	setInputBuffer( std::string buffer );
		std::string	getInputBuffer( void );

		void	trimInputBuffer( void );

		u_int16_t	getRegistration( void ) const;
		void	setRegistration( u_int16_t mask );
		bool	passwordAuthenticated( void ) const ;
		bool	userAuthenticated( void ) const ;
		bool	authenticated( void ) const;
		bool	validateServerPassword( const Server &ircserv ); // test

		void	setNickName( std::string nickname );
		std::string	getNickName( void ) const;
		void	setUserName( std::string username );
		void	setRealName( std::string realname );

};	/*	Client	*/

#endif	/*	CLIENT_HPP_	*/
