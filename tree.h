#ifndef TREE_H
#define TREE_H

#include<vector>
#include<string>
using namespace std;

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
	int val1;
	int val2;
	Property(int pname, int val1):pname(pname),val1(val1),val2(0) {}
	Property(int pname, int val1, int val2):pname(pname),val1(val1),val2(val2) {}
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

class Circle_stmt:public FB_stmt
{
public:
	vector<Property*> *properties;
	Circle_stmt(vector<Property*> *properties):FB_stmt(4),properties(properties) {}
};

#endif
