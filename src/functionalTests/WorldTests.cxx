#include <MiniCppUnit.hxx>
#include "World.hxx"

class WorldTests : public TestFixture< WorldTests >
{
public:
	TEST_FIXTURE( WorldTests )
	{
		TEST_CASE( test_locations_afterAddingALocation );
		TEST_CASE( test_locations_byDefault );
		TEST_CASE( test_locations_afterAddingASecondLocation );
		TEST_CASE( test_locationDetails_whenNoLocation );
		TEST_CASE( test_locationDetails_whenEmptyAndUnconnected );
		TEST_CASE( test_locationDetails_whenLocationDoesNotExist );
		TEST_CASE( test_addItemAtLocation_withOneItem );
		TEST_CASE( test_addItemAtLocation_withWrongLocation );
		TEST_CASE( test_locationDetails_whenConnectedNorthSouth );
		TEST_CASE( test_locationDetails_whenConnectedEastWest );
		TEST_CASE( test_locationDetails_whenFullyConnected );
		TEST_CASE( test_characters_whenEmpty );
		TEST_CASE( test_characters_withOneCharacter );
		TEST_CASE( test_characters_withTwoCharacters );
		TEST_CASE( test_placeCharacter_whenCharacterDoesNotExist );
		TEST_CASE( test_locationDetails_withOneCharacter );
		TEST_CASE( test_locationDetails_withManyCharacters );
		TEST_CASE( test_locationDetails_withCharactersItemsAndConnections );
		TEST_CASE( test_placeCharacter_whenWasAlreadyPlaced );

		//TEST_CASE( test_connectNorthToSouth_whenNorthAlreadyConnected ); // Optional
		//TEST_CASE( test_connectNorthToSouth_whenSouthAlreadyConnected ); // Optional
		//TEST_CASE( test_connectWestToEast_whenEastAlreadyConnected ); // Optional
		//TEST_CASE( test_connectWestToEast_whenWestAlreadyConnected ); // Optional
	}

