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

# define	WELCOMED_AUTH	0b00010000
# define	DEFAULT_AUTH	0b00000001
# define	PASS_AUTH		0b00000010
# define	NICK_AUTH		0b00000100
# define	USER_AUTH		0b00001000
# define	FULL_AUTH		0b00001111

///	---------------------------------------------------------- @section CLASS.ES

class	Clients {
	private:
		int					_fd;
		std::string			_IPadd;
		std::string			_input_buffer;
		u_int16_t			_registered;
		std::string			_username;
		std::string			_nickname;
		std::string			_nickname_prev;
		std::string			_realname;
		std::string			_port;
		std::vector<int>	_privmsgtarget;
		bool				_pendingquit;

	public:
		Clients( void );
		~Clients( void );

		int					getFd( void );
		void				setFd( int fd );
		std::string 		getPort( void );
		void 				setPort( std::string port );
		void				setIpAdd( std::string ipadd);
		void				setInputBuffer( std::string buffer );
		std::string			getInputBuffer( void );
		void				quit( void );
		bool				getPendingQuit( void );

		void				trimInputBuffer( void );

		bool				isAuthenticatedAs( u_int16_t status ) const;
		u_int16_t			getRegistration( void ) const;
		void				setRegistration( u_int16_t mask );
		bool				validateServerPassword( const Server &ircserv );

		void				setNickName( std::string nickname );
		std::string			getNickName( void ) const;
		std::string			getNickNamePrev( void ) const;
		void				setUserName( std::string username );
		void				setRealName( std::string realname );
		std::string			getRealName( void ) const;
		void				addPrivmsgTarget( int fd );
		std::vector<int>	getPrivmsgTarget( void );

};	/*	Client	*/

#endif	/*	CLIENT_HPP_	*/
