/**	
 *	Enginyeria del Software G1-15
 *	
 *	FILE: ConcreteBomb.hxx
 */

#include "Location.hxx"
#include "Character.hxx"

// If the item is a bomb, the information should include if it is enabled or not
// and also to distribute magic when it explodes
std::string ConcreteBomb::useItem( Location * newLocation, Character * newCharacter )
{
	if( this->state() != true )
		return "Bomb not enabled\n";

	std::string uses = ItemDecorator::useItem( newLocation, newCharacter );
	uses += "Bomb explodes\n";
	uses += newLocation->distributeMagic( 5 );

	return uses;
}

// A bomb change from disabled to enabled when it receives magic
std::string ConcreteBomb::receiveMagic( const unsigned int newPoints )
{
	this->state( true );
	std::string receives = ItemDecorator::receiveMagic( newPoints );	
	return receives;
}