#ifndef LAB_4_AUTOMATON_H
#define LAB_4_AUTOMATON_H

//"CAPACITIES"
#define MAX_STATES 3
#define MAX_TRANSITIONS 120 // The DSL has 116 transitions

#define MAX_CHARACTERS 63 //a-z,A-Z,0-9,_ = 63 chars

// An automaton is a data structure that is filled with a set of rules, it dfines the shape of the structure:
// that is, its states, transition, initial state and final state
//
// States = what we have read until now: nothing, a 0 (final state), a digit from 1-9
//Transition = going from one state to the other. For exp, q0 -> q1 means we didn't read anythin yet -> oop we read a digit
#include <stdio.h>
typedef struct Transition {
    //exp {0,'a',1} =>  q0 —a→ q1
    int source;
    char symbol;
    int destination;
} Transition;

//Seminar Notation:
//M = (Q, Σ, δ, q₀, F) is an automaton
//Q = the set of states = stateCount (3 = {0,1,2})
//Σ =  the alphabet = allowedCharacters[]
//δ = transitions[]
//q0 = initialState
//F = the set of final states = the set of states i where isFinalState[i] = 1 (true)
typedef struct Automat{
    //= "size", how many elements we've actually used (0,1,2)
    int stateCount;

    //For identifiers only. a-z,A-Z,0-9,_
    char allowedCharacters[MAX_CHARACTERS + 1];

    // Initial state is always q0 in our AF. Here just so we don't hardcode stuff
    int initialState;
    int isFinalState[MAX_STATES]; // exp. q1 =  digits is 0 => is final

    Transition transitions[MAX_TRANSITIONS];
    //= "size", as in static arrays. how many elements we've actually used
    int transitionCount;
} Automaton;

//IDENTIFIERS
void init_identifier_automaton(Automaton *automaton);
//CONSTANTS
void init_integer_automaton(Automaton *automaton);

void print_automaton(const Automaton *automaton, FILE *output);

#endif


