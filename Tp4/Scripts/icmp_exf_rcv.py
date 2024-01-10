from scapy.all import *

def printMessage(packet):
    if packet[ICMP].type == 8 and len(packet.load) == 1:
        print(packet.load.decode('utf-8'))

sniff(filter="icmp", prn=printMessage, count=1)
