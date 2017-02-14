/**	
 *	Enginyeria del Software G1-15
 *	
 *	FILE: ItemTests.cxx		
 */

#include <MiniCppUnit.hxx>
#include "Item.hxx"

class ItemTest : public TestFixture< ItemTest >
{

public:

	TEST_FIXTURE( ItemTest )
	{
		TEST_CASE( test_name_byDefault );
		TEST_CASE( test_level_byDefault );
		TEST_CASE( test_bool_byDefault );
	}

	void test_name_byDefault()
	{
		Item item;

		ASSERT_EQUALS( "unknown", item.getName() );
	}

	void test_level_byDefault()
	{
		Item item;

		ASSERT_EQUALS( 50u, item.getLevel() );
	}

	void test_bool_byDefault()
	{
		Item item;

		ASSERT_EQUALS( false, item.state() );
	}

};

REGISTER_FIXTURE( ItemTest )

