#define BOOST_ASIO_HAS_IO_URING 1
#define BUFFER_SIZE 10

#include <boost/asio.hpp>
#include <iostream>
#include <vector>

int main() {
  boost::asio::io_context io_context;

  std::vector<char> arr1(BUFFER_SIZE);
  std::vector<char> arr2(BUFFER_SIZE);
  std::vector<char> results;

  boost::asio::stream_file stream1(io_context, "1.txt", boost::asio::stream_file::read_only);
  stream1.async_read_some(
      boost::asio::buffer(arr1),
      [&](const boost::system::error_code& ec, std::size_t n) {
        if (!ec) {
          std::cout << "Read " << n << " bytes from stream" << std::endl;
          results.insert(results.end(), arr1.begin(), arr1.begin() + n);
        }
      });

  boost::asio::stream_file stream2(io_context, "2.txt", boost::asio::stream_file::read_only);
  stream2.async_read_some(
      boost::asio::buffer(arr2),
      [&](const boost::system::error_code& ec, std::size_t n) {
        if (!ec) {
          std::cout << "Read " << n << " bytes from stream" << std::endl;
          results.insert(results.end(), arr2.begin(), arr2.begin() + n);
        }
      });

  io_context.run();

  for (auto c : results) {
    std::cout << c;
  }

  return 0;
}
