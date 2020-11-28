#ifndef TREE_H
#define TREE_H

#include<vector>
#include<string>
#include<iostream>
using namespace std;

#define HEIGHT_T 1
#define WIDTH_T 2
#define FRAME_RATE_T 3
#define TOTAL_FRAMES_T 4
#define IMAGE_NAME_T 5
#define FRAME_START_T 6
#define FRAME_END_T 7
#define START_POS_T 8
#define END_POS_T 9
#define SIDE_T 10

class FB_stmt
{
public:
	int type;
	FB_stmt(int type):type(type) {}
};

class Property
{
public:
	int pname;
	string *str;
	int val1;
	int val2;
	Property(int pname, int val1):pname(pname),val1(val1),val2(0) {cout << pname << " " << val1 << " " << val2 << endl;}
	Property(int pname, string *str):pname(pname),str(str),val1(0),val2(0)  {cout << pname << " " << val1 << " " << val2 << endl;}
	Property(int pname, int val1, int val2):pname(pname),val1(val1),val2(val2)  {cout << pname << " " << val1 << " " << val2 << endl;}
};

class Base_stmt:public FB_stmt
{
public:
	vector<Property*> *properties;
	Base_stmt(vector<Property*> *properties):FB_stmt(1),properties(properties) {}
};

class Still_stmt:public FB_stmt
{
public:
	vector<Property*> *properties;
	Still_stmt(vector<Property*> *properties):FB_stmt(2),properties(properties) {}
};

class Line_stmt:public FB_stmt
{
public:
	vector<Property*> *properties;
	Line_stmt(vector<Property*> *properties):FB_stmt(3),properties(properties) {}
};

class Square_stmt:public FB_stmt
{
public:
	vector<Property*> *properties;
	Square_stmt(vector<Property*> *properties):FB_stmt(4),properties(properties) {}
};

#endif
