#ifndef CommandWidget_hxx
#define CommandWidget_hxx

#include <QtGui>
#include <vector>
#include "Controller.hxx"

class CommandWidget : public QWidget
{
Q_OBJECT

	QPushButton _north;
	QPushButton _south;
	QPushButton _east;
	QPushButton _west;
	QPushButton _use;
	QLabel _itemLabel;
	QComboBox _items;
	QLabel _characterLabel;
	QComboBox _characters;
	QGridLayout _layout;

public:

	CommandWidget( const Controller * controller )
		: _north( "Move north" )
		, _south( "Move south" )
		, _east( "Move east" )
		, _west( "Move west" )
		, _use( "Use item" )
		, _itemLabel( "Items" )
		, _characterLabel( "Characters" )
		, _layout( this )
	{
		setFixedSize( 300, 400 );
		_layout.addWidget( &_south, 2, 0 );
		_layout.addWidget( &_north, 0, 0 );
		_layout.addWidget( &_east, 1, 0 );
		_layout.addWidget( &_west, 3, 0 );
		_layout.addWidget( &_use, 4, 0 );
		_layout.addWidget( &_itemLabel, 5, 0 );
		_layout.addWidget( &_items, 6, 0 );
		_layout.addWidget( &_characterLabel, 7, 0 );
		_layout.addWidget( &_characters, 8, 0 );
		_layout.setAlignment( Qt::AlignCenter );

		connect( &_north, SIGNAL( clicked() ), controller, SLOT( moveNorth() ) );
		connect( &_south, SIGNAL( clicked() ), controller, SLOT( moveSouth() ) );
		connect( &_east,  SIGNAL( clicked() ), controller, SLOT( moveEast()  ) );
		connect( &_west,  SIGNAL( clicked() ), controller, SLOT( moveWest()  ) );
		connect( &_use,   SIGNAL( clicked() ), this,       SLOT( useItem()   ) );

		connect( this, SIGNAL( useItem( const std::string & ) ),
		         controller, SLOT( useItem( const std::string & ) ) );
	}
	
	void updateItems( std::vector< std::string > & items )
	{
		_items.clear();
		for ( std::vector< std::string >::iterator it = items.begin(); it != items.end(); ++it )
			_items.addItem( QString::fromStdString( *it ) );
	}
	
	void updateCharacters( std::vector< std::string > & chars )
	{
		_characters.clear();
		for ( std::vector< std::string >::iterator it = chars.begin(); it != chars.end(); ++it )
			_characters.addItem( QString::fromStdString( *it ) );
	}

public slots:

	void useItem()
	{
		emit useItem( _items.currentText().toStdString() );
	}

signals:

	void useItem( const std::string & itemName );

};

#endif
