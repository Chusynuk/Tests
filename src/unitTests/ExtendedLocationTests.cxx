/**	
 *	Enginyeria del Software G1-15
 *	
 *	FILE: ExtendedLocationTests.cxx	
 */

#include <MiniCppUnit.hxx>
#include "Location.hxx"
#include "Character.hxx"

class ExtendedLocationTests : public TestFixture< ExtendedLocationTests >
{
	
public:
	TEST_FIXTURE( ExtendedLocationTests )
	{
		TEST_CASE( test_addItem_withOneItem );
		TEST_CASE( test_addItem_withNoItem );
		TEST_CASE( test_addItem_withTwoItems );
		TEST_CASE( test_findItem_withTwoItems );
		TEST_CASE( test_findItem_withInexistentItem );
		TEST_CASE( testDescription_withoutItems );
		TEST_CASE( testDescription_withItems );
		TEST_CASE( test_placeCharacter_withOneCharacter );
		TEST_CASE( test_placeCharacter_withNoCharacter );
		TEST_CASE( test_placeCharacter_withTwoCharacters );
		TEST_CASE( test_findCharacter_withTwoCharacters );
		TEST_CASE( test_findCharacter_withInexistentCharacter );
		TEST_CASE( testDescription_withItemsAndCharacters );
		TEST_CASE( testDescription_withUnplacedCharacter );
	}

	void test_addItem_withOneItem()
	{
		Location location;
		location.addItem( "Hammer", 0u );

		ASSERT_EQUALS( "\tItem: Hammer [0]\n", location.items() );
	}

	void test_addItem_withNoItem()
	{
		Location location;

		ASSERT_EQUALS( "", location.items());
	}

	void test_addItem_withTwoItems()
	{
		Location location;
		location.addItem( "Hammer", 0u );
		location.addItem( "Nail", 0u );

		ASSERT_EQUALS(	"\tItem: Hammer [0]\n"
						"\tItem: Nail [0]\n", location.items() );
	}

	void test_findItem_withTwoItems()
	{
		Location location;
		location.addItem( "Hammer", 0u );
		location.addItem( "Nail", 0u );

		AbstractItem & item = location.findItem( "Nail" );

		ASSERT_EQUALS( "Nail [0]", item.description() );
	}

	void test_findItem_withInexistentItem()
	{
		Location location;
		location.addItem( "Hammer", 0u );

		try
		{
			location.findItem( "Nail" );
			FAIL( "An exception should be caught!" );
		}
		catch ( std::exception & e )
		{
			ASSERT_EQUALS( "The item does not exist", e.what() )
		}
	}

	void testDescription_withoutItems()
	{
		Location location;
		location.name( "Workshop" );
		
		ASSERT_EQUALS( "Location: Workshop\n", location.description() )
	}

	void testDescription_withItems()
	{
		Location location;
		location.name( "Workshop" );
		location.addItem( "Hammer", 0u );
		location.addItem( "Nail", 0u );
		
		ASSERT_EQUALS(	"Location: Workshop\n"
						"\tItem: Hammer [0]\n"
						"\tItem: Nail [0]\n", location.description() )
	}

	void test_placeCharacter_withOneCharacter()
	{
		Location location;

		Character carpenter;
		carpenter.name( "Carpenter" );

		location.placeCharacter( carpenter );

		ASSERT_EQUALS( "- Carpenter is here.\n", location.characters() );
	}

	void test_placeCharacter_withNoCharacter()
	{
		Location location;

		ASSERT_EQUALS( "", location.characters() );
	}

	void test_placeCharacter_withTwoCharacters()
	{
		Location location;

		Character carpenter;
		carpenter.name( "Carpenter" );
		location.placeCharacter( carpenter );

		Character painter;
		painter.name( "Painter" );
		location.placeCharacter( painter );

		ASSERT_EQUALS(	"- Carpenter is here.\n"
						"- Painter is here.\n", location.characters() );
	}

	void test_findCharacter_withTwoCharacters()
	{
		Location location;

		Character carpenter;
		carpenter.name( "Carpenter" );
		location.placeCharacter( carpenter );

		Character painter;
		painter.name( "Painter" );
		location.placeCharacter( painter );

		Character & character = location.findCharacter( "Painter" );

		ASSERT_EQUALS( "Painter", character.name() );
	}

	void test_findCharacter_withInexistentCharacter()
	{
		Location location;

		Character carpenter;
		carpenter.name( "Carpenter" );
		location.placeCharacter( carpenter );

		try
		{
			location.findCharacter( "Painter" );
			FAIL( "An exception should be caught!" );
		}
		catch ( std::exception & e )
		{
			ASSERT_EQUALS( "The character does not exist", e.what() )
		}
	}

	void testDescription_withItemsAndCharacters()
	{
		Location location;
		location.name( "Workshop" );
		location.addItem( "Hammer", 0u );
		location.addItem( "Nail", 0u );

		Character carpenter;
		carpenter.name( "Carpenter" );
		location.placeCharacter( carpenter );

		Character painter;
		painter.name( "Painter" );
		location.placeCharacter( painter );
		
		ASSERT_EQUALS(	"Location: Workshop\n"
						"\tItem: Hammer [0]\n"
						"\tItem: Nail [0]\n"
						"- Carpenter is here.\n"
						"- Painter is here.\n", location.description() )
	}

	void testDescription_withUnplacedCharacter()
	{
		Location location;
		location.name( "Workshop" );

		Character carpenter;
		carpenter.name( "Carpenter" );
		location.placeCharacter( carpenter );

		Character painter;
		painter.name( "Painter" );
		location.placeCharacter( painter );
		
		location.unplaceCharacter( carpenter );
		
		//ASSERT_EQUALS(	"Location: Workshop\n"
		//				"- Painter is here.\n", location.description() )
	}

};

REGISTER_FIXTURE( ExtendedLocationTests )




