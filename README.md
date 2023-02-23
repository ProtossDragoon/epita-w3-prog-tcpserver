# Implementation of TCP Server

EPITA - Week3 - Programming

![Workflow](https://github.com/ProtossDragoon/epita-w3-prog-tcpserver/actions/workflows/master.yaml/badge.svg)

## Quickstart

`terminal`
```bash
$ git clone https://github.com/ProtossDragoon/epita-w2-prog-tcpclient.git
$ cd epita-w2-prog-tcpclient
```

### echo_server

`terminal`
```bash
$ cd echo_server
$ make
```

#### echo_test

`test1`
```
$ ./echo_test
Hello World!           # Press Enter
Hello World!
My name is David.      # Press Enter
My name is David.
Good Bye!              # Press Enter
Good Bye!              # Press Ctrl-D (send the EOF character).
$
```

`test2`
```
$ ./echo_test echo.h
#ifndef ECHO_H
#define ECHO_H

void echo(int fd_in, int fd_out);

#endif
```

#### single_server

`server terminal`
```
$ ./single_server 2048
Waiting for connections...
```

`client terminal`
```
$ nc localhost 2048
```

`server terminal`
```
$ ./single_server 2048
Waiting for connections...
Connection successful!
```

`client terminal`
```
$ nc localhost 2048
Hello World!
Hello World!
Who are you?
Who are you?
^C
```

#### loop_server

```
$ ./loop_server 2048
Waiting for connections...
```

```
`client1 terminal`
$ nc localhost 2048
```

`server terminal`
```
$ ./loop_server 2048
Waiting for connections...
Connection successful!
```

`client2 terminal`
```
$ nc localhost 2048
```

`server terminal`
```
$ ./loop_server 2048
Waiting for connections...
Connection successful!
```

`client1 terminal`
```
$ nc localhost 2048
Hello World!
Hello World!
Are you a number?
Are you a number?
```

`client2 terminal`
```
$ nc localhost 2048
No, I am not.
I mean, I am not a number.
```

`client1 terminal`
```
$ nc localhost 2048
Hello World!
Hello World!
Are you a number?
Are you a number?
^C
```

`server terminal`
```
$ ./loop_server 2048
Waiting for connections...
Connection successful!
Waiting for connections...
Connection successful!
```

`client2 terminal`
```
$ nc localhost 2048
No, I am not.
I mean, I am not a number.
No, I am not.
I mean, I am not a number.
```

`client2 terminal`
```
$ nc localhost 2048
No, I am not.
I mean, I am not a number.
No, I am not.
I mean, I am not a number.
^C
```

`server terminal`
```
$ ./loop_server 2048
Waiting for connections...
Connection successful!
Waiting for connections...
Connection successful!
Waiting for connections...
```


#### fork_server

`server terminal`
```
$ ./fork_server 2048
Waiting for connections...
```

`client1 terminal`
```
$ nc localhost 2048
```

`server terminal`
```
$ ./fork_server 2048
Waiting for connection...
New connection (pid = 12717)
```

`client2 terminal`
```
$ nc localhost 2048
```

`server terminal`
```
$ ./fork_server 2048
Waiting for connection...
New connection (pid = 12717)
New connection (pid = 12773)
```

`client1 terminal`
```
$ nc localhost 2048
Hello World!
Hello World!
Are you a number?
Are you a number?
```

`client2 terminal`
```
$ nc localhost 2048
No, I am not.
No, I am not.
I mean, I am not a number.
I mean, I am not a number.
```

`client1 terminal`
```
$ nc localhost 2048
Hello World!
Hello World!
Are you a number?
Are you a number?
^C
```

`server terminal`
```
$ ./fork_server 2048
Waiting for connection...
New connection (pid = 12717)
New connection (pid = 12773)
Close connection (pid = 12717)
Finally, close the second client.
```

`client2 terminal`
```
$ nc localhost 2048
No, I am not.
No, I am not.
I mean, I am not a number.
I mean, I am not a number.
^C
```

`server terminal`
```
$ ./fork_server 2048
Waiting for connection...
New connection (pid = 12717)
New connection (pid = 12773)
Close connection (pid = 12717)
Close connection (pid = 12773)
```

### bc_server

`terminal`
```bash
$ cd bc_server
$ make
```

`server terminal`
```
$ ./main 2048
```

`client1 terminal`
```
$ nc localhost 2048
84/2
42
```

`client2 terminal`
```
$ nc localhost 2048
30+12
42
10/0
Runtime error (func=(main), adr=6): Divide by zero
10*2
20
^C
```

## Notes

If you are using VSCode, change your "type" in your launch.json file, e.g. `"type": "gdb"`