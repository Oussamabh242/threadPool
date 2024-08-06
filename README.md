# TCP File Server and Client

This project implements a multi-threaded TCP file server in C and a concurrent TCP client in Python. The server can handle multiple client connections simultaneously and serve requested files to clients.

## Server (C)

The server is implemented in C and uses a thread pool to handle multiple client connections concurrently.

### Features

- Multi-threaded design using a thread pool
- Custom queue implementation for managing client connections
- File reading and serving capabilities
- Error handling for file operations and network communications

### Files

- `server.c`: Main server implementation
- `queue.c`: Queue data structure implementation
- `queue.h`: Header file for the queue

### Compilation

To compile the server, use the following command:

   ```bash
   gcc server.c queue.c -o server -pthread
```

### Usage

Run the compiled server:

```bash
./server <number_of_threads>
```
The server will start and listen for incoming connections on `127.0.0.1:65432`.

## Client (Python)

The client is implemented in Python and can send multiple concurrent requests to the server.

### Features

- Asynchronous implementation using `asyncio`
- Supports sending multiple concurrent requests
- Configurable number of concurrent requests

### Files

- `client.py`: Python client implementation

### Requirements

- Python 3.7+
- `asyncio` library (included in Python standard library)

### Usage

Run the client with the desired number of concurrent requests:

   ```bash
   python3 client.py <number_of_concurrent_requests>
```

## How It Works

1. The server starts and listens for incoming connections.
2. When a client connects, the connection is added to a queue.
3. Worker threads from the thread pool pick up client connections from the queue.
4. The client sends a filename to the server.
5. The server reads the requested file and sends its contents back to the client.
6. The client receives and displays the file contents.
