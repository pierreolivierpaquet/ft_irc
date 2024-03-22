/******************************************************************************/
/*                                                                            */
/*                                    IRC                                     */
/*                                                                            */
/******************************************************************************/

#include	"main.hpp"

/// @brief N/A
/// @param argc == 3
/// @param argv [ 1 ] <port> which current server will accept connexions.
/// @param argv [ 2 ] <password> which will allow identifications of IRC clients.
/// @return Exit status.
int	main ( int argc, char **argv ){
	static_cast< void >( argc );
	try {
		Server ircserv;
		ircserv.setPort( argv[ 1 ] );

	} catch ( std::exception &e ) {
		std::cerr << e.what() << std::endl;
	}
	return ( EXIT_SUCCESS );
}
