# TP6 : Un peu de root-me

## Sommaire

- [TP6 : Un peu de root-me](#tp6--un-peu-de-root-me)
  - [Sommaire](#sommaire)
  - [I. DNS Rebinding](#i-dns-rebinding)
  - [II. Netfilter erreurs courantes](#ii-netfilter-erreurs-courantes)
  - [III. ARP Spoofing Ecoute active](#iii-arp-spoofing-ecoute-active)
  - [IV. Bonus : Trafic Global System for Mobile communications](#iv-bonus--trafic-global-system-for-mobile-communications)

## I. DNS Rebinding

🌞 **Write-up de l'épreuve**

On utilise [ce site](https://lock.cmpxchg8b.com/rebinder.html) pour mettre en ligne un serveur DNS avec les paramètres :

- A : 127.0.0.1
- B : 8.8.8.8

On obtient l'url suivante : `7f000001.08080808.rbndr.us`.

En effectuant une requête sur le site du challenge ou trouve que l'url pour faire une requête est : `http://challenge01.root-me.org:54022/grab?url=7f000001.08080808.rbndr.us:54022/admin`.

Puis [ce script](./Scripts/dns.py) va envoyer des requêtes en boucles jusqu'à obtenir le code source de la page admin :

```bash
$ python3 netfilter.py           
b'\n        <html>\n            <head>\n                <title>Admin page</title>\n                <link rel="stylesheet" href="/static/bootstrap.min.css">\n            </head>\n            <body style="background:pink">\n                <br/>\n                <h1 class="d-flex justify-content-center">Well done!</h1>\n                <h3 class="d-flex justify-content-center">Have a cookie. Admins love cookies.</h1>\n                <h6 class="d-flex justify-content-center">Flag: [coucou toi le flag est caché]\n</h6>\n                <div class="d-flex justify-content-center">\n                    <img src="/static/cookie.png"/>\n                </div>\n            </body>\n        </html>\n    '
```

🌞 **Proposer une version du code qui n'est pas vulnérable**

## II. Netfilter erreurs courantes

🌞 **Write-up de l'épreuve**

On a [ce fichier](./Resources/fw.sh) de configuration.

En le lisant on trouve ces lignes :

```bash
IP46T -A INPUT-HTTP -m limit --limit 3/sec --limit-burst 20 -j LOG --log-prefix 'FW_FLOODER '
IP46T -A INPUT-HTTP -m limit --limit 3/sec --limit-burst 20 -j DROP
```

L'administrateur a visiblement mis une limitte de flood à 20 requêtes toutes les 3 secondes.

On utilise donc [ce script](./Scripts/netfilter.py) pour envoyer 21 requêtes à la page d'adminisatrateur et afficher la réponse de la dernière :

```bash
$ python3 netfilter.py 
b"\nNicely done:)\n\nThere are probably a few things the administrator was missing when writing this ruleset:\n\n    1) When a rule does not match, the next one is tested against\n\n    2) When jumped in a user defined chain, if there is no match, then the\n       search resumes at the next rule in the previous (calling) chain\n\n    3) The 'limit' match is used to limit the rate at which a given rule can\n       match: above this limit, 1) applies\n\n    4) When a rule with a 'terminating' target (e.g.: ACCEPT, DROP...) matches\n       a packet, then the search stops: the packet won't be tested against any\n       other rules\n    \n\n\n\nThe flag is: [coucou toi le flag est caché]\n\n"
```

🌞 **Proposer un jeu de règles firewall**

## III. ARP Spoofing Ecoute active

🌞 **Write-up de l'épreuve**

🌞 **Proposer une configuration pour empêcher votre attaque**

## IV. Bonus : Trafic Global System for Mobile communications

⭐ **BONUS : Write-up de l'épreuve**
