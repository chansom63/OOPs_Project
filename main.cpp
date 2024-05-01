#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>
#include <limits>
#include <iomanip>
#include "Random.h"
using namespace std;

// Error proof input functions
void clearScreen();
void ignoreLine();
double getDouble(string s);
string getString(string a);
int getInt(string s);
bool getBool(string s);

class Appliances
{
	string name;
	double power;
	unsigned int qty;
	bool status;
	bool conditions;
	vector <string> failure = { "Warning: risk of electric shock due to high current!", "Warning: risk of short circuit due to high power consumption!",
	"Warning: potential physical damage to electronic components!", "Warning: risk of any malfunction!", "Warning: risk of over heating and equipment damage" };

public:
	Appliances() = default;
	Appliances(string N, double P, unsigned int Q, bool S, bool C)
	{
		name = N;
		power = P;
		qty = Q;
		status = S;
		conditions = C;
	}
	// member functions here
	// Report function
	void report()
	{
		cout << "------------------------------------------------------------" << endl;
		bool maintain = false;
		int code = Random::get(0, 2 * failure.size());
		int random = Random::get(50, 100);
		int random1 = Random::get(0, 100);
		cout << "Name: " << name << endl;
		cout << "Status: " << status << endl;
		cout << "Power Consumption: " << power << endl <<
			"Energy Efficiency: " << random << endl;
		if (code < failure.size())
		{
			conditions = 1;
			cout << failure[code] << endl;
			maintain = true;
		}
		cout << "Conditions: " << conditions << endl;

		if ((random1 >= 0 && random1 <= 10) || maintain)
			cout << "Maintainence required." << endl;
		else
			cout << "Maintainence not required. " << endl;
	}
	friend class Room;
};

// forward declaration
Appliances inputAppliance();

class Room
{
	vector<Appliances> appliances;
	string name;
	unsigned int qty;
public:
	Room() = default;
	Room(vector<Appliances> a, string n, unsigned int q)
	{
		appliances = a;
		name = n;
		qty = q;
	}
	// member functions here
	void addAppliance()
	{
		appliances.push_back(inputAppliance());
	}
	void addAppliance(Appliances a)
	{
		appliances.push_back(a);
	}
	void currentStatus()
	{
		cout << "Current Status of Appliances in Room " << name << ":" << endl;
		for (unsigned int i = 0; i < appliances.size(); ++i)
		{
			cout << "Appliance: " << appliances[i].name << " - Status: ";
			if (appliances[i].status)
				cout << "On" << endl;
			else
				cout << "Off" << endl;
		}
	}
	void report() // add synonymous function to other classes as well
	{
		for (auto& appliance : appliances)
		{
			appliance.report();
		}
	}
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
	void addAppliance()
	{
		appliances.push_back(inputAppliance());
	}
	void report()
	{
		for (auto& room : rooms)
		{
			room.report();
		}
	}
};

class PowerSource
{
	unsigned int qty;
	double PowerRating;
public:
	PowerSource() {}
	PowerSource(unsigned int q, double rate)
	{
		qty = q;
		PowerRating = rate;
	}
	// member functions here
};

class Admin
{
	vector<Sections> sections;
	PowerSource Solar;
	PowerSource RegularSupply;
	vector<Room> Rooms;
public:
	Admin(vector<Sections> section,
		PowerSource solar,
		PowerSource regularSupply,
		vector<Room> rooms)
	{
		sections = section;
		Solar = solar;
		RegularSupply = regularSupply;
		Rooms = rooms;
	}
	// member functions here
	void report()
	{
		for (auto& section : sections)
		{
			section.report();
		}
	}
};

class ComplaintRecord;

class Complaints
{
	string complaintID;
	string complainant;
	string PhNo;
	string Description;
	string FaultLocation;
	string Date;
	bool status;
	friend class ComplaintRecord;
public:
	Complaints(string complaintID,
		string complainant,
		string PhNo,
		string Description,
		string Date,
		bool status,
		string FaultLocation)
	{
		this->complaintID = complaintID;
		this->complainant = complainant;
		PhNo = PhNo;
		this->Description = Description;
		Date = Date;
		this->status = status;
		this->FaultLocation = FaultLocation;
	}
};

class ComplaintRecord {
	vector<Complaints> List;
public:
	ComplaintRecord()
	{
		Complaints c1("CN001", "Somesh Chandra", "6745910345", "Projector not Working", "25-03-24", 0, "LT-II 203");
		Complaints c2("CN002", "Amit", "7459160345", "Sound System not Working", "28-03-24", 1, "LT-I 106");
		Complaints c3("CN003", "Aman", "4591034985", "Fan not Working", "31-03-24", 0, "CSE LAB-C123A");
		Complaints c4("CN004", "Sam", "5910376945", "System-21 not Working", "05-04-24", 0, "CEF GENERIC");
		List.push_back(c1);
		List.push_back(c2);
		List.push_back(c3);
		List.push_back(c4);
	}

