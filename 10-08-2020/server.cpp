
#include <boost/asio.hpp>
#include <iostream>
#include <fstream>

using namespace boost::asio;
using ip::tcp;
using std::string;
using std::cout;
using std::endl;

int main() {
  boost::asio::io_service io_service;

//listen 
  tcp::acceptor acceptor_(io_service, tcp::endpoint(tcp::v4(), 3333));

//socket  
  tcp::socket socket_(io_service);

//waiting
  acceptor_.accept(socket_);

//read
  boost::asio::streambuf buf;
  boost::asio::read_until(socket_, buf, "\nend\n");
  auto data = boost::asio::buffer_cast<const char*>(buf.data());
  
  std::ofstream file("transferd.bin");
  file.write(data, buf.size());

//response
  boost::asio::write(socket_, boost::asio::buffer("data recived"));

  return 0;
}
