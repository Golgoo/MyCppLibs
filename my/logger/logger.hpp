#pragma once

#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/smart_ptr/make_shared_object.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/sources/basic_logger.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/log/attributes/scoped_attribute.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>

#include <boost/core/null_deleter.hpp>

#include <boost/log/support/date_time.hpp>

#include <functional>
#include <iostream>
#include <iomanip>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/smart_ptr/make_shared_object.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/sources/basic_logger.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/log/attributes/scoped_attribute.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>

#include <boost/core/null_deleter.hpp>

#include <boost/log/support/date_time.hpp>



namespace logging = boost::log;
namespace expr = boost::log::expressions;
namespace attrs = boost::log::attributes;
namespace sinks = boost::log::sinks;
namespace src = boost::log::sources;

namespace my{
namespace logger{


    enum severity_level{
        trace,
        debug,
        info,
        warning,
        error,
        fatal
    };
    inline std::ostream& operator<< (std::ostream& strm, my::logger::severity_level level)
    {
        static const char* strings[] =
        {
            "trace",
            "debug",
            "info",
            "warning",
            "error",
            "fatal"
        };
       

        if (static_cast< std::size_t >(level) < sizeof(strings) / sizeof(*strings))
            strm << strings[level];
        else
            strm << static_cast< int >(level);

        return strm;
        
    }


    BOOST_LOG_ATTRIBUTE_KEYWORD(line_id, "LineID", unsigned int)
    BOOST_LOG_ATTRIBUTE_KEYWORD(severity, "Severity", severity_level)
    BOOST_LOG_ATTRIBUTE_KEYWORD(tag_attr, "Tag", std::string)
    BOOST_LOG_ATTRIBUTE_KEYWORD(scope, "Scope", attrs::named_scope::value_type)
    BOOST_LOG_ATTRIBUTE_KEYWORD(timeline, "Timeline", attrs::timer::value_type)
    BOOST_LOG_ATTRIBUTE_KEYWORD(channel_attr, "Channel", std::string)

    namespace formatter{
        void default_formatter(boost::log::record_view const& rec, boost::log::formatting_ostream& strm);
        void my_formatter(boost::log::record_view const& rec, boost::log::formatting_ostream& strm);
    }

    
    
    class Logger
    {
        public:
            Logger(
                std::string path,
                severity_level severity = severity_level::warning,
                std::function<void(boost::log::record_view const&, boost::log::formatting_ostream&)> format = 
                    &formatter::default_formatter
            );
        private:
            std::string _channel_name ;
            src::severity_logger< severity_level > _slg;
        protected:

            struct Loggit {
                severity_level _severity ;
                Logger& _parent ;

                Loggit(Logger &parent):_parent(parent){}

                inline Loggit& operator()(severity_level severity)
                {
                    _severity = severity ;
                    return *this;
                }

                inline Loggit& operator<<(std::string str)
                {
                    BOOST_LOG_SCOPED_THREAD_TAG("Channel", _parent._channel_name);
                    BOOST_LOG_SEV(_parent._slg, _severity) << str;
                    return *this;
                }
            };

        Loggit loggit ;
    };



}
}



