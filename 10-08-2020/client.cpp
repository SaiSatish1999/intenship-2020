
#include <boost/asio.hpp>
#include <iostream>
#include <fstream>
#include <vector>

using namespace boost::asio;
using ip::tcp;
using std::string;
using std::cout;
using std::endl;
using std::vector;

const vector<char> fileVec(const std::string & fileName) {
    std::ifstream file(fileName, std::ios::in | std::ios::binary);
  vector<char> tempVec ((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
  file.close();
    return tempVec;
};

int main() {
  boost::asio::io_service io_service;

//socket
  tcp::socket socket(io_service);
//connection
  socket.connect(tcp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 3333));

//write to server
    auto vdata = fileVec("example.bin");
    vdata.push_back('\n');
    vdata.push_back('e');
    vdata.push_back('n');
    vdata.push_back('d');
    vdata.push_back('\n');
  boost::system::error_code error;
  boost::asio::write(socket, boost::asio::buffer(vdata), error);

//response from server
  boost::asio::streambuf receive_buffer;
  boost::asio::read(socket, receive_buffer, boost::asio::transfer_all(), error);
  const char* response = boost::asio::buffer_cast<const char*>(receive_buffer.data());
  cout << response;

  return 0;
}
