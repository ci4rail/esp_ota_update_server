import http.server
import os
import socket
import ssl
import threading
import time

URL="https://192.168.7.10:8070/<binary>"
EEPROM_SIZE=512

class HTTPS_Server(threading.Thread):

    def __init__(self, server_ip, server_port):
        threading.Thread.__init__(self)
        self.server_ip = server_ip
        self.server_port = server_port

    def run(self):
        server_file = os.path.join('.', 'ca_cert.pem')
        key_file = os.path.join('.', 'ca_key.pem')
        httpd = http.server.HTTPServer((self.server_ip, self.server_port), http.server.SimpleHTTPRequestHandler)
        httpd.socket = ssl.wrap_socket(httpd.socket,
                                       keyfile=key_file,
                                       certfile=server_file, server_side=True)
        httpd.serve_forever()

if __name__ == '__main__':
    https_thread = HTTPS_Server('192.168.7.10', 8070)
    https_thread.start()
    time.sleep(2)
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect(("192.168.7.1", 1234))
    data = s.recv(EEPROM_SIZE)
    s.send(URL.encode())
    s.close()
    https_thread.join()
