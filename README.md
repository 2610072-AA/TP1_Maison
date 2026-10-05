# raylib-base

`git clone --recursive https://github.com/jsteach/raylib-base.git`

## To Build:
Pour travailler sur ce projet vous devez ouvrir `vscode` au dossier du répertoire du repository.

Avant de pouvoir construire vous devez rouler dans le terminal de vscode le script: `setup.bat`.

```batch
.\setup.bat
```

Après avoir rouler le script, vous pouvez cliquer sur `ctrl+shift+b` lorsque l'application à le focus pour construire le code C/C++.

Pour comprendre comment le build fonctionne vous pouvez aller lire le fichier `nob.c` et `.vscode/tasks.json`.

Pour que la compilation fonctionne, vous devez modifier cette ligne dans `nob.c` et remplacer le nom du fichier par le nom de votre `entrypoint.cpp`:

```
#define LAB_NAME "entrypoint"
```



g++ src/client.cpp -o client.exe -lws2_32 (Pour recompiler)

Référence pour l'école: https://share.gemini.google/lFsZqgOkpSUv



## To Run/Debug:
Pour débugger le code, peser sur `F5` comme dans Visual Studio. Assurez-vous d'avoir installé l'extension c/c++:
![Capture](https://github.com/jsteach/raylib-base/assets/114700235/4313801d-b186-4bf2-b907-662c2f61ba3a)

Pour comprendre comment le run fonctionne, vous pouvez lire `launch.json`.

## Pour travailler:
Pour chacun des labos copier le fichier `entrypoint.cpp` et renommer le `labX_entrypoint.cpp`, `X` étant le numéros du labo.


Pour vous aider, vous pouvez lire la documentation de [raylib](https://www.raylib.com/cheatsheet/cheatsheet.html).

Vous pouvez aussi utiliser les [examples](https://www.raylib.com/examples.html) pour voir les possibilités.

