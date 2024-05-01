#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <variant>
#include <limits>
#include <iomanip>
#include <cstdlib>
using namespace std;
namespace Random {
	unsigned int get(int start, int End)
	{
		int value;
		srand(time(0));
		value = rand() % End;
		if (value < start) return value + start;
		else return value;
	}
};

string timeToString(time_t time) {
	char buffer[80];
	strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localtime(&time));
	return string(buffer);
}

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
	string& getName() { return name; }
	// Report function
	void report()
	{
		cout << "Report of appliance " << name << endl;
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
	// current status function
	void currentStatus()
	{
		cout << "Appliance: " << name << " - Status: ";
		if (status)
			cout << "On" << endl;
		else
			cout << "Off" << endl;
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
	vector<Appliances>& getAppliances() { return appliances; }
	void addAppliance()
	{
		appliances.push_back(inputAppliance());
	}
	void addAppliance(Appliances a)
	{
		appliances.push_back(a);
	}
	void currentStatus() // updated
	{
		cout << "Current Status of Appliances in Room " << name << ":" << endl;
		for (unsigned int i = 0; i < appliances.size(); ++i)
		{
			appliances[i].currentStatus();
		}
	}
	string& getName() { return name; }
	void report() // add synonymous function to other classes as well
	{
		cout << "Report of room " << name << endl;
		for (auto& appliance : appliances)
		{
			appliance.report();
		}
	}
	//        void DynamicScheduling(){
	//		for(auto& app: appliances){
	//			app.DynamicScheduling();
	//		}
	//	}
};

class Sections
{
	vector<Room> rooms;
	vector<Appliances> appliances;
	string name;
public:
	Sections() = default;
	Sections(vector<Room> r, vector<Appliances> a)
	{
		rooms = r;
		appliances = a;
	}
	Sections(vector<Room> r, vector<Appliances> a, string n)
	{
		rooms = r;
		appliances = a;
		name = n;
	}
	// member functions here
	void currentStatus()
	{
		cout << "Current Status of Appliances in Section " << name << ":" << endl;
		for (auto& app : appliances)
		{
			app.currentStatus();
		}
		for (auto& room : rooms)
		{
			room.currentStatus();
		}
	}
	vector<Room>& getRooms() { return rooms; }
	void addAppliance()
	{
		appliances.push_back(inputAppliance());
	}
	void report()
	{
		cout << "Report of section " << name << endl;
		for (auto& app : appliances)
		{
			app.report();
		}
		for (auto& room : rooms)
		{
			room.report();
		}
	}
	string& getName() { return name; }
	//void DynamicScheduling(){
	//	for(auto& room:rooms){
	//		room.DynamicScheduling();
	//	}
	//}
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
	string name;
	vector<Sections> sections;
	PowerSource Solar;
	PowerSource RegularSupply;
	vector<Room> Rooms;
	int maintenanceInterval; 
	time_t lastMaintenance;
public:
	Admin() {
		lastMaintenance = time(0) - 30 * 60 * 60 * 24 * 2;
		maintenanceInterval = 30;
	}
	Admin(vector<Sections> section,
		PowerSource solar,
		PowerSource regularSupply,
		vector<Room> rooms, string n)
	{
		sections = section;
		Solar = solar;
		RegularSupply = regularSupply;
		Rooms = rooms;
		lastMaintenance = time(0) - 30 * 60 * 60 * 24 * 2;
		maintenanceInterval = 30;
		name = n;
	}

	string& getName() { return name; }

	vector<Sections>& getSections () { return sections; } 
	void currentStatus()
	{
		cout << "Current Status of Appliances in Admin " << name << ":" << endl;
		for (auto& room : Rooms)
		{
			room.currentStatus();
		}
		for (auto& section : sections)
		{
			section.currentStatus();
		}
	}
	void performEarthingMaintenance() {
		time_t now = time(0);
		cout << "Performing earthing maintenance............................................... " << endl << endl;
		lastMaintenance = now; // Update last maintenance timestamp
		cout << "Earthing maintenance completed " << endl;
	}


	bool isMaintenanceDue() const {
		time_t now = time(0);
		int daysSinceLastMaintenance = (now - lastMaintenance) / (60 * 60 * 24); // Convert seconds to days
		return daysSinceLastMaintenance >= maintenanceInterval;
	}
	void EarthingMaintainence() {
		cout << "Performing dynamic scheduling of maintenance tasks..." << endl;
		cout << "Last Maintenance: " << timeToString(lastMaintenance) << endl;

		cout << "Maintenance Interval: " << maintenanceInterval << " days" << endl;

		if (isMaintenanceDue()) {
			bool ch;
			cout << "Maintenance is due...." << endl;
			ch = getBool("\nPress 1 to perform maintenance:");
			if (ch) { performEarthingMaintenance(); }
			else cout << "\nMaintenance is due yet." << endl;
		}
		else {
			cout << "Maintenance is not due yet." << endl;
		}
		cout << endl;
		cout << "Dynamic scheduling completed." << endl;
	}

	// member functions here
	void report()
	{
		cout << "Report of Admin " << name << endl;
		for (auto& room : Rooms)
		{
			room.report();
		}
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
	string Action_Taken;
	bool status;
	friend class ComplaintRecord;
public:
	Complaints(string complaintID,
		string complainant,
		string PhNo,
		string Description,
		string Date,
		bool status,
		string FaultLocation, string Action_Taken)
	{
		this->complaintID = complaintID;
		this->complainant = complainant;
		PhNo = PhNo;
		this->Description = Description;
		Date = Date;
		this->status = status;
		this->FaultLocation = FaultLocation;
		this->Action_Taken = Action_Taken;
	}
};

class ComplaintRecord {
	vector<Complaints> List;
public:
	ComplaintRecord()
	{
		Complaints c1("CN001", "Somesh Chandra", "6745910345", "Projector not Working", "25-03-24", 0, "LT-II 203", "NIL");
		Complaints c2("CN002", "Amit", "7459160345", "Sound System not Working", "28-03-24", 1, "LT-I 106", "Repaired");
		Complaints c3("CN003", "Aman", "4591034985", "Fan not Working", "31-03-24", 0, "CSE LAB-C123A", "NIL");
		Complaints c4("CN004", "Sam", "5910376945", "System-21 not Working", "05-04-24", 0, "CEF GENERIC", "NIL");
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
			<< "4.Replace & Repair." << endl
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
			case '4':
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
				cout << "\nAction_Taken:" << List[i].Action_Taken;
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
				cout << "\nAction_Taken:" << List[i].Action_Taken;
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
				cout << "\nAction_Taken:" << List[i].Action_Taken;
				cout << endl << endl;
			}
			break;

		case '4':
			bool select;
			string ID;
			int i = 0;
			ID = getString("\nEnter the Complaint ID:");
			while (1) {
				for (; i < List.size(); i++)
				{
					if (List[i].complaintID == ID) goto x;
				}
				i = 0;
				cout << "\nInvalid ID,Enter the ID again:";
				ID = getString("\nEnter the Complaint ID:");
			}
		x:
			select = getBool("\nEnter 1 to replace 0 to repair:");
			if (select) {
				List[i].Action_Taken = "Replaced";
				List[i].status = 1;
				cout << "\nApliance Replaced.......................................";
			}
			else {
				List[i].Action_Taken = "Repaired";
				List[i].status = 1;
				cout << "\nApliance Repaired.......................................";
			}
			break;


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


// functionality for location based function call 
			
variant<Admin, Sections, Room, Appliances> parseLocation(string& loc, vector<Admin>& obj, bool& success) // parse the location and return the reference of appropriate object based on it
{
	// location will be in the form A/B/C/D
	// we can ignore leading and ending spaces and capitalization
	success = true;
	int k = loc.size();
	std::transform(loc.begin(), loc.end(), loc.begin(), ::tolower);
	int i = 0;
	vector<string> processed; // get the processed words from string
	while (i < k)
	{
		string temp;
		while (i != k && loc[i] != '/')
		{
			if (loc[i] != ' ')
				temp += loc[i];
			i++;
		}
		i++;
		processed.push_back(temp);
	}
	int level = processed.size();
	Admin ret; // update codebase
	// find the right admin
	success = false;
	Admin& t1 = obj[0];
	for (auto& a : obj)
	{
		if (a.getName().compare(processed[0]) == 0)  // update codebase
		{
			t1 = a;
			success = true;
		}
	}
	if (success == false) return ret; // failed 
	if (level == 1) return t1;

	// find the right section
	success = false;
	vector<Sections>& temp1 = t1.getSections(); // update codebase
	Sections& t2 = temp1[0];
	for (auto& a : temp1)
	{
		if (a.getName().compare(processed[1]) == 0)
		{
			t2 = a;
			success = true;
		}
	}
	if (success == false) return ret; // failed 
	if (level == 2) return t2;

	// find the right room
	success = false;
	vector<Room>& temp2 = t2.getRooms(); // update codebase
	Room& t3 = temp2[0];
	for (auto& a : temp2)
	{
		if (a.getName().compare(processed[2]) == 0)
		{
			t3 = a;
			success = true;
		}
	}
	if (success == false) return ret; // failed 
	if (level == 3) return t3;

	// find the right appliance
	success = false;
	vector<Appliances>& temp3 = t3.getAppliances();
	Appliances& t4 = temp3[0];
	for (auto& a : temp3)
	{
		if (a.getName().compare(processed[3]) == 0)
		{
			t4 = a;
			success = true;
		}
	}
	if (success == false) return ret; // failed 
	if (level == 4) return t4;

	success = false; // failed
	return ret;
}


int main()
{
	ComplaintRecord c;

	//		Room a;
	//		Appliances b = Appliances("Bulb", 30, 2, 1, 1);
	//		a.addAppliance(b);
	//		a.report();
	//		a.DynamicScheduling();
	//		a.currentStatus();
	//		testing the parsing
	Appliances a("bulb", 20, 2, 1, 1);
	Room b({ a }, "class", 1);
	Sections d({ b }, {}, "lt1");
	Admin e({ d }, PowerSource(3, 2), PowerSource(3, 2), {}, "blocka");
	string l = "blockA/lt1";
	bool s = true;
	vector<Admin> pass = { e };
	variant< Admin, Sections, Room, Appliances> var = parseLocation(l, pass, s);
	if (s == false) return 0;
	// Define a lambda to call the report function
	auto reportFunc = [](auto& obj) {
		obj.report();
		};
	auto currentStatusFunc = [](auto& obj) {
		obj.currentStatus();
		};

	// Call the report function through std::visit
	visit(reportFunc, var);
	visit(currentStatusFunc, var);
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