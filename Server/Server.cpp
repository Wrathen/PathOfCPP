#include "Core.h"
#include "Core/Network/Windows.h"

int main() {
    Core::Log("<-------------------------------->");
    Core::Log("<---- ASCENDANTS GAME SERVER ---->");
    Core::Log("<-------------------------------->");

    Core::ServerSocket server = Core::ServerSocket();
    server.StartListening();
    server.Send(server.clients[0], "haha very funny bro", 21);
    server.Read(server.clients[0]);
    while (1) {};
}