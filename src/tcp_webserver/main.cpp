#include <sys/socket.h>
#include <iostream>
#include <netinet/in.h>
#include <unistd.h>

int main() {
    /** socket
     * domain ==> IPv4: AF_INET; IPv6: AF_INET6
     * type ==> TCP: SOCK_STEAM; UDP: SOCK_DGRAM
     * protocol ==> auto: 0
     * return int file descriptor
     */
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        std::cout << "socket failed" << std::endl;
        return 1;
    }

    /** sockaddr_in
     * Internet: sockaddr_in; Local Unix Sockets: sockaddr_un
     * sin_family: address type
     * sin_addr: IP address
     * sin_port: Port Number
     * htons (host to network short): Byte ordering
     */
    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(9090);
    if(bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        std::cout << "bind failed" << std::endl;
        return 1;
    }

    listen(server_fd, 3);
    std::cout << "listen on 127.0.0.1:9090.." << std::endl;

    close(server_fd);
    return 0;
}