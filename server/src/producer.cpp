#include <arpa/inet.h>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <malloc.h>
#include <memory.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

namespace
{

std::byte buffer[1000000];

} // namespace

int main()
{
    memset(&buffer, 'd', sizeof(buffer));

    std::int32_t socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in socket_address;
    socket_address.sin_family = AF_INET;
    socket_address.sin_port   = htons(8080); // bind to port 8080
    inet_pton(AF_INET, "127.0.0.1", &socket_address.sin_addr);

    if (auto result = connect(socket_fd, reinterpret_cast<const struct sockaddr *>(&socket_address), sizeof(socket_address)); result != 0)
    {
        std::perror("connect failed");
        std::exit(-1);
    }

    write(socket_fd, buffer, sizeof(buffer));
    sleep(5);
    close(socket_fd);
}
