#include "converter.h"
//Seminar Notation:
// G = (N, Σ, P, S) a RG ( Regular Grammar)
// N = the set of nonterminals (ex. {S,A}
// Σ = terminals' alphabet (ex. {a,b})
// P = the productions' set (ex. S → aA, A → b)
// S = the start symbol ( an element of N ) (ex. S)

// Conversion from AF -> RG
// Q (stateCount) = N
// Σ (allowedCharacters[]) = Σ
// q0 (initialState) = S
// transition q0 —a→ q2 = production q0 → a q2
// q0 —a→ q1, where q1 final = q0 → a q1 | a
//RG specific:
// If the initial state is final, also add S → ε: the empty string is accepted.
// Our initial states are not final, so we do not need an ε production.

void convert_to_rg(const Automaton *automaton, FILE *output) {
    // 1. Print all Nonterminals ( N = Q, the set of all states )
    fprintf(output, "N = {");

    for (int i = 0; i < automaton->stateCount; i++) {
        if (i > 0) {
            fprintf(output, ", ");
        }
        fprintf(output, "q%d", i);
    }

    fprintf(output, "}\n");

    // 2. Print all Terminals ( Σ )
    fprintf(output, "Sigma = {");

    for (int i = 0; automaton->allowedCharacters[i] != '\0'; i++) {
        if (i > 0) {
            fprintf(output, ", ");
        }
        fprintf(output, "%c", automaton->allowedCharacters[i]);
    }

    fprintf(output, "}\n");

    // 3. The AF's initial state = the RG's start symbol ( S )
    fprintf(output, "S = q%d\n", automaton->initialState);

    // 4. Convert transitions into productions
    fprintf(output, "P:\n");

    for (int i = 0; i < automaton->transitionCount; i++) {
        Transition transition = automaton->transitions[i];

        // CASE 1: q0 -a-> q1 becomes q0 -> a q1
        fprintf(output, "q%d -> %c q%d\n", transition.source, transition.symbol, transition.destination);

        // CASE 2: Final State: If q1 is final, also add q0 -> a
        if (automaton->isFinalState[transition.destination])
            fprintf(output, "q%d -> %c\n", transition.source, transition.symbol);
    }
}