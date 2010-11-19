#include "ftpsession.h"

FtpSession::FtpSession() {
	boost::asio::io_service io_service;

	resolver_ = new tcp::resolver(io_service);
	socket_ = new tcp::socket(io_service);
}

FtpSession::~FtpSession() { 
	delete resolver_;
	delete socket_;

	delete connectCallback;
	delete connectErrorCallback;
}

void FtpSession::Connect(std::string& server, EmptyCallback *connectCallback, ErrorCallback *errorCallback) {
	this->connectCallback = connectCallback;
	this->connectErrorCallback = errorCallback;

	tcp::resolver::query query(server, "ftp");

	resolver_->async_resolve(query,
		boost::bind(&FtpSession::OnResolve, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::iterator));
}

void FtpSession::OnResolve(const boost::system::error_code& err, tcp::resolver::iterator endpoint_iterator) {
	if (!err)
	{
		tcp::endpoint endpoint = *endpoint_iterator;

		socket_->async_connect(endpoint,
			boost::bind(&FtpSession::OnConnect, this,
				boost::asio::placeholders::error, ++endpoint_iterator));
	}
	else
	{
		this->connectErrorCallback->Run(err.message());
	}
}

void FtpSession::OnConnect(const boost::system::error_code& err, tcp::resolver::iterator endpoint_iterator) {
	if (!err)
	{
		this->connectCallback->Run();
		
	}
	else if (endpoint_iterator != tcp::resolver::iterator())
	{
		socket_->close();
		tcp::endpoint endpoint = *endpoint_iterator;
		socket_->async_connect(endpoint,
			boost::bind(&FtpSession::OnConnect, this,
				boost::asio::placeholders::error, ++endpoint_iterator));
	}
	else
	{
		this->connectErrorCallback->Run(err.message());
	}
}
