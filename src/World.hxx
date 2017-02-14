/**	
 *	Enginyeria del Software G1-15
 *	
 *	FILE: World.hxx	
 */

#ifndef World_hxx
#define World_hxx

#include <iostream>
#include <fstream>
#include <sstream>

#include "Location.hxx"
#include "Character.hxx"
#include "Item.hxx"

#include "Model.hxx"

// Location and Character vectors are redefined
typedef std::vector<Location *> Locations;
typedef std::vector<Character *> Characters;

class World : public Model {

private:
	Locations _locations;
	Characters _characters;	

public:

	// Constructor
	World() {

	}



	/*  %%%%%%%%%  *
	 *	LOCATIONS  *
	 *	%%%%%%%%%  */

	// Location's name is stored at the end of the vector
	void addLocation ( const std::string & newLocation )
	{
		_locations.push_back( new Location(newLocation) );
	}

	// For each relation in this function we assign north and south direction vice versa
	void connectNorthToSouth ( const std::string & north, const std::string & south )
	{
		for ( Locations::iterator it = _locations.begin(); it != _locations.end(); ++it )
		{
			if( (*it)->name() == north )	(*it)->connectSouth( findLocation( south ) );
			if( (*it)->name() == south )	(*it)->connectNorth( findLocation( north ) );
		}

	}

	// For each relation in this function we assign west and east direction vice versa
	void connectWestToEast ( const std::string & west, const std::string & east )
	{
		for ( Locations::iterator it = _locations.begin(); it != _locations.end(); ++it )
		{
			if( (*it)->name() == west )		(*it)->connectEast( findLocation(east) );
			if( (*it)->name() == east )		(*it)->connectWest( findLocation(west) );
		}

	}

	// This method allow to add magic points to all characters of a location 
	std::string distributeMagic ( std::string newLocation, unsigned int newPoints )
	{		
		return findLocation( newLocation ).distributeMagic( newPoints );
	}

	// We iterate through the _locations vector in order to extract the whole ubications
	std::string locations () const
	{
		std::string locations = "";

		if ( _locations.empty() != true )
			for ( Locations::const_iterator it = _locations.begin(); it != _locations.end(); ++it )
				locations += (*it)->name() + "\n";

		return locations;
	} 

	// We look for the location that corresponds to the input parameter newDetails
	std::string locationDetails ( const std::string & newLocation )
	{
		// We call the description method in Location Class
		return findLocation( newLocation ).description();
	}

	// Returns a reference to the location specified in the argument
	Location & findLocation ( const std::string & newLocation )
	{
		// If _locations has no locations in it, we skip to iterate and throw the exception
		if ( _locations.empty() != true )
		{	
			for ( Locations::iterator it = _locations.begin(); it != _locations.end(); ++it )
				if( (*it)->name() == newLocation )
					return (**it);
		}

		throw LocationNotFound();
	}

	// In order to know if a Location exists, in order to check it without managing exceptions
	bool isLocation ( const std::string & newName )
	{
		for ( Locations::const_iterator it = _locations.begin(); it != _locations.end(); ++it )
			if( (*it)->name() == newName )
				return true;

		return false;
	}



	/*  %%%%%%%%%%  *
	 *	CHARACTERS  *
	 *	%%%%%%%%%%  */

	// Store a character into the vector declared in the beginning
	void addCharacter ( const std::string & newName, unsigned int newLevel )
	{
		_characters.push_back( new Character(newName, newLevel) );
	}

	// Creates a new character, damage character type, and store it into the vector 
	void addDamageCharacter ( const std::string & newName, unsigned int newPoints )
	{
		Character * damCharacter = new DamageCharacter( newName, newPoints );
		_characters.push_back( damCharacter );
	}

	void addCureCharacter ( const std::string & newName, unsigned int newPoints )
	{
		Character * cureCharacter = new CureCharacter( newName, newPoints );
		_characters.push_back( cureCharacter );
	}

	// We run through the characters and locations, so we can match the names and assign a location using locateAt
	void placeCharacter ( const std::string & newCharacter, const std::string & newLocation )
	{	
		findCharacter( newCharacter ).locateAt( findLocation(newLocation) );
	}

	// It returns a string containing the names of each character in the vector
	std::string characters () const
	{
		std::string characters = "";

		for ( Characters::const_iterator it = _characters.begin(); it != _characters.end(); ++it )
				characters += (*it)->name() + "\n";

		return characters;
	}

