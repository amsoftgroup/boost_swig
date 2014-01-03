#pragma once	

#include <string>
#include <boost/program_options.hpp>
#include "client.h"

namespace singularity{


	class logger
	{

	public:

		static logger *instance();	
		void set_api(const std::string& logger_api);
		void set_server(const std::string& logger_fqdn);
		void set_app_id(const std::string& logger_app_id);
		void set_port(const std::string& logger_port);
		std::string get_api();
		std::string get_server();
		std::string get_app_id();
		std::string get_port();
		void write_settings();
		void write_settings(const std::string& logger_app_id, const std::string& logger_fqdn, const std::string& logger_port, const std::string& logger_api);

	private:

		logger();
		logger(const std::string& server, const std::string& path);
		client c;
		//logger(const std::string& logger_app_id, const std::string& logger_fqdn, const std::string& logger_port, const std::string& logger_api);
		static boost::atomic<logger *> instance_;
		static boost::mutex instantiation_mutex;
		void read_settings(boost::program_options::options_description& desc, boost::program_options::variables_map& vm);
		static boost::asio::io_service io_service;
	};

}