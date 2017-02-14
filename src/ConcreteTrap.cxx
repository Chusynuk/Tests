/**	
 *	Enginyeria del Software G1-15
 *	
 *	FILE: ConcreteTrap.cxx
 */

#include "Location.hxx"
#include "Character.hxx"

// If the item is a trap, the information returned must include the damage done
std::string ConcreteTrap::useItem( Location * newLocation, Character * newCharacter )
{
	std::string uses = ItemDecorator::useItem( newLocation, newCharacter );

	return uses + newCharacter->name() + newCharacter->setDamage( 5 );
}
