# UIElement PoC

Bevat PoC's voor de volgende onderwerpen:
- UIElement, er kan een vierkant en tekst getekend worden en hiervan kan de positie en schaal aangepast worden
- Er kan een mini HuD gemaakt wordt d.m.v. layers
- Sprites rendereren
- Sprites animaren d.m.v. spritesheets
- UIElements animeren d.m.v. berekeningen

## Installatie
Voer het volgende command uit om alle libraries te installeren. Hierna kan de PoC eenvoudig gestart worden d.m.v CMake:

```shell
mkdir -p libraries
cd libraries

git clone https://github.com/libsdl-org/SDL SDL
git clone https://github.com/libsdl-org/SDL_ttf SDL_TTF

cd ..

cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release
```