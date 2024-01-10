from scapy.all import *

ping = ICMP(type=8)
packet = IP(src="192.168.56.5", dst="192.168.56.1")
frame = packet/ping

answers, unanswered_packets = sr(frame, timeout=10)

print("Answers :")
for i in answers:
    print(" - " + str(i))
