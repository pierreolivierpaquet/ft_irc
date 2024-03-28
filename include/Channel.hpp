/******************************************************************************/
/*                                                                            */
/*                                    IRC                                     */
/*                                                                            */
/******************************************************************************/

#ifndef		__CHANNEL_H__
# define	__CHANNEL_H__

# include "main.hpp"

class	Channel {

	public:

		Channel( std::string name );			// Name of the channel
		~Channel( void );

		std::string getName( void );
		void addClient( Clients client );

	private:

		std::map<int, Clients> _clientList;		//	MAP Container: <key>[ Clients->_fd ]:<value>[ Clients instance ]
		std::string _name;
};	/*	Channel	*/

#endif // __CHANNEL_H__
