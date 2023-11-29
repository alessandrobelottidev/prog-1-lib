#include "../include/magic/magic.hpp"

using namespace std;
using namespace magic;

/*
 * Sabbie mobili (trovare una path in base a regole custom)
 * Rappresentiamo una palude con una matrice che contiene solo 0 e 1, in cui 1 rappresenta terraferma, mentre 0 rappresenta sabbie mobili in cui si sprofonda. \nScrivere una programma che, data la mappa di una palude (ovvero una matrice di 0 e 1), cerca un percorso per attraversarla su terraferma e, se tale percorso esiste, lo visualizza tramite un array che contiene i passi fatti su terraferma e una matrice che codifica terraferma con '*' e sabbie mobili con '-'. \nPiù specificatamente: \n• Si cerchi un percorso da sinistra a destra, cioè dalla colonna 0 alla colonna (colonna-1); \n• Sono possibili solo movimenti in avanti, cioè partendo dalla posizione (riga, colonna) ci si può spostare in: \n(riga-1, colonna+1) (solo se la riga non è la prima) \n(riga, colonna+1) \n(riga+1, colonna+1) (solo se la riga non è l’ultima) \n• Si memorizzi l’eventuale percorso di attraversamento in un array i cui elementi sono gli indici delle righe corrispondenti ad ogni passo del percorso.
*/

int main() {
    return 0;
}
