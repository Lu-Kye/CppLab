#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

string* get_values(char* buff)
{
    string* result = new string[10];
    int index = 0;
    for (int i = 0, max = sizeof(buff) - 1; i < max; i++)
    {
	if (buff[i] == '\n')
	    break;

	if (buff[i] == ',' || buff[i] == ' ')
	{
	    index ++;
	    continue;
	}
	
	result[index] += buff[i];
    }
    return result;
}
