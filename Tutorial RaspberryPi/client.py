import paho.mqtt.client as mqtt
import time
import serial



def on_connect(client, userdata, flags, rc): # func for making connection
	print(f"Connected to MQTT Server {ADD} at port {PORT}")
	print("Connection returned result: " +str(rc))
	topic = "ifn649"
	client.subscribe("ifn649")
	print(f"Subscribed to topic: {topic} ")

def on_message(client, userdata, msg): 	#Func For Sending msg
	print(msg.topic+" "+str(msg.payload))
	print("relaying to teensy over BT...")
	
	#ser = serial.Serial("/dev/rfcomm1", 9600)
	#ser.write(msg.payload)
	
ADD = "3.27.149.9"
PORT = 1883
client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message
client.connect(ADD, PORT, 60)

client.loop_forever()
