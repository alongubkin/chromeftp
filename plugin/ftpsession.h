#ifndef _FTPSESSION_H_
#define _FTPSESSION_H_

#include <string>

#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include "callbacks.h"

using boost::asio::ip::tcp;

namespace chromeftp {

typedef Closure FtpSessionConnectCallback;
typedef Callback1<const std::string&> FtpSessionErrorCallback;

class FtpSession {
public:
    FtpSession();
    ~FtpSession();

    void Connect(std::string& server, FtpSessionConnectCallback *connectCallback, FtpSessionErrorCallback *errorCallback);

private:
    void OnResolve(const boost::system::error_code& err, tcp::resolver::iterator endpoint_iterator);
    void OnConnect(const boost::system::error_code& err, tcp::resolver::iterator endpoint_iterator);
      
    boost::shared_ptr<FtpSessionConnectCallback> onconnect_;
    boost::shared_ptr<FtpSessionErrorCallback> onerror_;

    boost::shared_ptr<boost::asio::io_service> io_service_;
    boost::shared_ptr<tcp::resolver> resolver_;
    boost::shared_ptr<tcp::socket> socket_;

    // boost::asio::streambuf request_;
    // boost::asio::streambuf response_;
};
}

#endif // _FTPSESSION_H_
