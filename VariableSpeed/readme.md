# Variable speed
Setup:
```shell
mkdir libraries
cd libraries
git clone https://github.com/libsdl-org/SDL SDL
```

Gebruikt een [Time singleton](./includes/Time.h) om de tijd modifier overal te kunnen gebruiken of aan te passen.
Hierdoor is ook meteen de snelheid modifier overal hetzelfde.

Je kan de snelheid in dit PoC aanpassen met = (omhoog) en - (omlaag).