# Monopoly

N.B.
- Per eseguire il programma bisogna creare i file nella cartella build tramite il programma CMake oppure su linea di comando, digitando il comando "cmake -S .. -B ." all'interno della directory "build". In seguito è sufficiente lanciare il comando "make", quindi eseguire il file

- Si consiglia di usare il terminale a schermo intero per una migliore visualizzazione del programma

- Per terminare programma usare Ctrl+z

# Scelte di progettazione
- *Classe Table*:<br>
È stato scelto di implementare il tabellone mediante vector di shared pointer di Cell, dove le varie celle laterali hanno un tipo diverso a ogni esecuzione. Tale vector viene poi usato per caricare una matrice utile alla corretta visualizzazione del tabellone. La partenza è fissa alla posizione (0,0).<br>
Non è stato implementato il distruttore perché il memory leak è già impedito dal distruttore di shared_ptr.

- *Ordine dei giocatori*:<br>
Durante la definizione dell'ordine dei giocatori, nel caso in cui ci sia parità di punteggio, si chiede ai giocatori interessati di ritirare i dadi: questo secondo tiro non ha influenza sui giocatori che, nel tiro precedente, hanno fatto un punteggio maggiore. Ad esempio se nel primo tiro di dadi il punteggio è stato G1=2, G2=10, G3=8 e G4=8, viene definito G2 come primo giocatore e in seguito si effettua lo spareggio. Se poi nel secondo turno i giocatori 3 e 4 ottengono rispettivamente 12 e 7, G3, nonostante abbia ottenuto un punteggio superiore a G2, viene definito come secondo giocatore e non come primo. L'ordine quindi diventa G2, G3, G4, G1.