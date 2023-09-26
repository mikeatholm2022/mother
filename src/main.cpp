// Main function for mother
//
// Copyright HOLM, 2023

#include "logger.h"
#include "utils.h"
#include "application_details.h"
#include "mother_app.h"

#include <fstream>
#include <signal.h>

#include <boost/asio.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/thread/thread.hpp>

// =============================================================================================
boost::asio::io_service& main_io_instance()
{
    static boost::asio::io_service main_io;
    return main_io;
}

// =============================================================================================
chaos::ChaosApp& application_instance()
{
    static chaos::mother::MotherApp app(main_io_instance());
    return app;
}

// =============================================================================================
void signal_handler(int sig)
{
    std::stringstream ss;
    ss << "Received Signal " << sig << " -  Request to kill application";
    LOG(PUB_MSG, ss.str());
    auto& app = application_instance();
    app.stop();
    chaos::sleep(1);
    app.get_main_io()->stop();
}

// =============================================================================================
int main()
{
    chaos::ApplicationDetails::instance()->set_details("mother", "Event Monitor", "MAIN", 22001, 30000);
    if (!chaos::ApplicationDetails::instance()->is_configuration_okay())
    {
        // We are missing configuration details
        std::cerr << "ERROR - We are missing configuration details, please investigate" << std::endl;
        LOG(PUB_MSG, "We are missing configuration details");
        return -1;
    }

    chaos::set_thread_name("Main");
    LOG(PUB_MSG, "Mother is starting");

    std::stringstream ss;
    ss << "Main Thread = " << boost::this_thread::get_id();
    LOG(PUB_MSG, ss.str().c_str());

    boost::asio::io_service& mainIo = main_io_instance();
    auto& app = application_instance();
    chaos::ApplicationDetails::instance()->set_version(app.get_version());
    app.start();

    // Signals we want to handle
    signal(SIGSEGV, &signal_handler);  // Segment violation
    signal(SIGINT, &signal_handler);   // Interrupt
    signal(SIGILL, &signal_handler);   // Illegal instruction - invalid function image
    signal(SIGFPE, &signal_handler);   // Floating point exception
    signal(SIGTERM, &signal_handler);  // Software termination signal from kill
    signal(SIGABRT, &signal_handler);  // Abnormal termination triggered by abort call

    // Main event loop
    boost::asio::io_service::work work(mainIo);
    mainIo.run();

    LOG(PUB_MSG, "Application is shutting down");

    // Clean-up time
    chaos::Logger::instance()->stop();
    chaos::sleep(1);
    chaos::Logger::instance()->join();
    //delete chaos::Logger::instance();
    //delete chaos::ApplicationDetails::instance();

    return 0;
}

// =============================================================================================
