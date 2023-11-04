# Rapport de Projet AP4A: Simulateur d'environnement IOT

William Imbert - Université de Technologie de Belfort-Montbéliard
Github du projet:  https://github.com/Wiqiro/TD-AP4A



## I. Introduction et but du projet

Ce projet a pour but de créer un simulateur d'écosystème IOT spécialisé dans le monitoring de qualité de l'air d'espace de travail. Un écosystème est composé d'un serveur ainsi que de différents types de capteurs communiquant avec celui-ci (humidité, température, niveau sonore, luminosité). Les données récupérées par chaque capteur seront stockées dans des fichiers de logs et/ou affichées dans la console. Le projet a pour objectif d'appliquer les concepts de programmation orientée objet (POO) vus dans l'UV AP4A et demandera d'utiliser différents outils durant sa réalisation, tant au niveau de la conception que de l'implémentation.



## II. Structure du projet

**Différentes classes:**

La structure du projet est constituée de plusieurs classes. Dans un premier temps, on retrouve la classe `Server`, qui doit pouvoir recevoir des données des capteurs, les afficher dans la console et les stocker dans des fichiers de logs.

On trouve également une classe `Sensor`, représentant les capteurs du système IOT. Les capteurs doivent permettre de générer des valeurs simulées en fonction de leur type ainsi que de les envoyer au serveur. Chaque type de capteur (humidité, température, niveau sonore, luminosité) est représenté par une classe dérivée de la classe capteur. Ainsi, chaque capteur simule de manière différente les mesures de valeurs.

Enfin, la classe Scheduler permet la communication entre un capteur et des serveurs. Le scheduler doit pouvoir récupérer les données de chaque capteur pour les envoyer à son serveur à des intervalles pouvant être différentes pour chaque capteur. La simulation doit pouvoir être arrêtée et reprise à n'importe quel moment.

**Relations et diagramme de classes UML:**

Le diagramme de classes réalisé lors de la conception du projet se base sur celui distribué lors du second TD. Dans la version finale, on voit qu'un serveur peut être relié à plusieurs scheduler (relation `0..*`) lui envoyant les données des capteurs reliés à chacun d'entre eux. Chaque scheduler peut être relié à 0 ou plusieurs capteurs (`0..*`). Enfin, les différents types de capteurs sont liés à la classe `Sensor` par un héritage publique. On remarque également dans la classe `Sensor` la méthode virtuelle pure `generateValue()` qui est implémentée dans chacun des différents types de capteurs, ce qui permet une génération de valeur aléatoire cohérente pour chaque type de capteur. Se référer au diagramme de classes fourni avec le rapport pour plus de détails.



## III. Implémentation

L'implémentation du projet a été réalisée avec le language `C++`, étudié dans le cadre de l'UV AP4A. Le code étant également fourni avec le rapport, il serait inutile de détailler l'implémentation de chaque fonction une par une. Cependant, voici quelques points dans l'étape d'implémentation qui me semble intéressants à mentionner:

**La classe template `Sensor`:**

Le projet demandait à ce que les différents types de capteurs génèrent des valeurs de différents types:

- `float` pour les capteurs d'humidité et de température
- `int` pour les capteurs de son
- `bool` pour les capteurs de lumière

Pour cela, la classe abstraite `Sensor` est implémentée en tant que template. Ainsi, il est théoriquement possible de créer des capteurs  retournant n'importe quel type. Ainsi, chaque type de capteur proposé par la consigne hérite d'une implémentation de la classe template `Sensor` et redéfinis la méthode `generateValue()`. Le point négatif de l'utilisation de template pour la classe `Sensor` est que cela implique une perte généricité. En effet, la classe `Scheduler` doit être en mesure de contenir une liste de capteurs de différents types, ce qui n'est pas possible car les différents capteurs n'héritent pas réellement de la même classe (mais des différentes implémentations de la classe template `Sensor`). Ainsi, le scheduler devra contenir une liste pour chaque type de valeur stockée par les capteurs:

```cpp
std::list<Sensor<int> *> i_sensors;
std::list<Sensor<float> *> f_sensors;
std::list<Sensor<bool> *> b_sensors;
```

**Liaison par pointeurs:**

