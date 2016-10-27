// ConsoleApplication1.cpp : 定義主控台應用程式的進入點。
//

#include "stdafx.h"
#include "DrawObj.h"
#include <iostream>
#include <fstream>
#include "json.hpp"

using json = nlohmann::json;

int main()
{
	// create an empty structure (null)
	json j;
	LineObj newline;
	newline.makeStart(12, 34, 2);
	newline.makeEnd(56, 78, 0, 0);
	cout << "newline ptBeg=" << newline.ptBeg.x << ", " << newline.ptBeg.y << endl;
	cout << "newline ptEnd=" << newline.ptEnd.x << ", " << newline.ptEnd.y << endl;
	cout << "newline color=" << newline.color << endl;

	j["objectType"] = "LineObj";
	j["ptBeg"] = { newline.ptBeg.x, newline.ptBeg.y };
	j["ptEnd"] = { newline.ptEnd.x, newline.ptEnd.y };
	j["color"] = newline.color;

	cout << j << endl;

	// open a file in write mode.
	ofstream outfile;

	outfile.open("afile.dat");
	cout << "Writing to the file" << endl;
	outfile << j << endl;

	// open a file in read mode.
	ifstream infile;
	json j2;

	infile.open("afile.dat");
	cout << "\nReading from the file" << endl;
	infile >> j2;
	cout << j2 << endl;

	// close the opened file.
	infile.close();

	//convert j2 to lineobj
	if (j["objectType"] == "LineObj")
	{
		cout << "\nj2 is LineObj!\n";
		LineObj line2;
		line2.makeStart(j2["ptBeg"][0], j2["ptBeg"][1], j2["color"]);
		newline.makeEnd(j2["ptEnd"][0], j2["ptEnd"][1], 0, 0);
		cout << "\nline2 ptBeg=" << line2.ptBeg.x << ", " << line2.ptBeg.y << endl;
		cout << "line2 ptEnd=" << line2.ptEnd.x << ", " << line2.ptEnd.y << endl;
		cout << "line2 color=" << line2.color << endl;
	}
	return 0;
}

