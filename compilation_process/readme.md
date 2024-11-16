![alt text](https://github.com/alemilos/arduino/blob/main/compilation_process/compilation-process.png?raw=true)

### Per prima cosa

Creiamo tre files 

- source.cpp (implementation)
- source.hpp (interface / function)
- main.cpp   (entry)

Nel main.cpp includiamo l'header file source.hpp, in cui c'è l'intestatura della funzione add.
Tale funzione è però implementata in source.cpp.


``` g++ main.cpp -o exe```

Cosa è successo in questo step ? Sono successe tante cose...
Ma possiamo riassumere con "è stato creato un executable con il nome exe, che posssiamo 
eseguire"

## Preprocessore

``` g++ -E main.cpp -o exe ``` 

Con la flag -E possiamo vedere in exe cosa fa il preprocessore.
Elimina l' #include e lo sostituisce con l'intestatura che abbiamo creato in 
source.hpp 

``` g++ main.cpp -o exe ```

!Problema... La funzione add(int a, int b) esiste, ma non ne conosciamo la funzionalità.
Questo perchè nel file main.cpp abbiamo incluso l'header source.hpp, ma lì c'è solo 
l'intestazione di questa funzione.

Per risolvere compiliamo main.cpp insieme a source.cpp

``` g++ main.cpp source.cpp -o exe ```

oppure 

``` g++ *.cpp -o exe ``` per abbreviare...


# Vediamo una possibile problematica: l'inclusione multipla della stessa libreria

Se ad esempio nel file main.cpp importassi molte volte l'header source.hpp

```
#include "source.hpp"
#include "source.hpp"
#include "source.hpp" 

```

L'intestazione della mia funzione add(int a, int b) lì definita, sarà sostituita dal 
preprocessore per 3 volte in main.cpp. 
Questo potrebbe causare problemi e conflitti oltre che appesantire il programma.
 
Per risolvere questa situazione, possiamo usare delle direttiva del preprocessore...

```
#ifndef SOURCE_HPP
#define SOURCE_HPP
int add(int a, int b);
#endif
```

Queste assicurano che l'intestaizione della funzione add() verrà aggiunta al main.cpp 
se e solo se non è già stata definita precedentemente.

Per vedere più nel dettaglio ho aggiunto l'include della libreria <iostream> nel file
main.cpp, così da vedere cosa fa il preprocessore. 

# Parsing e compilazione.

In questa fase viene controllata la sintassi delle espressioni 
attraverso la generazione di alberi che ne verifichino la corrette "grammatiche". 

int x = 2 + 2;

                            int 
                            / \
                           =   ;
                          / \
                         x   + 
                            / \
                           2   2

E come nell'esempio viene visitato in-order per controllare che sia ben formato.

Possiamo vedere il tutto tramite i seguenti tools.

``` g++ -fdump-tree-all-graph -g main.cpp source.cpp ```
Verranno generati moltissimi files...
Eseguiamo ad esempio

``` xdot a-main.cpp...einline.dot ``` 

Mostrerà l'albero costruito con i suoi collegamenti a partire dal main()

# Conversione ad Assembly

Possiamo simulare questo step tramite il seguente comando.

``` g++ -S main.cpp ``` 

Abbiamo generato un file .s assembly, in cui sono presenti tutte le funzionalità del nostro
programma in formato assembly, molto più vicino al formato macchina a cui dobbiamo 
arrivare. 

# Object files

Abbiamo scritto due file cpp, main.cpp e source.cpp. Vogliamo unirli insieme per renderli
funzionali.
Per farlo dobbiamo creare dei file oggetto di entrambi

``` g++ -c main.cpp -o main.o ```
``` g++ -c source.cpp -o source.o ```

E poi incollarli insieme... ma prima vediamo con questo strumento più nel dettaglio 
source.o 

``` objdump -t source.o ```

Che mostra il contenuto della symbol table (ma che é non lo voglio sapere xD) 
dove ad esempio c'è la definizione della nostra funzione add, scritta come _Z3addii

# Fase di Linking  

``` g++ main.o source.o -o exe ```

Possiamo vedere le shared libraries in un executable e da dove provengono...

``` ldd exe ```

Per capire un po più nel dettaglio le fasi vedere

https://stackoverflow.com/questions/6264249/how-does-the-compilation-linking-process-work

