#include <array>
#include <boost/asio.hpp>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <vector>
using namespace boost::asio;
using ip::tcp;
using std::cout;
using std::endl;
using std::string;

struct MessageHeader {
  int64_t totalSize;
  int64_t chunkCount;
};

struct ChunkHeader {
  int64_t index;
  int64_t size;
};

MessageHeader parseHeader(const char* data) {
  MessageHeader header;
  memcpy(&header, data, sizeof(MessageHeader));
  return header;
}

ChunkHeader parseChunkHeader(const char* data) {
  ChunkHeader header;
  memcpy(&header, data, sizeof(MessageHeader));
  return header;
}

MessageHeader readHeader(tcp::socket& socket) {
  std::array<char, sizeof(MessageHeader)> buffer;
  boost::asio::read(socket, boost::asio::buffer(buffer));
  return parseHeader(buffer.data());
}

ChunkHeader readChunkHeader(tcp::socket& socket) {
  std::array<char, sizeof(ChunkHeader)> buffer;
  boost::asio::read(socket, boost::asio::buffer(buffer));
  return parseChunkHeader(buffer.data());
}

std::vector<char> readChunkMessage(tcp::socket& socket) {
  auto chunkHeader = readChunkHeader(socket);
  std::vector<char> chunk(chunkHeader.size);
  boost::asio::read(socket, boost::asio::buffer(chunk));
  return chunk;
}

int main() {
  boost::asio::io_service io_service;

  // listen
  tcp::acceptor acceptor_(io_service, tcp::endpoint(tcp::v4(), 3333));

  // socket
  tcp::socket socket_(io_service);

  // waiting
  acceptor_.accept(socket_);

  auto messageHeader = readHeader(socket_);

  for (auto chunkIndex = 0ll; chunkIndex != messageHeader.chunkCount; ++chunkIndex) {
    auto chunk = readChunkMessage(socket_);

    // open the file in append mode
    std::ofstream file("transferd.bin", std::ofstream::app);
    file.write(chunk.data(), chunk.size());
  }

  // response
  boost::asio::write(socket_, boost::asio::buffer("data recived"));

  return 0;
}
