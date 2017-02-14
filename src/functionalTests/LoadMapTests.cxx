#include <MiniCppUnit.hxx>
#include "World.hxx"

class LoadMapTests : public TestFixture< LoadMapTests >
{
public:
	TEST_FIXTURE( LoadMapTests )
	{
		TEST_CASE( test_loadMap_withNoLocation );
		TEST_CASE( test_loadMap_withIncompleteItem );
		TEST_CASE( test_loadCharacterMap );
		TEST_CASE( test_loadSmallMap );
		TEST_CASE( test_loadConnectionMap );
		TEST_CASE( test_loadTrapMap );
		TEST_CASE( test_loadMap_withInvalidItemType );
		TEST_CASE( test_loadDamageMap );
		TEST_CASE( test_loadMap_withInvalidCharacterType );
		TEST_CASE( test_loadLargeMap );
	}

	void test_loadMap_withNoLocation()
	{
		// requires a method "loadMap" in World.hxx
		World world;
		try
		{
			world.loadMap( "maps/NoLocation.txt" );
			FAIL( "Exception expected" );
		}
		catch( LocationNotFound & e )
		{
			ASSERT_EQUALS( "The location does not exist", e.what() );
		}
	}
	void test_loadMap_withIncompleteItem()
	{
		// requires a new exception "IncorrectMap"
		World world;
		try
		{
			world.loadMap( "maps/IncompleteItem.txt" );
			FAIL( "Exception expected" );
		}
		catch( IncorrectMap & e )
		{
			ASSERT_EQUALS( "Incorrect map", e.what() );
		}
	}

	void test_loadCharacterMap()
	{
		World world;
		world.loadMap( "maps/CharacterMap.txt" );
		ASSERT_EQUALS(
			"Location: Cave\n"
			"- Warrior is here.\n",
			world.locationDetails( "Cave" )
		);
	}

	void test_loadSmallMap()
	{
		World world;
		world.loadMap( "maps/SmallMap.txt" );
		ASSERT_EQUALS(
			"Location: Cave\n"
			"\tItem: Apple [0]\n"
			"- Warrior is here.\n",
			world.locationDetails( "Cave" )
		);
	}

	void test_loadConnectionMap()
	{
		World world;
		world.loadMap( "maps/ConnectionMap.txt" );
		ASSERT_EQUALS(
			"Location: Cave\n"
			"\tNorth: Swamp\n"
			"\tSouth: Forest\n",
			world.locationDetails( "Cave" )
		);
	}

	void test_loadTrapMap()
	{
		// requires the ability to distinguish between different types of items
		World world;
		world.loadMap( "maps/TrapMap.txt" );
		ASSERT_EQUALS(
			"Warrior uses Trap at Forest\n"
			"Warrior takes 5 damage\n",
			world.useItem( "Forest", "Warrior", "Trap" )
		);
	}

	void test_loadMap_withInvalidItemType()
	{
		// requires a new exception "InvalidType"
		World world;
		try
		{
			world.loadMap( "maps/InvalidItemType.txt" );
			FAIL( "Exception expected" );
		}
		catch( InvalidType & e )
		{
			ASSERT_EQUALS( "Invalid type", e.what() );
		}
	}

	void test_loadDamageMap()
	{
		// requires the ability to distinguish between different types of characters
		World world;
		world.loadMap( "maps/DamageMap.txt" );
		ASSERT_EQUALS(
			"Demon receives 5 magic points\n"
			"Demon takes 5 damage\n",
			world.distributeMagic( "Cave", 5 )
		);
	}

	void test_loadMap_withInvalidCharacterType()
	{
		World world;
		try
		{
			world.loadMap( "maps/InvalidCharacterType.txt" );
			FAIL( "Exception expected" );
		}
		catch( InvalidType & e )
		{
			ASSERT_EQUALS( "Invalid type", e.what() );
		}
	}

	void test_loadLargeMap()
	{
		World world;
		world.loadMap( "maps/LargeMap.txt" );
		ASSERT_EQUALS(
			"Location: Cave\n"
			"\tNorth: Swamp\n"
			"\tSouth: Forest\n"
			"\tEast: River\n"
			"\tWest: Mountain\n"
			"\tItem: Apple [0]\n"
			"- Warrior is here.\n",
			world.locationDetails( "Cave" )
		);
	}

};

REGISTER_FIXTURE( LoadMapTests )