	void display()
	{
		char selector; int check = 0;
		cout << "\n\n---------------------------------Complaint Portal----------------------------------------------";
		if (List.size() == 0) { cout << "\nNo complaints exist"; return; }
		cout << "\nEnter the following keys to view Complaints:-" << endl
			<< "1.View Pending complaints." << endl
			<< "2.View Resolved complaints." << endl
			<< "3.View all Complaints" << endl
			<< "Press the key: " << endl;
		cin >> selector;
		if (!std::cin.eof() && std::cin.peek() != '\n')
		{
			goto ERROR;
		}

		//Checker block
		while (!check)
		{
			switch (selector)
			{
			case '1':
			case '2':
			case '3':
				check = 1; break;
			default:
			ERROR:
				fflush(stdin);
				cout << "\nInvalid input" << endl
					<< "Press the key again: ";
				ignoreLine();
				cin >> selector;
				if (!std::cin.eof() && std::cin.peek() != '\n')
				{
					goto ERROR;
				}
			}
		}
		switch (selector)
		{
		case '1':
			for (int i = 0; i < List.size(); i++)
			{
				if (List[i].status != 0) continue;
				cout << "\nComplaint ID:" << List[i].complaintID;
				cout << "\nComplainant:" << List[i].complainant;
				cout << "\nPhoneNo.:" << List[i].PhNo;
				cout << "\nDescription:" << List[i].Description;
				cout << "\nDate Of Complaint:" << List[i].Date;
				cout << "\nFault Location:" << List[i].FaultLocation;
				cout << "\nstatus:";
				(List[i].status) ? cout << "Resolved" : cout << "Pending";
				cout << endl << endl;
			}
			break;
		case '2':
			for (int i = 0; i < List.size(); i++)
			{
				if (List[i].status != 1) continue;
				cout << "\nComplaint ID:" << List[i].complaintID;
				cout << "\nComplainant:" << List[i].complainant;
				cout << "\nPhoneNo.:" << List[i].PhNo;
				cout << "\nDescription:" << List[i].Description;
				cout << "\nDate Of Complaint:" << List[i].Date;
				cout << "\nFault Location:" << List[i].FaultLocation;
				cout << "\nstatus:";
				(List[i].status) ? cout << "Resolved" : cout << "Pending";
				cout << endl << endl;
			}
			break;

		case '3':
			for (int i = 0; i < List.size(); i++)
			{
				cout << "\nComplaint ID:" << List[i].complaintID;
				cout << "\nComplainant:" << List[i].complainant;
				cout << "\nPhoneNo.:" << List[i].PhNo;
				cout << "\nDescription:" << List[i].Description;
				cout << "\nDate Of Complaint:" << List[i].Date;
				cout << "\nFault Location:" << List[i].FaultLocation;
				cout << "\nstatus:";
				(List[i].status) ? cout << "Resolved" : cout << "Pending";
				cout << endl << endl;
			}
			break;
		default:
			cout << "\nInvalid Input";
		}
		cout << "\n\n-----------------------------------------------------------------------------------------------\n";
	}
};

// Input function for add appliances functionality

Appliances inputAppliance()
{
	cout << "+-----------------+" << std::endl;
	cout << "|  Add Appliance  |" << std::endl;
	cout << "+-----------------+" << std::endl;
	string name;
	double power;
	int qty = -1;
	bool status;
	bool condition;
	name = getString("Enter the name of appliance: ");
	power = getDouble("Enter power: ");
	while (qty < 0)
		qty = getInt("Enter quantity: ");
	status = getBool("Enter status(1 / 0) : ");
	condition = getBool("Enter condition: (1 / 0): ");
	return Appliances(name, power, qty, status, condition);
}


int main()
{
	while (true)
	{
		Room a;
		Appliances b = Appliances("Bulb", 30, 2, 1, 1);
		a.addAppliance(b);
		a.report();
		a.currentStatus();
		bool clear;
		clear = getBool("enter 1 to clear ");
		if (clear)
			clearScreen();
	}
}


void clearScreen() {
	std::cout << "\033[2J\033[1;1H"; // ANSI escape sequence to clear screen
}

// Error check functionalities
void ignoreLine()
{
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

double getDouble(string s)
{
	while (true)
	{
		double x{};
		cout << s;
		std::cin >> x;

		if (!std::cin)
		{
			std::cin.clear();
			ignoreLine();
			std::cout << "Input is invalid. Please try again.\n";
			continue;
		}
		if (!std::cin.eof() && std::cin.peek() != '\n')
		{
			ignoreLine(); // remove extraneous input
			std::cout << "Input is invalid. Please try again.\n";
			continue;
		}
		return x;
	}
}

string getString(string a)
{
	string s{};
	cout << a;
	getline(cin >> ws, s);
	return s;
}

int getInt(string s)
{
	while (true)
	{
		int x{};
		cout << s;
		std::cin >> x;

		if (!std::cin)
		{
			std::cin.clear();
			ignoreLine();
			std::cout << "Input is invalid. Please try again.\n";
			continue;
		}
		if (!std::cin.eof() && std::cin.peek() != '\n')
		{
			ignoreLine(); // remove extraneous input
			std::cout << "Input is invalid. Please try again.\n";
			continue;
		}
		return x;
	}
}

bool getBool(string s)
{
	while (true)
	{
		bool x{};
		cout << s;
		std::cin >> x;

		if (!std::cin)
		{
			std::cin.clear();
			ignoreLine();
			std::cout << "Input is invalid. Please try again.\n";
			continue;
		}
		if (!std::cin.eof() && std::cin.peek() != '\n')
		{
			ignoreLine(); // remove extraneous input
			std::cout << "Input is invalid. Please try again.\n";
			continue;
		}
		return x;
	}
}