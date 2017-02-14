/**	
 *	Enginyeria del Software G1-15
 *	
 *	FILE: ConcreteVanish.cxx
 */

#include <iostream>
#include "Location.hxx"
#include "Character.hxx"

// For a item to disappear it just call the main method
std::string ConcreteVanish::useItem( Location * newLocation, Character * newCharacter )
{	
	// Before removing the item we obtain its information
	std::string uses = ItemDecorator::useItem( newLocation, newCharacter );

	// The item will vanish/disappears, so it cannot be used again
	newLocation->removeItem( this->getName() );

	return uses;
}