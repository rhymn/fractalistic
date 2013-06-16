# -*- coding: utf-8 -*- 
	
import MySQLdb
import serial
import datetime
import re

db = MySQLdb.connect(host = "localhost", user = "arduino", passwd = "arduino", db = "arduino")

# Arduino Diecimila
# port = '/dev/ttyUSB0'

# Arduino Uno
port = '/dev/ttyACM0'

cursor = db.cursor()
now = datetime.datetime.now()

buffer = bytes()

try:
	ser = serial.Serial(port, 9600, timeout=2)
	ser.setDTR(True)
except Exception:
	print 'Kan inte öppna '+port+', är Arduinon ansluten? Avslutar...'
	exit()
	

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

cursor.execute("INSERT INTO log(date, data, time, output, ref, R, T, lastInput, lastError, lastOutput, p, i, d) VALUES(%s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s)", (now, data, l[0], l[1], l[2], l[3], l[4], l[5], l[6], l[7], l[8], l[9], l[10]))

db.commit()

db.close()
