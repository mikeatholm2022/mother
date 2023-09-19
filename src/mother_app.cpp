
// Main application object for mother
//
// Copyright HOLM, 2023

#include "mother_app.h"
#include "utils.h"
#include "time_utils.h"
#include "logger.h"

#include <cstring>
#include <vector>
#include <chrono>
#include <algorithm>

#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/asio/ip/host_name.hpp>
#include <boost/asio.hpp>
#include <boost/foreach.hpp>
#include <boost/format.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

// ==========================================================================================================
namespace chaos
{
    namespace mother
    {
        // ======================================================================================================
        MotherApp::MotherApp(boost::asio::io_service& io, int interval) :
            chaos::ChaosApp(io, interval)
        {
     
        }

        // ======================================================================================================
        MotherApp::~MotherApp()
        {
            
        }

        // ======================================================================================================
        void MotherApp::event_loop()
        {
            // Event loop that triggers every 1 seconds ...
            LOG(PUB_MSG, "Event loop ...");
        }

        // ======================================================================================================
        void MotherApp::start()
        {
            // Lets initialize everything
            LOG(PUB_MSG, STR("Version ") + get_version());
        }

        // ======================================================================================================
        void MotherApp::stop()
        {
            m_loop = false;
        }
    }
}
