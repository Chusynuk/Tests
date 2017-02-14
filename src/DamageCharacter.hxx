/**	
 *	Enginyeria del Software G1-15
 *	
 *	FILE: DamageCharacter.hxx	
 */

#ifndef DamageCharacter_hxx
#define DamageCharacter_hxx

#include <iostream>
#include "Character.hxx"

class DamageCharacter : public Character {

public:

	// Constructor for DamageCharacters
	DamageCharacter ( const std::string newName, const unsigned int newLevel ) {
		_name = newName;
		_level = newLevel;
		_type = 3;
	} 

	// For a damage character it returns how many magic points he has received and also the damage done 
	std::string receiveMagic ( unsigned int newPoints )
	{
		setDamage( newPoints );

		std::stringstream points;
		points << newPoints;

		// The next line calls to the method of the superior class
		return 	Character::receiveMagic( newPoints ) +
				_name + " takes " + points.str() + " damage\n";
	}

};

#endif

