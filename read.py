# -*- coding: utf-8 -*- 
	
import MySQLdb
import serial
import datetime
import re

ports = [
	# Arduino Diecimila
	'/dev/ttyUSB0',

	# Arduino Uno
	'/dev/ttyACM0'
]


def getserial(ports):
	for port in ports:
		try:
			ser = serial.Serial(port, 9600, timeout=2)
			ser.setDTR(True)
			return ser
		except SerialException:
			print 'Kan inte öppna %s' % port

	print 'Hittade ingen port, är Arduinon ansluten?'
	exit()


def insert(now, data, l):
	try:
		db = MySQLdb.connect(host = "localhost", user = "arduino", passwd = "arduino", db = "arduino")
	except Exception:
		print 'Kunde inte ansluta till databas'
		exit()

	cursor = db.cursor()
	cursor.execute("INSERT INTO log(date, data, time, output, ref, R, T, lastInput, lastError, lastOutput, p, i, d) VALUES(%s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s)", (now, data, l[0], l[1], l[2], l[3], l[4], l[5], l[6], l[7], l[8], l[9], l[10]))
	db.commit()
	db.close()


def main(ports):

	ser = getserial(ports)

	now = datetime.datetime.now()

	buffer = bytes()

	while buffer.count('<log>') < 1:
		buffer += ser.readline()
	    
	# data = ser.readline()

	string = buffer.strip('\x00\n\s').strip().translate(None, ' ');

	# Create Reg Exp
	match = re.search(r'(<log>)(.*)(</log>)', string)

	# Exit if we don't have good measure data
	if not (match):
		exit()

	# Remove the trailing ';' before split()
	data = match.group(2).rstrip(';');

	# Create list from data string
	l = data.split(';')

	insert(now, data, l)


main(ports)