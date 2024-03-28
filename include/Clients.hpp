/******************************************************************************/
/*                                                                            */
/*                                    IRC                                     */
/*                                                                            */
/******************************************************************************/

#ifndef		CLIENTS_HPP_
# define	CLIENTS_HPP_

# include	"main.hpp"

///	----------------------------------------------------------- @section MACRO.S



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
		u_int16_t	_mode;

	public:
		Clients( void );
		~Clients( void );
		// Client( const Client &rhs );	//	Coplien form requisite
		// Client &operator=( const Client &rhs );	//	Coplien form requisite

		int		getFd( void );
		void	setFd( int fd );
		void	setIpAdd( std::string ipadd);
		void	setInputBuffer( std::string buffer );
		std::string	getInputBuffer( void );

		void	clearInputBuffer( void );
		void	setMode( u_int16_t mode );

		u_int16_t	getRegistration( void ) const;
		void	setRegistration( u_int16_t mask );

		void	setNickName( std::string nickname );
		std::string	getNickName( void ) const;
		void	setUserName( std::string username );
		void	setRealName( std::string realname );

};	/*	Client	*/

#endif	/*	CLIENT_HPP_	*/
