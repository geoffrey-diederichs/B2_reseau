from scapy.all import *

request = IP(dst="8.8.8.8") / UDP() / DNS(rd=1, qd=DNSQR(qname="ynov.com"))
answer = sr1(request, verbose=0)

if DNSRR in answer:
    for i in range(0, answer.ancount):
        print(answer.an[i].rdata, end=" ; ")
    print()
