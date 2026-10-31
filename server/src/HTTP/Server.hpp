#include <string>
#include <string_view>

namespace HTTP
{

class Server
{
public:
    Server(std::string_view socket, std::string_view port) : m_Socket{ socket }, m_Port{ port } {}

    void Run();

private:
    std::string_view m_Socket;
    std::string_view m_Port;
};

} // namespace HTTP
