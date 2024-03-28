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
		// u_int8_t	_mode; // NO NEED FOR USER MODE? ONLY CHANNELS ?
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
		// void	setMode( u_int8_t mode );

		u_int16_t	getRegistration( void ) const;
		void	setRegistration( u_int16_t mask );

		void	setNickName( std::string nickname );
		std::string	getNickName( void ) const;
		void	setUserName( std::string username );
		void	setRealName( std::string realname );

};	/*	Client	*/

#endif	/*	CLIENT_HPP_	*/
