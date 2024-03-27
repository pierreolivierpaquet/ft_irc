/******************************************************************************/
/*                                                                            */
/*                                    IRC                                     */
/*                                                                            */
/******************************************************************************/

# include "Commands.hpp"

void	execute( Server &ircserv, Clients &client_data ) {
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
		//
		if (tmp_split.at(0).compare( "PASS" ) == 0) {
			pass( ircserv, client_data, tmp_split );
		} else if ( tmp_split.at( 0 ).compare( "NICK" ) == 0 ) {
			nick( ircserv, client_data, tmp_split );
		} else if (tmp_split.at(0).compare( "USER" ) == 0) {
			user( ircserv, client_data, tmp_split );
		}
		//
		input = input.substr( cr_lf + 2 ); // '+ 2' Since CR_LF was found.
		cr_lf = input.find( CR_LF );
	}
	client_data.clearInputBuffer(); // DONT CLEAR, BUT TRIM UNTIL \r\n to avoid losing data
	return ;
}
