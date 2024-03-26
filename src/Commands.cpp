/******************************************************************************/
/*                                                                            */
/*                                    IRC                                     */
/*                                                                            */
/******************************************************************************/

# include "main.hpp"

void	execute( Clients &client_data ) {
	size_t						cr_lf = 0;
	std::string					input;
	std::vector< std::string >	tmp_split;

	input = client_data.getInputBuffer();
	cr_lf = input.find( CR_LF );
	while (cr_lf != NOT_FOUND) {
		tmp_split = cmd::split( input.substr( 0, cr_lf ) );
		/*
			tmp_split >> TOKENIZE + EXECUTION HERE
		*/
		input = input.substr( cr_lf + 2 ); // '+ 2' Since CR_LF was found.
		cr_lf = input.find( CR_LF );
	}
	client_data.clearInputBuffer();
	return ;
}
