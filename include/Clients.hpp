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

	public:
		Clients( void );
		~Clients( void );
		// Client( const Client &rhs );	//	Coplien form requisite
		// Client &operator=( const Client &rhs );	//	Coplien form requisite

		int		getFd( void );
		void	setFd( int fd );
		void	setIpAdd( std::string ipadd);

};	/*	Client	*/

#endif	/*	CLIENT_HPP_	*/
