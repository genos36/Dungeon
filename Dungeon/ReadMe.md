Questo è un mio progetto per imparare un po' di cose sul framework sfml

dovrebbe essere un rpg 2D


## dipendenze
SFML 2.6 
cmake
(conan opzionale)


## work flow
il progetto usa cmake come sistema di build automation
se sono stati aggiunti nuovi file si può usare il file "build.sh" per aggiornare la lista di file usata da cmake (per aggiornare manualmente i file da includere si può andare al file ./cmake/extra) 

si può usare conan per aggiornare le dipendenze tramite il file updateDependencies

## road map
nel file roadMap.md c'è una bozza di ciò che verrà implementato