#include <gtkmm/application.h>
#include "main_window.hpp"
#include "trace_reader.hpp"
#include "files.hpp"

int main(int argc, char * argv[]) {

    int fake_argc = 1;
    std::string filename = process_command_line(argc, argv);
    const TraceReader::locations_t locations = get_locations(filename);


    // Don't let GTK process the arguments.
    auto app = Gtk::Application::create(fake_argc, argv, "edu.uoregon.paraducks.atv");
    MainWindow main_window(filename, locations);
    return app->run(main_window);

}
