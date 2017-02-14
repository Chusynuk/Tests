/**	
 *	Enginyeria del Software G1-15
 *	
 *	FILE: AbstractItem.hxx
 */

#ifndef AbstractItem_hxx
#define AbstractItem_hxx

#include "Character.hxx"

class AbstractItem {

public:

	virtual std::string getName () = 0;
	virtual unsigned int getLevel () = 0;

	virtual bool state () = 0;
	virtual void state ( bool newState ) = 0;
	virtual bool isCarried () = 0;

	virtual std::string description () = 0;		
	virtual std::string receiveMagic ( const unsigned int newPoints ) = 0;
	virtual std::string useItem ( Location * newLocation, Character * newCharacter ) = 0;
	virtual std::string carry () = 0;

	virtual ~AbstractItem() {};

};


#endif
