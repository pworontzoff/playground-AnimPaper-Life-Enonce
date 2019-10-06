# Laboratoire Papers animés, avec "step_display()"

Pour ces laboratoires nous utilisons une nouvelle fonctionnalité des Papers animés : le principe du "step_display()".
En effet, jusqu'à présent, chaque `colorize()` provoquait un affichage. Nous allons maintenant pouvoir colorier autant de cases que nous le souhaitons avec `colorize()`, et ne faire des affichages de toutes ces étapes que quand nous le souhaitons, en utilisant une nouvelle fonction spécifique pour ça : la fonction `step_display()`.

Il y a juste une petite subtilité supplémentaire pour pouvoir utiliser des `colorize()` sans que les cases ne soient systématiquement affichées de suite (et pour pouvoir utiliser `step_display()` qui provoque tous les affichages des `colorize()` précédents), il faudra donner la valeur *1* au dernier paramètre (`useStepping`) de la fonction `init_paper()`.

## Manipuler les papers animés (avec "step_display()")

Un `paper animé` en mode "useStepping" est donc un quadrillage dans lequel on va pouvoir se déplacer et colorier des cases. Le "curseur" de coloriage se trouve initialement toujours dans le coin supérieur gauche et chaque appel à `step_display()` est une étape de l'animation (qui affiche d'un seul coup tous les `colorize()` faits jusque-là).

### Exemple

Voici un exemple qui re-colorie (9 fois) les cases noires en blanc et inversement. Ceci en dessinant des petits carrés (de côtés 2) tout en haut à gauche du paper animé :

@[Sample step_display()]({"stubs": ["main.c"],"command": "sh /project/target/run.sh", "project" : "animPaperWithStepDisplay"})

On voit que chaque `colorize()` n'est pas immédiatement affiché, c'est seulement lors des `step_display()` que les affichages (des 4 cases noires ou blanches, d'un coup) se font. Notons également que la dernière valeur de paramètre de `init_paper()` est bien *1* !
