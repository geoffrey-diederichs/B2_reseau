from scapy.all import *

def printResult(packet):
    if DNSRR in packet:
        for i in range(0, packet.ancount):
            print(packet.an[i].rdata, end=" ; ")
        print()

sniff(filter="udp and port 53", prn=printResult)