Comme vu dans le paragraphe précédent, le scheduler stocke les capteurs (ainsi que le serveur) comme des pointeurs. Ne pas stocker directement l'objet permet de ne pas avoir à le copier au moment de la liaison. Ainsi, le serveur et les capteurs liés au scheduler sont aussi accessible en dehors de celui-ci, permettant par exemple à l'utilisateur de changer le paramètre d'un capteur lorsqu'il le souhaite. Pour créer un capteur et le lier au scheduler, il faudra donc procéder ainsi:

```cpp
SoundSensor *sensor = new SoundSensor(sensor_name, sensor_interval);
scheduler.linkSensor(sensor);
```

Etant donné que l'espace mémoire du capteur est créé en dehors du scheduler, on laisse l'utilisateur le libérer lui-même: le destructeur du scheduler ne libérera pas la mémoire allouée aux capteurs automatiquement (dans certains rares cas, l'utilisateur pourrait toujours vouloir utiliser le capteur après la destruction du scheduler). Cependant, dans le cas où l'utilisateur ne voudrait pas garder la trace de chaque pointeur, il disposera toujours des fonctions `deleteServer()` et `deleteSensors()` permettant de libérer la mémoire depuis le scheduler.

**Le fonctionnement du scheduler en parallèle du reste du programme:**

Pour que le simulateur soit facile à utiliser, il est important qu'il soit possible de lancer la simulation via le scheduler tout en pouvant continuer à exécuter le reste du programmeen parallèle. Pour cela, il est nécessaire que chaque simulation lancée via un scheduler soit exécutée sur un autre thread, d'où l'utilisation la classe `std::thread`. Pour lancer la simulation dans un scheduler, ces instructions sont utilisées:

```cpp
is_running = true;
data_collector = std::thread([this]() {
    while (is_running) {
        processSensorList(i_sensors);
        processSensorList(f_sensors);
        processSensorList(b_sensors);
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
});
```

Cela permet de créer un nouveau thread qui, à chaque milliseconde, procédera à l'analyse des données de chaque capteur pour les envoyer au serveur si besoin. Pour stopper la simulation, on utilisera simplement les instructions:

```cpp
is_running = false;
data_collector.join();
```

La méthode `join()` permet simplement d'attendre que le thread `data_collector` ait fini son exécution pour continuer. Pour cela, le booléen `is_running` et le thread `data_collector` doivent être stockés en tant qu'attributs de la classe `Scheduler`.

Pour la gestion des intervalles de collecte de données par le scheduler, un interval est défini en attribut de chaque capteur, ainsi que la dernière fois que celui-ci a été lu. Ainsi, la fonction `processSensorList` appelée par le thread `data_collector` parcours une liste de capteurs et détermine pour chacun d'eux si il est prêt à être lu pour que ses données soient envoyées au serveur.

**L'implémentation de l'opérateur `<<` :**

Une des fonctionnalités requises par l'énoncé du projet était l'implémentation de l'opérateur `<<` dans la classe `Server`, permettant de passer directement les informations d'un capteur au serveur pour que celui les affiche dans la console ou les inscrive dans les fichiers de logs. Cependant, le nom du fichier de log dans lequel les données sont enregistrées dépend du nom du capteur qui lui est associé. Ainsi, il n'est pas suffisant de passer uniquement la valeur du capteur au serveur pour qu'il puisse la traiter correctement. Pour remédier à cela, il est possible d'utiliser la classe template `std::tuple`, permettant de stocker un groupe ordonné d'éléments de types différents:

```cpp
template <typename T>
void operator<<(const std::tuple<std::string, T> &data) {
    this->recieveData(std::get<0>(data), std::get<1>(data));
}
```

Ainsi, le premier élément du tuple `data` (auquel on accède par `std::get<0>(data)`) contient le nom du capteur et le second le valeur du capteur. Pour passer les données d'un capteur au serveur depuis le scheduler, on utilise donc l'opérateur ainsi:

```cpp
std::tuple<std::string, T> data = {sensor->getName(), sensor->sendData()};
server << data;
```



## IV. Résultat final et tests

Une fois le simulateur implémenté, il est nécessaire de tester le programme pour vérifier que toutes les fonctionnalités prévues fonctionnent et éviter les fuites de mémoire. Pour cela, un programme de démo a été réalisé dans le fichier `main.cpp` réalisant les actions suivantes:

```
Créer un scheduler vide
Demander à l'utilisateur les paramètres du serveur (activation de la console et des logs, dossier de stockage des logs)
Créer un serveur suivant ces paramètres et le lier au scheduler
Tant que l'utilisateur veut créer un nouveau capteur:
	Demander le type, le nom et l'intervalle du capteur
	Créer un capteur suivant ces paramètres et le lier au scheduler
Tant que l'utilisateur ne quitte pas:
	Si l'utilisateur entre L: mettre la simulation en marche
	Si l'utilisateur entre P: mettre la simulation en pause
	Si l'utilisateur entre C: clear les précédentes mesures de la console
	Si l'utilisateur entre Q: quitter le programme
Stopper la simulation
Détruire le serveur et les capteurs dans le schedule
```

Ce programme est compilé avec le simulateur à l'aide d'un Makefile qui permet d'automatiser le processus de compilation en créant un exécutable `iot_simulator`. Ce Makefile propose les flags `all`, `run` pour lancer le programme après la compilation et `clean` pour supprimer les fichiers occasionnés par la compilation. Pour compiler et lancer le programme, il suffira donc simplement d'exécuter la commande `make run`.

Enfin, l'outil `valgrind` est utilisé pour vérifier que le programme ne présente aucune fuite de mémoire. Après avoir lancé une simulation d'une minute avec 8 capteurs (2 de chaque type), voici le résultat du test:

```
Fin du programme
==222774== 
==222774== HEAP SUMMARY:
==222774==     in use at exit: 0 bytes in 0 blocks
==222774==   total heap usage: 1,998 allocs, 1,998 frees, 3,010,763 bytes allocated
==222774== 
==222774== All heap blocks were freed -- no leaks are possible
==222774== 
==222774== For lists of detected and suppressed errors, rerun with: -s
==222774== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

On voit ainsi que l'intégralité de la mémoire allouée a été libérée et qu'aucune erreur n'est survenue.

De plus, les fichiers de logs pour l'intégralité des capteurs ont été créés:

```
> tree ./logs    
./logs
├── hum1	
├── hum2
├── lum1
├── lum2
├── son1
├── son2
├── temp1
└── temp2
```

Et sont chacun rempli sous le format `hh::mm::ss:  valeur`

Le programme semble donc ne pas comporter de fuite de mémoire ni d'erreur.



## V. Conclusion et améliorations possibles

Pour conclure, l'intégralité des fonctionnalités demandés par le sujet du TP a pu être implémentée. Cela a permis de mettre en application les concepts de programmation orienté objet vue dans l'UV AP4A ainsi que les bases du language C++ à travers différents outils, tels qu'Astah pour la réalisation de diagrammes de classes, g++ et make pour la compilation, git et github pour la gestion et l'hébergement du code ou encore valgrind pour la détection de fuites de mémoire. Nous avons pu voir que d'après les tests réalisés, le simulateur ne semble pas contenir de bugs ou de fuites de mémoires. Il y a cependant plusieurs points qui pourront être améliorés par la suite et en voici quelques-uns.

- Utiliser des smart pointers pour relier le serveur et les capteurs au scheduler afin que l'utilisateur n'ait pas à se soucier de la mémoire.
- Améliorer la généricité des capteurs afin de permettre à l'utilisateur du simulateur de créer des capteurs héritant de pouvant stocker n'importe quelle valeur. Cela demanderait cependant un changement dans la structure du programme ou une utilisation avancée de `std::any` de manière à pouvoir avoir une seule et même liste de capteurs dans le scheduler. Actuellement, l'utilisateur peut créer n'importe quel type de capteur, mais ne peut les lier au scheduler que si ils stockent une valeur de type `float`, `int` ou `bool`.
- Améliorer la génération des valeurs aléatoires pour les capteurs en utilisant la librairie `random` au lieu de la fonction `rand()` héritée de C. Il serait également possible de faire en sorte que la valeur générée par `generateValue()` soit basée sur la dernière valeur générée afin de la rendre plus cohérente.
- Une utilisation plus sécurisée des threads pour éviter de potentiels problèmes de synchronisation dans le cas d'une utilisation plus complexe

Pour aller plus loin, il serait également très intéressant de proposer une gestion d'environnements plus complexes, avec par exemple un système permettant de gérer et sauvegarder des scénarios de simulation personnalisés par l'utilisateur, des outils d'analyse des fichiers de logs résultant des simulations , ou encore une liaison avec de réels capteurs.



## Annexe: Diagramme de classes UML

