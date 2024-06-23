#pragma once
#include <vector>

// Winsocket Includes
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

// Internal Includes
#include "Core/Network/Configs.h"
#include "Core/Miscellaneous/ErrorHandler.h"

namespace Core
{
    struct BaseSocket
    {
        // Windows specific members
        WSADATA wsaData;
        addrinfo* addressInfo = nullptr;
        addrinfo hints;
        int iResult = 0;

        BaseSocket()
        {
            // Initialize Winsock
            iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
            VERIFYF(iResult == 0, "WSAStartup failed with error: iResult");

            ZeroMemory(&hints, sizeof(hints));
            hints.ai_family = AF_INET;
            hints.ai_socktype = SOCK_STREAM;
            hints.ai_protocol = IPPROTO_TCP;
        }

        void GetAddressInfo()
        {
            if (addressInfo)
                return;

            // Resolve the server address and port
            iResult = getaddrinfo(SERVER_ADDRESS, SERVER_PORT, &hints, &addressInfo);
            VERIFYF(iResult == 0, "getaddrinfo failed with error: iResult");
        }
        void ResetAddressInfo()
        {
            // Free memory.
            freeaddrinfo(addressInfo);
            addressInfo = nullptr;
        }
    };

    struct ClientSocket : BaseSocket
    {
        SOCKET server = INVALID_SOCKET;

        // Generic members
        bool isConnected = false;

        void Connect()
        {
            GetAddressInfo();

            // Connect to the Socket
            server = socket(addressInfo->ai_family, addressInfo->ai_socktype, addressInfo->ai_protocol);
            VERIFYF(server != INVALID_SOCKET, "Unable to create a socket to the server!");

            iResult = connect(server, addressInfo->ai_addr, (int)addressInfo->ai_addrlen);
            VERIFYF(iResult != SOCKET_ERROR, "Unable to connect to server!");

            ResetAddressInfo();

            isConnected = true;
        }

        void Destroy()
        {
            closesocket(server);
            WSACleanup();

            isConnected = false;
        }

        // Shuts down specific operations.
        void Shutdown(int flag = SD_BOTH)
        {
            iResult = shutdown(server, flag);
            VERIFYF(iResult != SOCKET_ERROR, "shutdown failed with error: WSAGetLastError()");
        }

        void Send(const char* buffer, size_t bufferSize)
        {
            iResult = send(server, buffer, bufferSize, 0);
            VERIFYF(iResult != SOCKET_ERROR, "Send failed with error: WSAGetLastError()");

            printf("Bytes Sent: %ld\n", iResult);
        }

        void Read()
        {
            while (iResult >= 0)
            {
                char recvbuf[DEFAULT_BUFLEN];
                iResult = recv(server, recvbuf, DEFAULT_BUFLEN, 0);
                VERIFYF(iResult >= 0, "recv failed with error: WSAGetLastError()");

                if (iResult == 0)
                {
                    printf("Connection closed.\n");
                    return;
                }

                std::cout << "[Server " << iResult << "bytes] " << recvbuf << "\n";
            }
        }
    };

    struct ServerSocket : BaseSocket
    {
        SOCKET listener = INVALID_SOCKET;
        std::vector<SOCKET> clients;

        void CloseSocket(SOCKET client) { closesocket(client); }
        void Destroy()
        {
            for (SOCKET client : clients)
                CloseSocket(client);

            WSACleanup();
        }

        void StartListening()
        {
            GetAddressInfo();

            VERIFYF(listener == INVALID_SOCKET, "You are already listening, wth!?");
            
            listener = socket(addressInfo->ai_family, addressInfo->ai_socktype, addressInfo->ai_protocol);
            VERIFYF(listener != INVALID_SOCKET, "socket failed with error: WSAGetLastError()");

            // Bind the socket.
            iResult = bind(listener, addressInfo->ai_addr, (int)addressInfo->ai_addrlen);
            VERIFYF(iResult != SOCKET_ERROR, "bind failed with error: WSAGetLastError()");

            // Listen to the connection.
            iResult = listen(listener, SOMAXCONN);
            VERIFYF(iResult != SOCKET_ERROR, "listen failed with error: WSAGetLastError()");

            // Accept a client socket.
            clients.push_back(accept(listener, NULL, NULL));
            VERIFYF(clients[0] != INVALID_SOCKET, "accept failed with error: WSAGetLastError()");

            ResetAddressInfo();
        }

        void StopListening()
        {
            VERIFYF(listener != INVALID_SOCKET, "Can you at least learn how to listen first before stopping?");
            VERIFYF(false, "To be implemented");

            closesocket(listener);
            listener = INVALID_SOCKET;
        }

        // Shuts down specific operations.
        void Shutdown(SOCKET client, int flag)
        {
            iResult = shutdown(client, flag);
            VERIFYF(iResult != SOCKET_ERROR, "shutdown failed with error: WSAGetLastError()");
        }

        void Send(SOCKET client, const char* buffer, size_t bufferSize)
        {
            int result = send(client, buffer, bufferSize, 0);
            VERIFYF(result != SOCKET_ERROR, "send failed with error: WSAGetLastError()");
            printf("Bytes sent: %d\n", result);
        }

        void Read(SOCKET client)
        {
            while (iResult >= 0)
            {
                char recvbuf[DEFAULT_BUFLEN];
                iResult = recv(client, recvbuf, DEFAULT_BUFLEN, 0);
                VERIFYF(iResult >= 0, "recv failed with error: WSAGetLastError()");

                if (iResult == 0)
                {
                    printf("Connection closed.\n");
                    return;
                }

                std::cout << "[Client " << iResult << "bytes] " << recvbuf << "\n";
            } 
        }
    };
}