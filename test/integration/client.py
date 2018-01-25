import socket

SERVER_ADDRESS = ('localhost', 3000)
BUFFER_SIZE = 1024
NUMBERS_DELIMITER = ' '


def send(interval):
    connection = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    connection.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    connection.connect(SERVER_ADDRESS)
    connection.sendall(interval)
    print("Sent %a" % interval)
    buffer = connection.recv(BUFFER_SIZE)
    print("Received %a" % buffer)


if __name__ == "__main__":
    send(b'100 200')
    send(b'200 300')
    send(b'500 700')
    send(b'200 700')
