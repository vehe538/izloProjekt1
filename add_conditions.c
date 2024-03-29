#include <stddef.h>
#include "cnf.h"

//
// LOGIN: xmesikj00
//

// Tato funkce by mela do formule pridat klauzule predstavujici podminku 1)
// Křižovatky jsou reprezentovany cisly 0, 1, ..., num_of_crossroads-1
// Cislo num_of_streets predstavuje pocet ulic a proto i pocet kroku cesty
// Pole streets ma velikost num_of_streets a obsahuje vsechny existujuci ulice
//    - pro 0 <= i < num_of_streets predstavuje streets[i] jednu existujici
//      ulici od krizovatky streets[i].crossroad_from ke krizovatce streets[i].crossroad_to
void at_least_one_valid_street_for_each_step(CNF* formula, unsigned num_of_crossroads, unsigned num_of_streets, const Street* streets) {
    assert(formula != NULL);
    assert(num_of_crossroads > 0);
    assert(num_of_streets > 0);
    assert(streets != NULL);

    // ZDE PRIDAT KOD
    
    for (int i = 0; i < num_of_streets; i++){
       
        int z = streets[i].crossroad_from;
        int k = streets[i].crossroad_to;

        Clause *cl = create_new_clause(formula);
        for (int j = 0; j < num_of_streets; j++){   //ulice zo vstupu budu moct byt zvolene v ktoromkolvek kroku 
            
            add_literal_to_clause(cl, true, j, z, k);
        }   
    }
}

// Tato funkce by mela do formule pridat klauzule predstavujici podminku 2)
// Křižovatky jsou reprezentovany cisly 0, 1, ..., num_of_crossroads-1
// Cislo num_of_streets predstavuje pocet ulic a proto i pocet kroku cesty
void at_most_one_street_for_each_step(CNF* formula, unsigned num_of_crossroads, unsigned num_of_streets) {
    assert(formula != NULL);
    assert(num_of_crossroads > 0);
    assert(num_of_streets > 0);

    // ZDE PRIDAT KOD
    for (int i = 0; i < num_of_streets; i++){

        for (int z = 0; z < num_of_crossroads; z++){
            for (int k = 0; k < num_of_crossroads; k++){

                for (int p = 0; p < num_of_crossroads; p++){
                    for (int q = 0; q < num_of_crossroads; q++){

                        if (z != p || k != q){   // "bude sa vyberat" z prave dvoch roznych ulic
                            
                            Clause *cl = create_new_clause(formula);
                            add_literal_to_clause(cl, false, i, z, k);
                            add_literal_to_clause(cl, false, i, p, q);
                        
                        }
                    }
                }
            }
        }
    }
}

    


// Tato funkce by mela do formule pridat klauzule predstavujici podminku 3)
// Křižovatky jsou reprezentovany cisly 0, 1, ..., num_of_crossroads-1
// Cislo num_of_streets predstavuje pocet ulic a proto i pocet kroku cesty
void streets_connected(CNF* formula, unsigned num_of_crossroads, unsigned num_of_streets) {
    assert(formula != NULL);
    assert(num_of_crossroads > 0);
    assert(num_of_streets > 0);

    // ZDE PRIDAT KOD
    for (int i = 0; i < num_of_streets-1; i++){

        
        for (int z = 0; z < num_of_crossroads; z++){
            for (int k = 0; k < num_of_crossroads; k++){

                for (int p = 0; p < num_of_crossroads; p++){
                    for (int q = 0; q < num_of_crossroads; q++){
                        
                        if (k != p){    // pri prechadzani na novu ulicu budu 2 ulice false, ak na seba nenavazuju

                            Clause *cl = create_new_clause(formula);    
                            add_literal_to_clause(cl, false, i, z, k);  
                            add_literal_to_clause(cl, false, i+1, p, q);
                            
                        }
                    }
                }
            }
        }   
    }
}

// Tato funkce by mela do formule pridat klauzule predstavujici podminku 4)
// Křižovatky jsou reprezentovany cisly 0, 1, ..., num_of_crossroads-1
// Cislo num_of_streets predstavuje pocet ulic a proto i pocet kroku cesty
void streets_do_not_repeat(CNF* formula, unsigned num_of_crossroads, unsigned num_of_streets) {
    assert(formula != NULL);
    assert(num_of_crossroads > 0);
    assert(num_of_streets > 0);
    
    for (unsigned i = 0; i < num_of_streets; ++i) {
        // pro kazdy krok i
        for (unsigned j = 0; j < num_of_streets; ++j) {
            if (i != j) {
                // pro kazdy jiny krok j
                for (unsigned z = 0; z < num_of_crossroads; ++z) {
                    for (unsigned k = 0; k < num_of_crossroads; ++k) {
                        // pro kazdu dvojici krizovatek (z, k)
                        Clause* cl = create_new_clause(formula);
                        add_literal_to_clause(cl, false, i, z, k);
                        add_literal_to_clause(cl, false, j, z, k);
                    }
                }
            }
        }
    }
}