	// Returns a reference to the character specified in the argument as a string
	Character & findCharacter ( const std::string & newCharacter )
	{
		// If _characters has no people in it, we skip to iterate and throw the exception
		if ( _characters.empty() != true )
		{	
			for ( Characters::iterator it = _characters.begin(); it != _characters.end(); ++it )
				if( (*it)->name() == newCharacter )
					return (**it);
		}

		throw CharacterNotFound();
	}

	// We want to know if the location where the character is staying, contains the item specified
	std::string pickup ( const std::string & newCharacter, const std::string & newItem )
	{
		// We distinguish whether the character is placed or not, in order to manage memory leaks
		// Since in the test_pickup_whenAlreadyTaken the second character is not placed anywhere
		
		// If the character is not placed, we must look for the item through all the locations
		if ( findCharacter( newCharacter ).getLocation() == 0 )
		{
			for ( Locations::iterator it = _locations.begin(); it != _locations.end(); ++it )
				// We check if the location contains the item
				if ( (*it)->isItem( newItem ) )
					// If so, we get its concrete reference and check if it is carried
					if( (*it)->findItem( newItem ).isCarried() == true )
						throw ItemNotFound();
		}
		// If the character is placed, then we check in its location if the item is already carried
		else
			if ( findCharacter( newCharacter ).getLocation()->findItem( newItem ).isCarried() == true )
				throw ItemNotFound();

		// Finally if the item is not carried we pick it up and return the corresponding message
		return findCharacter( newCharacter ).pickup( newItem );
	}

	// Check if the weapon to set is carried by the character and returns information about the setting
	std::string setMainWeapon( const std::string & newCharacter, const std::string & newItem )
	{
		// Since we setted a link between a character and the Item he has picked up,
		// We check that the Item is carried by the character specified
		if ( findCharacter( newCharacter ).getItem() == 0 || 
			 findCharacter( newCharacter ).getItem()->getName() != newItem )
			throw ItemNotFound();

		return findCharacter( newCharacter ).setMainWeapon( newItem );
	}

	// When a character hits another one
	std::string hit ( const std::string & newAttacker, const std::string & newPrey )
	{
		// In order to hit a character, both have to be in the same location
		if ( findCharacter( newAttacker ).getLocation() != findCharacter( newPrey ).getLocation() )
			throw CharacterNotFound();

		std::string droppedItem = "";

		// We want the prey to drop its currently carrying item and record the fact in a string
		if ( findCharacter( newPrey ).getItem() != 0 )
			droppedItem = findCharacter( newPrey ).drop();

		return droppedItem + findCharacter( newAttacker ).hit( findCharacter(newPrey) );
	}

	// When we want to change a character from one location to another
	void move( const std::string & newCharacter, const std::string & newLocation )
	{
		// If the location exists, there is a location with that name, we proceed by placing the character
		if ( isLocation( newLocation ) )
			placeCharacter( newCharacter, newLocation );
		// In other case, we should reassure that the location does not exists and let the method throw the exception
		else
			findLocation( newLocation );

	}

	/*  %%%%%
		ITEMS
		%%%%%  */

	// We search for the newLocation and once we find it, we store the item with the assigned parameters
	void addItemAtLocation ( const std::string & newLocation, const std::string & newItem, unsigned int newLevel )
	{
		return findLocation( newLocation ).addItem( newItem, newLevel );
	}

	// If the location exists we include a new item, in this case a trap, to a location
	void addTrapAtLocation ( const std::string & newLocation, const std::string & newName, unsigned int newPoints )
	{		
		return findLocation( newLocation ).addTrap( newName, newPoints );
	}

	void addPotionAtLocation ( const std::string & newLocation, const std::string & newName, unsigned int newPoints )
	{
		return findLocation( newLocation ).addPotion( newName, newPoints );
	}

	void addBombAtLocation ( const std::string & newLocation, const std::string & newName, unsigned int newPoints )
	{ 
		return findLocation( newLocation ).addBomb( newName, newPoints );
	}

	// We look for the location that enters as an argument and launch its own version of the method
	std::string useItem ( const std::string & newLocation, const std::string & newCharacter, const std::string & newItem )
	{
		return findLocation( newLocation ).useItem( newCharacter, newItem );
	}



	/*  %%%%
		MAPS
		%%%%  */

	// In order to read information from a file, the argument is the path to the text file
	void loadMap ( const char newPath[] )
	{
		std::ifstream file( newPath );	// We get in 'file' the content of the map
		
		std::string line;
		std::string token;

		// We do the following until we reach the end of file
		while ( file.eof() != true )
		{
			// Extract a line from the file stream and store it in 'line' variable
			std::getline( file, line );

			// Declare an input stream and obtain the first token of the line
			std::istringstream is( line );
			is >> token;

			// In order to skip blank/empty lines
			if ( line.empty() )		continue;

			// Distinguish between each action in map's file
			if ( token == "Location" )	checkLocation( line );
			if ( token == "Connection")	checkConnection( line );
			if ( token == "Character" )	checkCharacter( line );
			if ( token == "LocateAt" )	checkLocateAt( line );
			if ( token == "Item" )		checkItem( line );
		}

		file.close();
	}

