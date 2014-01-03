#include "logger.h"
#include <iostream>
#include <istream>
#include <ostream>
#include <iostream>
#include <fstream>
#include <iterator>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/log/sources/basic_logger.hpp>
#include <boost/log/trivial.hpp>

namespace po = boost::program_options;
using namespace singularity;

client c;
const std::string	WEB_PREFIX			= "https://";
const std::string	SERVER_PRODUCTION	= "www.server.com";
const std::string	SERVER_DEVELOPMENT	= "www.dev-server.com";

std::string server	= SERVER_PRODUCTION;
std::string port	= "80";
std::string api		= "/";
std::string app_id	= "1";

po::options_description desc("Options");
po::variables_map vm;

boost::atomic<logger *> logger::instance_(0);
boost::mutex logger::instantiation_mutex;

/* logger public singleton accessor */

	logger* logger::instance()
	{
		logger * tmp = instance_.load(boost::memory_order_consume);
		if (!tmp) {
			std::cout << "!logger: " << "\n";

			boost::mutex::scoped_lock guard(instantiation_mutex);
			tmp = instance_.load(boost::memory_order_consume);
			if (!tmp) {
				tmp = new logger();
				instance_.store(tmp, boost::memory_order_release);
			}
		}
		std::cout << "logger: " << "\n";
		return tmp;
	}

/* logger private constructors */

	// no arguement constructor, this should always called. ALWAYS.
	logger::logger()
	{
		// set program options: these will be read in on instantiation if settings.ini exists
		desc.add_options()
		  ("app_id", po::value< std::string >( &app_id ), "app_id" )
		  ("server", po::value< std::string >( &server ), "server" )
		  ("api", po::value< std::string >( &api ), "api" )
		  ("port", po::value< std::string >( &port ), "port" );

		read_settings( desc, vm );
		c = new client("localhost", "/");

	    
	}

	logger::logger(const std::string& server_fqdn, const std::string& path)
	{
		server = server_fqdn;
		api = path;
		logger();
	}

/* logger class getter/setters */
	void logger::set_api(const std::string& logger_api)
	{
		api = logger_api;
	}
	void logger::set_server(const std::string& logger_fqdn)
	{
		server = logger_fqdn;
	}
	void logger::set_app_id(const std::string& logger_app_id)
	{
		app_id = logger_app_id;
	}
	void logger::set_port(const std::string& logger_port)
	{
		port = logger_port;
	}
	std::string logger::get_api()
	{
		return api;
	}
	std::string logger::get_server()
	{
		return server;
	}
	std::string logger::get_app_id()
	{
		return app_id;
	}
	std::string logger::get_port()
	{
		return port;
	}

/*  config.ini read/write functions */
	void logger::write_settings(const std::string& logger_app_id,const std::string& logger_fqdn,const std::string& logger_port,const std::string& logger_api)
	{
		std::ofstream settings_file( "settings.ini" );
		settings_file << "app_id = " << logger_app_id.c_str() << std::endl;
		settings_file << "server = " << logger_fqdn.c_str() << std::endl;
		settings_file << "port = " << logger_port.c_str() << std::endl;
		settings_file << "api = " << logger_api.c_str() << std::endl;
		settings_file.close();  
	}

	void logger::write_settings()
	{
		std::ofstream settings_file( "settings.ini" );
		settings_file << "app_id = " << app_id.c_str() << std::endl;
		settings_file << "server = " << server.c_str() << std::endl;
		settings_file << "port = " << port.c_str() << std::endl;
		settings_file << "api = " << api.c_str() << std::endl;
		settings_file.close();  
	}

	void logger::read_settings( po::options_description& desc, po::variables_map& vm )
	{
		std::ifstream settings_file( "settings.ini" );

		// Clear the map. This is important to get the latest changes...
		vm = po::variables_map();

		po::store( po::parse_config_file( settings_file , desc ), vm );
		settings_file.close();
		po::notify( vm );    
	}

	int main(int argc, char* argv[])
	{

		logger *l1 = logger::instance();
		logger *l2 = logger::instance();
		std::cout << l1->get_api() << "\n";
		l2->set_api("35");
		l2->write_settings();
		std::cout << l2->get_api() << "\n";
		std::cout << l1->get_api() << "\n";

		return 0;

	};
