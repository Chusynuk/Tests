/**	
 *	Enginyeria del Software G1-15
 *	
 *	FILE: ConcreteTrap.hxx
 */

#ifndef ConcreteTrap_hxx
#define ConcreteTrap_hxx

#include <iostream>
#include "ItemDecorator.hxx"

class ConcreteTrap : public ItemDecorator {
	
public:

	ConcreteTrap( AbstractItem * absItem ) : ItemDecorator(absItem){}
	
	std::string useItem( Location * newLocation, Character * newCharacter );
	
};

#endif

