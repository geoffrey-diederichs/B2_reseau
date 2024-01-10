from scapy.all import *

def printResult(packet):
    print("TCP SYN ACK reçu !\n- Adresse IP src : ", packet[IP].src, "\n- Adresse IP dst : ", packet[IP].dst, "\n- Port TCP src : ", packet[TCP].sport, "\n- Port TCP dst : ", packet[TCP].dport, sep="", end="\n")

sniff(filter="tcp[tcpflags] & (tcp-syn|tcp-ack) == tcp-syn|tcp-ack", prn=printResult, count=1)
