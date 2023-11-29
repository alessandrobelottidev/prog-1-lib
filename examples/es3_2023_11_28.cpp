#include "magic.hpp"
#include <fstream>
#include "cstring"

using namespace std;
using namespace magic;

/*
 * Scrivere un programma che simuli l'arrivo e lo smaltimento di una coda
 * all'ufficio postale. Gli elementi della coda sono i nomi delle persone. Il
 * main sarà un menù con tre opzioni: (1) aggiungi persona, (2) smaltisci
 * persona, (3) stampa situazione corrente
 * Potete usare la funzione strcmp della libreria <cstring>
 */

int main() {
    ds::ll_queue<std::string> queue;

    ds::init(queue);

    int option = -1;
    while (option != 4) {
        option = io::showMenu(
            "Smaltimento di una coda postale",
            "Seleziona un'opzione: ",
            {
                    "aggiungi persona",
                    "smaltisci persona",
                    "stampa situazione corrente",
                    "esci"
            },std::cin);

        switch (option) {
            case 1: {
                std::string name = io::read<std::string>(std::cin, "Inserisci il nome della persona: ");
                ds::enqueue(name, queue);
                break;
            }
            case 2: {
                if (ds::emptyp(queue)) {
                    std::cout << "La coda è vuota" << std::endl;
                } else {
                    ds::dequeue(queue);
                }
                break;
            }
            case 3: {
                ds::print(queue);
                break;
            }
            case 4: {
                std::cout << "Arrivederci!" << std::endl;
                break;
            }
            default: {
                std::cout << "Opzione non valida" << std::endl;
                break;
            }
        }

        std::cout << std::endl;
    }

    ds::deinit(queue);

    return 0;
}