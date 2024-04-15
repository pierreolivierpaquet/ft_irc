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
#  define	DEFAULT_MODE		0b00000001
# endif	/*	DEFAULT_MODE	*/

# define	INVITE_MODE			0b00000010
# define	TOPIC_MODE			0b00000100
# define	KEY_MODE			0b00001000
# define	OPERATOR_MODE		0b00010000
# define	LIMIT_MODE			0b00100000
# define	FULL_MODE			0b00111111

# define	CHMOD_CHAR			"+-"
# define	MODE_CHAR			"snitkol"

# define	MODE_FUNC_AMOUNT	5

///	------------------------------------------------------------------- @section CLASS.ES

class	Channel {

	public:

		Channel( std::string name );			// Name of the channel
		~Channel( void );

		std::string				getName( void );
		std::vector<int>		&getOper( void );
		std::map<int, Clients>	&getClientList( void );
		void					setOper( Clients & client );
		int						addClient( Clients client );
		void					addWhiteList( Clients & client );
		void					deleteWhiteList( Clients & client );
		bool					isInvited( Clients & client );
		void					deleteClient( Clients client );
		void					deleteOper( Clients client );
		bool					checkKey( std::string key );
		bool					checkLimit( void	 );

		void					ModeOption( Clients &client, short set, char mode, std::vector< std::string > param );
		void					setMode( u_int16_t mask );
		void					unsetMode( u_int16_t mask );
		u_int16_t				getMode( void ) const;
		std::string				getTopic( void ) const;
		void					setTopic( const std::string& );
		bool					isMode( u_int16_t mode ) const;
		int						findClient( std::string name ) const;
		std::vector< int >::const_iterator	findOperator( int client_fd ) const;

	private:

		std::map<int, Clients>	_clientList;		//	MAP Container: <key>[ Clients->_fd ]:<value>[ Clients instance ]
		std::vector<int> 		_operList;
		std::vector<std::string> _whiteList;
		std::string				_name;
		std::string				_topic;
		u_int16_t				_mode; // Bitfield to monitor channel's mode(s).
		void					_ChanMode( char mode );
		std::string	 			_key;
		u_int32_t				_clients_limit;

		typedef	enum {
			INV, TOP, KEY, OPS, LIM
		}	e_func_mode;
		typedef	void (Channel::*fmode)( Clients &, short, char, std::vector< std::string > );
		void	_modefuncmapping( void );
		fmode	_mode_func[ MODE_FUNC_AMOUNT ];
		void	_mode_topic( Clients &client, short set, char mode, std::vector< std::string > param );
		void	_mode_invite( Clients &client, short set, char mode, std::vector< std::string > param );
		void	_mode_key( Clients &client, short set, char mode, std::vector< std::string > param );
		void	_mode_operator( Clients &client, short set, char mode, std::vector< std::string > param );
		void	_mode_limit( Clients &client, short set, char mode, std::vector< std::string > param );
		void	_broadcast( std::string message ) const;

};	/*	Channel	*/

#endif // CHANNEL_HPP_
