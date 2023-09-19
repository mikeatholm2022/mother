// Main application object for pegasus
//
// Copyright HOLM, 2023

#pragma once

#include "logger.h"
#include "chaos_app.h"

#include <boost/asio.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/strand.hpp>
#include <boost/function.hpp>
#include <boost/bind/bind.hpp>
#include <boost/thread/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/unordered_map.hpp>

#include <set>
#include <string>
#include <unordered_map>

// ===========================================================================
namespace chaos
{
    // ===========================================================================
    namespace mother
    {
        class MotherApp : public chaos::ChaosApp
        {
        public:
            MotherApp(boost::asio::io_service& io, int interval = 1);
            virtual ~MotherApp();

            virtual void start();
            virtual void stop();
            virtual std::string get_version() { return "v1.0.0"; }

        protected:
            virtual void event_loop();

        };
    }
}