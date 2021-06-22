import http.server
import os
import socket
import ssl
import threading

class HTTPS_Server(threading.Thread):

    def __init__(self, ota_image_dir, server_ip, server_port):
        threading.Thread.__init__(self)
        self.ota_image_dir = ota_image_dir
        self.server_ip = server_ip
        self.server_port = server_port

    def run(self):
        os.chdir(self.ota_image_dir)
        server_file = os.path.join(self.ota_image_dir, 'ca_cert.pem')
        key_file = os.path.join(self.ota_image_dir, 'ca_key.pem')
        httpd = http.server.HTTPServer((self.server_ip, self.server_port), http.server.SimpleHTTPRequestHandler)
        httpd.socket = ssl.wrap_socket(httpd.socket,
                                       keyfile=key_file,
                                       certfile=server_file, server_side=True)
        httpd.serve_forever()

if __name__ == '__main__':
    https_thread = HTTPS_Server(".", '192.168.7.10', 8070)
    https_thread.start()
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect(("192.168.7.1", 1234))
    s.send("https://192.168.7.10:8070/<binary>".encode())
    s.close()
    https_thread.join()
