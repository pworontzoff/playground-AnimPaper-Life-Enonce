# Laboratoire Papers animés, avec "step_display()"

Pour ces laboratoires nous utilisons une nouvelle fonctionnalité des Papers animés : le principe du "step_display()".
En effet, jusqu'à présent, chaque `colorize()` et chaque `erase()` provoquaient un affichage. Nous allons maintenant pouvoir colorier et/ou effacer autant de cases que nous le souhaitons avec `colorize()` et `erase()`, et ne faire des affichages de toutes ces étapes que quand nous le souhaitons, en utilisant une nouvelle fonction spécifique pour ça : la fonction `step_display()`.

Il y a juste une petite subtilité supplémentaire pour pouvoir utiliser des `colorize()` et des `erase()` sans que les cases ne soient systématiquement affichées de suite (et pour pouvoir utiliser `step_display()` qui provoque tous les affichages des `colorize()` et `erase()` précédents), il faudra donner la valeur *1* au dernier paramètre (`useStepping`) de la fonction `init_paper()`.

## Manipuler les papers animés (avec "step_display()")

Un `paper animé` en mode "useStepping" est donc un quadrillage dans lequel on va pouvoir se déplacer, colorier et effacer des cases. Le "curseur" de coloriage se trouve initialement toujours dans le coin supérieur gauche et chaque appel à `step_display()` est une étape de l'animation (qui affiche d'un seul coup et dans l'ordre, tous les `colorize()` et `erase()` faits jusque-là).

Les fonctions permettant de manipuler un `paper animé` :
- `init_paper(nb_lignes,nb_colonnes,taille,delai_anim,useStepping)` : 
    * Permet de créer un `paper animé` contenant `nb_lignes` lignes ;
    * et `nb_colonnes` colonnes ;
    * `taille` est la dimension en pixel d'une case et ;
    * `delai_anim` est le temps de pause (en secondes) entre chaque affichages. Ce délai peut-être décimal, par exemple 0.05 pour 5 centièmes de seconde ;
    * Le paramètre `useStepping` permet de différer les coloriages et effacement de cases (via `colorize()` et `erase()`) qui n'auront lieu (d'un seul coup) qu'une fois appelée la fonction `step_display()`. Pour ce faire, ce paramètre `useStepping` devra valoir 1. (S'il vaut 0, `step_display()` n'a aucun effet et chaque `colorize()` et `erase()` sont effectifs immédiatement). En mode `useStepping` (dernier paramètre à 1), chaque étape montrée par `step_display()` s'affiche pendant `delai_anim` secondes. En mode normal (dernier paramètre `useStepping` à 0), chaque `colorize()` et chaque `erase()` s'affichent pendant `delai_anim` secondes.
- `move_left()` : déplace le "curseur" de coloriage d'une case à gauche ;
- `move_right()` : déplace le "curseur" de coloriage d'une case à droite ;
- `move_down()` : déplace le "curseur" de coloriage d'une case vers le bas ;
- `move_up()`  : déplace le "curseur" de coloriage d'une case vers le haut ;
- `move_to(i,j)` : déplace le "curseur" de coloriage en ligne `i`, colonne `j`. NB : la première ligne est la ligne numéro 0 et la première colonne est la colonne numéro 0 ;
- `colorize()` : colorie la case où se trouve le "curseur" de coloriage. **Attention : on ne peut jamais colorier hors du `paper animé`**. NB : en mode `useStepping` (dernier paramètre à 1), ce coloriage sera différé jusqu'au prochain appel à `step_display()` ;
- `erase()` : efface la couleur de la case où se trouve le "curseur" de coloriage. **Attention : on ne peut jamais effacer hors du `paper animé `**. NB : en mode `useStepping` (dernier paramètre à 1), cet effacement sera différé jusqu'au prochain appel à `step_display()` ;
- `step_display()` : en mode `useStepping` (dernier paramètre à 1), affiche d'un seul coup et dans l'ordre tous les `colorize()` et `erase()` effectués depuis le `step_display()` précédent (ou à défaut, depuis le début du programme). NB : en mode normal (dernier paramètre `useStepping` à 0), cette fonction n'a aucun effet.
- `is_colored()` : retourne 0 si la case actuelle (sous le "curseur") n'est pas coloriée et 1 si elle l'est. (Initialement, aucune case n'est coloriée) ;
- `change_color(rouge,vert,bleu)` : permet de définir la couleur de coloriage en fixant l'intensité des composantes rouge, verte et bleu. **Attention : chaque composante de couleur ne peut qu'être un nombre entier entre 0 inclus et 255 inclus** ;
- `display_paper()` : affiche le `paper animé`.

### Exemple

Voici un exemple qui colorie un petit carré de 4 cases en en haut à gauche du paper, puis les efface, et recommence 9 fois :

@[Sample step_display()]({"stubs": ["main.c"],"command": "sh /project/target/run.sh", "project" : "animPaperWithStepDisplay"})

On voit que chaque `colorize()` n'est pas immédiatement affiché, c'est seulement lors des `step_display()` que les affichages (des 4 cases dessinées ou effacées, d'un coup) se font. Notons également que la dernière valeur de paramètre de `init_paper()` est bien *1*.
