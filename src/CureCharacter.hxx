/**	
 *	Enginyeria del Software G1-15
 *	
 *	FILE: CureCharacter.hxx	
 */

#ifndef CureCharacter_hxx
#define CureCharacter_hxx

#include <iostream>
#include "Character.hxx"

class CureCharacter : public Character {

public:

	// Constructor for DamageCharacters
	CureCharacter ( const std::string newName, const unsigned int newLevel ) {
		_name = newName;
		_level = newLevel;
		_type = 2;
	} 

	// For a cure character it returns how many magic points he has received and also the healing done 
	std::string receiveMagic ( unsigned int newPoints )
	{
		setCure( newPoints );

		std::stringstream points;
		points << newPoints;

		// The next line calls to the method of the superior class
		return 	Character::receiveMagic( newPoints ) +
				_name + " gains " + points.str() + " life\n";
	}

};

#endif

