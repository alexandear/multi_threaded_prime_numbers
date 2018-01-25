import re
import socket

PORT = 3000
RECV_BUFFER_SIZE = 1024
NUMBERS_DELIMITER = ' '


def listen(port):
    connection = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    connection.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    connection.bind(('0.0.0.0', port))
    connection.listen(10)

    while True:
        current_connection, address = connection.accept()
        recv_data = current_connection.recv(RECV_BUFFER_SIZE)
        if not recv_data:
            continue
        print("Received: %a" % recv_data)

        send_data = get_send_data(recv_data)
        if not send_data:
            continue

        current_connection.send(send_data)
        print("Send: %a" % send_data)
        current_connection.close()


def get_send_data(recv_data):
    low, high = map(int, recv_data.decode().split(NUMBERS_DELIMITER))
    prime_numbers = primes(low, high)
    return NUMBERS_DELIMITER.join(str(x) for x in prime_numbers).encode()


def primes(low, high):
    return [x for x in range(low, high + 1) if is_prime(x)]


def is_prime(n):
    return re.compile(r'^1?$|^(11+)\1+$').match('1' * n) is None


if __name__ == "__main__":
    listen(PORT)
