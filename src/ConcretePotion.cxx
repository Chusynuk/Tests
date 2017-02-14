/**	
 *	Enginyeria del Software G1-15
 *	
 *	FILE: ConcretePotion.cxx
 */

#include "Location.hxx"
#include "Character.hxx"

// If the item is a potion, the information returned must include the healing done
std::string ConcretePotion::useItem( Location * newLocation, Character * newCharacter )
{
	std::string uses = ItemDecorator::useItem( newLocation, newCharacter );

	return uses + newCharacter->name() + newCharacter->setCure( 5 );
}
