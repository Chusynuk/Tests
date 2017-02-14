/**	
 *	Enginyeria del Software G1-15
 *	
 *	FILE: LocationTests.cxx	
 */

#include <MiniCppUnit.hxx>
#include "Location.hxx"
#include "Character.hxx"

class LocationTest : public TestFixture< LocationTest >
{

public:

	TEST_FIXTURE( LocationTest )
	{
		TEST_CASE( test_name_byDefault );
		TEST_CASE( test_name_whenChanged );
		TEST_CASE( test_description_whenEmpty );

		TEST_CASE( test_connections_whenNotConnected );
		TEST_CASE( test_connections_whenConnectedAtSouth );
		TEST_CASE( test_connections_whenConnectedAtNorth );
		TEST_CASE( test_description_whenConnectedNorthSouth );

		// Test added to verify the unplaceCharacter method
		TEST_CASE( test_unplaceCharacter );
	}

	void test_name_byDefault()
	{
		Location location;

		ASSERT_EQUALS( "unknown", location.name() );
	}

	void test_name_whenChanged()
	{
		Location location;
		location.name( "A location" );

		ASSERT_EQUALS( "A location", location.name() );
	}

	void test_description_whenEmpty()
	{
		Location location;
		location.name( "A location" );

		ASSERT_EQUALS( "Location: A location\n", location.description() );
	}

	// Unit test when not connected
	void test_connections_whenNotConnected()
	{
		Location location;

		ASSERT_EQUALS( "", location.connections() );
	}

	// Unit test when connect at south
	void test_connections_whenConnectedAtSouth()
	{
		Location location;

		Location locSouth;
		locSouth.name( "Morocco" );

		location.connectSouth( locSouth );

		ASSERT_EQUALS( "\tSouth: Morocco\n", location.connections() );
	}

	// when connected at north
	void test_connections_whenConnectedAtNorth()
	{
		Location location;

		Location locNorth;
		locNorth.name( "Grenoble" );		
		
		location.connectNorth( locNorth );

		ASSERT_EQUALS( "\tNorth: Grenoble\n", location.connections() );
	}

	// when connected north south
	void test_description_whenConnectedNorthSouth()
	{
		Location location;
		location.name( "Spain" );
		
		Location locNorth;
		locNorth.name( "Grenoble" );
		location.connectNorth( locNorth );

		Location locSouth;
		locSouth.name( "Morocco" );
		location.connectSouth( locSouth );

		ASSERT_EQUALS(  "Location: Spain\n"
						"\tNorth: Grenoble\n"
						"\tSouth: Morocco\n", location.description() );
	}
	
	
	// Test added to verify the unplaceCharacter method
	void test_unplaceCharacter()
	{
		Location location;
		location.name( "Hall" );
		
		Character character;
		character.name( "Akira" );
		
		location.placeCharacter( character );
		location.unplaceCharacter( character );

		ASSERT_EQUALS( "Location: Hall\n" , location.description() );
	}

};

REGISTER_FIXTURE( LocationTest )

