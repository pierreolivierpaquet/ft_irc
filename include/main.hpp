/******************************************************************************/
/*                                                                            */
/*                                    IRC                                     */
/*                                                                            */
/******************************************************************************/

#ifndef		MAIN_HPP_
# define	MAIN_HPP_

# include	<vector>
// # include	<list>
// # include	<map>

# include	"Network.hpp"	//	Socket API.
# include	"errors.hpp"	//	Error management.
# include	"Client.hpp"	//	Client data.

# ifndef	EXIT_SUCCESS
#  define	EXIT_SUCCESS	0
# endif	/*	EXIT_SUCCESS	*/

///	----------------------------------------------------------- @section COLOR.S

# define BLD_RED "\033[1;31m"			//	BOLD RED
# define RED "\033[31m"					//	RED
# define BLD_WHI "\033[1m"				//	BOLD WHITE
# define WHI "\033[0m"					//	WHITE (reset color)
# define BLD_GRE "\033[1;32m"			//	BOLD GREEN
# define GRE "\033[32m"					//	GREEN
# define BLD_YEL "\033[1;33m"			//	BOLD YELLOW
# define YEL "\033[33m"					//	YELLOW
# define BLD_ORA "\033[1;38;5;208m"		//	BOLS ORANGE
# define ORA "\033[38;5;208m"			//	ORANGE

#endif	/*	MAIN_HPP_	*/
