#include <MiniCppUnit.hxx>
#include "World.hxx"

class AdvancedCharacterTests : public TestFixture< AdvancedCharacterTests >
{
public:
	TEST_FIXTURE( AdvancedCharacterTests )
	{
		TEST_CASE( test_pickup_whenNoItem );
		TEST_CASE( test_pickup_whenWrongLocation );
		TEST_CASE( test_pickup_whenSuccessful );
		TEST_CASE( test_pickup_whenAlreadyTaken );
		TEST_CASE( test_setMainWeapon_whenNoWeapon );
		TEST_CASE( test_setMainWeapon_withHammer );
		TEST_CASE( test_hit_whenNoCharacter );
		TEST_CASE( test_hit_whenWrongLocation );
		TEST_CASE( test_hit_withoutWeapon );
		TEST_CASE( test_hit_withHammer );
		TEST_CASE( test_hit_withStaff );
		TEST_CASE( test_hit_withSword );
		TEST_CASE( test_hit_whenDead );
		TEST_CASE( test_move_whenNoNeighbor );
		TEST_CASE( test_move_whenSuccessful );
	}

	void test_pickup_whenNoItem()
	{
		// Requires a method "pickup" in World
		// Requires a method "pickup" in Character
		// An item has to exist in order to pick it up
		World world;
		world.addLocation( "Field" );
		world.addCharacter( "Cain", 0 );
		world.placeCharacter( "Cain", "Field" );
		try
		{
			world.pickup( "Cain", "Hammer" );
			FAIL( "Exception expected" );
		}
		catch( ItemNotFound & e )
		{
			ASSERT_EQUALS( "The item does not exist", e.what() );
		}
	}
	void test_pickup_whenWrongLocation()
	{
		// To pick up an item it has to be in the same location
		World world;
		world.addLocation( "Field" );
		world.addLocation( "House" );
		world.addCharacter( "Cain", 0 );
		world.placeCharacter( "Cain", "Field" );
		world.addItemAtLocation( "House", "Hammer", 0 );
		try
		{
			world.pickup( "Cain", "Hammer" );
			FAIL( "Exception expected" );
		}
		catch( ItemNotFound & e )
		{
			ASSERT_EQUALS( "The item does not exist", e.what() );
		}
	}
	void test_pickup_whenSuccessful()
	{
		// Picking up an item should cause a character to carry it
		// Careful with memory leaks!
		World world;
		world.addLocation( "Field" );
		world.addCharacter( "Cain", 0 );
		world.placeCharacter( "Cain", "Field" );
		world.addItemAtLocation( "Field", "Hammer", 0 );
		ASSERT_EQUALS(
			"Cain picks up Hammer\n",
			world.pickup( "Cain", "Hammer" )
		);
	}
	void test_pickup_whenAlreadyTaken()
	{
		// An item can only be picked up once
		World world;
		world.addLocation( "Field" );
		world.addCharacter( "Cain", 0 );
		world.addCharacter( "Abel", 0 );
		world.placeCharacter( "Cain", "Field" );
		world.addItemAtLocation( "Field", "Hammer", 0 );
		world.pickup( "Cain", "Hammer" );
		try
		{
			world.pickup( "Abel", "Hammer" );
			FAIL( "Exception expected" );
		}
		catch( ItemNotFound & e )
		{
			ASSERT_EQUALS( "The item does not exist", e.what() );
		}
	}
	void test_setMainWeapon_whenNoWeapon()
	{
		// Requires a method "setMainWeapon" in World
		// Requires a method "setMainWeapon" in Character
		// An item has to be carried to set it as main weapon
		World world;
		world.addLocation( "Field" );
		world.addCharacter( "Cain", 0 );
		world.placeCharacter( "Cain", "Field" );
		world.addItemAtLocation( "Field", "Hammer", 0 );
		try
		{
			world.setMainWeapon( "Cain", "Hammer" );
			FAIL( "Exception expected" );
		}
		catch( ItemNotFound & e )
		{
			ASSERT_EQUALS( "The item does not exist", e.what() );
		}
	}
	void test_setMainWeapon_withHammer()
	{
		World world;
		world.addLocation( "Field" );
		world.addCharacter( "Cain", 0 );
		world.placeCharacter( "Cain", "Field" );
		world.addItemAtLocation( "Field", "Hammer", 0 );
		world.pickup( "Cain", "Hammer" );
		ASSERT_EQUALS(
			"Cain set Hammer as main weapon\n",
			world.setMainWeapon( "Cain", "Hammer" )
		);
	}
	void test_hit_whenNoCharacter()
	{
		// Requires a method "hit" in World
		// Requires a method "hit" in Character
		// A character has to exist in order to hit it
		World world;
		world.addLocation( "Field" );
		world.addCharacter( "Cain", 0 );
		world.placeCharacter( "Cain", "Field" );
		try
		{
			world.hit( "Cain", "Abel" );
			FAIL( "Exception expected" );
		}
		catch( CharacterNotFound & e )
		{
			ASSERT_EQUALS( "The character does not exist", e.what() );
		}
	}
	void test_hit_whenWrongLocation()
	{
		// To hit a character it has to be in the same location
		World world;
		world.addLocation( "Field" );
		world.addCharacter( "Cain", 0 );
		world.addCharacter( "Abel", 0 );
		world.placeCharacter( "Cain", "Field" );
		try
		{
			world.hit( "Cain", "Abel" );
			FAIL( "Exception expected" );
		}
		catch( CharacterNotFound & e )
		{
			ASSERT_EQUALS( "The character does not exist", e.what() );
		}
	}
	void test_hit_withoutWeapon()
	{
		World world;
		world.addLocation( "Field" );
		world.addCharacter( "Cain", 0 );
		world.addCharacter( "Abel", 0 );
		world.placeCharacter( "Cain", "Field" );
		world.placeCharacter( "Abel", "Field" );
		ASSERT_EQUALS(
			"Abel takes 1 damage\n",
			world.hit( "Cain", "Abel" )
		);
	}
	void test_hit_withHammer()
	{
		World world;
		world.addLocation( "Field" );
		world.addCharacter( "Cain", 0 );
		world.addCharacter( "Abel", 0 );
		world.placeCharacter( "Cain", "Field" );
		world.placeCharacter( "Abel", "Field" );
		world.addItemAtLocation( "Field", "Hammer", 0 );
		world.addItemAtLocation( "Field", "Apple", 0 );
		world.pickup( "Cain", "Hammer" );
		world.pickup( "Abel", "Apple" );
		world.setMainWeapon( "Cain", "Hammer" );
		ASSERT_EQUALS(
			"Abel drops Apple\n"
			"Abel takes 2 damage\n",
			world.hit( "Cain", "Abel" )
		);
	}
	void test_hit_withStaff()
	{
		World world;
		world.addLocation( "Field" );
		world.addCharacter( "Cain", 0 );
		world.addDamageCharacter( "Abel", 0 );
		world.placeCharacter( "Cain", "Field" );
		world.placeCharacter( "Abel", "Field" );
		world.addItemAtLocation( "Field", "Staff", 0 );
		world.pickup( "Cain", "Staff" );
		world.setMainWeapon( "Cain", "Staff" );
		ASSERT_EQUALS(
			"Abel receives 5 magic points\n"
			"Abel takes 5 damage\n",
			world.hit( "Cain", "Abel" )
		);
	}
	void test_hit_withSword()
	{
		World world;
		world.addLocation( "Field" );
		world.addCharacter( "Cain", 0 );
		world.addDamageCharacter( "Abel", 0 );
		world.placeCharacter( "Cain", "Field" );
		world.placeCharacter( "Abel", "Field" );
		world.addItemAtLocation( "Field", "Sword", 0 );
		world.pickup( "Cain", "Sword" );
		world.setMainWeapon( "Cain", "Sword" );
		ASSERT_EQUALS(
			"Abel takes 4 damage\n",
			world.hit( "Cain", "Abel" )
		);
	}
	void test_hit_whenDead()
	{
		World world;
		world.addLocation( "Field" );
		world.addCharacter( "Cain", 0 );
		world.addDamageCharacter( "Abel", 0 );
		world.placeCharacter( "Cain", "Field" );
		world.placeCharacter( "Abel", "Field" );
		world.addItemAtLocation( "Field", "Sword", 0 );
		world.pickup( "Cain", "Sword" );
		world.setMainWeapon( "Cain", "Sword" );
		world.hit( "Cain", "Abel" );
		world.hit( "Cain", "Abel" );
		ASSERT_EQUALS(
			"Abel takes 4 damage\n"
			"Abel is dead\n",
			world.hit( "Cain", "Abel" )
		);
	}
	void test_move_whenNoNeighbor()
	{
		// Requires a method "move" in World
		// Requires a method "move" in Character
		// The current location has to have a proper neighbor
		World world;
		world.addLocation( "Field" );
		world.addCharacter( "Cain", 0 );
		world.placeCharacter( "Cain", "Field" );
		try
		{
			world.move( "Cain", "West" );
			FAIL( "Exception expected" );
		}
		catch( LocationNotFound & e )
		{
			ASSERT_EQUALS( "The location does not exist", e.what() );
		}
	}
	void test_move_whenSuccessful()
	{
		World world;
		world.addLocation( "Field" );
		world.addLocation( "House" );
		world.addCharacter( "Cain", 0 );
		world.placeCharacter( "Cain", "Field" );
		world.connectWestToEast( "House", "Field" );
		world.move( "Cain", "House" );
		ASSERT_EQUALS(
			"Location: House\n"
			"\tEast: Field\n"
			"- Cain is here.\n",
			world.locationDetails( "House" )
		);
	}

};

REGISTER_FIXTURE( AdvancedCharacterTests )

