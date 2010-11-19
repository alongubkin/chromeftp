#ifndef _FTPSESSION_H_
#define _FTPSESSION_H_

#include <string>

#include <boost/asio.hpp>
#include <boost/bind.hpp>

using boost::asio::ip::tcp;

class FtpSession {
	public:
		class EmptyCallback {
			public: 
				virtual void Run() = 0; 
		};
		
		class ErrorCallback {
			public:
				virtual void Run(std::string message) = 0;
		};

		FtpSession();
		 ~FtpSession();

		void Connect(std::string& server, EmptyCallback *connectCallback, ErrorCallback *errorCallback);

	private:
		void OnResolve(const boost::system::error_code& err, tcp::resolver::iterator endpoint_iterator);
		void OnConnect(const boost::system::error_code& err, tcp::resolver::iterator endpoint_iterator);

		EmptyCallback *connectCallback;
		ErrorCallback *connectErrorCallback;

		tcp::resolver *resolver_;
		tcp::socket *socket_;

		boost::asio::streambuf request_;
		boost::asio::streambuf response_;
};

#endif // _FTPSESSION_H_
