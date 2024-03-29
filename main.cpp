#include <iostream>
#include <vector>
using namespace std;

class Appliances
{
	string name;
	double power;
	unsigned int qty;
	bool status;
	bool conditions;
public:
	Appliances(string N, double P, unsigned int Q, bool S, bool C)
	{
		name = N;
		power = p;
		qty = Q;
		status = S;
		conditions = C;
	}
	// member functions here
};


class Room
{
	vector<Appliances> appliances;
	string name;
	unsigned int quantity;
public:
	Room(vector<Appliances> a, string n, unsigned int q)
	{
		appliances = a;
		name = n;
		quantity = q;
	}
	// member functions here
};

class Sections
{
	vector<Room> rooms;
	vector<Appliances> appliances;
	string name;
public:
	Sections(vector<Room> r, vector<Appliances> a)
	{
		rooms = r;
		appliances = a;
	}
	// member functions here
};

class Admin;

class PowerSource;

int main()
{

}