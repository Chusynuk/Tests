/**	
 *	Enginyeria del Software G1-15
 *	
 *	FILE: Character.cxx	
 */

#include <iostream>
#include "Location.hxx"

void Character::locateAt ( Location & newLocation )
{
	// In order to place a character with no previous location
	if ( _location == 0 )		
		newLocation.placeCharacter( *this );
	// Otherwise, we should delete it from that place and put it into the new location
	else {
		_location->unplaceCharacter( *this );
		newLocation.placeCharacter( *this );
	}
	
	// We always want to maintain the pointer to the location itself
	_location = &newLocation;
}

std::string Character::pickup ( const std::string & newItem )
{
	// We store the reference to the item that the character is going to pick up
	_item = &( _location->findItem( newItem ) );

	// We call 'carry' Item's method to ensure this character is now carrying the object
	return name() + _item->carry();
}

std::string Character::drop ()
{
	std::string drop = name() + " drops " + _item->getName() + "\n"; 

	// It is important to reset the variable to 0, as he does not carry any item
	_item = 0;

	return drop;
}

void Character::move ( const std::string & newDirection )
{
	if ( _location == NULL )	throw LocationNotFound();
	else
	{
		if ( newDirection == "North" )
		{
			if ( _location->north() == NULL )	throw LocationNotFound();
			else								locateAt( * _location->north() );
		}

		else if ( newDirection == "South" )
		{
			if ( _location->south() == NULL )	throw LocationNotFound();
			else								locateAt( * _location->south() );
		}

		else if ( newDirection == "West" )
		{
			if ( _location->west() == NULL )	throw LocationNotFound();
			else								locateAt( * _location->west() );
		}
		
		else if ( newDirection == "East" )
		{
			if ( _location->east() == NULL )	throw LocationNotFound();
			else								locateAt( * _location->east() );
		}
			
	}  
		
}

