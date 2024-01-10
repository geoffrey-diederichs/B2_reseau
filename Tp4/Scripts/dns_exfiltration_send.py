from scapy.all import *

def sendMessage(server, message):
    packet = IP(dst=server)/UDP(dport=53)/DNS(rd=1, qd=DNSQR(qname=message))
    send(packet)

if len(sys.argv) < 3:
    print("No arguments")
    exit()

server = sys.argv[1]
message = sys.argv[2]

i = 0
while (i*10 < len(message)):
    sendMessage(server, message[i*10: (i+1)*10])
    i += 1
