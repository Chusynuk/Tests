/**	
 *	Enginyeria del Software G1-15
 *	
 *	FILE: Item.hxx
 */

#ifndef Item_hxx
#define Item_hxx

#include <iostream>
#include "AbstractItem.hxx"

class Location;
class Character;

class Item : public AbstractItem {

protected:

	std::string _name;
	unsigned int _level;
	bool _state;
	bool _isCarried;

public:

	Item () {
		_name = "unknown";
		_level = 50;
		_state = false;
		_isCarried = false;
	}

	Item ( const std::string & newName, const unsigned int newLevel ) {
		_name = newName;
		_level = newLevel;
		_state = false;
		_isCarried = false;
	}

	std::string getName () { return _name; }

	unsigned int getLevel () { return _level; }


	// 0 / false  =>  disabled
	// 1 / true   =>   enabled
	bool state () { return _state; }

	void state ( bool newState ) { _state = newState; }

	bool isCarried () { return _isCarried; }

	
	std::string description () 
	{
		std::stringstream ss;
		ss << getName() << " [" << getLevel() << "]";
 		return ss.str();  
	}

	// Returns a string containing how many magic the item has received	
	std::string receiveMagic ( const unsigned int newPoints )
	{
		std::stringstream points;
		points << newPoints;

		return _name + " receives " + points.str() + " magic points\n";
	}


	/* The next methods are implemented at Item.cxx, since they use Character information */

	// In order to mantain a reference to the current character and location
	std::string useItem ( Location * newLocation, Character * newCharacter );

	// In order to mantain a reference to the character that is currently using the item
	std::string carry ();

};

#endif
