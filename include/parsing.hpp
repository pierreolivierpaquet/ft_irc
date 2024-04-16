/******************************************************************************/
/*                                                                            */
/*                                    IRC                                     */
/*                                                                            */
/******************************************************************************/

#ifndef		PARSING_HPP_
# define	PARSING_HPP_

# include	"main.hpp"

///	------------------------------------------------------------------- @section MACRO.S

# define	EMPTY_STR		""

///	------------------------------------------------------------------- @section NAMESPACE.S

/// @brief Parsing realated to the commands.
namespace	cmd {
	std::vector< std::string >	split( Clients &client_data, std::string input );
};	/*		cmd	*/

#endif	/*	PARSING_HPP_	*/
