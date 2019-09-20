#include <iostream>
#include <sstream>
#include <string>
#include <memory>
#include <gtkmm.h>
#include "GameWindow.h"
#include "StraightsController.h"
using namespace std;


int main(int argc, char** argv) {

    // default seed value
    int seed = 0;
    shared_ptr<StraightsController> controller = make_shared<StraightsController>(seed);
    
    // start game
    try {
        auto app = Gtk::Application::create( argc, argv, "" );
        auto builder = Gtk::Builder::create_from_file( "straights.glade" );

        GameWindow* window = nullptr;
        builder->get_widget_derived( "window", window);
        if ( window == nullptr) {
            g_warning("unable to extract window"); 
            return -1;
        }

        window->setController(controller);
        window->setGame();

        app->run(*window);
        delete window;

	}  catch( const Glib::FileError & ex ) {
		std::cerr << "FileError: " << ex.what() << std::endl;
		return 1;
	} catch( const Glib::MarkupError & ex ) {
		std::cerr << "MarkupError: " << ex.what() << std::endl;
		return 1;
	} catch( const Gtk::BuilderError & ex ) {
		std::cerr << "BuilderError: " << ex.what() << std::endl;
		return 1;
    }
    
  return 0;
}