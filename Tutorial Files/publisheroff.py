import paho.mqtt.publish as publish

publish.single("ifn649","LED_OFF",hostname="3.27.156.48")
print("Done, LED is OFF")
