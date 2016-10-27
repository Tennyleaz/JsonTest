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
	newline.objectType = 1;
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
	outfile.close();

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
		line2.makeEnd(j2["ptEnd"][0], j2["ptEnd"][1], 0, 0);
		cout << "\nline2 ptBeg=" << line2.ptBeg.x << ", " << line2.ptBeg.y << endl;
		cout << "line2 ptEnd=" << line2.ptEnd.x << ", " << line2.ptEnd.y << endl;
		cout << "line2 color=" << line2.color << endl;
	}

	LineObj line3;
	line3.objectType = 1;
	line3.makeStart(90, 1112, 3);
	line3.makeEnd(1314, 1516, 0, 0);

	RectangularObj rect1;
	rect1.objectType = 2;
	rect1.makeStart(87, 87, 4);
	rect1.makeEnd(95, 27, 0, 0);

	list<DrawObj*> DrawObjList;
	DrawObjList.push_back(new LineObj(newline));
	DrawObjList.push_back(new LineObj(line3));
	DrawObjList.push_back(new RectangularObj(rect1));

	//put each object to json
	json j3;
	for (auto& it : DrawObjList)  //Draw each object in DrawObjList
	{
		json jit;
		jit["objectType"] = it->objectType;
		jit["ptBeg"] = { it->ptBeg.x, it->ptBeg.y };
		jit["ptEnd"] = { it->ptEnd.x, it->ptEnd.y };
		jit["color"] = it->color;
		
		/*//test a list
		list<string> ls;//{ "aaa", "bbb", "", "ccc"};
		ls.push_back("aaa");
		ls.push_back("aaa");
		ls.push_back("");
		jit["text"] = ls;*/

		//cout << "iterator: type=" << it->objectType << " ptbeg=(" << it->ptBeg.x << ", " << it->ptBeg.x << ") color=" << it->color << endl;
		cout << "jit = " << jit << endl;
		j3.push_back(jit);
	}
	//cout << j3[2] << endl;
	//write to file
	outfile.open("mylist.json");
	cout << "\nWriting to the file" << endl;
	outfile << j3 << endl;

	//read from file
	json j4;
	infile.open("mylist.json");
	cout << "\nReading from the file" << endl;
	infile >> j4;
	cout << j4 << endl;
	infile.close();

	/*if (j3 == j4)
		cout << "j3 == j4 !\n";*/

	cout << "size of j4 is " << j4.size()<<endl;
	int i = 0;
	for (json::iterator it = j4.begin(); it != j4.end(); ++it)
	{
		cout << endl << *it << '\n';
		LineObj L2;
		L2.makeStart(it[i]["ptBeg"][0], it[i]["ptBeg"][1], it[i]["color"]);
		L2.makeEnd(it[i]["ptEnd"][0], it[i]["ptEnd"][1], 0, 0);
		cout << "L2 ptBeg=" << L2.ptBeg.x << ", " << L2.ptBeg.y << endl;
		cout << "L2 ptEnd=" << L2.ptEnd.x << ", " << L2.ptEnd.y << endl;
		cout << "L2 color=" << L2.color << endl;
		i++;
	}

	return 0;
}


