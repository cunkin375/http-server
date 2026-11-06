#include <arpa/inet.h>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <malloc.h>
#include <memory.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>

namespace
{

bool show_message = false;

} // namespace

int main(int argc, char **argv)
{
    if (argc > 1)
        show_message = true;

    std::int32_t socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    // bind socket to port
    struct sockaddr_in socket_address;
    socket_address.sin_family = AF_INET;
    socket_address.sin_port   = htons(8080);
    inet_pton(AF_INET, "0.0.0.0", &socket_address.sin_addr);
    if (0 != bind(socket_fd, reinterpret_cast<struct sockaddr *>(&socket_address), sizeof(socket_address)))
    {
        std::perror("bind() failed");
        std::exit(-1);
    }
    listen(socket_fd, 5);

    // accept producer
    struct sockaddr_in producer_socket_address;
    producer_socket_address.sin_family = AF_INET;
    producer_socket_address.sin_port   = htons(8080);
    socklen_t    socket_len            = sizeof(producer_socket_address);
    std::int32_t producer_fd           = accept(socket_fd, reinterpret_cast<struct sockaddr *>(&producer_socket_address), &socket_len);
    if (producer_fd < 0)
    {
        std::perror("accept() client failed");
        std::exit(-1);
    }
    const char *msg = "Hello!\r\n";
    write(producer_fd, msg, strlen(msg));

    // read in chunks
    std::string   final_message;
    std::uint32_t bytes_read{ 0 };
    char          buffer[4096];
    while (true)
    {
        std::int32_t result = read(producer_fd, buffer, sizeof(buffer));
        if (result < 0)
        {
            std::cout << "read() error after" << bytes_read <<  "bytes: " << strerror(errno) << "\n";
            break;
        }
        if (result == 0)
        {
            std::cout << "EOF\n";
            break;
        }
        bytes_read += result;
        final_message.append(buffer);
    }

    if (show_message)
        std::cout << final_message << "\n";
    std::cout << "Read" << bytes_read << "bytes";
}
