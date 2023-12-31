# Monopoly
-Per sviluppare il tabellone del monopoli abbiamo deciso di utilizzare un vector e caricarlo poi su una matrice per avere la giusta formattazione e al tempo stesso la migliore gestione dello spostamento delle pedine durante il gioco.

N.B.
-Bisogna creare i file nella cartella build tramite il programma CMake o su linea di comando all'interno della directory "build" (cmake -S .. -B .), poi è sufficiente lanciare il comando "make" e poi eseguire il file

-Si consiglia di usare il terminale a schermo intero per una migliore visualizzazione del programma


richieste per il main:

a pier
bool hasOwner()
bool hasHouse()
bool hasAlbergo()
int getIDofOwner()

a piopo
void move(player,fromCell,numeroSalti)
bool passAcrossStart(player,fromCell,toCell)
Cell whereIs(player)

RICHIESTA FUNZIONE
//tutte le sue proprietà vengono rese libere (dato il player)