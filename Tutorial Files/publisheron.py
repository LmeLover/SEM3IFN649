import paho.mqtt.publish as publish

publish.single("ifn649","LED_ON",hostname="3.27.156.48")
print("Done, LED is ON.")
