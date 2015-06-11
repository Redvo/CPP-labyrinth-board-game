ICP Projekt - 6.5.2015

Autori: Lukáš Rendvanský (xrendv00@stud.fit.vutbr.cz)
        Irena Talašová   (xtalas04@stud.fit.vutbr.cz)

Úlohou projektu bolo implementovať stolnú hru Labyrint v textovom aj grafickom prostredí.

Spustenie hry v textovom CLI prostredí je vysvetlené v nápovede ./labyrinth2015-cli --help

Implementácia je rozdelená do 3 častí. 
1. časťou sú súbory v priečinku src/source (s výnimkou main.c),
ktoré slúžia ako knižnica funkcií potrebných pre chod projektu, nezávisle na použitom prostredí.

2. časťou je súbor src/source/main.c, ktorý ukazuje implementáciu projektu v CLI rozhraní,
s použítím zvyšných súborov.

3. časťou je implementácia grafického prostredia v priečinku src/gui, ktoré opäť využíva rovnaké
súbory z priečinka src/source ako CLI verzia.

V pričinku src/header sa nachádzajú všetky hlavičkové súbory a sú zahrnuté do projektu pri preklade
pomocou direktívy "-I../header/".


POZOR - ZNÁMA CHYBA:
Na niektorých počítačoch nechce správne načítavať niektoré náhodné obrázky do QPixmap, nefunguje to ani na serveri Merlin.
V prípade že projekt preložím u seba alebo na Merlinovi a skopírujem binárku k sebe, všetky obrázky sa pri spustení u mňa zobrazia.
Ak preložím projekt na Merlinovi alebo u seba a skopírujem binárku na Merlina, niektoré obrázky sa pri spustení na Merlinovi nezobrazia.
Obrázky sa načítavajú cez resource súbor a sú zahrnuté v priečinku src/gui/img/. 
Skúšal som aj prekladaný resource súbor, efekt bol rovnaký. Na obhajobe ukážem funkčnosť na svojom notebooku.
PS: pri spustení cez QT creator by sa mali obrázky načítať správne.
