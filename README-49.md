# README 
## Hortense Liaras et Maud Dupont-Roc - groupe 49

### Programmation Orientée-objets(SV)
---

## INTRODUCTION
Ce programme est une simulation de l'évolution de colonies de fourmis, dans un monde ou les différentes colonies sont en compétition, les fourmis sont à la quête de nourriture, et elles sont la proies de termites.

L'environement est un monde torique, qui contient des animaux, des sources de nourriture (et un générateur de ces dernières) et des fourmilières. 

Les animaux sont des fourmis et des termites. Ils sont caractérisés par leurs points de vie et leur espérance de vie, qui évolue au cours du temps. 
Les fourmis sont carctérisées par la fourmilière auquelles elles appartiennet, et peuvent être de plusieurs types. Les fourmis ouvrières sont à la quête de nourriture, qu'elles tentent de ramener à leur fourmilière. Les fourmis combattantes se battent contre les ennemis, qui sont des fourmis venant d'une autre fourmilière et les termites.
Les fourmis sont générés à partir d'une fourmilière, et peuvent aussi être générées à partir d'une touche clavier.

Les animaux se déplacent en tentant régulièrement des rotations : elles ont une probabilité plus grande de faire de petites rotations que de changer brutalement de direction. Les fourmis sont également soumises à un déplacement sensoriel : en présence de phéromones, elles ont tendance à les suivre, ce qui peut les aider par exemple à retrouver le chemin vers leur fourmilière ou vers des sources de nourriture

---

## COMPILATION ET EXECUTION

Ce projet compile au moyen de [Cmake](https://cmake.org/).

* en ligne de commande :
  * dans le dossier build: cmake ../src
  * make nom_cible pour la génération de la cible

* Dans QTCreator:
  * mise en place du projet : ouvrir le fichier src/CmakeLists.txt
  * choisir la cible à exécuter
  
---

## CIBLES PRINCIPALES

* application :  correspond à l'application finale.
* antTest, foodTest, anthillTest et termiteTest : permettent de faire générer des éléments dans l'environnement via certaines commandes.
* pheromoneTest : permet de déposer des phéromones avec la souris et d'observer le déplacement sensoriel d'une fourmi.
* vec2dTest, toricTest, positionnableTest et enemyTest : vérifie si le programme est fidèle à certaines assertions à propos des Vec2d, du monde torique et des reconnaissances entre ennemi.

---

## FICHIERS DE CONFIGURATION

Les fichiers de configuration à utiliser pour application sont app.json.

---

## COMMANDES

Les commandes pour l'utilisation d'une cible particulières sont données
dans un panneau d'aide à gauche de la fenêtre de simulation.

--- 

## MODIFICATION DE CONCEPTION

Le codage du projet a été réalisé en adéquation avec l'énoncé.

---

## EXTENSIONS

Nous avons rajouté la possibilité d'augmenter (touche U) et de baisser (touche L) la température, ce qui à pour effet de diviser par 2 la vitesse des fourmis lorsqu'elle passe au dessus de 30 degrés. 
Nous avons également codé deux nouvelles classes héritant de Ant : AntScout (fourmis éclaireuses) et AntKamikaze. Les fourmis éclaireuses sont générés environ à la même fréquence que les fourmis soldates/ouvrière (cela peut être modifié dans les fichiers de configuration). Elles se déplacent comme les autres fourmis, mais lorsqu'elles perçoivent une fourmilière ennemi, elles la repèrent puis font demi-tour. Plus précisément, sachant qu'elles se rappellent de la position de leur propre fourmilière, elles gardent ensuite en mémoire la distance entre les deux fourmilières et la direction. Lorsqu'elles retombent sur leur fourmilière, elles donnent ces informations à la fourmilière, qui se met en mode attaque et fait apparaître une fourmi kamikaze. La fourmi kamikaze n'est pas sensible aux phéromones, elle apparait directement dans la direction de la fourmilière ennemi, avec un décompte avant son explosion, initialisé en fonction de la distance entre les deux fourmilières. Lorsque son minuteur arrive à 0, elle explose, les fourmilières présentes dans le rayon d'explosion sont détruites et les animaux perdent des points de vie. Les fourmilières détruitent perdent toute leur nourriture et arrêtent d'être considérés comme des fourmilières ennemis. Elles ne produisent plus de fourmis non plus, donc leur population est vouée à disparaître. Cette manière de défense est surtout efficace pour éviter que des fourmilière ennemies s'installent l'une à côté de l'autre. 
Les fourmilières kamikazes et scout apparaissent dans nos statistiques.
