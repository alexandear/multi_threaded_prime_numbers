import socket
import time
import rand

def listen():
    connection = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    connection.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    connection.bind(('localhost', 3000))
    connection.listen(10)

    while True:
        current_connection, address = connection.accept()
        data = current_connection.recv(1024)
        if data:
            print data
            time.sleep(random.uniform(0, 2))


if __name__ == "__main__":
    try:
        listen()
    except KeyboardInterrupt:
        pass