	void test_locations_afterAddingALocation()
	{
		World world;
		world.addLocation( "Hall" );
		ASSERT_EQUALS(
			"Hall\n",
			world.locations()
		);
	}
	void test_locations_byDefault()
	{
		World world;
		ASSERT_EQUALS(
			"",
			world.locations()
		);
	}
	void test_locations_afterAddingASecondLocation()
	{
		World world;
		world.addLocation( "Hall" );
		world.addLocation( "Garden" );
		ASSERT_EQUALS(
			"Hall\n"
			"Garden\n",
			world.locations()
		);
	}
	void test_locationDetails_whenNoLocation()
	{
		World world;
		try
		{
			world.locationDetails( "Paradise" );
			FAIL( "Exception expected" );
		}
		catch ( LocationNotFound & e )
		{
			ASSERT_EQUALS(
				"The location does not exist",
				e.what()
			);
		}
	}
	void test_locationDetails_whenEmptyAndUnconnected()
	{
		// The idea is to use the method Location::description.
		World world;
		world.addLocation( "Madrid" );
		ASSERT_EQUALS(
			"Location: Madrid\n",
			world.locationDetails( "Madrid" )
		);
	}
	void test_locationDetails_whenLocationDoesNotExist()
	{
		World world;
		world.addLocation( "Madrid" );
		try
		{
			world.locationDetails( "Paradise" );
			FAIL( "Exception expected" );
		}
		catch ( LocationNotFound & e )
		{
			ASSERT_EQUALS(
				"The location does not exist",
				e.what()
			);
		}
	}
	void test_addItemAtLocation_withOneItem()
	{
		// The idea is to use the method Location::addItem.
		World world;
		world.addLocation( "Hall" );
		unsigned requiredLevel = 0;
		world.addItemAtLocation( "Hall", "BulletinBoard", requiredLevel );
		ASSERT_EQUALS(
			"Location: Hall\n"
			"\tItem: BulletinBoard [0]\n"
			, world.locationDetails("Hall")
		);
	}
	void test_addItemAtLocation_withWrongLocation()
	{
		World world;
		try
		{
			world.addItemAtLocation( "Paradise", "BulletinBoard", 0u );
			FAIL( "Exception expected" );
		}
		catch ( LocationNotFound & e )
		{
			ASSERT_EQUALS(
				"The location does not exist",
				e.what()
			);
		}
	}
	void test_locationDetails_whenConnectedNorthSouth()
	{
		// Remember that the (unary) association is *optional*, not multiple.
		// Use the same strategy as for items: first test and implement a
		// method Location::connections that only returns information about
		// connections, then integrate this information in Location::description.
		//
		// A single method Location::connectSouth is necessary to implement this
		// functional test. This new method can be tested using four unit tests:
		//
		// LocationTests::test_connections_whenNotConnected()
		//  - simple, but requires the use of a pointer to pass the other tests
		// LocationTests::test_connections_whenConnectedAtSouth()
		//  - use Location::connectSouth to establish a connection to the south
		// LocationTests::test_connections_whenConnectedAtNorth()
		//  - use Location::connectNorth to establish a connection to the north
		// LocationTests::test_description_whenConnectedNorthSouth()
		//  - add the information about connections to Location::description
		//
		// The last thing to do is uncomment this functional test, fail the test
		// (RED) and implement the method connectNorthToSouth.

		World world;
		world.addLocation( "Madrid" );
		world.addLocation( "Cadiz" );
		world.addLocation( "Bilbao" );
		world.connectNorthToSouth( "Madrid", "Cadiz" );
		world.connectNorthToSouth( "Bilbao", "Madrid" );
		ASSERT_EQUALS(
			"Location: Madrid\n"
			"\tNorth: Bilbao\n"
			"\tSouth: Cadiz\n",
			world.locationDetails("Madrid")
		);
	}
	void test_locationDetails_whenConnectedEastWest()
	{
		// Similar to the previous test but for east-west connections.
		World world;
		world.addLocation( "Madrid" );
		world.addLocation( "Valencia" );
		world.addLocation( "Badajoz" );
		world.connectWestToEast( "Badajoz", "Madrid" );
		world.connectWestToEast( "Madrid", "Valencia" );
		ASSERT_EQUALS(
			"Location: Madrid\n"
			"\tEast: Valencia\n"
			"\tWest: Badajoz\n",
			world.locationDetails("Madrid")
		);
	}
	void test_locationDetails_whenFullyConnected()
	{
		// Tests the order in which connections are presented.
		World world;
		world.addLocation( "Madrid" );
		world.addLocation( "Valencia" );
		world.addLocation( "Badajoz" );
		world.addLocation( "Cadiz" );
		world.addLocation( "Bilbao" );
		world.connectWestToEast( "Badajoz", "Madrid" );
		world.connectWestToEast( "Madrid", "Valencia" );
		world.connectNorthToSouth( "Madrid", "Cadiz" );
		world.connectNorthToSouth( "Bilbao", "Madrid" );
		ASSERT_EQUALS(
			"Location: Madrid\n"
			"\tNorth: Bilbao\n"
			"\tSouth: Cadiz\n"
			"\tEast: Valencia\n"
			"\tWest: Badajoz\n",
			world.locationDetails("Madrid")
		);
	}
	void test_characters_whenEmpty()
	{
		World world;
		ASSERT_EQUALS(
			""
			, world.characters()
		);
	}
	void test_characters_withOneCharacter()
	{
		World world;
		unsigned level = 3;
		world.addCharacter( "Sami", level );
		ASSERT_EQUALS(
			"Sami\n",
			world.characters()
		);
	}
	void test_characters_withTwoCharacters()
	{
		World world;
		world.addCharacter( "Sami", 2 );
		world.addCharacter( "Fijoles", 3 );
		ASSERT_EQUALS(
			"Sami\n"
			"Fijoles\n",
			world.characters()
		);
	}
	void test_placeCharacter_whenCharacterDoesNotExist()
	{
		World world;
		world.addLocation( "Hall" );
		try
		{
			world.placeCharacter( "God", "Hall" );
			FAIL( "Exception expected" );
		}
		catch ( CharacterNotFound & e )
		{
			ASSERT_EQUALS(
				"The character does not exist",
				e.what()
			);
		}
	}
	void test_locationDetails_withOneCharacter()
	{
		// The idea is to use the method Location::placeCharacter.
		World world;
		world.addLocation( "Hall" );
		world.addCharacter( "Sami", 200 );
		world.placeCharacter( "Sami", "Hall" );
		ASSERT_EQUALS(
			"Location: Hall\n"
			"- Sami is here.\n",
			world.locationDetails( "Hall" )
		);
		
	}
	void test_locationDetails_withManyCharacters()
	{
		World world;
		world.addLocation( "Hall" );
		world.addCharacter( "Sami", 200 );
		world.placeCharacter( "Sami", "Hall" );
		world.addCharacter( "Frijoles", 400 );
		world.placeCharacter( "Frijoles", "Hall" );
		ASSERT_EQUALS(
			"Location: Hall\n"
			"- Sami is here.\n"
			"- Frijoles is here.\n",
			world.locationDetails( "Hall" )
		);
	}
	void test_locationDetails_withCharactersItemsAndConnections()
	{
		// Tests the order of the information in locationDetails.
		World world;
		world.addLocation( "Hall" );
		world.addLocation( "Southern" );
		world.addLocation( "Northern" );
		world.addLocation( "Eastern" );
		world.addLocation( "Western" );
		world.connectNorthToSouth( "Hall", "Southern" );
		world.connectNorthToSouth( "Northern", "Hall" );
		world.connectWestToEast( "Western", "Hall" );
		world.connectWestToEast( "Hall", "Eastern" );
		world.addItemAtLocation( "Hall", "BulletinBoard", 0u );
		world.addCharacter( "Sami", 200 );
		world.placeCharacter( "Sami", "Hall" );
		world.addCharacter( "Frijoles", 400 );
		world.placeCharacter( "Frijoles", "Hall" );
		ASSERT_EQUALS(
			"Location: Hall\n"
			"\tNorth: Northern\n"
			"\tSouth: Southern\n"
			"\tEast: Eastern\n"
			"\tWest: Western\n"
			"\tItem: BulletinBoard [0]\n"
			"- Sami is here.\n"
			"- Frijoles is here.\n",
			world.locationDetails( "Hall" )
		);
	}
	void test_placeCharacter_whenWasAlreadyPlaced()
	{
		// Here we see that it is convenient to maintain a backlink from
		// the character to the location to be able to "unplace" the
		// character from the previous location. In fact, using this
		// backlink it is better to introduce a method Character::locateAt
		// that is responsible for connecting characters and locations.
		//
		// This implies a design change that we can implement using the
		// following guide:
		//
		// - Since the classes point at each other, start with a forward
		//   declaration 'class Location;' in Character.hxx. This means
		//   all code in Character involving Location has to be placed
		//   in a code file Character.cxx, from where we can include
		//   Location.hxx.
		//
		// - CharacterTests::test_locateAt_whenNoPreviousLocation()
		//   tests whether Character::locateAt has the same effect as
		//   Location::placeCharacter.
		//
		// - Refactor: create an attribute 'Location * _location' in the
		//   Character class, initialized to 0. This attribute is set in
		//   Character::locateAt.
		//
		// - LocationTests::test_unplaceCharacter()
		//   tests whether Location::unplaceCharacter removes the character
		//   from the location.
		//
		// - CharacterTests::test_locateAt_whenPreviousLocation()
		//   tests whether the character correctly moves from one location
		//   to another (without causing memory leaks!). Use the method
		//   Location::unplaceCharacter.
		//
		// - Finally, uncomment this test and (after failing the test)
		//   implement it using Character::locateAt instead of
		//   Location::placeCharacter.

		World world;
		world.addLocation( "Hall" );
		world.addLocation( "Garden" );
		world.addCharacter( "Sami", 200 );
		world.placeCharacter( "Sami", "Hall" );
		world.placeCharacter( "Sami", "Garden" );
		ASSERT_EQUALS(
			"Location: Hall\n"
			"Location: Garden\n"
			"- Sami is here.\n",
			world.locationDetails( "Hall" ) +
			world.locationDetails( "Garden" )
		);
	}
/*
	// Optional test
	void test_connectNorthToSouth_whenNorthAlreadyConnected()
	{
		World world;
		world.addLocation( "Location" );
		world.addLocation( "Connection1" );
		world.addLocation( "Connection2" );
		world.connectNorthToSouth( "Location", "Connection1" );
		world.connectNorthToSouth( "Location", "Connection2" );
		ASSERT_EQUALS(
			"Location: Location\n"
			"\tSouth: Connection2\n"
			"Location: Connection1\n"
			"Location: Connection2\n"
			"\tNorth: Location\n",
			world.locationDetails( "Location" ) +
			world.locationDetails( "Connection1" ) +
			world.locationDetails( "Connection2" )
		);
	}
	// Optional test
	void test_connectNorthToSouth_whenSouthAlreadyConnected()
	{
		World world;
		world.addLocation( "Location" );
		world.addLocation( "Connection1" );
		world.addLocation( "Connection2" );
		world.connectNorthToSouth( "Connection1", "Location" );
		world.connectNorthToSouth( "Connection2", "Location" );
		ASSERT_EQUALS(
			"Location: Location\n"
			"\tNorth: Connection2\n"
			"Location: Connection1\n"
			"Location: Connection2\n"
			"\tSouth: Location\n",
			world.locationDetails( "Location" ) +
			world.locationDetails( "Connection1" ) +
			world.locationDetails( "Connection2" )
		);
	}
	// Optional test
	void test_connectWestToEast_whenEastAlreadyConnected()
	{
		World world;
		world.addLocation( "Location" );
		world.addLocation( "Connection1" );
		world.addLocation( "Connection2" );
		world.connectWestToEast( "Connection1", "Location" );
		world.connectWestToEast( "Connection2", "Location" );
		ASSERT_EQUALS(
			"Location: Location\n"
			"\tWest: Connection2\n"
			"Location: Connection1\n"
			"Location: Connection2\n"
			"\tEast: Location\n",
			world.locationDetails( "Location" ) +
			world.locationDetails( "Connection1" ) +
			world.locationDetails( "Connection2" )
		);
	}
	// Optional test
	void test_connectWestToEast_whenWestAlreadyConnected()
	{
		World world;
		world.addLocation( "Location" );
		world.addLocation( "Connection1" );
		world.addLocation( "Connection2" );
		world.connectWestToEast( "Location", "Connection1" );
		world.connectWestToEast( "Location", "Connection2" );
		ASSERT_EQUALS(
			"Location: Location\n"
			"\tEast: Connection2\n"
			"Location: Connection1\n"
			"Location: Connection2\n"
			"\tWest: Location\n",
			world.locationDetails( "Location" ) +
			world.locationDetails( "Connection1" ) +
			world.locationDetails( "Connection2" )
		);
	}
*/
};

REGISTER_FIXTURE( WorldTests )

