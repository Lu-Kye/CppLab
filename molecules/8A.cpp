#include <stdio.h>
#include <iostream>
#include <string>
#include "utils.h"
#include "molecules.h"

using namespace std;

int main() {
    Molecule molecule;
    int number = 0;
    while (number <= 10)
    {
	cout << "Enter the element and its count (enter 'QUIT' for the element name to stop): ";
	string input;
	getline(cin, input);
	if (input == "QUIT")
	    break;

        char *buff = new char[input.length() + 1];
        strcpy(buff, input.c_str());
	string* values = get_values(buff);
    
	molecule.elements[molecule.element_num] = values[0];
	molecule.element_num ++;
	molecule.counts[molecule.counts_num] = atoi(values[1].c_str());
	molecule.counts_num ++;

	// Elements number check
	number ++;
    }

    cout << "Enter the number of bonds: ";
    int bonds;
    cin >> bonds;
    molecule.bonds = bonds;

    cout << "Enter the charge (-1 for negative, 0 for neutral, 1 for positive): ";
    int charge;
    cin >> charge;
    molecule.charge = charge;

    // Print
    molecule.print();

    return 0;
}
