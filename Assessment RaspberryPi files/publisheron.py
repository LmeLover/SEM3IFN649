import paho.mqtt.publish as publish
import time
import string
import serial

# MQTT broker address and port
broker_address = "3.27.149.9"  # Replace with your MQTT broker's address
port = 1883  # Default MQTT port

# Topic to which you want to publish the message
topic = "ifn649"  # Replace with the desired MQTT topic

ser = serial.Serial("/dev/rfcomm0", 9600)
ser.write(str.encode('Start\r\n'))

while True:
	if ser.in_waiting > 0:
			rawserial = ser.readline()
			cookedserial = rawserial.decode('utf-8').strip('\r\n')
			print(cookedserial)
			publish.single(topic, cookedserial, hostname=broker_address, port=port)
