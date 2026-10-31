#include "HTTP/Server.hpp"
#include "HTTP/RequestHandler.hpp"
#include "Util/Log.hpp"

int main()
{
    Log::Info("Hello, world!");
    auto handler = HTTP::RequestHandler{};
    auto server  = HTTP::Server{ "0.0.0.0", "8000" };
    server.Run();
}
