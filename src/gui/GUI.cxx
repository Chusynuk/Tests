
#include "Controller.hxx"
#include "Model.hxx"
#include "View.hxx"

#include "World.hxx"

int main( int argc, char * argv[] )
{
	QApplication app( argc, argv );

	Controller controller;
	Model * model;
	View view( &controller );

	World world;
	model = &world;

	QObject::connect( &controller, SIGNAL( doMove( const std::string & ) ),
	                  model, SLOT( doMove( const std::string & ) ) );
	QObject::connect( &controller, SIGNAL( doUseItem( const std::string & ) ),
	                  model, SLOT( doUseItem( const std::string & ) ) );
	QObject::connect( model, SIGNAL( modify( const std::string &, const std::string & ) ),
	                  &view, SLOT( update( const std::string &, const std::string & ) ) );

	model->loadMap( "maps/LargeMap.txt" );
	model->registerPlayer( "Warrior" );
	model->start();

	view.show();
	return app.exec();
}
