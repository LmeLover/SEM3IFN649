import paho.mqtt.client as mqtt
import serial
import time

# Define callback function for when the client connects to the broker
def on_connect(client, userdata, flags, rc):
    if rc == 0:
        print("Connected to MQTT broker")
        client.subscribe("ifn649_mode")  # Subscribe to the desired MQTT topic
    else:
        print("Connection failed with code:", rc)

# Define callback function for when a message is received from the broker
def on_message(client, userdata, msg):
    print(f"Received message on topic {msg.topic}: {msg.payload.decode('utf-8')}")
    ser = serial.Serial("/dev/rfcomm0", 9600)
    message_to_send = msg.payload.decode('utf-8') + '\n'
    ser.write(message_to_send.encode())

# Create an MQTT client instance
client = mqtt.Client()

# Set the callback functions
client.on_connect = on_connect
client.on_message = on_message

# Set the MQTT broker address and port
broker_address = "3.27.149.9"  # Replace with your MQTT broker's address
port = 1883  # Default MQTT port

# Connect to the MQTT broker
client.connect(broker_address, port, 60)

# Start the MQTT loop to handle incoming messages
client.loop_forever()
