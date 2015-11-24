#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

class Molecule
{
public:
    Molecule()
    {
    }

    Molecule( const Molecule& other ) :
	name( other.name ), 
	element_num( other.element_num ),
	counts_num( other.counts_num ),
	bonds ( other.bonds ),
	charge ( other.charge )
    {
	// Elements
	for (int i = 0; i < other.element_num; i++)
	{
	    this->elements[i] = other.elements[i];
	}	    

	// Counts
	for (int i = 0; i < other.counts_num; i++)
	{
	    this->counts[i] = other.counts[i];
	}	    
    }

    string name;
    void print_name()
    {
	cout << "Molecule " << this->name << endl;
    }

    // Array of elements
    string elements[10];
    int element_num;
    void set_elements(string* values)
    {
	for (int i = 0; i < 10; i++)
	{
	    string value = values[i];
	    if (value.empty())
	    {
		this->element_num = i;
		break;
	    }
	    this->elements[i] = value;
	}
    }
    void add_elements(const Molecule& other)
    {
	for (int i = 0; i < other.element_num; i++)
	{
	    if (this->element_num >= 10)
	    {
		cout << "Error: elements is full" << endl;
		return;
	    }
	    string element = other.elements[i];

	    // Find
	    int index = this->find_element(element); 
	    if (index == -1)
	    {
		// New
		this->elements[this->element_num] = element;
		this->element_num ++;
		this->counts[this->counts_num] = other.counts[i];
		this->counts_num ++;
	    }
	    else
	    {
		// Add count
		this->counts[index] += other.counts[i];
	    }
	}
    }
    int find_element(string element)
    {
	for (int i = 0; i < this->element_num; i++)
	{
	    if (this->elements[i] == element)
		return i;
	}
	return -1;
    }
    void print_elements()
    {
	string str;
	for (int i = 0; i < this->element_num; i++)
	{
	    string element = this->elements[i];
	    str += element; 
	    if (i != this->element_num - 1)
		str += ", ";
	}
	cout << "Elements: " << str << endl;
    }
    
    // Array of counts of each element
    int counts[10];
    int counts_num;
    void set_counts(string* values)
    {
	for (int i = 0; i < 10; i++)
	{
	    string value = values[i];
	    if (value.empty())
	    {
		this->counts_num = i;
		break;
	    }
	    this->counts[i] = atoi(value.c_str());
	}
    }
    void print_counts()
    {
	string str;
	for (int i = 0; i < this->counts_num; i++)
	{
	    int count = this->counts[i];
	    str += to_string(count);
	    if (i != this->counts_num - 1)
		str += ", ";
	}
	cout << "Counts: " << str << endl;
    }

    // Sum of counts
    int count()
    {
	int result = 0;
	for (int i = 0; i < this->counts_num; i++)
	{
	    result += this->counts[i];
	}
	return result;
    }
    void print_count()
    {
	cout << "Total count: " << this->count() << endl;
    }
    
    // Number of bonds
    int bonds;
    void print_bonds()
    {
	cout << "Bonds: " << this->bonds << endl;
    }

    // Charge
    int charge;
    string charge_str()
    {
	switch (this->charge)
	{
	    case -1:
		return "Negative";
	    case 0:
		return "Neutral";
	    case 1:
		return "Postive";
	}
	return "NAN";
    }
    void print_charge()
    {
	cout << "Charge: " << this->charge_str() << endl;
    }

    // TODO test
    // Print 
    void print()
    {
	this->print_name();	
	this->print_elements();
	this->print_counts();
	this->print_count();
	this->print_bonds();
	this->print_charge();
	cout << endl;	
    }

    // Operators
    Molecule operator+ (const Molecule& molecule)
    {
        Molecule result = Molecule(*this);
	result.add_elements(molecule);
	result.bonds += molecule.bonds;

	if (result.charge != 0 && molecule.charge != 0)
	    cout << "Error: either molecule is neutral" << endl;

	if (result.charge != molecule.charge)
	    result.charge += molecule.charge;

	return result;
    }

    Molecule operator- ()
    {
        Molecule result = Molecule(*this);
        result.charge = -result.charge;
        return result; 
    }
};
