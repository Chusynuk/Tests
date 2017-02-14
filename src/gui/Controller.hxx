#ifndef Controller_hxx
#define Controller_hxx

#include <QObject>

class Controller : public QObject
{
Q_OBJECT

public slots:

	void moveNorth()
	{
		emit doMove( "North" );
	}

	void moveSouth()
	{
		emit doMove( "South" );
	}

	void moveEast()
	{
		emit doMove( "East" );
	}

	void moveWest()
	{
		emit doMove( "West" );
	}

	void useItem( const std::string & itemName )
	{
		emit doUseItem( itemName );
	}

signals:

	void doMove( const std::string & direction );
	void doUseItem( const std::string & itemName );

};

#endif
