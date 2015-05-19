This is the specification of a eventbased shared memory protocol that can be used as an IPC.

Description:

This specification provides one of the way of using the shared memory with sockets as locks and events between one or more processes
with in the same system.

The disadvantage of the shared memory system is that it does not provide an event based notification when a process writes to it or
reads on the shared memory is complete so that the other process can use that memory to write further more data or something that
is similar to it.

This problem can be solved between two processes easily with semaphores. But here comes another issue of the events when used
along with in a system that uses event based select , epoll mechanism to wait on some particular sockets or timers to perform
the work. Such systems or the software needs a big amount of change (like writing a thread that waits on the semaphore for the
lock and distributes the data to the corresponding client).

This is solved in this specification with the usage of sockets.

Sockets are the communication end points that acts as channels and also as events so that a process can go to sleep on a particular
socket and it can do its job without worrying about waiting on that socket forever (in the meanwhile epoll can do that job for
the process).

The large amount of data transfer via socket is considered as an overhead because of the memcpy in the kernel side. But the performance
remains the same with small amounts of data.

The sockets here are used as event activators holding some kind of header information.

For example the following:

```
// tokens are used as the memory block locks
// the whole shared memory that is allocated for both of the producer
// and consumer is divided into a set of blocks of 1024 bytes in size or
// more.
//
// each of the block has a start pointer, length and lock that protects
// it from illegal writes.

struct _token_data {
    int token_number;
};

struct sapi_socket_event {
    void *block_start;
    uint32 block_len;
    struct _token_data tokens;
    int total_blocks;
};

// the producer list is hold by the producer and will be
// updated by her. The producer before sending the socket
// event sets one of the sent_tokens list node to a token
// number and increments the sent_token_count.
// upon reception of a socket event from the consumer the
// producer decrements the sent_token_count and it does a
// search in the sent_tokens list and destroys it .

struct token_producer_list {
    int sent_tokens[MAX_TOKENS];
    int sent_token_count;
    int free_tokens[MAX_TOKENS]; // MAX_TOKENS - sent_tokens gives us free tokens
};

// the consumer list is hold by the consumer and will be
// updated by her. The consumer after receiving the socket
// event sets one of the recv_tokens list node to a token
// number and increments the recv_tokens_count.
// after it is done with the shared memory it then, resets the
// token value in the recv_tokens list and decrements the
// recv_tokens_count. This table is only useful when the receiver
// has a thread that performs the reception and the data processing
// is handled in the other threads.


struct token_consumer_list {
    int recv_tokens[MAX_TOKENS];
    int recv_tokens_count;
    int free_tokens[MAX_TOKENS]; // MAX_TOKENS - recv_tokens gives us free tokens
};
```

This system provides a faster, same speed as the socket (10 usec on a modern-ish computer) with an event data to and fro from the
producer and consumer. Thus providing a larger data transfer with minimal over head between the links.
