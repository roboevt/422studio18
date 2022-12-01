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
5. 