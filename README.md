# Multithreaded TCP Server in C with Python Client

This project includes a multithreaded TCP server implemented in C and a TCP client implemented in Python. The server handles concurrent client connections using a thread pool and processes requests to read and send the contents of a file.

## Table of Contents

- [Features](#features)
- [Requirements](#requirements)
- [Usage](#usage)
  - [Running the Server](#running-the-server)
  - [Running the Client](#running-the-client)
- [Code Explanation](#code-explanation)
  - [Server Code](#server-code)
  - [Queue Implementation](#queue-implementation)
  - [Client Code](#client-code)
- [Files](#files)

## Features

- Multithreaded server with a thread pool for handling multiple client connections concurrently.
- Simple queue implementation for managing client requests.
- Server reads the contents of a requested file and sends it back to the client.
- Python client capable of making multiple concurrent requests to the server.

## Requirements

- GCC compiler for C code.
- Python 3.6 or higher for the client.
- `pthread` library for multithreading in C.
- Basic understanding of socket programming in C and Python.

## Usage

### Running the Server

1. **Compile the Server:**

   ```bash
   gcc -o server server.c queue.c -lpthread
