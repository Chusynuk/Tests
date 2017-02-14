/**	
 *	Enginyeria del Software G1-15
 *	
 *	FILE: Character.hxx	
 */

#ifndef Character_hxx
#define Character_hxx

#include <iostream>

class Location;
class AbstractItem;

class Character{

// We define the attributes of character, so inherited classes can change them 
protected:

	std::string _name;
	unsigned int _level;
	unsigned int _life;
	std::string _weapon;
	unsigned int _type;

	// Pointer manipulated at "Character.cxx", uses Location information
	Location * _location;

	// Pointer manipulated at "Character.cxx", uses Item information
	AbstractItem * _item;

public:

	Character() {
		_name = "unknown";		
		_level = 0;
		_life =  10;
		_weapon = "";
		_type = 1;
		_location = 0;
		_item = 0;
	}

	Character( const std::string & newName ) {
		_name = newName;
		_level = 0;
		_life =  10;
		_weapon = "";
		_type = 1;	
		_location = 0;
		_item = 0;
	}

	Character( const std::string & newName, unsigned int newLevel ) {
		_name = newName;
		_level = newLevel;	
		_life =  10;	
		_weapon = "";
		_type = 1;
		_location = 0;
		_item = 0;
	}


	std::string name() const { return _name; }

	unsigned int getLevel() const { return _level; }

	unsigned int getLife() const { return _life; }

	unsigned int getType() const { return _type; }

	Location * getLocation() const { return _location; }

	AbstractItem * getItem() const { return _item; }

	
	void name( const std::string &newName ) { _name = newName; }

	void setLevel( const unsigned int newLevel ) { _level = newLevel; }

	void setLife( const unsigned int newLife ) { _life = newLife; }

	
	std::string setCure ( const unsigned int someCure )
	{
		if ( _life + someCure <= 10 )
			_life += someCure;		
		else
			_life = 10;

		std::stringstream ss;
		ss << someCure;

		return " gains " + ss.str() + " life\n";
	}

	std::string setDamage( const unsigned int someDamage )
	{
		if ( someDamage > _life )
			_life = 0;
		else
			_life -= someDamage;

		std::stringstream ss;
		ss << someDamage;

		return " takes " + ss.str() + " damage\n";
	}


	// Returns a string containing how many magic the character has received
	virtual std::string receiveMagic ( unsigned int newPoints )	
	{
		std::stringstream points;
		points << newPoints;

		return name() + " receives " + points.str() + " magic points\n";
	}

	// Method that stablish a main weapon when the character is carrying the item
	std::string setMainWeapon( const std::string newItem )
	{
		_weapon = newItem;

		return name() + " set " + newItem + " as main weapon\n";
	}

	// The character hits the character referenced in the argument
	std::string hit ( Character & newPrey )
	{
		std::string damage = "";
		unsigned int points;

		// If no weapon has been picked up, the character attacks with arms and legs
		if ( _weapon == "" ) {
			points = 1; damage = newPrey.setDamage( points );
		} else if ( _weapon == "Hammer" ) {
			points = 2; damage = newPrey.setDamage( points );
		} else if ( _weapon == "Sword" ) {
			points = 4; damage = newPrey.setDamage( points );
		} else if ( _weapon == "Staff" ) {
			points = 5; damage = newPrey.setDamage( points );
		}		

		// We want to distinguish between CureCharacters (type==2) and DamageCharacters (type==3)
		if ( newPrey.getType() == 2 )
			return newPrey.name() + newPrey.setDamage( points );
		else if ( newPrey.getType() == 3 && points == 4 ) {
		
			std::string newDamage = newPrey.name() + newPrey.setDamage( points );

			if ( newPrey.getLife() == 0 )
				newDamage += newPrey.name() + " is dead\n";

			return newDamage;
		}
		else if ( newPrey.getType() == 3 )
			return newPrey.receiveMagic( points );

		return newPrey.name() + damage;
	}


	/* The next methods are implemented at Character.cxx, since they use Location information */

	// Method used to assign each character into a concrete location
	void locateAt( Location & newLocation );

	// In order to take an object if it is not carried by anyone
	std::string pickup ( const std::string & newItem );

	// When a character is attacked, he drops the item carried
	std::string drop ();

	//
	void move ( const std::string & newDirection );


	virtual ~Character() {}

};

#endif
