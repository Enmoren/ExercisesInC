/* The program connects to advice server and prints a reply.

Author: Enmo Ren
Copyright (c) Enmo Corporation.

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software.

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

void error(char *msg)
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(1);
}

int open_socket()
{
    // create the listening socket
    int sender_d = socket(PF_INET, SOCK_STREAM, 0);
    if (sender_d == -1)
        error("socket failed.");

    struct sockaddr_in name;
    name.sin_family = PF_INET;
    name.sin_port = (in_port_t)htons(30000);
    name.sin_addr.s_addr = htonl(INADDR_ANY);

    // Do we need to reset socket options for client?
    // set socket options
    // int reuse = 1;
    // int res = setsockopt(sender_d,
    //                SOL_SOCKET,
    //                SO_REUSEADDR,
    //                (char *)&reuse,
    //                sizeof(int));
    // if (res == -1)
    //     error("Can't set the 'reuse' option on the socket.");

    // connect the socket to server
    int res = connect(sender_d, (struct sockaddr *) &name, sizeof(name));
    if (res == -1)
        error("Can't bind the port");

    return sender_d;
}

int main(int argc, char *argv[])
{
    int d_sock, bytes_received;
    char buf[255], rec[256];

    /* connect to server */
    d_sock = open_socket();

    /* display page on stdout in 255 byte chunks */
    bytes_received = recv(d_sock, rec, 255, 0);
    while (bytes_received) {
        if (bytes_received == EOF)
            error("can't read from server");

        rec[bytes_received] = '\0';
        printf("%s", rec);
        bytes_received = recv(d_sock, rec, 255, 0);
    }
    //print a reply to server
    printf("%s\n", "Here is the reply!");
    close(d_sock);

    return 0;
}
