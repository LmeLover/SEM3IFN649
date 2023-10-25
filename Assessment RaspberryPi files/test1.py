import paho.mqtt.publish as publish

# MQTT broker address and port
broker_address = "3.27.149.9"  # Replace with your MQTT broker's address
port = 1883  # Default MQTT port

# Topic to which you want to publish the message
topic = "ifn649"  # Replace with the desired MQTT topic

# Message content
message = "Warning"

# Publish the message
publish.single(topic, message, hostname=broker_address, port=port)

print(f"Published message to topic '{topic}': {message}")
