DIEDERICHS Geoffrey B2A

# TP1 : Maîtrise réseau du poste

- [I. Basics](#i-basics)
- [II. Go further](#ii-go-further)
- [III. Le requin](#iii-le-requin)

# I. Basics

☀️ **Carte réseau WiFi**

```sh
$ ip a | head -14 | tail -6
3: wlp4s0: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc noqueue state UP group default qlen 1000
    link/ether d8:f3:bc:54:c7:8f brd ff:ff:ff:ff:ff:ff
    inet 10.33.76.225/20 brd 10.33.79.255 scope global dynamic noprefixroute wlp4s0
       valid_lft 79049sec preferred_lft 79049sec
    inet6 fe80::4864:7737:c0b3:b168/64 scope link noprefixroute 
       valid_lft forever preferred_lft forever
```

- MAC : d8:f3:bc:54:c7:8f 
- IPv4 : 10.33.76.225/20 
- IPv6 : fe80::4864:7737:c0b3:b168/64
- Masque de sous-réseau 
  - /20
  - 255.255.240.0.0

---

☀️ **Déso pas déso**

- Adresse de réseau : 10.33.64.0
- Broadcast : 10.33.79.255
- Adresses disponibles : 4 094

---

☀️ **Hostname**

```sh
$ hostname
geoffrey
```

---

☀️ **Passerelle du réseau**

```sh
$ ip n
10.33.79.254 dev wlp4s0 lladdr 7c:5a:1c:d3:d8:76 REACHABLE 
```

- IP de la passerelle : 10.33.79.254
- MAC de la passerelle : 7c:5a:1c:d3:d8:76  

---

☀️ **Serveur DHCP et DNS**

```sh
$ sudo /sbin/dhclient -v
Internet Systems Consortium DHCP Client 4.4.3-P1
Copyright 2004-2022 Internet Systems Consortium.
All rights reserved.
For info, please visit https://www.isc.org/software/dhcp/

Listening on LPF/vboxnet0/0a:00:27:00:00:00
Sending on   LPF/vboxnet0/0a:00:27:00:00:00
Listening on LPF/docker0/02:42:5c:3d:ec:9e
Sending on   LPF/docker0/02:42:5c:3d:ec:9e
Listening on LPF/wlp4s0/d8:f3:bc:54:c7:8f
Sending on   LPF/wlp4s0/d8:f3:bc:54:c7:8f
Listening on LPF/enp3s0/c0:18:50:0e:cb:bb
Sending on   LPF/enp3s0/c0:18:50:0e:cb:bb
Sending on   Socket/fallback
DHCPDISCOVER on vboxnet0 to 255.255.255.255 port 67 interval 4
DHCPDISCOVER on docker0 to 255.255.255.255 port 67 interval 4
DHCPREQUEST for 10.33.65.248 on wlp4s0 to 255.255.255.255 port 67
DHCPDISCOVER on enp3s0 to 255.255.255.255 port 67 interval 3
DHCPACK of 10.33.65.248 from 10.33.79.254
RTNETLINK answers: File exists
bound to 10.33.65.248 -- renewal in 36031 seconds.

$ nmcli device show wlp4s0 | grep IP4.DNS
IP4.DNS[1]:                             8.8.8.8
IP4.DNS[2]:                             1.1.1.1
```

- IP du serveur DHCP : 10.33.79.254
- IP du serveur DNS : 8.8.8.8 et 1.1.1.1
---

☀️ **Table de routage**

Route par défaut :

```sh
$ ip r s | head -2
default via 10.33.79.254 dev wlp4s0 
default via 10.33.79.254 dev wlp4s0 proto dhcp src 10.33.76.225 metric 600
```

# II. Go further

☀️ **Hosts ?**

```sh
$ sudo cat /etc/hosts | tail -2
# Pour tp
1.1.1.1 b2.hello.vous
$ ping b2.hello.vous -c 1
PING b2.hello.vous (1.1.1.1) 56(84) bytes of data.
64 bytes from b2.hello.vous (1.1.1.1): icmp_seq=1 ttl=57 time=13.0 ms

--- b2.hello.vous ping statistics ---
1 packets transmitted, 1 received, 0% packet loss, time 0ms
rtt min/avg/max/mdev = 13.001/13.001/13.001/0.000 ms
```

---

☀️ **Go mater une vidéo youtube et déterminer, pendant qu'elle tourne...**

- IP du serveur : 142.251.209.14
- Port serveur : 443
- Port pc : 38308

---

☀️ **Requêtes DNS**

```sh
$ dig ynov.com | grep ynov.com. | tail -3
ynov.com.		300	IN	A	104.26.10.233
ynov.com.		300	IN	A	104.26.11.233
ynov.com.		300	IN	A	172.67.74.226
```

```sh
$ nslookup 174.43.238.89 | grep name
89.238.43.174.in-addr.arpa	name = 89.sub-174-43-238.myvzw.com.
```

- IP de ynov.com : 104.26.10.233 ; 104.26.11.233 ; 172.67.74.226
- Nom de domaine de `174.43.238.89` : 89.sub-174-43-238.myvzw.com

---

☀️ **Hop hop hop**

```sh
$ traceroute ynov.com
traceroute to ynov.com (104.26.10.233), 30 hops max, 60 byte packets
 1  _gateway (10.33.79.254)  4.321 ms  4.200 ms  4.164 ms
 2  145.117.7.195.rev.sfr.net (195.7.117.145)  4.807 ms  4.772 ms  4.738 ms
 3  * * *
 4  196.224.65.86.rev.sfr.net (86.65.224.196)  4.601 ms  4.569 ms  4.535 ms
 5  12.148.6.194.rev.sfr.net (194.6.148.12)  12.720 ms 68.150.6.194.rev.sfr.net (194.6.150.68)  12.690 ms  12.657 ms
 6  68.150.6.194.rev.sfr.net (194.6.150.68)  12.621 ms 12.148.6.194.rev.sfr.net (194.6.148.12)  13.012 ms  12.906 ms
 7  141.101.67.48 (141.101.67.48)  12.861 ms  13.114 ms  12.818 ms
 8  172.71.124.4 (172.71.124.4)  12.774 ms  12.736 ms  12.702 ms
 9  104.26.10.233 (104.26.10.233)  12.657 ms  12.622 ms  12.719 ms
```

Les paquets passent par 9 machines pour atteindre ynov.com.

---

☀️ **IP publique**

```sh
$ curl ifconfig.me
195.7.117.146
```

---

☀️ **Scan réseau**

```sh
$ sudo nmap -sn 10.33.64.0/20
[...]
Host is up (0.051s latency).
MAC Address: 1A:E8:FA:7D:49:51 (Unknown)
Nmap scan report for 10.33.79.247
Host is up (0.071s latency).
MAC Address: EC:2E:98:CA:95:97 (AzureWave Technology)
Nmap scan report for 10.33.79.254
Host is up (0.0040s latency).
MAC Address: 7C:5A:1C:D3:D8:76 (Sophos)
Nmap scan report for 10.33.76.225
Host is up.
Nmap done: 4096 IP addresses (853 hosts up) scanned in 161.25 seconds
```

853 machines dans le LAN.

# III. Le requin

☀️ **Capture ARP**

```sh
$ sudo arping 10.33.79.254
```

Filtre : arp

[Capture ARP](./captures/arp.pcap)

---

☀️ **Capture DNS**

```sh
$ dig google.com
```

Filtre : dns

[Capture DNS](./captures/dns.pcap)

---

☀️ **Capture TCP**

Filtre : tcp

[Capture TCP](./captures/tcp.pcap)
