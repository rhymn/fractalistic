# -*- coding: utf-8 -*- 
	
import serial
import datetime
import re
import json
import time
import urllib

ports = [
	# Arduino Diecimila
	'/dev/ttyUSB0',

	# Arduino Uno
	'/dev/ttyACM0'
]

arduinoDataObject = {}

def getserial(ports):
	for port in ports:
		try:
			ser = serial.Serial(port, 9600, timeout=2)
			print 'Använder port %s' % port
			ser.setDTR(True)
			return ser
		except serial.SerialException as e:
			dummy = False

	print 'Hittade ingen port, är Arduinon ansluten?'
	exit()

def readFromArduino(ser):
	buffer = ""

	while buffer.count('{') < 1:
		buffer += ser.readline()

	buffer = buffer.strip('\n').strip('\r').replace('\'', '"')

	print buffer

	try:
		arduinoDataObject = json.loads(buffer)
		return arduinoDataObject
	except ValueError as e:
		return False

def sendDataToArduino(data):
	ser.write(b'{mode:"%s"}' % data['mode'])

def publishData(data):
	response = urllib.urlopen('http://r.pnd.se/setstat/temp/%s/mode/%s/output/%s/outputRes/%s' % (data['temp'], data['mode'], data['output'], data['outputRes'])).read()
	print response

def main(ser):
	while 1:
		now = datetime.datetime.now()

		# Get settings from web
		settings = urllib.urlopen('http://r.pnd.se/getsettings').read()
		settingsObject = json.loads(settings)

		# Get data from Arduino
		arduinoDataObject = readFromArduino(ser)

		# Send settings to Arduino
		sendDataToArduino(settingsObject)

		# Publicate data from Arduino to web
		if(arduinoDataObject):
			publishData(arduinoDataObject)

		time.sleep(10)

ser = getserial(ports)
main(ser)