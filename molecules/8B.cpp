#include <stdio.h>
#include <iostream>
#include <string>
#include "utils.h"
#include "molecules.h"

using namespace std;

Molecule molecules[10];
int number = 0;

void parse_molecules()
{
    FILE* file_in;
    file_in = fopen("molecules.dat", "r");
    if (file_in == NULL)
    {
        cout << "read file molecules.dat error" << endl;
        return;
    }

    // Field index
    int index = 0;

    // Read
    char buff[256];
    while (fgets(buff, 256, file_in) != NULL)
    {
        // Check quit
        if ((string)buff == "QUIT\n")
	{
	    number ++;
	    index = 0;
            continue;
	}

	Molecule& molecule = molecules[number];

	string* values = get_values(buff);
	switch (index)
	{
	    // Name
	    case 0:
		molecule.name = values[0];
		break;
	    
	    // Elements
	    case 1:
		molecule.set_elements(values);
		break;

	    // Counts
	    case 2:
		molecule.set_counts(values);
		break;

	    // Bonds
	    case 3:
		molecule.bonds = atoi(values[0].c_str());
		break;

	    // Charge
	    case 4:
		molecule.charge = atoi(values[0].c_str());
		break;
	}	    
	index ++;
    }

    // Close file io
    fclose(file_in);
}

void print_molecules()
{
    for (int i = 0; i < number; i++)
    {
	molecules[i].print();
    }	
}

void additional_molecules()
{
    // #0 + #1    
    // number 3
    Molecule& molecule0 = molecules[0];
    Molecule& molecule1 = molecules[1];
    molecules[number] = molecule0 + molecule1;
    molecules[number].name = "(#0 + #1)";
    number++;

    // #-2
    // number 4
    Molecule& molecule2 = molecules[2];
    molecules[number] = -molecule2;
    molecules[number].name = "-#2";
    number++;
}

int main() {
    // Parse molecules
    parse_molecules();

    // Add additional molecules
    additional_molecules();

    // Print
    print_molecules();

    return 0;
}
