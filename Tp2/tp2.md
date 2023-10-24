DIEDERICHS Geoffrey B2A

# TP2 : Environnement virtuel

- [0. Prérequis](#0-prérequis)
- [I. Topologie réseau](#i-topologie-réseau)
- [II. Interlude accès internet](#ii-interlude-accès-internet)
- [III. Services réseau](#iii-services-réseau)

# 0. Prérequis

Lan 1 (192.168.56.0/24) :

```sh
[rocky@node1 ~]$ cat /etc/sysconfig/network-scripts/ifcfg-enp0s8 
NAME=enp0s8
DEVICE=enp0s8

BOOTPROTO=static
ONBOOT=yes

IPADDR=192.168.56.11
NETMASK=255.255.255.0

GATEWAY=192.168.56.1
DNS1=1.1.1.1

[rocky@node1 ~]$ ip a
1: lo: <LOOPBACK,UP,LOWER_UP> mtu 65536 qdisc noqueue state UNKNOWN group default qlen 1000
    link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00
    inet 127.0.0.1/8 scope host lo
       valid_lft forever preferred_lft forever
    inet6 ::1/128 scope host 
       valid_lft forever preferred_lft forever
2: enp0s8: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc fq_codel state UP group default qlen 1000
    link/ether 08:00:27:f3:98:99 brd ff:ff:ff:ff:ff:ff
    inet 192.168.56.11/24 brd 192.168.56.255 scope global noprefixroute enp0s8
       valid_lft forever preferred_lft forever
    inet6 fe80::a00:27ff:fef3:9899/64 scope link 
       valid_lft forever preferred_lft forever

[rocky@node1 ~]$ systemctl is-active sshd
active

[rocky@node1 ~]$ systemctl is-active firewalld
active

[rocky@node1 ~]$ sestatus
SELinux status:                 disabled

[rocky@node1 ~]$ hostname
nod1.lan1.tp2

[rocky@node1 ~]$ cat /etc/hosts | tail -n 4
192.168.56.12 node2.lan1.tp2
192.168.57.11 node1.lan2.tp2
192.168.57.12 node2.lan2.tp2
192.168.56.254 routeur.tp2
```

```sh
[rocky@node2 ~]$ cat /etc/sysconfig/network-scripts/ifcfg-enp0s8 
NAME=enp0s8
DEVICE=enp0s8

BOOTPROTO=static
ONBOOT=yes

IPADDR=192.168.56.12
NETMASK=255.255.255.0

GATEWAY=192.168.56.1
DNS1=1.1.1.1

[rocky@node2 ~]$ ip a
1: lo: <LOOPBACK,UP,LOWER_UP> mtu 65536 qdisc noqueue state UNKNOWN group default qlen 1000
    link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00
    inet 127.0.0.1/8 scope host lo
       valid_lft forever preferred_lft forever
    inet6 ::1/128 scope host 
       valid_lft forever preferred_lft forever
2: enp0s8: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc fq_codel state UP group default qlen 1000
    link/ether 08:00:27:a8:0f:50 brd ff:ff:ff:ff:ff:ff
    inet 192.168.56.12/24 brd 192.168.56.255 scope global noprefixroute enp0s8
       valid_lft forever preferred_lft forever
    inet6 fe80::a00:27ff:fea8:f50/64 scope link 
       valid_lft forever preferred_lft forever

[rocky@node2 ~]$ systemctl is-active sshd
active

[rocky@node2 ~]$ systemctl is-active firewalld
active

[rocky@node2 ~]$ sestatus
SELinux status:                 disabled

[rocky@node2 ~]$ hostname
node2.lan1.tp2

[rocky@node2 ~]$ cat /etc/hosts | tail -n 4
192.168.56.11 node1.lan1.tp2
192.168.57.11 node1.lan2.tp2
192.168.57.12 node2.lan2.tp2
192.168.56.254 routeur.tp2
```

Lan 2 (192.168.57.0/24) :

```sh
[rocky@node1 ~]$ cat /etc/sysconfig/network-scripts/ifcfg-enp0s8
NAME=enp0s8
DEVICE=enp0s8

BOOTPROTO=static
ONBOOT=yes

IPADDR=192.168.57.11
NETMASK=255.255.255.0

GATEWAY=192.168.57.1
DNS1=1.1.1.1

[rocky@node1 ~]$ ip a
1: lo: <LOOPBACK,UP,LOWER_UP> mtu 65536 qdisc noqueue state UNKNOWN group default qlen 1000
    link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00
    inet 127.0.0.1/8 scope host lo
       valid_lft forever preferred_lft forever
    inet6 ::1/128 scope host 
       valid_lft forever preferred_lft forever
2: enp0s8: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc fq_codel state UP group default qlen 1000
    link/ether 08:00:27:f5:0a:55 brd ff:ff:ff:ff:ff:ff
    inet 192.168.57.11/24 brd 192.168.57.255 scope global noprefixroute enp0s8
       valid_lft forever preferred_lft forever
    inet6 fe80::a00:27ff:fef5:a55/64 scope link 
       valid_lft forever preferred_lft forever

[rocky@node1 ~]$ systemctl is-active sshd
active

[rocky@node1 ~]$ systemctl is-active firewalld
active

[rocky@node1 ~]$ sestatus
SELinux status:                 disabled

[rocky@node1 ~]$ hostname
node1.lan2.tp2

[rocky@node1 ~]$ cat /etc/hosts | tail -n 4
192.168.56.11 node1.lan1.tp2
192.168.56.12 node2.lan1.tp2
192.168.57.12 node2.lan2.tp2
192.168.57.254 routeur.tp2
```

```sh
[rocky@node2 ~]$ cat /etc/sysconfig/network-scripts/ifcfg-enp0s8 
NAME=enp0s8
DEVICE=enp0s8

BOOTPROTO=static
ONBOOT=yes

IPADDR=192.168.57.12
NETMASK=255.255.255.0

GATEWAY=192.168.57.1
DNS1=1.1.1.1

[rocky@node2 ~]$ ip a
1: lo: <LOOPBACK,UP,LOWER_UP> mtu 65536 qdisc noqueue state UNKNOWN group default qlen 1000
    link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00
    inet 127.0.0.1/8 scope host lo
       valid_lft forever preferred_lft forever
    inet6 ::1/128 scope host 
       valid_lft forever preferred_lft forever
2: enp0s8: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc fq_codel state UP group default qlen 1000
    link/ether 08:00:27:27:f9:78 brd ff:ff:ff:ff:ff:ff
    inet 192.168.57.12/24 brd 192.168.57.255 scope global noprefixroute enp0s8
       valid_lft forever preferred_lft forever
    inet6 fe80::a00:27ff:fe27:f978/64 scope link 
       valid_lft forever preferred_lft forever

[rocky@node2 ~]$ systemctl is-active sshd
active

[rocky@node2 ~]$ systemctl is-active firewalld
active

[rocky@node2 ~]$ sestatus
SELinux status:                 disabled

[rocky@node2 ~]$ hostname
node2.lan2.tp2

[rocky@node2 ~]$ cat /etc/hosts | tail -n 4
192.168.56.11 node1.lan1.tp2
192.168.56.12 node2.lan1.tp2
192.168.57.11 node1.lan2.tp2
192.168.57.254 routeur.tp2
```

Routeur :

```sh
[rocky@routeur ~]$ cat /etc/sysconfig/network-scripts/ifcfg-enp0s8
NAME=enp0s8
DEVICE=enp0s8

BOOTPROTO=static
ONBOOT=yes

IPADDR=192.168.56.254
NETMASK=255.255.255.0

GATEWAY=192.168.56.1
DNS1=1.1.1.1

[rocky@routeur ~]$ cat /etc/sysconfig/network-scripts/ifcfg-enp0s9
NAME=enp0s9
DEVICE=enp0s9

BOOTPROTO=static
ONBOOT=yes

IPADDR=192.168.57.254
NETMASK=255.255.255.0

GATEWAY=192.168.57.1
DNS1=1.1.1.1

[rocky@routeur ~]$ ip a
1: lo: <LOOPBACK,UP,LOWER_UP> mtu 65536 qdisc noqueue state UNKNOWN group default qlen 1000
    link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00
    inet 127.0.0.1/8 scope host lo
       valid_lft forever preferred_lft forever
    inet6 ::1/128 scope host 
       valid_lft forever preferred_lft forever
2: enp0s8: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc fq_codel state UP group default qlen 1000
    link/ether 08:00:27:b7:4f:88 brd ff:ff:ff:ff:ff:ff
    inet 192.168.56.254/24 brd 192.168.56.255 scope global noprefixroute enp0s8
       valid_lft forever preferred_lft forever
    inet6 fe80::a00:27ff:feb7:4f88/64 scope link 
       valid_lft forever preferred_lft forever
3: enp0s9: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc fq_codel state UP group default qlen 1000
    link/ether 08:00:27:9a:d7:c4 brd ff:ff:ff:ff:ff:ff
    inet 192.168.57.254/24 brd 192.168.57.255 scope global noprefixroute enp0s9
       valid_lft forever preferred_lft forever
    inet6 fe80::a00:27ff:fe9a:d7c4/64 scope link 
       valid_lft forever preferred_lft forever

[rocky@routeur ~]$ systemctl is-active sshd
active

[rocky@routeur ~]$ systemctl is-active firewalld
active

[rocky@routeur ~]$ sestatus
SELinux status:                 disabled

[rocky@routeur ~]$ hostname
routeur.tp2

[rocky@routeur ~]$ cat /etc/hosts | tail -n 4
192.168.56.11 node1.lan1.tp2
192.168.56.12 node2.lan1.tp2
192.168.57.11 node1.lan2.tp2
192.168.57.12 node2.lan2.tp2
```

# I. Topologie réseau

## Configuration

Routeur :

```sh
[rocky@routeur ~]$ sudo firewall-cmd --add-masquerade --permanent
success

[rocky@routeur ~]$ sudo sysctl -w net.ipv4.ip_forward=1
net.ipv4.ip_forward = 1
```

Lan 1 (192.168.56.0) :

```sh
[rocky@node1 ~]$ cat /etc/sysconfig/network-scripts/route-enp0s8 
192.168.57.0/24 via 192.168.56.254 dev enp0s8
```

```sh
[rocky@node2 ~]$ cat /etc/sysconfig/network-scripts/route-enp0s8
192.168.57.0/24 via 192.168.56.254 dev enp0s8
```

Lan 2 (192.168.57.0) :

```sh
[rocky@node1 ~]$ cat /etc/sysconfig/network-scripts/route-enp0s8 
192.168.56.0/24 via 192.168.57.254 dev enp0s8
```

```sh
[rocky@node2 ~]$ cat /etc/sysconfig/network-scripts/route-enp0s8 
192.168.56.0/24 via 192.168.57.254 dev enp0s8
```

## Compte-rendu

Sur node1.lan1.tp2 :

```sh
[rocky@node1 ~]$ ip a
1: lo: <LOOPBACK,UP,LOWER_UP> mtu 65536 qdisc noqueue state UNKNOWN group default qlen 1000
    link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00
    inet 127.0.0.1/8 scope host lo
       valid_lft forever preferred_lft forever
    inet6 ::1/128 scope host 
       valid_lft forever preferred_lft forever
2: enp0s8: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc fq_codel state UP group default qlen 1000
    link/ether 08:00:27:f3:98:99 brd ff:ff:ff:ff:ff:ff
    inet 192.168.56.11/24 brd 192.168.56.255 scope global noprefixroute enp0s8
       valid_lft forever preferred_lft forever
    inet6 fe80::a00:27ff:fef3:9899/64 scope link 
       valid_lft forever preferred_lft forever

[rocky@node1 ~]$ ping node2.lan2.tp2 -c 1
PING node2.lan2.tp2 (192.168.57.12) 56(84) bytes of data.
64 bytes from node2.lan2.tp2 (192.168.57.12): icmp_seq=1 ttl=63 time=0.673 ms

--- node2.lan2.tp2 ping statistics ---
1 packets transmitted, 1 received, 0% packet loss, time 0ms
rtt min/avg/max/mdev = 0.673/0.673/0.673/0.000 ms

[rocky@node1 ~]$ traceroute node2.lan2.tp2
traceroute to node2.lan2.tp2 (192.168.57.12), 30 hops max, 60 byte packets
 1  routeur.tp2 (192.168.56.254)  1.556 ms  1.422 ms  1.338 ms
 2  node2.lan2.tp2 (192.168.57.12)  1.160 ms !X  1.131 ms !X  1.063 ms !X
```

# II. Interlude accès internet

☀️ **Sur `router.tp2`**

```sh
[rocky@routeur ~]$ ping 1.1.1.1 -c 1
PING 1.1.1.1 (1.1.1.1) 56(84) bytes of data.
64 bytes from 1.1.1.1: icmp_seq=1 ttl=63 time=13.0 ms

--- 1.1.1.1 ping statistics ---
1 packets transmitted, 1 received, 0% packet loss, time 0ms
rtt min/avg/max/mdev = 13.048/13.048/13.048/0.000 ms

[rocky@routeur ~]$ ping google.com -c 1
PING google.com (172.217.20.174) 56(84) bytes of data.
64 bytes from par10s49-in-f14.1e100.net (172.217.20.174): icmp_seq=1 ttl=63 time=17.4 ms

--- google.com ping statistics ---
1 packets transmitted, 1 received, 0% packet loss, time 0ms
rtt min/avg/max/mdev = 17.402/17.402/17.402/0.000 ms
```

☀️ **Accès internet LAN1 et LAN2**

node2.lan1.tp2 :

```sh
[rocky@node2 ~]$ cat /etc/sysconfig/network-scripts/route-enp0s8 | tail -n 1
default via 192.168.56.254 dev enp0s8

[rocky@node2 ~]$ cat /etc/sysconfig/network-scripts/ifcfg-enp0s8 | grep DNS
DNS1=1.1.1.1

[rocky@node2 ~]$ ping 1.1.1.1 -c 1
PING 1.1.1.1 (1.1.1.1) 56(84) bytes of data.
64 bytes from 1.1.1.1: icmp_seq=1 ttl=61 time=15.9 ms

--- 1.1.1.1 ping statistics ---
1 packets transmitted, 1 received, 0% packet loss, time 0ms
rtt min/avg/max/mdev = 15.861/15.861/15.861/0.000 ms

[rocky@node2 ~]$ ping google.com -c 1
PING google.com (142.250.179.110) 56(84) bytes of data.
64 bytes from par21s20-in-f14.1e100.net (142.250.179.110): icmp_seq=1 ttl=61 time=17.9 ms

--- google.com ping statistics ---
1 packets transmitted, 1 received, 0% packet loss, time 0ms
rtt min/avg/max/mdev = 17.853/17.853/17.853/0.000 ms
```

# III. Services réseau

## 1. DHCP

☀️ **Sur `dhcp.lan1.tp2`**

```sh
[rocky@dhcp ~]$ hostname
dhcp.lan1.tp2

[rocky@dhcp ~]$ ip a | grep 'scope global'
    inet 192.168.56.253/24 brd 192.168.56.255 scope global noprefixroute enp0s8

[rocky@dhcp ~]$ sudo dnf install -y dhcp-server
Last metadata expiration check: 4:44:18 ago on Tue 24 Oct 2023 10:38:12 AM CEST.
Package dhcp-server-12:4.4.2-18.b1.el9.x86_64 is already installed.
Dependencies resolved.
Nothing to do.
Complete!

[rocky@dhcp ~]$ sudo cat /etc/dhcp/dhcpd.conf
default-lease-time 600;
max-lease-time 7200;
authoritative;
subnet 192.168.56.0 netmask 255.255.255.0 {
	range dynamic-bootp 192.168.56.2 192.168.56.252;
	option broadcast-address 192.168.56.255;
	option routers 192.168.56.254;
}

[rocky@dhcp ~]$ sudo systemctl enable --now dhcpd

[rocky@dhcp ~]$ systemctl is-active dhcpd
active

[rocky@dhcp ~]$ sudo firewall-cmd --add-service=dhcp
success

[rocky@dhcp ~]$ sudo firewall-cmd --runtime-to-permanent
success
```

☀️ **Sur `node1.lan1.tp2`**

```sh
[rocky@node1 ~]$ cat /etc/sysconfig/network-scripts/ifcfg-enp0s8 
NAME=enp0s8
DEVICE=enp0s8

BOOTPROTO=dhcp
ONBOOT=yes

[rocky@node1 ~]$ sudo dhclient -v enp0s8
Internet Systems Consortium DHCP Client 4.4.2b1
Copyright 2004-2019 Internet Systems Consortium.
All rights reserved.
For info, please visit https://www.isc.org/software/dhcp/

Listening on LPF/enp0s8/08:00:27:f3:98:99
Sending on   LPF/enp0s8/08:00:27:f3:98:99
Sending on   Socket/fallback
DHCPREQUEST for 192.168.56.3 on enp0s8 to 255.255.255.255 port 67 (xid=0x9d68736c)
DHCPACK of 192.168.56.3 from 192.168.56.253 (xid=0x9d68736c)
bound to 192.168.56.3 -- renewal in 229 seconds.

[rocky@node1 ~]$ ip r s | head -n 1
default via 192.168.56.254 dev enp0s8 

[rocky@node1 ~]$ ping node1.lan2.tp2 -c 1
PING node1.lan2.tp2 (192.168.57.11) 56(84) bytes of data.
64 bytes from node1.lan2.tp2 (192.168.57.11): icmp_seq=1 ttl=63 time=0.896 ms

--- node1.lan2.tp2 ping statistics ---
1 packets transmitted, 1 received, 0% packet loss, time 0ms
rtt min/avg/max/mdev = 0.896/0.896/0.896/0.000 ms
```

## 2. Web web web

☀️ **Sur `web.lan2.tp2`**

```sh
[rocky@web ~]$ hostname
web.lan2.tp2

[rocky@web ~]$ sudo dnf install -y nginx
Last metadata expiration check: 5:38:24 ago on Tue 24 Oct 2023 10:38:12 AM CEST.
Package nginx-1:1.20.1-14.el9_2.1.x86_64 is already installed.
Dependencies resolved.
Nothing to do.
Complete!

[rocky@web ratio]$ cat /var/www/ratio/index.html 
ratio

[rocky@web ratio]$ cat /etc/nginx/nginx.conf
[...]
    server {
        listen       80;
        listen       [::]:80;
        server_name  _;
        root         /var/www/ratio/;
[...]

[rocky@web ~]$ sudo systemctl enable nginx
Created symlink /etc/systemd/system/multi-user.target.wants/nginx.service → /usr/lib/systemd/system/nginx.service.

[rocky@web ratio]$ sudo systemctl start nginx

[rocky@web ratio]$ sudo systemctl is-active nginx
active

[rocky@web ratio]$ sudo firewall-cmd --permanent --add-service=http
success

[rocky@web ratio]$ sudo firewall-cmd --reload
success

[rocky@web ratio]$ curl localhost:80
ratio

[rocky@web ratio]$ sudo firewall-cmd --list-all
public (active)
  target: default
  icmp-block-inversion: no
  interfaces: enp0s8
  sources: 
  services: cockpit dhcpv6-client http ssh
  ports: 
  protocols: 
  forward: yes
  masquerade: no
  forward-ports: 
  source-ports: 
  icmp-blocks: 
  rich rules:

[rocky@web ratio]$ sudo ss -altp | grep nginx
LISTEN 0      511          0.0.0.0:http      0.0.0.0:*    users:(("nginx",pid=1538,fd=6),("nginx",pid=1537,fd=6))
LISTEN 0      511             [::]:http         [::]:*    users:(("nginx",pid=1538,fd=7),("nginx",pid=1537,fd=7))
```

http étant le port 80.

☀️ **Sur `node1.lan1.tp2`**

```sh
[rocky@node1 ~]$ cat /etc/hosts | tail -n 1
192.168.57.12 web.lan2.tp2

[rocky@node1 ~]$ curl web.lan2.tp2
ratio
```
