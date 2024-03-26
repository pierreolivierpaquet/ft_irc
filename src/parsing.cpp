/******************************************************************************/
/*                                                                            */
/*                                    IRC                                     */
/*                                                                            */
/******************************************************************************/

#include "main.hpp"

//	3.1.1 Password message
//			Command: PASS
//			Parameters: <password>


//	3.1.2 Nick message
//			Command: NICK
//			Parameters: <nickname>

//	3.1.3 User message
//			Command: USER
//			Parameters: <user> <mode> <unused> <realname>
//			ex:	USER 	guest 		0	 *		 :Ronnie Reagan

//	3.1.4 Oper message
//			Command: OPER
//			Parameters: <name> <password>

//	3.1.5 User mode message
//			Command: MODE
//			Parameters: <nickname> *( ( "+" / "-" ) *( "i" / "w" / "o" / "O" / "r" ) )
//			ex:	MODE	 WiZ		 -w

//	3.1.6 Service message
//			Command: SERVICE
//			Parameters: <nickname> <reserved> <distribution> <type> <reserved> <info>

//	3.1.7 Quit
//			Command: QUIT
//			Parameters: [ <Quit Message> ]

//	3.1.8 Squit
//			Command: SQUIT
//			Parameters: <server> <comment>

/// @brief Takes a string and split it using whitespaces as delimiter.
/// @param input	String from Client (user) used to populate the container, to be
///					used in the tokenization process of each IRC command.
/// @return The populated container.
std::vector< std::string >	cmd::split( std::string input ) {
	std::vector< std::string >	tmp_split;
	std::istringstream			IN( input );
	std::string					buffer = EMPTY_STR;
	std::string					tmp_buffer = EMPTY_STR;

	while (IN.eof() == false && IN.good()) {
		IN >> buffer;
		if (buffer[ 0 ] == ':') {
			getline( IN, tmp_buffer );
			buffer.append( tmp_buffer );
			buffer = buffer.substr( 1, std::string::npos );
		}
		if (buffer.size()) {
			tmp_split.push_back( buffer );
			buffer.clear();
		}
	}
	//	PRINT DELETE --------
		for(std::vector<std::string>::iterator it = tmp_split.begin(); it != tmp_split.end(); it++) {
			std::cout << *it << std::endl;
		}
	//	DELETE --------------
	return ( tmp_split );
}
