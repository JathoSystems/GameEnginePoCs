# SceneManagement PoC

Bevat PoC's voor de volgende onderwerpen:
- Scenes kunnen gemaakt worden en elementen aan toegevoegd worden
- Verwisseling van scene's d.m.v de scenemanager
- Camera handling

## Installatie
Voer het volgende command uit om alle libraries te installeren. Hierna kan de PoC eenvoudig gestart worden d.m.v CMake:

### Windows
```shell
mkdir -p libraries
cd libraries

git clone https://github.com/libsdl-org/SDL SDL

cd ..

cmake .. -DCMAKE_INSTALL_PREFIX=../../install
cmake --build . --target install

./SceneManagement
```

### Linux / MacOS

```shell
mkdir -p libraries
cd libraries

git clone https://github.com/libsdl-org/SDL SDL

cmake .. -DCMAKE_INSTALL_PREFIX=../../install
cmake --build . --target install

./SceneManagement
```