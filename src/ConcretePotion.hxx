/**	
 *	Enginyeria del Software G1-15
 *	
 *	FILE: ConcretePotion.hxx
 */

#ifndef ConcretePotion_hxx
#define ConcretePotion_hxx

#include <iostream>
#include "ItemDecorator.hxx"

class ConcretePotion : public ItemDecorator {
	
public:

	ConcretePotion( AbstractItem * absItem ) : ItemDecorator(absItem){}
	
	std::string useItem( Location * newLocation, Character * newCharacter );
	
};

#endif
