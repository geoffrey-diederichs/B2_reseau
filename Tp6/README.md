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

Puis [ce script](./Scripts/netfilter.py) va envoyer des requêtes en boucles jusqu'à obtenir le code source de la page admin.

🌞 **Proposer une version du code qui n'est pas vulnérable**

## II. Netfilter erreurs courantes

🌞 **Write-up de l'épreuve**

🌞 **Proposer un jeu de règles firewall**

## III. ARP Spoofing Ecoute active

🌞 **Write-up de l'épreuve**

🌞 **Proposer une configuration pour empêcher votre attaque**

## IV. Bonus : Trafic Global System for Mobile communications

⭐ **BONUS : Write-up de l'épreuve**
