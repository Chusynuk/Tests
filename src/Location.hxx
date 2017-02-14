/**	
 *	Enginyeria del Software G1-15
 *	
 *	FILE: Location.hxx
 */

#ifndef Location_hxx
#define Location_hxx

#include <iostream>
#include <sstream>
#include <vector>
#include "Exceptions.hxx"

#include "Character.hxx"
#include "DamageCharacter.hxx"
#include "CureCharacter.hxx"

#include "Item.hxx"
#include "AbstractItem.hxx"
#include "ConcreteVanish.hxx"
#include "ConcreteTrap.hxx"
#include "ConcretePotion.hxx"
#include "ConcreteBomb.hxx"

// AbstractItem and Character vectors are redefined
typedef std::vector<AbstractItem *> Items;
typedef std::vector<Character *> Characters;

class Location{

private:

	std::string _name;
	Items _items;
	Characters _characters;

	Location * _north;
	Location * _south;
	Location * _east;
	Location * _west;

public:

	Location () {
		_name = "unknown";
		_north = NULL;
		_south = NULL;
		_east = NULL;
		_west = NULL;
	}

	Location ( const std::string &newName ) {
		_name = newName;
		_north = NULL;
		_south = NULL;
		_east = NULL;
		_west = NULL;
	}
	

	void name ( const std::string &newName ) { _name = newName; }

	std::string name () const { return _name; }
	

	std::string description ()
	{
		std::string description = "Location: " + _name + "\n";

		description += connections();
		description += items();
		description += characters();

		return description;
	}

	// Here we return a string that includes the four posible directions of each location
	std::string connections () const 
	{
		std::string connections = "";

		// In order to include in the description whether it has an exit or not
		if ( _north != NULL )	connections += "\tNorth: " + _north->name() + "\n";
		if ( _south != NULL )	connections += "\tSouth: " + _south->name() + "\n";
		if ( _east 	!= NULL )	connections += "\tEast: " + _east->name() + "\n";
		if ( _west  != NULL )	connections += "\tWest: " + _west->name() + "\n";

		return connections;
	}
	

	// Assign a south direction to the main location
	void connectSouth ( Location & newConnection ) { _south = & newConnection; }
	// Assign a north direction to the main location
	void connectNorth ( Location & newConnection ) { _north = & newConnection; }
	// Assign a west direction to the main location
	void connectWest ( Location & newConnection ) { _west = & newConnection; }
	// Assign a east direction to the main location
	void connectEast ( Location & newConnection ) { _east = & newConnection; }


	// Getters
	Location * south () { return _south; }
	Location * north () { return _north; }
	Location * west ()  { return _west; }
	Location * east ()  { return _east; }


	// We run both "_characters" and "_items" vectors and store the addition in a string
	std::string distributeMagic ( const unsigned int newPoints )
	{
		std::string distribution = "";

		for ( Characters::iterator it = _characters.begin(); it != _characters.end(); ++it )
			distribution += (*it)->receiveMagic( newPoints );

		for ( Items::const_iterator it2 = _items.begin(); it2 != _items.end(); ++it2 )			
			distribution += (*it2)->receiveMagic( newPoints );	

		return distribution;
	}



	/*  %%%%%
		ITEMS
		%%%%%  */

	// Item's description is stored by creating an instance of Item and saving it into the vector
	void addItem ( const std::string & newName, const unsigned int newPoints )
	{
		AbstractItem * absItem = new Item( newName, newPoints );
		_items.push_back( absItem );
	}

	void addTrap ( const std::string & newName, unsigned int newPoints )
	{
		// Vanish -> It disappears after one use
		// Trap   -> Damages 5 points to the character's life
		AbstractItem * absItem = new ConcreteVanish(
								 new ConcreteTrap(
								 new Item(newName, newPoints) ) );

		_items.push_back( absItem );		
	}

	void addPotion ( const std::string & newName, unsigned int newPoints )
	{
		// Vanish -> It disappears after one use
		// Potion -> Heals 5 points to the character's life
		AbstractItem * absItem = new ConcreteVanish(
								 new ConcretePotion(
								 new Item(newName, newPoints) ) );

		_items.push_back( absItem );
	}

	void addBomb ( const std::string & newName, unsigned int newPoints )
	{
		// Bomb   -> It enables when receives magic, distribute magic when is used and enabled
		// Vanish -> It disappears after one use
		AbstractItem * absItem = new ConcreteBomb(
								 new ConcreteVanish(
								 new Item(newName, newPoints) ) );

		_items.push_back( absItem );
	}

	// Method that returns a string containing all the information about each item that has been created
	std::string items () const
	{
		std::string items = "";

		for ( Items::const_iterator it = _items.begin(); it != _items.end(); ++it )
			items += "\tItem: " + (*it)->description() + "\n";

		return items;
	}

	// This matches "itemName" with each item name stored in the vector and returns its position in memory
	AbstractItem & findItem ( const std::string & newName )
	{
		if ( _items.empty() != true )
		{
			for ( Items::const_iterator it = _items.begin(); it != _items.end(); ++it )
				if( (*it)->getName() == newName )
					return (**it);
		}

		throw ItemNotFound();	
	}

	// In order to know if an Item is at the location, in order to check it without managing exceptions
	bool isItem ( const std::string & newName )
	{
		for ( Items::const_iterator it = _items.begin(); it != _items.end(); ++it )
			if( (*it)->getName() == newName )
				return true;

		return false;
	}

	// By matching the where the iterator points and the pointer of a item, we can delete it from the vector
	void removeItem ( const std::string & newName )
	{
		AbstractItem & absItem = findItem( newName );

		for ( Items::iterator it = _items.begin(); it != _items.end(); ++it )
			if( *it == &absItem )
			{
				delete *it;
				it = _items.erase(it);
				return;
			}
	}

	// Checks whether a character is able to pick up an item or not 
	std::string useItem ( const std::string & newCharacter, const std::string & newItem )
	{
		if ( findCharacter( newCharacter ).getLevel() < findItem( newItem ).getLevel() )			
			return "The level of " + newCharacter + " is too low\n";

		else
			return findItem( newItem ).useItem( this, & (findCharacter( newCharacter )) );		
	}



	/*  %%%%%%%%%%  *
	 *	CHARACTERS  *
	 *	%%%%%%%%%%  */

	// The same way as we did with Items, now we store a character in the back of the character's vector
	void placeCharacter ( Character & c )
	{
		Character * characterPlaced = &c;
		_characters.push_back( characterPlaced );
	}

	// In order to put a character off a location
	void unplaceCharacter ( Character & c )
	{
		for ( Characters::iterator it = _characters.begin(); it != _characters.end(); ++it )
			if ( (*it)->name() == c.name() )
			{
				it = _characters.erase(it);
				return;
			}

		throw CharacterNotFound();
	}     

	// Returns a string that enumerates the characters stored in a location
	std::string characters ()
	{
		std::string characters = "";

		for ( Characters::iterator it = _characters.begin(); it != _characters.end(); ++it )
			characters += "- " + (*it)->name() + " is here.\n";

		return characters;
	}

	// A reference to the character is returned with its name as an argument
	Character & findCharacter ( const std::string & newName )
	{
		if ( _characters.empty() != true ) {
			for ( Characters::const_iterator it = _characters.begin(); it != _characters.end(); ++it )
				if ( (*it)->name() == newName )
					return (**it);
		}

		throw CharacterNotFound();
	}



	~Location()
	{
		for ( Items::iterator it = _items.begin(); it != _items.end(); ++it )
			delete(*it);
	}

};

#endif








