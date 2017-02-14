/**	
 *	Enginyeria del Software G1-15
 *	
 *	FILE: ConcreteBomb.hxx
 */

#ifndef ConcreteBomb_hxx
#define ConcreteBomb_hxx

#include <iostream>
#include "ItemDecorator.hxx"

class ConcreteBomb : public ItemDecorator {
	
public:

	ConcreteBomb( AbstractItem * absItem ) : ItemDecorator(absItem){}
	
	std::string useItem( Location * newLocation, Character * newCharacter );
	std::string receiveMagic( const unsigned int newPoints );

};

#endif

