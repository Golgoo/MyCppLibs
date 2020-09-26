#include <my/logger/logger.hpp>

#include <boost/date_time/posix_time/posix_time.hpp>

using namespace my::logger;


void formatter::my_formatter(boost::log::record_view const& rec,
                  boost::log::formatting_ostream& strm)
{
    logging::formatter f = 
            expr::stream
            << std::hex << std::setw(8) << std::setfill('0') << line_id << 
            std::dec << std::setfill(' ')
            << ": <" << severity << ">\t"
            << std::setw(4) 
            << expr::format_date_time< boost::posix_time::ptime >("TimeStamp", "%Y-%m-%d %H:%M:%S")
            << "(" << scope << ") "
            << expr::if_(expr::has_attr(tag_attr))
            [
                    expr::stream << "[" << tag_attr << "] "
            ]
            << expr::if_(expr::has_attr(timeline))
            [
                    expr::stream << "[" << timeline << "] "
            ]
            << expr::smessage ;
    f(rec, strm);
};

void formatter::default_formatter(logging::record_view const& rec, logging::formatting_ostream& strm)
{
    logging::formatter f = 
            expr::stream
            << std::hex << std::setw(2) 
            << expr::format_date_time< boost::posix_time::ptime >("TimeStamp", "%Y-%m-%d %H:%M:%S")
            << std::setw(8)
            << std::dec << std::setfill(' ')
            << ": <" << severity << ">\t"
            << "(" << scope << ") "
            << expr::smessage ;
            
    f(rec, strm);
}

Logger::Logger(
        std::string path,
        severity_level log_severity,
        std::function<void(
            boost::log::record_view const&, 
            boost::log::formatting_ostream&
        )> formator
): loggit(*this), _channel_name(path)
{

    typedef sinks::synchronous_sink< sinks::text_ostream_backend > text_sink;
    boost::shared_ptr< text_sink > sink = boost::make_shared< text_sink >();

    sink->locked_backend()->add_stream(
        boost::make_shared< std::ofstream >(path)
    );

    sink->locked_backend()->auto_flush(true);

    sink->set_formatter(formator);
    
    sink->set_filter(severity >= log_severity && (expr::has_attr(channel_attr) && channel_attr == path));
    
    logging::core::get()->add_sink(sink);


    logging::add_common_attributes();
    logging::core::get()->add_global_attribute("Scope", attrs::named_scope());
}

