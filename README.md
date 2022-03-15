# my_ftirc

A Faire maintenant :
- refaire check nickname & channel name
- bien vérifier fichier server
- password / deconnection du client si mauvais pass
- modifier to_string
- ajouter msg mode : mode/<#channel> [<mode>] by <sender>
- ajouter msg à chaque user dans channel si changement de nick
- vérifier qu'un operator perd son statut s'il est kick d'un channel
- vérifier segfault quand user retiré du server
- pas de message d'erreur quand mode est déjà mis

Correction:
- vérifier Kill client => besoin de rajoutyer commande KILL ?
- vérifier Stop client


#1 Server setup (creation du socket, listen)
#2 Server run loop (poll & accept client)

#3 Envoie du msg connection server => irc

// Connection entre client et server ok

Q : multi clients marche, pas vraiment sur ?
ajouter fonction pour vérifier noms différents des users

A partir de là :
- Registration des users ? (même chose que accept client ?)
	(commande NICK et USER pour REGISTER, ensuite envoie message de bienvenue #3)
- Création des channels (regarder si channel par defaut et 			différend type de channels # et + à vérifier)
- interprétation et execution des commandes user
- interprétation et execution des commandes operator (celui qui crée le channel est forcement opeartor / regarder si ajout d'operator possible)
	(comprendre bien difference user et operator)
- commande mode (état du user, peut-etre modifier droit du 			channel) ? à confirmer
	Channel mode et user mode
- délivrance des messages à tous les users
- delog des users (clients)
- suppresion des channels

Q : La délivrance des reponses doit elle avoir un ordre (message bloqué / pas clair dans ma tête)
A regarder plus en détail !!

Gestion du password à creuser !

Q : quelles commandes implémenter ? 

Creation config pour garder info

# registration
- USER - Done
- NICK <nickname> : Set or change your nickname. - Done
- PASS
- QUIT
- (OPER)

# channel 
- (INVITE)
- JOIN (Join 0, quitte tous les channels)
- KICK
- LIST - Done
- (NAMES)
- PART - Done
- TOPIC

# sending msh
- NOTICE
- PRIVMSG 

# utils
- PING - Done

- (MODE)

Sujet:
- https://cdn.intra.42.fr/pdf/pdf/39385/fr.subject.pdf

Doc :
- RFC 2812 : https://datatracker.ietf.org/doc/html/rfc2812
- https://ircgod.com/
- https://www.geeksforgeeks.org/socket-programming-cc/
- http://se.inf.ethz.ch/student_projects/fabian_gremper/Report.pdf

Projects
- https://github.com/jeongwle/ft_irc (semble plutôt minimaliste, pas mal)
- https://github.com/42cursus/ft_irc