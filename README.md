# Padding Analyzer C++

  Le projet a pour but d'améliorer la taille de structure simple en c++  
  Affichage du padding et de l'alignement mémoire pour des structures simple dans le but d'améliorer le code  
  Le projet peut étre utiliser simplement comme montré dans le main.cpp  
  Ou par le script Python expliqué si dessous  
  

Ce projet contient :
- Un script Python (`script.py`) qui scanne vos fichiers `.hpp` / `.cpp` pour détecter les `struct`
- Un fichier `padding.hpp` utilisé pour générer un `layout.cpp` compilable
- Un exemple de génération d'analyse de padding mémoire

## Utilisation

```bash
python script.py --dir chemin/vers/fichiers --out layout.cpp
```

Ce script :
- détecte les `struct`
- extrait leurs champs
- génère `checkStructPadding<...>()` pour chacun

## Exemple de résultat généré

```cpp
#include "padding.hpp"
int main() {
    checkStructPadding<A, char, int, char>("A");
    return 0;
}
```

Vous pouvez ensuite compiler `layout.cpp` avec un compilateur C++ standard.

## Analyse récursive

Pour analyser une structure et ses sous-structures imbriquées :

```cpp
checkStructPaddingWithSubtypes<Outer, Inner, char>("Outer");
```

Cela va :
- Appeler `checkStructPadding<Outer, ...>()`
- Puis appeler récursivement `checkStructPaddingRecursive<Inner>()`

À vous d'ajouter `checkStructPadding<Inner, ...>()` séparément pour des résultats complets.
