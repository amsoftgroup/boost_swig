#pragma once	

#include <iostream>
#include <istream>
#include <ostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

class client//: resolver_, socket_
{
public:
	client(void);
	client(boost::asio::io_service& io_service, const std::string& server, const std::string& path);

	void set_path(const std::string& server_path);
	void set_server(const std::string& server_fqdn);

private:
	void handle_resolve(const boost::system::error_code& err, boost::asio::ip::tcp::resolver::iterator endpoint_iterator);
	void handle_connect(const boost::system::error_code& err);
	void handle_write_request(const boost::system::error_code& err);
	void handle_read_status_line(const boost::system::error_code& err);
	void handle_read_headers(const boost::system::error_code& err);
	void handle_read_content(const boost::system::error_code& err);
};

