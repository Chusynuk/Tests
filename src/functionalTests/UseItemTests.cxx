#include <MiniCppUnit.hxx>
#include "World.hxx"
#include "Location.hxx"


class UseItemTests : public TestFixture< UseItemTests >
{
public:
	TEST_FIXTURE( UseItemTests )
	{
		TEST_CASE( test_useItem_whenNoLocation );
		TEST_CASE( test_useItem_whenNoCharacter );
		TEST_CASE( test_useItem_whenNoItem );
		TEST_CASE( test_useItem_whenLevelTooLow );
		TEST_CASE( test_useBasicItem );
		TEST_CASE( test_distributeMagic_whenNoLocation );
		TEST_CASE( test_distributeMagic );
		TEST_CASE( test_distributeMagic_onDamageCharacter );
		TEST_CASE( test_useTrap );
		TEST_CASE( test_useTrapTwice );
		TEST_CASE( test_distributeMagic_onCureCharacter );
		TEST_CASE( test_usePotion );
		TEST_CASE( test_usePotionTwice );
		TEST_CASE( test_useBomb_whenNotEnabled );
		TEST_CASE( test_useBomb );
		TEST_CASE( test_useBombTwice );
		TEST_CASE( test_useBombOnManyThings );
	}

	void test_useItem_whenNoLocation()
	{
		// requires a method "useItem" in World.hxx
		// requires a method "useItem" in Location.hxx
		World world;
		try
		{
			world.useItem( "Paradise", "Eve", "Apple" );
			FAIL( "Exception expected" );
		}
		catch( LocationNotFound & e )
		{
			ASSERT_EQUALS( "The location does not exist" , e.what() );
		}
	}
	void test_useItem_whenNoCharacter()
	{
		World world;
		world.addLocation( "Paradise" );
		try
		{
			world.useItem( "Paradise", "Eve", "Apple" );
			FAIL( "Exception expected" );
		}
		catch( CharacterNotFound & e )
		{
			ASSERT_EQUALS( "The character does not exist" , e.what() );
		}
	}
	void test_useItem_whenNoItem()
	{
		World world;
		world.addLocation( "Paradise" );
		world.addCharacter( "Eve", 0 );
		world.placeCharacter( "Eve", "Paradise" );
		try
		{
			world.useItem( "Paradise", "Eve", "Apple" );
			FAIL( "Exception expected" );
		}
		catch( ItemNotFound & e )
		{
			ASSERT_EQUALS( "The item does not exist" , e.what() );
		}
	}
	void test_useItem_whenLevelTooLow()
  	{
		// requires checking whether the level of the character
		//   is high enough to use the item
		World world;
		world.addLocation( "Paradise" );
		world.addCharacter( "Eve", 0 );
		world.placeCharacter( "Eve", "Paradise" );
		world.addItemAtLocation( "Paradise", "Apple", 1 );
		ASSERT_EQUALS(
			"The level of Eve is too low\n",
			world.useItem( "Paradise", "Eve", "Apple" )
		);
  	}
	void test_useBasicItem()
	{
		// requires a method "use" in Item.hxx with two arguments:
		//  - the character that uses the item
		//  - the location where the item is used
		World world;
		world.addLocation( "Paradise" );
		world.addCharacter( "Eve", 0 );
		world.placeCharacter( "Eve", "Paradise" );
		world.addItemAtLocation( "Paradise", "Apple", 0 );
		ASSERT_EQUALS(
			"Eve uses Apple at Paradise\n",
			world.useItem( "Paradise", "Eve", "Apple" )
		);
	}
	void test_distributeMagic_whenNoLocation()
	{
		// requires a method "distributeMagic" in World.hxx
		// requires a method "distributeMagic" in Location.hxx
		World world;
		try
		{
			world.distributeMagic( "Paradise", 5 );
			FAIL( "Exception expected" );
		}
		catch( LocationNotFound & e )
		{
			ASSERT_EQUALS( "The location does not exist" , e.what() );
		}
	}
	void test_distributeMagic()
	{
		// requires a method "receiveMagic" in Item.hxx
		// requires a method "receiveMagic" in Character.hxx
		World world;
		world.addLocation( "Paradise" );
		world.addCharacter( "Eve", 0 );
		world.placeCharacter( "Eve", "Paradise" );
		world.addItemAtLocation( "Paradise", "Apple", 0 );
		world.addItemAtLocation( "Paradise", "Lemon", 0 );
		ASSERT_EQUALS(
			"Eve receives 5 magic points\n"
			"Apple receives 5 magic points\n"
			"Lemon receives 5 magic points\n",
			world.distributeMagic( "Paradise", 5 )
		);
	}
	void test_distributeMagic_onDamageCharacter()
	{
		// requires a method "addDamageCharacter" in World.hxx
		// requires a new class that inherits from Character
		World world;
		world.addLocation( "Paradise" );
		world.addDamageCharacter( "Eve", 0 );
		world.placeCharacter( "Eve", "Paradise" );
		ASSERT_EQUALS(
			"Eve receives 5 magic points\n"
			"Eve takes 5 damage\n",
			world.distributeMagic( "Paradise", 5 )
		);
	}
	void test_useTrap()
	{
		// refactor the Item class using the Decorator pattern
		// requires a method "addTrapAtLocation" in World.hxx
		// requires a method "addTrap" in Location.hxx
		// a trap is composed of two independent behaviors:
		//  - cause 5 damage to the character that uses it
		//  - disappears after use
		//		(requires a method "removeItem" in Location.hxx)
		World world;
		world.addLocation( "Paradise" );
		world.addCharacter( "Eve", 0 );
		world.placeCharacter( "Eve", "Paradise" );
		world.addTrapAtLocation( "Paradise", "Trap", 0 );
		ASSERT_EQUALS(
			"Eve uses Trap at Paradise\n"
			"Eve takes 5 damage\n",
			world.useItem( "Paradise", "Eve", "Trap" )
		);
	}
	void test_useTrapTwice()
	{
		// since the trap disappears it cannot be used twice
		World world;
		world.addLocation( "Paradise" );
		world.addCharacter( "Eve", 0 );
		world.placeCharacter( "Eve", "Paradise" );
		world.addTrapAtLocation( "Paradise", "Trap", 0 );
		world.useItem( "Paradise", "Eve", "Trap" );
		try
		{
			world.useItem( "Paradise", "Eve", "Trap" );
			FAIL( "Exception expected" );
		}
		catch( ItemNotFound & e )
		{
			ASSERT_EQUALS( "The item does not exist" , e.what() );
		}
	}
	void test_distributeMagic_onCureCharacter()
	{
		// requires a method "addCureCharacter" in World.hxx
		// requires a new class that inherits from Character
		World world;
		world.addLocation( "Paradise" );
		world.addCureCharacter( "Eve", 0 );
		world.placeCharacter( "Eve", "Paradise" );
		world.addTrapAtLocation( "Paradise", "Trap", 0 );
		world.useItem( "Paradise", "Eve", "Trap" );
		ASSERT_EQUALS(
			"Eve receives 5 magic points\n"
			"Eve gains 5 life\n",
			world.distributeMagic( "Paradise", 5 )
		);
	}
	void test_usePotion()
	{
		// requires a method "addPotionAtLocation" in World.hxx
		// requires a method "addPotion" in Location.hxx
		// a potion is composed of two independent behaviors:
		//  - heals 5 damage of the character that uses it
		//  - disappears after use
		World world;
		world.addLocation( "Paradise" );
		world.addCharacter( "Eve", 0 );
		world.placeCharacter( "Eve", "Paradise" );
		world.addTrapAtLocation( "Paradise", "Trap", 0 );
		world.useItem( "Paradise", "Eve", "Trap" );
		world.addPotionAtLocation( "Paradise", "Cure", 0 );
		ASSERT_EQUALS(
			"Eve uses Cure at Paradise\n"
			"Eve gains 5 life\n",
			world.useItem( "Paradise", "Eve", "Cure" )
		);
	}
	void test_usePotionTwice()
	{
		// since the potion disappears it cannot be used twice
		World world;
		world.addLocation( "Paradise" );
		world.addCharacter( "Eve", 0 );
		world.placeCharacter( "Eve", "Paradise" );
		world.addTrapAtLocation( "Paradise", "Trap", 0 );
		world.useItem( "Paradise", "Eve", "Trap" );
		world.addPotionAtLocation( "Paradise", "Cure", 0 );
		world.useItem( "Paradise", "Eve", "Cure" );
		try
		{
			world.useItem( "Paradise", "Eve", "Cure" );
			FAIL( "Exception expected" );
		}
		catch( ItemNotFound & e )
		{
			ASSERT_EQUALS( "The item does not exist" , e.what() );
		}
	}
	void test_useBomb_whenNotEnabled()
	{
		// requires a method "addBombAtLocation" in World.hxx
		// requires a method "addBomb" in Location.hxx
		// a bomb is composed of three independent behaviors:
		//  - distribute 5 magic points to the location where used
		//  - initially disabled, needs magic energy to use
		//  - disappears after use
		World world;
		world.addLocation( "Paradise" );
		world.addCharacter( "Eve", 0 );
		world.placeCharacter( "Eve", "Paradise" );
		world.addBombAtLocation( "Paradise", "Bomb", 0 );
		ASSERT_EQUALS(
			"Bomb not enabled\n",
			world.useItem( "Paradise", "Eve", "Bomb" )
		);
	}
	void test_useBomb()
	{
		// the bomb disappears before distributing magic energy
		World world;
		world.addLocation( "Paradise" );
		world.addCharacter( "Eve", 0 );
		world.placeCharacter( "Eve", "Paradise" );
		world.addBombAtLocation( "Paradise", "Bomb", 0 );
		world.distributeMagic( "Paradise", 0 );
		ASSERT_EQUALS(
			"Eve uses Bomb at Paradise\n"
			"Bomb explodes\n"
			"Eve receives 5 magic points\n",
			world.useItem( "Paradise", "Eve", "Bomb" )
		);
	}
	void test_useBombTwice()
	{
		// since the bomb disappears it cannot be used twice
		World world;
		world.addLocation( "Paradise" );
		world.addCharacter( "Eve", 0 );
		world.placeCharacter( "Eve", "Paradise" );
		world.addBombAtLocation( "Paradise", "Bomb", 0 );
		world.distributeMagic( "Paradise", 0 );
		world.useItem( "Paradise", "Eve", "Bomb" );
		try
		{
			world.useItem( "Paradise", "Eve", "Bomb" );
			FAIL( "Exception expected" );
		}
		catch( ItemNotFound & e )
		{
			ASSERT_EQUALS( "The item does not exist" , e.what() );
		}
	}
	void test_useBombOnManyThings()
	{
		World world;
		world.addLocation( "Paradise" );
		world.addCureCharacter( "Eve", 0 );
		world.placeCharacter( "Eve", "Paradise" );
		world.addDamageCharacter( "Adam", 1 );
		world.placeCharacter( "Adam", "Paradise" );
		world.addBombAtLocation( "Paradise", "Bomb", 0 );
		world.addTrapAtLocation( "Paradise", "Trap", 0 );
		world.useItem( "Paradise", "Eve", "Trap" );
		world.addItemAtLocation( "Paradise", "Apple", 0 );
		world.distributeMagic( "Paradise", 0 );
		ASSERT_EQUALS(
			"Eve uses Bomb at Paradise\n"
			"Bomb explodes\n"
			"Eve receives 5 magic points\n"
			"Eve gains 5 life\n"
			"Adam receives 5 magic points\n"
			"Adam takes 5 damage\n"
			"Apple receives 5 magic points\n",
			world.useItem( "Paradise", "Eve", "Bomb" )
		);
	}

};

REGISTER_FIXTURE(UseItemTests)

