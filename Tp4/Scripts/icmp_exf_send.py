from scapy.all import *

if len(sys.argv) < 3:
    print("No arguments")
    exit()

target = sys.argv[1]
data = sys.argv[2]

if len(data) > 1:
    print("Only 1 character")
    exit()

packet = IP(dst=target)/ICMP()/str(data)
send(packet)
