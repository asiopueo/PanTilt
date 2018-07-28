#!/usr/bin/env python

####################################################################
#
#   Node which requests commands and publishes on a twist topic
#
####################################################################

import cmd, sys
import math
import serial

SERIAL_PORT = '/dev/ttyACM0'



# Helper function
def parse(arg):
    #print (tuple(map(float, arg.split())))
    return tuple(map(float, arg.split()))


# ROS backend
class Interface(object):
    def __init__(self):
        # Serial port to publish motor control signals to
        # Lower boud rate to publish motor commands might be appropriate
        self.ser = serial.Serial('com1', 57600)

    def up(self, deg):
        print("Tilt up by %3.1f degrees." % deg[0])
        command = '{}'.format(deg[0])
        print(command)
        self.ser.write(command.encode())

    def down(self, deg):
        print("Tilt down by %3.1f degrees." % deg[0])
        command = '{}'.format(deg[0])
        print(command)
        self.ser.write(command.encode())

    def left(self, deg):
        print("Pan left by %3.1f degrees." % deg[0])
        command = '{}'.format(deg[0])
        print(command)
        self.ser.write(command.encode())

    def right(self, deg):
        print("Pan right by %3.1f degrees." % deg[0])
        command = '{}'.format(deg[0])
        print(command)
        self.ser.write(command.encode())

    def quit(self):
        print('Shutting down node \'r_console\'...')
        #raise SystemExit()



# Frontend
class Shell(cmd.Cmd, object):
    def __init__(self):
        super(Shell, self).__init__()
        self.prompt = '(panTilt) $ '
        self.intro = 'Welcome to the Pan&Tilt-Shell. Enter \'help\' or \'?\' to list commands.\n'
        self.file = None # Later for waypoint files...
        self.interface = Interface()

    # Basic commands:
    def do_up(self, arg):
        'Tilt up by the specified angle [degree]: \'up 10\''
        self.interface.up(parse(arg))

    def do_down(self, arg):
        'Tilt down by the specified angle [degree]: \'down 10\''
        self.interface.down(parse(arg))

    def do_left(self, arg):
        'Pan left by the specified angle [degree]: \'left 45\''
        self.interface.left(parse(arg))

    def do_right(self, arg):
        'Pan right by the specified angle [degree]: \'right 45\''
        self.interface.right(parse(arg))

    def do_quit(self, arg):
        'Quit shell and shutdown node.'
        quit()
        raise SystemExit()



if __name__=='__main__':
    Shell().cmdloop()




