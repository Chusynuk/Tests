#ifndef View_h
#define View_h

#include <sstream>
#include "CommandWidget.hxx"
#include "GameWidget.hxx"

class View : public QWidget
{
Q_OBJECT

	CommandWidget _command;
	GameWidget _south;
	GameWidget _north;
	GameWidget _east;
	GameWidget _west;
	GameWidget _location;
	QLabel _output;
	QGridLayout _layout;

public:

	View( const Controller * controller )
		: _command( controller )
		, _south( "South" )
		, _north( "North" )
		, _east( "East" )
		, _west( "West" )
		, _location( "Location" )
		, _layout(this)
	{
		_layout.addWidget( &_south, 2, 1 );
		_layout.addWidget( &_north, 0, 1 );
		_layout.addWidget( &_east, 1, 2 );
		_layout.addWidget( &_west, 1, 0 );
		_layout.addWidget( &_location, 1, 1 );
		_layout.addWidget( &_command, 0, 3, 3, 1 );
		_layout.addWidget( &_output, 4, 0, 1, 4 );
		_output.setAlignment( Qt::AlignCenter );
	}

public slots:

	void update( const std::string & locationDetails, const std::string & event )
	{
		std::string token, name;
		std::vector<std::string> items, characters;

		_south.update( "" );
		_north.update( "" );
		_east.update( "" );
		_west.update( "" );

		std::istringstream is( locationDetails );
		is >> token >> name;
		_location.update( name );
		while ( is >> token )
		{
			is >> name;
			if ( token == "South:" ) _south.update( name );
			if ( token == "North:" ) _north.update( name );
			if ( token == "East:" ) _east.update( name );
			if ( token == "West:" ) _west.update( name );
			if ( token == "Item:" )
			{
				items.push_back( name );
				is >> name;
			}
			if ( token == "-" ) {
				characters.push_back( name );
				is >> name >> name;
			}
		}
		_command.updateItems( items );
		_command.updateCharacters( characters );
		_output.setText( QString::fromStdString( event ) );
	}

};

#endif
