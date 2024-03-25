/******************************************************************************/
/*                                                                            */
/*                                    IRC                                     */
/*                                                                            */
/******************************************************************************/

#ifndef __CHANNEL_H__
#define __CHANNEL_H__

#include "main.hpp"

class Channel {

public:

	Channel( std::string name );
	~Channel( void );

	std::string getName( void );
	void addClient( Clients client );

private:

	std::map<int, Clients> _clientList;
	std::string _name;

};

#endif // __CHANNEL_H__