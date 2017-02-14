/**	
 *	Enginyeria del Software G1-15
 *	
 *	FILE: Item.cxx
 */

#include "Location.hxx"
#include "Character.hxx"

// Returns information about who uses which item in what location
std::string Item::useItem ( Location * newLocation, Character * newCharacter )
{
	return newCharacter->name() + " uses " + this->_name + " at " + newLocation->name() + "\n";
}

// Assign a character to the item and returns a string containing the action
std::string Item::carry ()
{
	// The item carried change its attribute for being carried to true
	_isCarried = true;

	return " picks up " + getName() + "\n";
}