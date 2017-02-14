/**	
 *	Enginyeria del Software G1-15
 *	
 *	FILE: ItemDecorator.hxx
 */

#ifndef ItemDecorator_hxx
#define ItemDecorator_hxx

#include "AbstractItem.hxx"

class ItemDecorator : public AbstractItem {
	
protected:

	AbstractItem * _absItem;

public:

	ItemDecorator ( AbstractItem * item ){
		_absItem = item;
	}


	std::string getName () { return _absItem->getName(); }

	unsigned int getLevel () { return _absItem->getLevel(); }


	bool state () { return _absItem->state(); }

	void state ( bool newState ) { return _absItem->state( newState ); }

	bool isCarried () { return _absItem->isCarried(); }


	std::string description ()
	{
		return _absItem->description();
	}

	std::string receiveMagic ( const unsigned int newPoints )
	{
		return _absItem->receiveMagic( newPoints );
	}

	std::string useItem ( Location * newLocation, Character * newCharacter )
	{
		return _absItem->useItem( newLocation, newCharacter );
	}

	std::string carry ()
	{
		return _absItem->carry();
	}



	~ItemDecorator()
	{
		if ( _absItem != NULL ) 
			delete _absItem; 
	}
	
};

#endif

