1. Eric Todd
2.  Client: roboevt@DESKTOP-JHQK8MN:~/dev/422/18-studio$ ./client a
        1 2 3 4 5 6 7 8 9 10
    Server: roboevt@DESKTOP-JHQK8MN:~/dev/422/18-studio$ ./server a
        1
        2
        3
        4
        5
        6
        7
        8
        9
        10
3.  ~/dev/422/18-studio$ ./server a
    Client connected
    1
    2
    3
    Client disconnected
    Client connected
    1
    2
    3
    Client disconnected
    Client connected
    1
    2
    3
    Client disconnected
    Client connected
    418
    I'm a teapot
    Code recieved, terminating
    Server terminated
4.  ./client2
    1 2 3
    roboevt@DESKTOP-JHQK8MN:~/dev/422/18-studio$ ./client2 quit
    [e.todd@shell cse422]$ ./server
    Client connected
    1
    2
    3
    Client disconnected
    Client connected
    418
    I'm a teapot
    Code recieved, terminating
    Server terminated
5.  roboevt@MSI_GS66:~/dev/422/422studio18$ ./client2
    Host name: MSI_GS66
    Connected to shell.cec.wustl.edu:30003
    1 2 3
    [e.todd@shell cse422]$ ./server
    Host name: shell.cec.wustl.edu
    Client connected
    1
    2
    3
    Client disconnected
    Client connected
    1
    2
    3
    Client disconnected
6.  The client uses htonl, in order to convert from the machine's byte order to that of
    the network. On the other end, the server uses ntohl to convert from the network's
    format to it's own. Both use the *l function, as it is appropriate for 32 bit
    unsigned integers, which is what we want to send.
7. 