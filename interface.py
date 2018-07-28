#!/usr/bin/env python

#################################################################################
#
#	Subscribes to twist topic and publishes them via serial port to the MCU
#
#################################################################################

import rospy
from std_msgs.msg import String
from robbie_msgs.msg import command
import serial

SERIAL_PORT = '/dev/ttyACM0'





class Controller:
	def __init__(self):
		rospy.init_node('motor_interface', anonymous=True)
		# Subscribe to commands from command node:
		subscriber = rospy.Subscriber('/command', command, self.motor_command)
		# Serial port to publish motor control signals to
		# Lower boud rate to publish motor commands might be appropriate
		#self.ser = serial.Serial('/dev/ttyACM0', 115200)
		rospy.spin()

	def motor_command(self, cmd_msg):
		duration = cmd_msg.duration
		rpm_left = cmd_msg.rpm_left
		rpm_right = cmd_msg.rpm_right

		print("%3.5f, %d, %d" % (duration, rpm_left, rpm_right))
		#command = '{},{},{}'.format(duration, rpm_left, rpm_right)
		#self.ser.write(command)


	"""
	def publisher():
		pub = rospy.Publisher('topic_name', std_msgs.msg.String, queue_size=3)
		pub.publish(std_msgs.msg.String('foo'))
		r = rospy.Rate(10)
		while not rospy.is_shotdown():
			r.sleep()
	"""


if __name__ == '__main__':
	print("Starting Motor Interface node...")
	#try:
	c = Controller()
	#except rospy.ROSInterruptException:
	#	pass
