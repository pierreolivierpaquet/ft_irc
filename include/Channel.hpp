/******************************************************************************/
/*                                                                            */
/*                                    IRC                                     */
/*                                                                            */
/******************************************************************************/

#ifndef		CHANNEL_HPP_
# define	CHANNEL_HPP_

# include	"main.hpp"

///	------------------------------------------------------------------- @section MACRO.S

# ifndef	DEFAULT_MODE
#  define	DEFAULT_MODE	0b00000001
# endif	/*	DEFAULT_MODE	*/

# define	INVITE_MODE			0b00000010
# define	TOPIC_MODE			0b00000100
# define	KEY_MODE			0b00001000
# define	OPERATOR_MODE		0b00010000
# define	LIMIT_MODE			0b00100000
# define	FULL_MODE			0b00111111

# define	CHMOD_CHAR		"+-"
# define	MODE_CHAR		"itkol"

///	------------------------------------------------------------------- @section CLASS.ES

class	Channel {

	public:

		Channel( std::string name );			// Name of the channel
		~Channel( void );

		std::string	getName( void );
		void setOper( Clients & client );
		std::vector<int> & getOper( void );
		int		addClient( Clients client );
		std::map<int, Clients> & getClientList( void );

		void			mode( char mode );
		void			setMode( u_int16_t mask );
		void			unsetMode( u_int16_t mask );
		u_int16_t		getMode( void ) const;
		std::string		getTopic( void ) const;
		void			setTopic( const std::string& );
		bool			isMode( u_int16_t mode ) const;

	private:

		std::map<int, Clients>	_clientList;		//	MAP Container: <key>[ Clients->_fd ]:<value>[ Clients instance ]
		std::vector<int> 		_operList;
		std::string				_name;
		std::string				_topic;
		u_int16_t				_mode; // Bitfield to monitor channel's mode(s).
};	/*	Channel	*/

#endif // 0CHANNEL_HPP_
