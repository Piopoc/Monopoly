# Monopoly
- Per sviluppare il tabellone del monopoli abbiamo deciso di utilizzare un vector
(e caricarlo poi su una matrice per stamparlo)

N.B.
- Bisogna creare i file nella cartella build tramite il programma CMake o su linea di comando all'interno della directory "build" (cmake -S .. -B .), poi è sufficiente lanciare il comando "make" e poi eseguire il file

- Si consiglia di usare il terminale a schermo intero per una migliore visualizzazione del programma

- Per terminare programma usare Ctrl+z

# Scelte di progettazione
- Classe Table:
Abbiamo scelto di utilizzare un vector di shared pointer di Cell dove le varie celle hanno un tipo diverso a ogni esecuzione, a eccezione della casella di partenza che è fissa in posizione (0,0). Tale vector viene poi usato per caricare una matrice funzionale alla corretta visualizzazione del tabellone.
Non è stato implementato il distruttore perché il memory leak è già impedito dal distruttore di shared_ptr 
-> spiegare scelta del tipo di vector

