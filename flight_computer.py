import krpc
import tornado.ioloop
import tornado.web

# -*- coding: utf-8 -*-

from sockjs.tornado import SockJSConnection, SockJSRouter, proto

favicon_path = 'favicon.ico'

# Start kRPC connection.
conn = krpc.connect()
print('Server version =', conn.krpc.get_status().version)
vessel = conn.space_center.active_vessel

# Setup telemetry streams.
try:
    ut = conn.add_stream(getattr, conn.space_center, 'ut')
    altitude = conn.add_stream(getattr, vessel.flight(), 'mean_altitude')
    apoapsis = conn.add_stream(getattr, vessel.orbit, 'apoapsis_altitude')
    stage3_resources = vessel.resources_in_decouple_stage(stage=3, cumulative=False)
    srb_fuel = conn.add_stream(stage3_resources.amount, 'SolidFuel')
except krpc.error.RPCError, e:
    print 'Make sure your server is at localhost:50000 and in Launch.'
    exit(1)
base_ut = ut()

class IndexHandler(tornado.web.RequestHandler):
    """Regular HTTP handler to serve the index page"""
    def get(self):
        self.render('index.html')


class FlightDisplayHandler(tornado.web.RequestHandler):
    """Regular HTTP handler to serve the flight display page"""
    def get(self):
        self.render('flight_display.html')


# Out broadcast connection.
class BroadcastConnection(SockJSConnection):
    clients = set()

    def on_open(self, info):
        self.clients.add(self)

    def on_message(self, msg):
        self.broadcast(self.clients, msg)

    def on_close(self):
        self.clients.remove(self)

BroadcastRouter = SockJSRouter(BroadcastConnection, '/broadcast')


# Telemetry class
class TelemetryConnection(SockJSConnection):
    def on_open(self, info):
        self.loop = tornado.ioloop.PeriodicCallback(self._send_telemetry, 1000)
        self.loop.start()

    def on_message(self):
        pass

    def on_close(self):
        self.loop.stop()

    def _send_telemetry(self):
        telemetry = {
            'uptime' : ut() - base_ut,
            'altitude' : altitude(),
            'apoapsis' : apoapsis(),
            'srb_fuel' : srb_fuel(),
        }
        data = proto.json_encode(telemetry)
        self.send(data)

TelemetryRouter = SockJSRouter(TelemetryConnection, '/telemetry')

if __name__ == "__main__":
    # import logging
    # logging.getLogger().setLevel(logging.DEBUG)

    # Create application.
    app = tornado.web.Application(
            [(r'/', IndexHandler),
             (r'/flight_display', FlightDisplayHandler),
            ] +
            BroadcastRouter.urls +
            TelemetryRouter.urls
    )
    app.listen(8080)

    print 'Listening on 0.0.0.0:8080'

    tornado.ioloop.IOLoop.instance().start()
