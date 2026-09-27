import socket
import threading
import time

HOST = "127.0.0.1"
PORT = 8080
CLIENTS = 10


def send_request(client_id):
    start = time.time()

    try:
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
            s.connect((HOST, PORT))

            request = (
                "GET / HTTP/1.1\r\n"
                "Host: localhost\r\n"
                "Connection: close\r\n"
                "\r\n"
            )

            s.sendall(request.encode())

            response = s.recv(4096)

            elapsed = time.time() - start

            print(
                f"Client {client_id}: "
                f"received {len(response)} bytes "
                f"in {elapsed:.2f}s"
            )

    except Exception as e:
        print(f"Client {client_id}: ERROR - {e}")


threads = []

print(f"Starting {CLIENTS} clients...\n")

total_start = time.time()

# Start all clients
for i in range(CLIENTS):
    thread = threading.Thread(
        target=send_request,
        args=(i,)
    )

    threads.append(thread)
    thread.start()


# Wait for all clients to finish
for thread in threads:
    thread.join()


total_elapsed = time.time() - total_start

print("\n----------------------------")
print(f"Total time: {total_elapsed:.2f}s")
print("----------------------------")