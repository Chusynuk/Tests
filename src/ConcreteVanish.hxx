/**	
 *	Enginyeria del Software G1-15
 *	
 *	FILE: ConcreteVanish.hxx
 */

#ifndef ConcreteVanish_hxx
#define ConcreteVanish_hxx

#include <iostream>
#include "ItemDecorator.hxx"

class ConcreteVanish : public ItemDecorator {

public:

	ConcreteVanish( AbstractItem * absItem ) : ItemDecorator(absItem){}

	std::string useItem( Location * newLocation, Character * newCharacter );
	
};

#endif

