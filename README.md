## Simple HTTP Server

A lightweight HTTP server that handles GET requests to serve HTML, CSS, JavaScript, and image files.
## Overview

This project was built to gain a deeper understanding of how HTTP requests work at a low level from the backend perspective. While I was already familiar with sockets and pthreads, this was a great way to reinforce my knowledge and apply them in a real-world scenario.

## Throughout the development process, I worked with:

    Sockets & Multithreading (pthreads) for handling client connections.
    Regex for parsing HTTP requests.
    File operations & stat library for serving static files efficiently.

## What I Learned

    The inner workings of HTTP requests and responses.
    How to manage multiple client connections using threads.
    Efficient file reading and serving different MIME types.
    The role of regex in extracting request data.

This project provided valuable insights into backend development, reinforcing key concepts and improving my low-level programming skills.

## Build and Run

1. If the `build` directory exists and contains files, delete them.
2. Enter the `build` directory:
   ```sh
   cd build
   ```
3. Run CMake:
   ```sh
   cmake ..
   ```
4. Compile the project:
   ```sh
   make
   ```
5. Run the server:
   ```sh
   ./HttpServer <Port>
   ```
   - If no port is specified, the default port `3000` will be used.

## Example Usage

Start the server on port 8080:
```sh
./HttpServer 8080
```

Start the server with the default port:
```sh
./HttpServer
```


