# -*- coding: utf-8 -*- 
	
import serial
import datetime
import re
import json
import time
import urllib2
from printhelp import ok, fail, inColor, writeflush
import config

ports = [
	# Arduino Diecimila on Linux
	'/dev/ttyUSB0',

	# Arduino Uno on Linux
	'/dev/ttyACM0'
]

delay = 10
arduinoDataObject = {}
debug = True

def getserial(ports):
	for port in ports:
		try:
			ser = serial.Serial(port, 9600, timeout=2)
			print 'Using %s for Arduino port' % port
			ser.setDTR(True)

			# Allow Arduino some time since it might reset
			time.sleep(3)
			return ser
		except serial.SerialException as e:
			dummy = False

	print 'No port found, is the Arduino connected?'
	exit()

def readFromArduino(ser):
	writeflush('Reading data from Arduino...')
	buffer = ""

	while buffer.count('{') < 1:
		line = ser.readline()
		buffer += line

	buffer = buffer.strip('\n').strip('\r').replace('\'', '"')

	try:
		arduinoDataObject = json.loads(buffer)
	except ValueError as e:
		print fail()
		return False

	if 'id' in arduinoDataObject:
		print ok()
		return arduinoDataObject

	print fail()
	return False


def sendDataToArduino(ser, data):
	writeflush('Sending data to Arduino...')
	ser.write(data)
	print ok()

def publishData(data):
	writeflush('Publishing data to web...')
	handler = urllib2.urlopen('%s/setstat/temp/%s/mode/%s/output/%s/outputRes/%s' % (config.url, data['temp'], data['mode'], data['output'], data['outputRes']))

	if handler.getcode() == 200:
		print ok()
		return True

	print fail()
	return False

def getSettingsFromWeb():
	writeflush('Fetching settings from web...')
	handler = urllib2.urlopen('%s/getsettings' % config.url)

	if handler.getcode() == 200:
		print ok()
		return handler.read()
	
	print fail()
	return False

def main(ser):
	now = datetime.datetime.now()

	# Get settings from web
	settings = getSettingsFromWeb()
	settingsObject = json.loads(settings)

	# Send settings to Arduino
	sendDataToArduino(ser, b'{mode:"%s"}' % settingsObject['mode'])

	# Get data from Arduino
	arduinoDataObject = readFromArduino(ser)

	# Publish data from Arduino to web
	if(arduinoDataObject):
		if debug:
			print arduinoDataObject
		
		publishData(arduinoDataObject)


ser = getserial(ports)
print 'Using %s for url' % config.url
main(ser)


