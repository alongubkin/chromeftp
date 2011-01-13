#include "ftpsession.h"

namespace chromeftp {
FtpSession::FtpSession() {
    io_service_.reset(new boost::asio::io_service());

    resolver_.reset(new tcp::resolver(*io_service_.get()));
    socket_.reset(new tcp::socket(*io_service_.get()));
}

void FtpSession::Connect(std::string& server, FtpSessionConnectCallback *connectCallback, FtpSessionErrorCallback *errorCallback) {
    onconnect_.reset(connectCallback);
    onerror_.reset(errorCallback);
    
    tcp::resolver::query query(server, "ftp");

	resolver_.get()->async_resolve(query,
	    boost::bind(&FtpSession::OnResolve, this, 
            boost::asio::placeholders::error, 
                boost::asio::placeholders::iterator));

    io_service_.get()->run();
}

void FtpSession::OnResolve(const boost::system::error_code& err, tcp::resolver::iterator endpoint_iterator) {
    
    if (!err)
    {
        tcp::endpoint endpoint = *endpoint_iterator;

        socket_.get()->async_connect(endpoint,
            boost::bind(&FtpSession::OnConnect, this,
                boost::asio::placeholders::error, ++endpoint_iterator));
    }
    else
    {
        onerror_.get()->Run(err.message());
    }
}

void FtpSession::OnConnect(const boost::system::error_code& err, tcp::resolver::iterator endpoint_iterator) {
    if (!err)
	{
	    onconnect_.get()->Run();
	}
	else if (endpoint_iterator != tcp::resolver::iterator())
	{
	    socket_->close();
	    tcp::endpoint endpoint = *endpoint_iterator;
	    socket_.get()->async_connect(endpoint,
		    boost::bind(&FtpSession::OnConnect, this,
		        boost::asio::placeholders::error, ++endpoint_iterator));
	}
	else
	{
	    onerror_.get()->Run(err.message());
	}
}
}
