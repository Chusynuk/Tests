/**	
 *	Enginyeria del Software G1-15
 *	
 *	FILE: CharacterTests.cxx	
 */

#include <MiniCppUnit.hxx>
#include "Character.hxx"
#include "Location.hxx"

class CharacterTest : public TestFixture< CharacterTest >
{

public:

	TEST_FIXTURE( CharacterTest )
	{
		TEST_CASE( test_name_byDefault );
		TEST_CASE( test_name_whenChanged );
		TEST_CASE( test_level_byDefault );
		TEST_CASE( test_level_whenChanged );
		TEST_CASE( test_life_byDefault );
		TEST_CASE( test_life_afterDamage );
		TEST_CASE( test_life_afterCure );
		TEST_CASE( test_life_afterDamageBeyondLife );
		TEST_CASE( test_life_afterCuringBeyondMax );
		
		// Tests added to proof locateAt method
		TEST_CASE( test_locateAt_whenNoPreviousLocation );
		TEST_CASE( test_locateAt_whenPreviousLocation );
	}

	void test_name_byDefault()
	{
		Character anonymous;

		ASSERT_EQUALS( "unknown", anonymous.name() );
	}

	void test_name_whenChanged()
	{
		Character character;
		character.name( "Peter" );

		ASSERT_EQUALS( "Peter", character.name() );
	}

	void test_level_byDefault()
	{
		Character character;

		ASSERT_EQUALS( 0u, character.getLevel() );
	}

	void test_level_whenChanged()
	{
		Character character;
		character.setLevel( 40 );

		ASSERT_EQUALS( 40u,	character.getLevel() );
	}

	void test_life_byDefault()
	{
		Character character;

		ASSERT_EQUALS( 10u, character.getLife() );
	}

	void test_life_afterDamage()
	{
		Character character;
		character.setDamage( 4u );

		ASSERT_EQUALS( 6u, character.getLife() );
	}

	void test_life_afterCure()
	{
		Character character;
		character.setDamage( 4u );
		character.setCure( 4u );

		ASSERT_EQUALS( 10u, character.getLife() );
	}

	void test_life_afterDamageBeyondLife()
	{
		Character character;
		character.setDamage( 15u );

		ASSERT_EQUALS( 0u, character.getLife() );
	}

	void test_life_afterCuringBeyondMax()
	{
		Character character;
		character.setCure( 1u );

		ASSERT_EQUALS( 10u, character.getLife() );
	}
	
	// In order to know if locateAt method assign a location correctly
	void test_locateAt_whenNoPreviousLocation()
	{
		Character character;
		character.name( "Akira" );
		
		Location location;
		location.name( "Hall" );
		
		character.locateAt( location );

		ASSERT_EQUALS( 	"Location: Hall\n"
						"- Akira is here.\n", location.description() );
	}

	// Here we check the consistency of changing a character
	void test_locateAt_whenPreviousLocation()
	{
		Character character;
		character.name( "Akira" );
		
		Location location;
		location.name( "Hall" );
		Location location2;
		location2.name( "Garden" );
		
		character.locateAt( location );
		character.locateAt( location2 );

		ASSERT_EQUALS( 	"Location: Hall\n"
						"Location: Garden\n"
						"- Akira is here.\n", location.description() + location2.description() );
	}

};

REGISTER_FIXTURE( CharacterTest )

