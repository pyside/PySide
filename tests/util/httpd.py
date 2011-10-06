import os
import sys
import threading
import select
import random
import py3kcompat as py3k

if py3k.IS_PY3K:
    import socketserver as SocketServer
    import http.server as BaseHTTPServer
else:
    import SocketServer
    import BaseHTTPServer

class TestHandler(BaseHTTPServer.BaseHTTPRequestHandler):
    DATA = "PySide Server"
    allow_reuse_address = True

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
    allow_reuse_address = True

    def do_GET(self):
        self.send_head()
        self.wfile.write(py3k.b(TestHandler.DATA))

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

# Workaround for the missing shutdown method in python2.5
class CompatTCPServer(SocketServer.TCPServer):
    def __init__(self, server_address, RequestHandlerClass):
        SocketServer.TCPServer.__init__(self, server_address, RequestHandlerClass)

        self.isPy25 = sys.version_info[0] == 2 and sys.version_info[1] == 5
        if self.isPy25:
            self.__is_shut_down = threading.Event()
            self.__serving = False

    def serve_forever(self, poll_interval=0.5):
        """Handle one request at a time until shutdown.

        Polls for shutdown every poll_interval seconds. Ignores
        self.timeout. If you need to do periodic tasks, do them in
        another thread.
        """
        if self.isPy25:
            self.__serving = True
            self.__is_shut_down.clear()
            while self.__serving:
                # XXX: Consider using another file descriptor or
                # connecting to the socket to wake this up instead of
                # polling. Polling reduces our responsiveness to a
                # shutdown request and wastes cpu at all other times.
                r, w, e = select.select([self], [], [], poll_interval)
                if r:
                    self.py25_handle_request_noblock()
            self.__is_shut_down.set()
        else:
            SocketServer.TCPServer.serve_forever(self, poll_interval)

    def py25_handle_request_noblock(self):
        """Handle one request, without blocking.

        I assume that select.select has returned that the socket is
        readable before this function was called, so there should be
        no risk of blocking in get_request().
        """
        if self.isPy25:
            try:
                request, client_address = self.get_request()
            except socket.error:
                return
            if self.verify_request(request, client_address):
                try:
                    self.process_request(request, client_address)
                except:
                    self.handle_error(request, client_address)
                    self.close_request(request)

    def shutdown(self):
        """Stops the serve_forever loop.

        Blocks until the loop has finished. This must be called while
        serve_forever() is running in another thread, or it will
        deadlock.
        """
        if self.isPy25:
            self.__serving = False
            if not self.__is_shut_down:
                self.__is_shut_down.wait()
        else:
            SocketServer.TCPServer.shutdown(self)


class TestServer(threading.Thread):

    def __init__(self, secure=False):
        threading.Thread.__init__(self)

        self._port = int(os.getenv("PYSIDE_TESTSERVER_PORT") or 12321)
        self.keep_running = True

        if secure:
            handle = TestSecureHandler
        else:
            handle = TestHandler

        while True:
            try:
                self.httpd = CompatTCPServer((''  , self._port), handle)
                break
            except:
                self._port = self._port + random.randint(1, 100)

    def port(self):
        return self._port

    def run(self):
        self.httpd.serve_forever()

    def shutdown(self):
        self.httpd.shutdown()
        self.join()

