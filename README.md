# Magic library for Computer Programming 1
## _The coolest least useful library ever_

Questa é una piccola libreria sviluppata da alcuni studenti durante il periodo di lezioni di programmazione 1 a Trento del 2023 con lo scopo di semplificare l'esame finale grazie a funzioni, strutture dati, ed algoritmi pre-implementanti.

La definiamo inutile in quanto seppure ben organizzata e con un codice abbastanza generalizzato e relativamente pulito probabilmente non sará possibile utilizzarla durante l'esame usando semplicemente  `#include <magic.hpp>`. Questo perché all'esame ci saranno da implementare solo alcune funzioni... la maggior parte della struttura ci sará data...

Nonostante ció é un ottimo diletto che permette di imparare meglio le basi del C++.

N.B.: Nuove pull request sono ben accette!

## Features
- Funzioni di debug e wrapper di altre funzioni
- Funzioni matematiche efficienti (es. sieveOfEratosthenes)
- Input Output semplificato, generatore di menu, lettura di stream piu semplice con controlli pre-integrati
- Operazioni su stringhe implentate da zero (utili se non si puo usare <string> in sede d'esame)
- Operazioni su matrici
- Strutture dati comuni (Stack, Queue, Tree, etc...)
- Algoritmi di sorting e di ricerca su array e su varie strutture dati

## Tech
Il progetto usa principalmente:
- C / C++
- CMake (deployment system)
- Catch2 (testing)

## Project structure
```
/
├── examples (esempi di come si usa la libreria)
├── external (librerie esterne)
│   └── catch2
│       └── catch2.hpp
├── include (le dichiarazioni front-facing)
│   ├── magic
│   │   └── magic.hpp
│   └── ds
│       ├── dynamic_array_stack.hpp
│       └── ...
├── lib (l'effettivo codice sorgente)
├── tests (da usare per lo sviluppo)
└── CMakeLists.txt
```

## Installation
// TODO

## Execution
// TODO

## License
MIT
**Free Software, Hell Yeah!**
