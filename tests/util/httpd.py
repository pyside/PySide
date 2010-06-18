import SocketServer
import BaseHTTPServer
import random

from threading import Thread


class TestHandler(BaseHTTPServer.BaseHTTPRequestHandler):
    DATA = "PySide Server"

    def do_GET(self):
        self.send_head()
        self.wfile.write(TestHandler.DATA)

    def do_HEAD(self):
        self.send_head()

    def send_head(self):
        self.send_response(200)
        self.send_header("Content-type", "text/plain")
        self.send_header("Content-Length", str(len(TestHandler.DATA)))
        self.end_headers()

class TestSecureHandler(BaseHTTPServer.BaseHTTPRequestHandler):
    DATA = "PySide"

    def do_GET(self):
        self.send_head()
        self.wfile.write(TestHandler.DATA)

    def do_HEAD(self):
        self.send_head()

    def send_head(self):
        try:
            handler = self.marshall_handler()
            handler.do_request(self)
        except:
            self.send_response(401)
            self.send_header("WWW-Authenticate", "Basic realm='Secure Area'")
            self.send_header("Content-type", "text/plain")
            self.send_header("Content-Length", str(len(TestHandler.DATA)))
            self.end_headers()


class TestServer(Thread):

    def __init__(self, secure=False):
        Thread.__init__(self)

        self._port = 8000 + random.randint(0, 100)
        self.keep_running = True
        server = SocketServer.TCPServer

        if secure:
            handle = TestSecureHandler
        else:
            handle = TestHandler

        self.httpd = SocketServer.TCPServer((''  , self._port), handle)

    def port(self):
        return self._port

    def run(self):
        self.httpd.serve_forever()

    def shutdown(self):
        self.httpd.shutdown()
        self.join()

