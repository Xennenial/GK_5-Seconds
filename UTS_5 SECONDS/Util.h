#pragma once
#pragma once
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

string readFile(string fileName)
{
	cout << "Reading FIle " << fileName << endl;
	//to read every fileText we made
	string fileText;
	ifstream myFile(fileName);
	string tempText;

	while (getline(myFile, tempText))
	{
		fileText += tempText + "\n";
	}

	cout << fileText << endl;

	return fileText;
}