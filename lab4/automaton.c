#include "automaton.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void add_transition(Automaton *automaton, int source, char symbol, int destination) {  //{0,'a',1}
    if (automaton->transitionCount >= MAX_TRANSITIONS) {
        fprintf(stderr, "Reached max capacity of transitions.\n");
        exit(1);
    }

    int index = automaton->transitionCount;

    //exp {0,'a',1} =>  q0 —a→ q1
    automaton->transitions[index].source = source;
    automaton->transitions[index].symbol = symbol;
    automaton->transitions[index].destination = destination;

    automaton->transitionCount++;
}

//IDENTIFIERS AUTOMATON
//-- States--:
// 1. q0 = no characters have been read, initial state, not final
// 2. q1 = a char has been read, not initial, final
//--Transitions--:
// 1. q0 -[a-zA-Z] - q1
// 2. q1 -[a-zA-Z0-9_] - q1
void init_identifier_automaton(Automaton *automaton) {
    // Initialize all fields to zero (isFinalState[], transitionCount..)
    *automaton = (Automaton){0};

    // Step 1: define the Automaton's Rules
    automaton->stateCount = 2; // q0, q1
    automaton->initialState = 0; // q0
    automaton->isFinalState[1] = 1; //q1 is final (yes, u can do q1 -> q1, but u can't transition into a different state from there)


    strcpy(automaton->allowedCharacters,"abcdefghijklmnopqrstuvwxyz" "ABCDEFGHIJKLMNOPQRSTUVWXYZ" "0123456789_");

    //Step 2: Add all possible transitions
    // Letters(a-zA-Z) are allowed anywhere in the symbol, no constraints (q0 -> q1 AND q1 -> q1)
    for (char letter = 'a'; letter <= 'z'; letter++) {
        add_transition(automaton, 0, letter, 1);
        add_transition(automaton, 1, letter, 1);
    }
    for (char letter = 'A'; letter <= 'Z'; letter++) {
        add_transition(automaton, 0, letter, 1);
        add_transition(automaton, 1, letter, 1);
    }

    // Digits and underscores are allowed only after the first letter ( only q1 -> q1 )
    for (char digit = '0'; digit <= '9'; digit++) {
        add_transition(automaton, 1, digit, 1);
    }
    add_transition(automaton, 1, '_', 1);
}

//CONSTANTS AUTOMATON
//-- States--:
// 1. q0 = no characters have been read, initial state, not final
// 2. q1 = a 0 has been read. not initial, final
// 3. q2 = a nonzero first digit has been, followed by 0 or more nonzero digits, not initial, final
//--Transitions--:
// 1. q0 -[0]- q1 ( from nothing, we read a 0)
// 2. q0 -[1-9] - q2 ( from nothing, we read a [1-9] digit)
// 3. q2 -[1-9] - q2 (from a 1-9 digit we read a [0-9] digit)
void init_integer_automaton(Automaton *automaton) {
    // Initialize all fields to zero (isFinalState[], transitionCount..)
    *automaton = (Automaton){0};

    // Step 1: define the Automaton's Rules
    automaton->stateCount = 3; // q0,q1,q2
    automaton->initialState = 0; // q0
    automaton->isFinalState[1] = 1; // q1 is final (first digit is 0)
    automaton->isFinalState[2] = 1; // q2 is final ( can only go q2 -> q2 from there)

    strcpy(automaton->allowedCharacters, "0123456789");

    //Step 2: Add all possible transitions

    //{q0,0,q1} (q1 = 0 first digit, final)
    add_transition(automaton, 0, '0', 1);

    //{q0,[1-9],q2}
    // A nonzero first digit leads to q2
    for (char digit = '1'; digit <= '9'; digit++) {
        add_transition(automaton, 0, digit, 2);
    }

    //{q2,[1-9],q2}
    for (char digit = '0'; digit <= '9'; digit++) {
        add_transition(automaton, 2, digit, 2);
    }
}

//M = (Q, Σ, δ, q₀, F) is an automaton
void print_automaton(const Automaton *automaton, FILE *output) {
    //Q = the set of states = stateCount (3 = {0,1,2})
    fprintf(output, "Q = {");
    for (int i=0; i<automaton->stateCount; i++) {
        fprintf(output, "%sq%d", i == 0 ? "" : ", ", i);
    }
    fprintf(output, "}\n");

    //Σ =  the alphabet = allowedCharacters[]
    fprintf(output, "Sigma = {%s}\n", automaton->allowedCharacters);
    //q0 = initialState
    fprintf(output, "Initial state = q%d\n", automaton->initialState);

    //F = the set of final states = the set of states i where isFinalState[i] = 1 (true)
    fprintf(output, "F = {");
    int first = 1;
    for (int i=0; i<automaton->stateCount; i++) {
        if (automaton->isFinalState[i]) {
            if (!first) {
                fprintf(output, ", ");
            }

            fprintf(output, "q%d", i);
            first = 0;
        }
    }
    fprintf(output, "}\n");

    //δ = transitions[]
    fprintf(output, "Transitions:\n");
    for (int i=0; i<automaton->transitionCount; i++) {
        Transition t = automaton->transitions[i];
        fprintf(output, "q%d -%c-> q%d\n", t.source, t.symbol, t.destination);
    }
}