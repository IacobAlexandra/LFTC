#include <stdio.h>
#include "automaton.h"
#include "converter.h"

int main(void) {
    Automaton identifierAutomaton;
    Automaton integerAutomaton;

    init_identifier_automaton(&identifierAutomaton);
    init_integer_automaton(&integerAutomaton);

    printf("------ Identifier AF ------\n");
    print_automaton(&identifierAutomaton, stdout);

    printf("------ Integer AF ------\n");
    print_automaton(&integerAutomaton, stdout);

    printf("------ Identifier RG ------\n");
    convert_to_rg(&identifierAutomaton, stdout);

    printf("\n------ Integer RG ------\n");
    convert_to_rg(&integerAutomaton, stdout);

    return 0;
}