# Minishell

## Description

**Minishell** est un projet de l'école 42 qui consiste à recréer un shell simplifié inspiré de bash. Ce projet permet de comprendre en profondeur le fonctionnement d'un interpréteur de commandes, la gestion des processus, des pipes, des redirections et des signaux sous Unix.

## Fonctionnalités

### Interpréteur de commandes
- Affichage d'un prompt en attente d'une nouvelle commande
- Gestion de l'historique des commandes
- Recherche et lancement des exécutables basés sur la variable PATH ou via un chemin relatif/absolu
- Exécution de commandes avec leurs arguments

### Gestion des quotes
- Gestion des guillemets simples (`'`) qui empêchent l'interprétation des métacaractères
- Gestion des guillemets doubles (`"`) qui empêchent l'interprétation des métacaractères sauf `$`

### Redirections
- `<` : redirection de l'entrée standard (stdin)
- `>` : redirection de la sortie standard (stdout)
- `>>` : redirection de la sortie en mode append
- `<<` : heredoc, lecture de l'entrée jusqu'à un délimiteur

### Pipes
- `|` : connexion de la sortie d'une commande à l'entrée de la suivante
- Gestion de plusieurs pipes enchaînés

### Variables d'environnement
- Expansion des variables d'environnement (`$VAR`)
- Variable spéciale `$?` qui contient le code de retour de la dernière commande exécutée

### Signaux
- `Ctrl+C` : Affiche un nouveau prompt sur une nouvelle ligne
- `Ctrl+D` : Quitte le shell
- `Ctrl+\` : Ne fait rien (comme dans bash)

### Commandes intégrées (Builtins)
- `echo` avec l'option `-n`
- `cd` avec chemins relatifs ou absolus
- `pwd` sans options
- `export` sans options
- `unset` sans options
- `env` sans options ni arguments
- `exit` sans options

## Compilation

```bash
make
```

Cela générera l'exécutable `minishell`.

Pour nettoyer les fichiers objets :
```bash
make clean
```

Pour nettoyer complètement (objets + exécutable) :
```bash
make fclean
```

Pour recompiler :
```bash
make re
```

## Utilisation

Pour lancer le minishell :
```bash
./minishell
```

Une fois lancé, vous pouvez utiliser le shell comme vous le feriez avec bash :

```bash
Minishell $ ls -la
Minishell $ echo "Hello World"
Minishell $ cat file.txt | grep "pattern" | wc -l
Minishell $ export MY_VAR=value
Minishell $ echo $MY_VAR
Minishell $ cd /tmp
Minishell $ pwd
Minishell $ exit
```

## Architecture

Le projet est organisé en plusieurs modules :

- **Parsing** : Analyse lexicale et syntaxique des commandes
  - Tokenisation des entrées utilisateur
  - Gestion des quotes et de l'expansion des variables
  - Vérification de la syntaxe

- **AST (Abstract Syntax Tree)** : Construction d'un arbre de syntaxe abstraite pour représenter la structure des commandes

- **Exécution** : 
  - Gestion des processus (fork, execve)
  - Gestion des pipes et redirections
  - Gestion des heredocs

- **Builtins** : Implémentation des commandes intégrées

- **Signaux** : Gestion des signaux (SIGINT, SIGQUIT, etc.)

- **Environnement** : Gestion des variables d'environnement

## Dépendances

- Bibliothèque Readline (`-lreadline`)
- Fonctions système POSIX standard

## Auteurs

Projet réalisé dans le cadre du cursus de l'école 42.

## Licence

Ce projet est réalisé dans un cadre éducatif.
