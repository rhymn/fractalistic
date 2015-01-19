# -*- coding: utf-8 -*-
import sys

colors = {
	'green' : '\033[92m',
	'red' : '\033[91m',
	'end' : '\033[0m'
}

def ok():
	return inColor('green', 'yes')

def fail():
	return inColor('red', 'no')

def inColor(color, text):

	if(color in colors):
		return colors[color] + text + colors['end']

	else:
		return text

def writeflush(str):
	sys.stdout.write( str )
	sys.stdout.flush()
