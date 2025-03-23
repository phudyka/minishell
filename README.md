# Minishell

![Minishell Miniature](minishell.png)

## 💻 Description

Minishell est un projet d'implémentation d'un shell Unix simplifié, conçu dans le cadre de ma formation à l'école 42. Ce shell reproduit le comportement de base d'un terminal Unix, tout en offrant un environnement de commande personnalisable et extensible.

## ⚙️ Fonctionnalités

- **Exécution de commandes** : Exécution de commandes en ligne de commande, similaire à un shell Unix standard
- **Gestion des pipes** : Permet l'enchaînement de plusieurs commandes avec des pipes (`|`)
- **Redirections** : Supporte les redirections de fichiers (`<`, `>`, `>>`)
- **Variables d'environnement** : Manipulation des variables d'environnement
- **Support des commandes internes** : Implémentation de commandes internes (`cd`, `echo`, `exit`, etc.)
- **Gestion des erreurs** : Traitement des erreurs courantes (commandes non trouvées, permissions insuffisantes, etc.)
- **Historique des commandes** : Enregistrement des commandes passées pour une utilisation plus fluide

## 🛠️ Technologies utilisées

- Langage: C
- Bibliothèques: Readline
- Architecture: Analyse lexicale et syntaxique personnalisée

## 🚀 Installation

```bash
# Cloner le dépôt
git clone https://github.com/votre-username/minishell.git

# Se déplacer dans le dossier
cd minishell

# Installer la bibliothèque readline (si nécessaire)
# Debian/Ubuntu
sudo apt-get install libreadline-dev
# MacOS (avec brew)
brew install readline

# Compiler le projet
make
```

## 📋 Utilisation

```bash
# Lancer le shell
./minishell
```

## 📌 Commandes internes implémentées

- `echo` - Affiche du texte (avec gestion de l'option `-n`)
- `cd` - Change de répertoire
- `pwd` - Affiche le répertoire de travail actuel
- `export` - Définit une variable d'environnement
- `unset` - Supprime une variable d'environnement
- `env` - Affiche les variables d'environnement
- `exit` - Quitte le shell avec un code de sortie

## 📝 Normes du projet

- Code conforme à la Norme 42
- Gestion propre des erreurs et de la mémoire
- Pas de fuites mémoire
- Compilation avec flags: `-Wall -Wextra -Werror`

## 👤 Auteur(s)

- [dtassel](https://github.com/Freiko789)
- [phudyka](https://github.com/phudyka)
- 
---
*Projet réalisé dans le cadre du cursus Unix à l'école 42*