	// For a Location, we extract its name from the line and store it to locations's vector
	void checkLocation ( const std::string & newLine )
	{
		std::istringstream is( newLine );
		std::string token;

		is >> token;	// token = "Location"
		is >> token;	// token = Location's name

		addLocation( token );
	}

	// Depending on the second word of the line we choose to connect north or west the two locations
	void checkConnection ( const std::string & newLine )
	{
		std::istringstream is( newLine );

		std::string token;		is >> token;		// token = "Connection"
		std::string type;		is >> type;			// type  = Where to connect
		std::string location1;	is >> location1;	// location1 = Location to connect
		std::string location2;	is >> location2;	// location2 = Location to connect

		if ( type == "North" )
			connectNorthToSouth( location1, location2 );
		if ( type == "West" )
			connectWestToEast( location1, location2 );
	}

	// For a Character, we proceed to extract the information and call the corresponding method
	void checkCharacter ( const std::string & newLine )
	{
		std::istringstream is( newLine );

		std::string token;		is >> token;	// token 	= "Character"
		std::string type;		is >> type;		// type  	= Character's type
		std::string newName;	is >> newName;	// newName 	= Character's name
		std::string newLevel;	is >> newLevel;	// newLevel = Character's level

		// We convert the level from a string to an unsigned int
		unsigned int level;
		std::istringstream ( newLevel ) >> level;

		// Here we distinguish the method to use by looking to the second line's parameter 
		if ( type == "Basic" )
			addCharacter( newName, level );
		else if ( type == "Damage" )
			addDamageCharacter( newName, level );
		else if ( type == "Cure" )
			addCureCharacter( newName, level );
		
		// Finally, if the Character's type does not match, we throw the Exception
		else
			throw InvalidType();
	}

	// We use the 'placeCharacter' method to put a character in a concrete location
	void checkLocateAt ( const std::string & newLine )
	{
		std::istringstream is( newLine );

		std::string token;		 is >> token;		// token 		= "LocateAt"
		std::string newName;	 is >> newName;		// newName  	= Character's name
		std::string newLocation; is >> newLocation;	// newLocation	= Character's location

		placeCharacter( newName, newLocation );
	}

	// For a Item, we extract its information from the 'newLine' and execute its concrete method
	void checkItem ( const std::string & newLine )
	{
		std::istringstream is( newLine );

		std::string token;		 is >> token;		// token 	   = "Item"
		std::string type;		 is >> type;		// type  	   = Item's type
		std::string newName;	 is >> newName;		// newName 	   = Item's name
		std::string newLevel;	 is >> newLevel;	// newLevel    = Item's level
		std::string newLocation; is >> newLocation;	// newLocation = Item's location

		// We convert the level from a string to an unsigned int
		unsigned int level;
		std::istringstream ( newLevel ) >> level;

		// If the name, level and location are equal; the map is not well defined
		if ( newName == newLevel || newLevel == newLocation )
			throw IncorrectMap();

		// We distinguish the method to use depending on Item's type
		else if ( type == "Basic" )
			addItemAtLocation( newLocation, newName, level );
		else if ( type == "Trap" )
			addTrapAtLocation( newLocation, newName, level );
		else if ( type == "Potion" )
			addPotionAtLocation( newLocation, newName, level );
		else if ( type == "Bomb" )
			addBombAtLocation( newLocation, newName, level );
		
		// Finally, if the Item's type does not match, we throw the Exception
		else
			throw InvalidType();	
	}



	/*  %%
		QT
		%%  */

	Character * _player;

	void registerPlayer ( const std::string & newPlayer )
	{
		_player = & findCharacter( newPlayer );
	}

	void move ( const std::string & newDirection )
	{
		_player->move( newDirection );
	}
	
	std::string locationDetails () const
	{
		return _player->getLocation()->description();
	}
	
	std::string useItem ( const std::string & newItem )
	{
		return useItem( _player->getLocation()->name(), _player->name(), newItem );
	}

	

	// Destructor
	~World()
	{		
		for( Locations::iterator it = _locations.begin(); it != _locations.end(); ++it )
			delete(*it);

		for( Characters::iterator it2 = _characters.begin(); it2 != _characters.end(); ++it2 )
			delete(*it2);
	}

};

#endif
