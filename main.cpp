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
#include <Windows.h>
#define SIZE 160
using namespace std;

class Admin;
class Sections;
class Room;
class Appliances;
void Analysis(vector<Admin>& pass);
namespace Random {
	unsigned int get(int start, int End) {
		static bool initialized = false;
		if (!initialized) {
			srand(time(0));
			initialized = true;
		}

		// Ensure start is smaller than End
		if (start >= End) {
			return 0; // Or some appropriate error handling
		}

		int range = End - start + 1;
		int value = rand() % range + start;
		return value;
	}
};

string timeToString(time_t time) {
	char buffer[80];
	strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localtime(&time));
	return string(buffer);
}

// Error proof input functions
void clearScreen();
void putSpace(int);
void ignoreLine();
double getDouble(string s);
string getString(string a);
int getInt(string s);
bool getBool(string s);
string lowerString(string loc);

// Define color constants
enum ConsoleColor {
	Black = 0,
	Blue = 1,
	Green = 2,
	Cyan = 3,
	Red = 4,
	Magenta = 5,
	Brown = 6,
	LightGray = 7,
	DarkGray = 8,
	LightBlue = 9,
	LightGreen = 10,
	LightCyan = 11,
	LightRed = 12,
	LightMagenta = 13,
	Yellow = 14,
	White = 15
};

void setColor(ConsoleColor text = White, ConsoleColor background = Black) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)((background << 4) | text));
}

class Appliances
{
	unsigned int qty;
	bool status;
	bool conditions;
	vector <string> failure = { "Warning: risk of electric shock due to high current!", "Warning: risk of short circuit due to high power consumption!",
	"Warning: potential physical damage to electronic components!", "Warning: risk of malfunction!", "Warning: risk of over heating and equipment damage" };

public:
	string name;
	double power;
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
	void report(bool heir = false, int h = 2)
	{
		setColor(DarkGray, Black);
		if (heir && h == 2)
			cout << "|    |    |    |--  ";
		if (heir && h == 1)
			cout << "|    |    |--  ";

		setColor(LightBlue, Black);
		cout << "Appliance: " << name << endl;
		bool maintain = false;
		int code = Random::get(0, 3 * failure.size());
		int random = Random::get(50, 100);
		int random1 = Random::get(0, 100);
		setColor(DarkGray, Black);
		if (h == 1)
			cout << "|    |    |        > ";
		if (h == 2)
			cout << "|    |    |    |        > ";
		setColor(LightGreen, Black);
		cout << "Name: " << name << endl;
		setColor(DarkGray, Black);
		if (h == 1)
			cout << "|    |    |        > ";
		if (h == 2)
			cout << "|    |    |    |        > ";
		setColor(LightGreen, Black);
		cout << "Status: " << status << endl;
		setColor(DarkGray, Black);

		if (h == 1)
			cout << "|    |    |        > ";
		if (h == 2)
			cout << "|    |    |    |        > ";
		setColor(LightGreen, Black);
		cout << "Power Consumption: " << power << endl;
		setColor(DarkGray, Black);

		if (h == 1)
			cout << "|    |    |        > ";
		if (h == 2)
			cout << "|    |    |    |        > ";
		setColor(LightGreen, Black);
		cout << "Energy Efficiency: " << random << endl;
		if (code < failure.size())
		{
			conditions = 1;
			setColor(DarkGray, Black);

			if (h == 1)
				cout << "|    |    |        > ";
			if (h == 2)
				cout << "|    |    |    |        > ";
			setColor(LightGreen, Black);

			cout << failure[code] << endl;
			maintain = true;
		}
		setColor(DarkGray, Black);

		if (h == 1)
			cout << "|    |    |        > ";
		if (h == 2)
			cout << "|    |    |    |        > ";
		setColor(LightGreen, Black);
		cout << "Conditions: " << conditions << endl;
		setColor(DarkGray, Black);

		if (h == 1)
			cout << "|    |    |        > ";
		if (h == 2)
			cout << "|    |    |    |        > ";
		setColor(LightGreen, Black);
		if ((random1 >= 0 && random1 <= 10) || maintain)
			cout << "Maintainence required." << endl;
		else
			cout << "Maintainence not required. " << endl;
		setColor(DarkGray, Black);

		if (h == 1)
			cout << "|    |              ";
		if (h == 2)
			cout << "|    |    |    |          ";
		cout << endl;
		setColor();
	}
	// current status function
	void currentStatus()
	{
		setColor(LightBlue, Black);
		cout << "Appliance: " << name << " - Status: ";
		setColor(LightGreen, Black);
		if (status)
			cout << "On" << endl;
		else
			cout << "Off" << endl;
		setColor();
		cout << endl;
	}
	friend class Room;
	friend void Analysis(vector<Admin>& pass);
};

// forward declaration
Appliances inputAppliance();

class Room
{
	
	string name;
	unsigned int qty;
public:
	vector<Appliances> appliances;
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
		setColor(LightMagenta, Black);
		cout << "Current Status of Appliances in Room " << name << ":" << endl << endl;
		setColor();
		for (unsigned int i = 0; i < appliances.size(); ++i)
		{
			appliances[i].currentStatus();
		}
	}
	string& getName() { return name; }
	void report(bool heir = false, int h = 0) // add synonymous function to other classes as well
	{
		setColor(DarkGray, Black);
		if (heir && h == 2)
			cout << "|    |    |--  ";
		else if (heir && h == 1)
			cout << "|    |--   ";
		setColor(LightMagenta, Black);
		cout << "Room: " << name << endl;
		setColor(DarkGray, Black);
		if (heir && h == 2)
			cout << "|    |    |     ";
		else if (heir && h == 1)
			cout << "|    |   ";
		cout << endl;
		setColor();
		for (auto& appliance : appliances)
		{
			appliance.report(true, 2);
		}
	}
	friend void Analysis(vector<Admin>& pass);
};

class Sections
{
	
	vector<Appliances> appliances;
	string name;
public:
	vector<Room> rooms;
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
		setColor(LightGray, Black);
		cout << "Current Status of Appliances in Section " << name << ":" << endl << endl;
		setColor();
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
	vector<Appliances>& getAppliances() { return appliances; }
	void addAppliance()
	{
		appliances.push_back(inputAppliance());
	}
	void report(bool heir = false) // additional bool heir to provide tree structure
	{
		setColor(DarkGray, Black);
		if (heir)
			cout << "|    |--  ";

		setColor(LightGray, Black);
		cout << "Section: " << name << endl;
		setColor(DarkGray, Black);
		if (heir)
			cout << "|    |     ";
		cout << endl;
		setColor();
		for (auto& app : appliances)
		{
			app.report(true, 1);
		}
		for (auto& room : rooms)
		{
			room.report(true, 2);
		}
	}
	string& getName() { return name; }
	friend void Analysis(vector<Admin>& pass);
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

	vector<Sections>& getSections() { return sections; }
	void currentStatus()
	{
		setColor(Yellow, Black);
		cout << "Current Status of Appliances in Admin " << name << ":" << endl << endl;
		setColor();
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
			ch = getBool("\nPress 1 to perform maintenance: ");
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
		setColor(DarkGray, Black);
		cout << "|--  ";
		setColor(Yellow, Black);
		cout << "Admin: " << name << endl;
		setColor(DarkGray, Black);
		cout << "|";
		setColor();
		cout << endl;
		for (auto& room : Rooms)
		{
			room.report(true, 1);
		}
		for (auto& section : sections)
		{
			section.report(true);
		}
	}
	friend void Analysis(vector<Admin>& pass);
};

// Function to get current time as a string
string getCurrentTime() {
	time_t now = time(0);
	tm* timeinfo = localtime(&now);
	char buffer[80];
	strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", timeinfo);
	return buffer;
}

class SolarPanel {
private:
	int id;
	float output;
public:
	SolarPanel(int _id, float _output) : id(_id), output(_output) {}

	float getOutput() const {
		return output;
	}

	void setOutput(float _output) {
		output = _output;
	}

	int getId() const {
		return id;
	}
};

class SolarPlant {
private:
	vector<SolarPanel> panels;
	SolarPanel referencePanel;
public:
	SolarPlant(const SolarPanel& _referencePanel) : referencePanel(_referencePanel) {}

	void addPanel(const SolarPanel& panel) {
		panels.push_back(panel);
	}

	void showAllPanels() const {
		cout << "Solar Panels in the Plant:\n";
		for (const auto& panel : panels) {
			cout << "ID: " << panel.getId() << ", Output: " << panel.getOutput() << "W\n";
		}
	}

	float getPanelOutput(int panelId) const {
		for (const auto& panel : panels) {
			if (panel.getId() == panelId) {
				return panel.getOutput();
			}
		}
		return -1; // Panel not found
	}

	void addSolarPanel() {
		int id;
		double output = 3000;
		id = getInt("Enter the ID of the new solar panel: ");
		while (output < 10 || output > 2000)
			output = getDouble("Enter the output of the new solar panel (in watts) range(10, 2000): ");
		addPanel(SolarPanel(id, output));
		cout << "Solar panel with ID " << id << " and output " << output << "W added successfully." << endl;
	}

	void displayMenu() {
		cout << "Welcome to Solar Panel Management System\n";
		cout << "Current time: " << getCurrentTime() << endl;
		cout << "Choose an option:\n";
		cout << "1. Add a new solar panel\n";
		cout << "2. See the output of a specific panel\n";
		cout << "3. Show ouput of all panels\n";
	}

	void handleOption(int option) {
		switch (option) {
		case 1: {
			addSolarPanel();
			break;
		}
		case 2: {
			int panelId;
			panelId = getInt("Enter the ID of the panel to get its output: ");
			float output = getPanelOutput(panelId);
			if (output != -1) {
				cout << "Output of Solar Panel " << panelId << ": " << output << "W" << endl;
			}
			else {
				cout << "Solar Panel with ID " << panelId << " not found." << endl;
			}
			break;
		}
		case 3: {
			showAllPanels();
			break;
		}
		default:
			cout << "Invalid option. Please choose 1 or 2." << endl;
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
			goto ERRORE;
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
			ERRORE:
				fflush(stdin);
				cout << "\nInvalid input" << endl
					<< "Press the key again: ";
				ignoreLine();
				cin >> selector;
				if (!std::cin.eof() && std::cin.peek() != '\n')
				{
					goto ERRORE;
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
			ID = getString("\nEnter the Complaint ID: ");
			while (1) {
				for (; i < List.size(); i++)
				{
					if (List[i].complaintID == ID) goto x;
				}
				i = 0;
				cout << "\nInvalid ID,Enter the ID again: ";
				ID = getString("\nEnter the Complaint ID: ");
			}
		x:
			select = getBool("\nEnter 1 to replace 0 to repair: ");
			if (select) {
				List[i].Action_Taken = "Replaced";
				List[i].status = 1;
				cout << "\nAppliance Replaced.......................................";
			}
			else {
				List[i].Action_Taken = "Repaired";
				List[i].status = 1;
				cout << "\nAppliance Repaired.......................................";
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
	double power = 3000;
	int qty = -1;
	bool status;
	bool condition;
	name = getString("Enter the name of appliance: ");
	while (power < 0 || power > 2000)
		power = getDouble("Enter power | range(10, 2000): ");
	while (qty < 0)
		qty = getInt("Enter quantity: ");
	status = getBool("Enter status(1 / 0) : ");
	condition = getBool("Enter condition: (1 / 0): ");
	return Appliances(name, power, qty, status, condition);
}

bool removeAppliance(vector<Appliances>& app, string name) {
	for (auto it = app.begin(); it != app.end(); ) {
		if (lowerString(it->getName()) == lowerString(name)) {
			it = app.erase(it);
			cout << "Appliance removed successfully." << endl;
			return true;
		}
		else {
			++it;
		}
	}
	cout << "Appliance not found, please try again." << endl;
	return false;
}


// functionality for location based function call 

string lowerString(string loc)
{
	std::transform(loc.begin(), loc.end(), loc.begin(), ::tolower);
	return loc;
}

variant<Admin*, Sections*, Room*, Appliances*> parseLocationReference(string loc, vector<Admin>& obj, bool& success, vector<string>& processed) // parse the location and return the reference of appropriate object based on it
{
	// location will be in the form A/B/C/D
	// we can ignore leading and ending spaces and capitalization
	success = true;
	int k = loc.size();
	loc = lowerString(loc);
	int i = 0;
	processed.clear(); // get the processed words from string
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
	Admin* ret = nullptr; // update codebase
	// find the right admin
	success = false;
	Admin* t1 = nullptr;
	for (auto& a : obj)
	{
		if (lowerString(a.getName()).compare(lowerString(processed[0])) == 0)  // update codebase
		{
			t1 = &a;
			success = true;
			break;
		}
	}
	if (success == false) return ret; // failed 
	if (level == 1) return t1;

	// find the right section
	success = false;
	Sections* t2 = nullptr;
	vector<Sections>* temp1 = &(t1->getSections()); // update codebase
	for (auto& a : *temp1)
	{
		if (lowerString(a.getName()).compare(lowerString(processed[1])) == 0)
		{
			t2 = &a;
			success = true;
			break;
		}
	}
	if (success == false) return ret; // failed 
	if (level == 2) return t2;

	// find the right room
	success = false;
	Room* t3 = nullptr;
	vector<Room>* temp2 = &(t2->getRooms()); // update codebase
	for (auto& a : *temp2)
	{
		if (lowerString(a.getName()).compare(lowerString(processed[2])) == 0)
		{
			t3 = &a;
			success = true;
			break;
		}
	}
	if (success == false) return ret; // failed 
	if (level == 3) return t3;

	// find the right appliance
	success = false;
	Appliances* t4 = nullptr;
	vector<Appliances>* temp3 = &(t3->getAppliances());
	for (auto& a : *temp3)
	{
		if (lowerString(a.getName()).compare(lowerString(processed[3])) == 0)
		{
			t4 = &a;
			success = true;
			break;
		}
	}
	if (success == false) return ret; // failed 
	if (level == 4) return t4;

	success = false; // failed
	return ret;
}



variant<Admin, Sections, Room, Appliances> parseLocation(string loc, vector<Admin> obj, bool& success, vector<string>& processed) // parse the location and return the reference of appropriate object based on it
{
	// location will be in the form A/B/C/D
	// we can ignore leading and ending spaces and capitalization
	success = true;
	int k = loc.size();
	loc = lowerString(loc);
	int i = 0;
	processed.clear(); // get the processed words from string
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
		if (lowerString(a.getName()).compare(lowerString(processed[0])) == 0)  // update codebase
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
		if (lowerString(a.getName()).compare(lowerString(processed[1])) == 0)
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
		if (lowerString(a.getName()).compare(lowerString(processed[2])) == 0)
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
		if (lowerString(a.getName()).compare(lowerString(processed[3])) == 0)
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


// bools for different sections
bool u_main = false;
bool u_status = false;
bool u_blueprint = false;
bool u_analysis = false;
bool u_configure = false;
bool u_home = true;
bool running = true;

// enum for sections
namespace pages
{
	enum sect
	{
		Home = 0,
		BluePrint = 1,
		Maintainence = 2,
		Status = 3,
		Configure = 4,
		Analysis = 5
	};
}


void toggle(pages::sect type) // to toggle a single section on the screen
{
	clearScreen();
	u_main = false;
	u_status = false;
	u_blueprint = false;
	u_analysis = false;
	u_configure = false;
	u_home = false;
	switch (type)
	{
	case pages::Maintainence:
		u_main = true;
		break;
	case pages::Status:
		u_status = true;
		break;
	case pages::BluePrint:
		u_blueprint = true;
		break;
	case pages::Home:
		u_home = true;
		break;
	case pages::Analysis:
		u_analysis = true;
		break;
	case pages::Configure:
		u_configure = true;
		break;
	default:
		u_home = true;
	}
}

void putSpace(int s)
{
	for (int i = 0; i < s; i++)
	{
		cout << ' ';
	}
}

void putLine(int s)
{
	for (int i = 0; i < s; i++)
	{
		cout << endl;
	}
}

string locate = "Admin1";
variant< Admin, Sections, Room, Appliances> var;
vector<string> processed;

// Blueprint
void BluePrint()
{
	setColor(LightGreen, Black);

	cout << "\n--------------------------------------------------------------------Admin Block-----------------------------------------------------------------------------";
	cout << "\n                                                                         |                                                                                      ";
	cout << "\n                                                                         |                                                                                      ";
	cout << "\n                               -------------------------------------------------------------------------------------------";
	cout << "\n                               |                                         |                                               |                                        ";
	cout << "\n                               |                                         |                                               |                                        ";
	cout << "\n                        Lecture_Theatre_1                         Lecture_Theatre_2                                 Departments                                   ";
	cout << "\n                               |                                         |                                               |                                        ";
	cout << "\n                               |                                         |                                               |                                        ";
	cout << "\n                               -------------------------------------------------------------------------------------------                                         ";
	cout << "\n                               |                                         |                                               |                                        ";
	cout << "\n                               |                                         |                                               |                                        ";
	cout << "\n                             Rooms                                     Rooms                                           Rooms                                      ";
	cout << "\n                               |                                         |                                               |                                        ";
	cout << "\n                               |                                         |                                               |                                        ";
	cout << "\n                           Appliances                                Appliances                                      Appliances                                   ";
	cout << "\n                               |                                         |                                               |                                        ";
	cout << "\n                               |                                         |                                               |                                        ";
	cout << "\n                               -------------------------------------------------------------------------------------------";
	cout << "\n                                                                         |                                                                                       ";
	cout << "\n                                                                         |                                                                                        ";
	cout << "\n                                                                    PowerSource                                                                                   ";
	cout << "\n------------------------------------------------------------------------------------------------------------------------------------------------------------";
	setColor();
}

void refreshLocation(vector<Admin>& obj)
{
	bool s;
	vector<string> temp;
	var = parseLocation(locate, obj, s, temp);
}

int main()
{
	// populate the database here

	// appliances
	Appliances bulb("bulb", 20, 2, true, true);
	Appliances fan("fan", 30, 1, true, true);
	Appliances ac("ac", 1500, 1, false, false);
	Appliances laptop("laptop", 200, 10, true, true);
	Appliances printer("printer", 100, 1, false, false);
	//cabin
	Appliances computer_System("computer System", 275, 12, true, true);
	Appliances led("LEDs", 10, 12, true, true);
	Appliances Electronic_Kit("Electronic_Kit", 800, 16, false, true);
	Appliances Projector("Projector", 300, 1, false, true);
	Appliances CCTV("CCTV", 10, 2, true, true);
	Appliances Water_Coolers("Water_Cooler", 150, 2, true, true);
	Appliances Tube_Lights("Tube_Light", 40, 140, true, true);



	// Create rooms and add appliances to them
	Room room101({ bulb, fan }, "room101", 1);
	Room room201({ bulb, laptop, fan }, "room201", 1);
	Room room301({ bulb, fan, printer, laptop }, "room301", 1);

	//cabin appliances
	Room room103({ computer_System,fan,bulb,ac,printer,CCTV }, "room103", 1);
	Room room105({ computer_System,fan,bulb,ac,printer,CCTV }, "room105", 1);
	Room room106({ computer_System,fan,bulb,ac,printer,CCTV }, "room106", 1);
	Room room107({ computer_System,fan,bulb,ac,printer,CCTV }, "room107", 1);
	Room room108({ computer_System,fan,bulb,ac,printer,CCTV }, "room108", 1);
	Room room109({ computer_System,fan,bulb,ac,printer,CCTV }, "room109", 1);
	Room room110({ computer_System,fan,bulb,ac,printer,CCTV }, "room110", 1);
	Room room113({ computer_System,fan,bulb,ac,printer,CCTV }, "room113", 1);
	Room room204({ computer_System,fan,bulb,ac,printer,CCTV }, "room204", 1);
	Room room302({ computer_System, Projector, fan, CCTV }, "room302", 2);

	//Room room101({ bulb, fan }, "room101", 1);
	//Room room203({ bulb, laptop, fan }, "room201", 1);
	Room room202({ fan }, "room202", 1);
	//Room room301({ bulb, fan, printer, laptop }, "room301", 1);
	Room room213({ led, ac, fan }, "room213", 1);
	Room room203({ led,laptop }, "room203", 1);
	Room room115({ Projector, ac,printer }, "room115", 1);
	Room room211({ Projector, fan }, "room211", 1);
	Room room112({ led, fan }, "room112", 1);
	Room room111({ ac }, "room111", 1);
	Room room210({ CCTV,fan }, "room210", 1);
	Room room114({ Projector,computer_System,bulb }, "room114", 1);
	Room room214({ computer_System }, "room214", 1);
	// Create sections and add rooms to them
	Sections sectionA({ room101 }, { bulb, fan }, "LT1");
	Sections sectionB({ room201, room202 }, { printer, laptop }, "LT2");
	Sections sectionC({ room301 }, { ac, bulb, fan }, "LT3");
	Sections sectionD({ room103,room105,room106,room107,room108,room109,room110,room111,room113,room204,room302 }, { computer_System,fan,bulb,ac,printer,CCTV }, "Department");
	Sections sectionE({ room203, room115 }, { Projector, ac, printer }, "LT4");
	Sections sectionF({ room109 }, { CCTV, led, ac }, "LT5");
	Sections sectionG({ room106, room211 }, { Projector, fan }, "LT6");
	Sections sectionH({ room111, room210 }, { CCTV, fan }, "LT7");
	Sections sectionI({ room114 }, { Projector, computer_System, bulb }, "LT8");
	Sections sectionJ({ room214 }, { computer_System }, "LT9");
	Sections sectionK({ room213 }, { led, ac, fan }, "LT10");

	//Lab
	Room room303({ Electronic_Kit,Projector,CCTV,ac,Tube_Lights }, "room303", 1);

	Admin admin1({ sectionA, sectionB, sectionC, sectionD, sectionE }, PowerSource(3, 2), PowerSource(3, 2), { room101, room112, room303}, "Admin1");
	Admin admin2({ sectionF, sectionG, sectionH, sectionI, sectionJ, sectionK }, PowerSource(3, 2), PowerSource(3, 2), {room112}, "Admin2");

	// solar panel data
	SolarPanel referencePanel(1, 100.0); // Setting reference panel with id 1 and output 100.0
	SolarPlant solarPlant(referencePanel);

	// Predefined dummy solar panels
	vector<SolarPanel> dummyPanels = {
		SolarPanel(1, 95.0),
		SolarPanel(2, 105.0),
		SolarPanel(3, 90.0)
	};

	// Adding dummy panels to the solar plant
	for (const auto& panel : dummyPanels) {
		solarPlant.addPanel(panel);
	}

	vector<Admin> pass = { admin1, admin2 };
	var = parseLocation(locate, pass, running, processed);


	// lambdas to use 
	auto reportFunc = [](auto& obj) {
		obj.report();
		};
	auto currentStatusFunc = [](auto& obj) {
		obj.currentStatus();
		};
	auto getNameFunc = [](auto& obj) {
		return obj.getName();
		};

	// main interface loop
	while (running)
	{
		if (u_home)
		{
			setColor(Yellow, Black);
			int pad = 60;
			putSpace(pad);
			std::cout << "+----------------------------------+" << std::endl;
			putSpace(pad);
			std::cout << "|      POWER MANAGEMENT SYSTEM     |" << std::endl;
			putSpace(pad);
			std::cout << "+----------------------------------+" << std::endl;
			setColor();
			cout << "Location: " << locate << endl;
			setColor(Cyan, Black);
			putLine(3);
			cout << "1 Blueprint" << endl << endl;
			cout << "2 Maintainance" << endl << endl;
			cout << "3 Status" << endl << endl;
			cout << "4 Configure" << endl << endl;
			cout << "5 Analysis" << endl << endl;
			cout << "6 Change location" << endl << endl;
			cout << "7 Clear screen" << endl << endl;
			cout << "8 Exit" << endl << endl;
			setColor();
			putLine(3);
			int ask = getInt("Enter your choice: ");

			if (ask == 6) // for changing location
			{
				bool s = false;
				while (!s)
				{
					locate = getString("Enter location: ");
					var = parseLocation(locate, pass, s, processed); // to check if location is true or false
					if (!s) cout << "Location inaccessible, please write correct location" << endl;
				}
			}
			if (ask == 8)
			{
				running = false;
			}
			toggle(static_cast<pages::sect> (ask));
		}
		if (u_main)
		{
			setColor(LightCyan, Black);
			int pad = 60;
			putSpace(pad);
			std::cout << "+----------------------------------+" << std::endl;
			putSpace(pad);
			std::cout << "|           MAINTAINANCE           |" << std::endl;
			putSpace(pad);
			std::cout << "+----------------------------------+" << std::endl;
			setColor();
			cout << "Location: " << locate << endl;
			setColor(Cyan, Black);
			putLine(3);
			cout << "1 View Complaints" << endl << endl;
			cout << "2 Earthing maintainence" << endl << endl;
			cout << "3 Solar maintainence" << endl << endl;
			cout << "4 Clear screen" << endl << endl;
			cout << "5 Home" << endl << endl;
			cout << "6 Exit" << endl << endl;
			setColor();
			putLine(3);

			int ask = getInt("Enter your choice: ");
			if (ask == 1)
			{
				// complaints
				putLine(3);
				cout << "+-----------------+" << std::endl;
				cout << "|    Complaints   |" << std::endl;
				cout << "+-----------------+" << std::endl;
				ComplaintRecord comp;
				comp.display();
				string hold = getString("Enter anything to reset: ");
				clearScreen();
			}
			else if (ask == 2)
			{
				// Earthing
				putLine(3);
				cout << "+-----------------+" << std::endl;
				cout << "|     Earthing    |" << std::endl;
				cout << "+-----------------+" << std::endl;
				string a = processed[0];
				for (auto& ad : pass)
				{
					if (lowerString(ad.getName()).compare(a) == 0)
					{
						ad.EarthingMaintainence();
					}
				}
				string hold = getString("Enter anything to reset: ");
				clearScreen();
			}
			else if (ask == 3)
			{
				putLine(3);
				cout << "+-----------------+" << std::endl;
				cout << "|   Solar Panels  |" << std::endl;
				cout << "+-----------------+" << std::endl;
				solarPlant.displayMenu();
				int option = 5;
				while (option <= 0 || option > 3)
					option = getInt("Enter option: ");
				solarPlant.handleOption(option);
				string hold = getString("Enter anything to reset: ");
				clearScreen();
			}
			else if (ask == 4)
			{
				toggle(pages::Maintainence);
			}
			else if (ask == 5)
			{
				toggle(pages::Home);
			}
			else if (ask == 6)
			{
				running = false;
			}
			else
			{
				toggle(pages::Maintainence);
			}
		}
		if (u_status)
		{
			setColor(Brown, Black);
			int pad = 60;
			putSpace(pad);
			std::cout << "+----------------------------------+" << std::endl;
			putSpace(pad);
			std::cout << "|              STATUS              |" << std::endl;
			putSpace(pad);
			std::cout << "+----------------------------------+" << std::endl;
			setColor();
			cout << "Location: " << locate << endl;
			setColor(Cyan, Black);
			putLine(3);
			cout << "1 View Report" << endl << endl;
			cout << "2 View Current status" << endl << endl;
			cout << "3 Clear screen" << endl << endl;
			cout << "4 Home" << endl << endl;
			cout << "5 Exit" << endl << endl;
			setColor();
			putLine(3);
			int ask = getInt("Enter your choice: ");
			if (ask == 1)
			{
				putLine(3);
				cout << "+-----------------+" << std::endl;
				cout << "|      Report     |" << std::endl;
				cout << "+-----------------+" << std::endl;
				visit(reportFunc, var);
				string hold = getString("Enter anything to reset: ");
				clearScreen();
			}
			else if (ask == 2)
			{
				putLine(3);
				cout << "+-----------------+" << std::endl;
				cout << "|  Current Status |" << std::endl;
				cout << "+-----------------+" << std::endl;
				visit(currentStatusFunc, var);
				string hold = getString("Enter anything to reset: ");
				clearScreen();
			}
			else if (ask == 3)
			{
				toggle(pages::Status);
			}
			else if (ask == 4)
			{
				toggle(pages::Home);
			}
			else if (ask == 5)
			{
				running = false;
			}
			else
			{
				toggle(pages::Status);
			}
		}
		if (u_blueprint)
		{
			setColor(Blue, Black);
			int pad = 60;
			putSpace(pad);
			std::cout << "+----------------------------------+" << std::endl;
			putSpace(pad);
			std::cout << "|             BLUEPRINT            |" << std::endl;
			putSpace(pad);
			std::cout << "+----------------------------------+" << std::endl;
			setColor();
			cout << "Location: " << locate << endl;
			setColor(Cyan, Black);
			putLine(3);
			cout << "1 View General blueprint" << endl << endl;
			cout << "2 Search particular location" << endl << endl;
			cout << "3 Clear screen" << endl << endl;
			cout << "4 Home" << endl << endl;
			cout << "5 Exit" << endl << endl;
			setColor();
			putLine(3);
			int ask = getInt("Enter your choice: ");
			if (ask == 1)
			{
				BluePrint();
				string hold = getString("Enter anything to reset: ");
				clearScreen();
			}
			else if (ask == 2)
			{
				// implement location based list based name display
				bool s = false;
				variant< Admin, Sections, Room, Appliances> tvar;
				vector<string> proc;
				while (!s)
				{
					string tlocate = getString("Enter location: ");
					tvar = parseLocation(tlocate, pass, s, proc); // to check if location is true or false
					if (!s) cout << "Location inaccessible, please write correct location" << endl;
				}
				// we just want to traverse name of its tree
				int tlev = proc.size();
				if (tlev == 1)
				{
					cout << "Nothing to display, please search section or room" << endl;
				}
				else if (tlev == 2)
				{
					Sections ts = get<Sections>(tvar);
					vector<Appliances>& tapp = ts.getAppliances();
					cout << "\nAppliances in section " << ts.getName() << " are: \n\n";
					for (auto& app : tapp)
					{
						cout << "> " << app.getName() << endl;
					}
					cout << endl;
				}
				else if (tlev == 3)
				{
					Room tr = get<Room>(tvar);
					vector<Appliances>& tapp = tr.getAppliances();
					cout << "\nAppliances in room " << tr.getName() << " are: \n\n";
					for (auto& app : tapp)
					{
						cout << "> " << app.getName() << endl;
					}
					cout << endl;
				}
				else if (tlev == 4)
				{
					cout << "Nothing to display, please search section or room" << endl;
				}
				string hold = getString("Enter anything to reset: ");
				clearScreen();
			}
			else if (ask == 3)
			{
				toggle(pages::BluePrint);
			}
			else if (ask == 4)
			{
				toggle(pages::Home);
			}
			else if (ask == 5)
			{
				running = false;
			}
			else
			{
				toggle(pages::BluePrint);
			}
		}
		if (u_analysis)
		{
			setColor(LightGreen, Black);
			int pad = 60;
			putSpace(pad);
			std::cout << "+----------------------------------+" << std::endl;
			putSpace(pad);
			std::cout << "|             ANALYSIS             |" << std::endl;
			putSpace(pad);
			std::cout << "+----------------------------------+" << std::endl;
			setColor();
			putLine(3);
			Analysis(pass);
			string ask = getString("Enter to go home: ");
			toggle(pages::Home);
		}
		if (u_configure)
		{
			setColor(Red, Black);
			int pad = 60;
			putSpace(pad);
			std::cout << "+----------------------------------+" << std::endl;
			putSpace(pad);
			std::cout << "|          CONFIGURATION           |" << std::endl;
			putSpace(pad);
			std::cout << "+----------------------------------+" << std::endl;
			setColor();
			cout << "Location: " << locate << endl;
			setColor(Cyan, Black);
			putLine(3);
			cout << "1 Add Appliance" << endl << endl;
			cout << "2 Remove Appliance" << endl << endl;
			cout << "3 Clear screen" << endl << endl;
			cout << "4 Home" << endl << endl;
			cout << "5 Exit" << endl << endl;
			setColor();
			putLine(3);
			int ask = getInt("Enter your choice: ");
			if (ask == 1)
			{
				// Add appliance based on location
				bool s = false;
				variant< Admin*, Sections*, Room*, Appliances*> tvar;
				vector<string> proc;
				while (!s)
				{
					string tlocate = getString("Enter location where to add appliance: ");
					tvar = parseLocationReference(tlocate, pass, s, proc); // to check if location is true or false
					if (!s) cout << "Location inaccessible, please write correct location" << endl;
				}
				cout << endl;
				// we just want to traverse name of its tree
				int lev = proc.size();
				if (lev == 1 || lev == 4)
				{
					cout << "Cannot add appliances in " << processed[lev - 1] << endl;
				}
				else
				{
					// now do according to level 
					if (lev == 2) // section
					{
						Sections* ts = get<Sections*>(tvar);
						ts->addAppliance();
					}
					else if (lev == 3) // room
					{
						Room* tr = get<Room*>(tvar);
						tr->addAppliance();
					}
					cout << "Successfully added appliance!" << endl;
					refreshLocation(pass);
				}
				string hold = getString("Enter anything to reset: ");
				clearScreen();
			}
			else if (ask == 2)
			{
				// Remove appliance baseed on location
				bool s = false;
				variant< Admin*, Sections*, Room*, Appliances*> tvar;
				vector<string> proc;
				while (!s)
				{
					string tlocate = getString("Enter location where to remove appliance: ");
					tvar = parseLocationReference(tlocate, pass, s, proc); // to check if location is true or false
					if (!s) cout << "Location inaccessible, please write correct location" << endl;
				}
				cout << endl;
				int lev = proc.size();
				if (lev == 1 || lev == 4)
				{
					cout << "No appliance to remove here, please select section or room" << endl;
				}
				else
				{
					if (lev == 2)
					{
						Sections* ts = get<Sections*>(tvar);
						vector<Appliances>& aps = ts->getAppliances();
						cout << "Choose appliance to remove: " << endl;
						for (auto& appl : aps)
						{
							cout << "> " << appl.getName() << endl;
						}
						string aname;
						do
						{
							aname = getString("Enter appliance name: ");
						} while (!removeAppliance(aps, aname));
					}
					if (lev == 3)
					{
						Room* tr = get<Room*>(tvar);
						vector<Appliances>& apr = tr->getAppliances();
						cout << "Choose appliance to remove: " << endl;
						for (auto& appl : apr)
						{
							cout << "> " << appl.getName() << endl;
						}
						string aname;
						do
						{
							aname = getString("Enter appliance name: ");
						} while (!removeAppliance(apr, aname));
					}
					refreshLocation(pass);
				}
				string hold = getString("Enter anything to reset: ");
				clearScreen();
			}
			else if (ask == 3)
			{
				toggle(pages::Configure);
			}
			else if (ask == 4)
			{
				toggle(pages::Home);
			}
			else if (ask == 5)
			{
				running = false;
			}
			else
			{
				toggle(pages::Configure);
			}
		}
	}
	putLine(25);
	putSpace(15);
	setColor(Black, Green);
	putSpace(40);
	cout << "Thank you for using Power Management System.";
	putSpace(40);
	setColor();
	putLine(25);
}


void clearScreen() {
	std::cout << "\033[2J\033[1;1H"; // ANSI escape sequence to clear screen
}

// Error check functionalities
void ignoreLine()
{
	std::cin.ignore(100, '\n');
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

void Analysis(vector<Admin>& pass)
{
	//Data inputs
	double netPower_daily = 0, netPower_annualy, netPower_monthly, GreenPower_Daily = 0, GreenPower_Monthly, GreenPower_Annually;

	vector<pair<string, double>> Appliance_Power;
	string MinName, MaxName;
	double MinPower, MaxPower;
	double Predicted_daily_cost, Predicted_monthly_cost, Predicted_annual_cost;

	double Last_daily_cost, Last_monthly_cost, Last_annual_cost, pdaily, pmonthly, pannual;

	double carbon_footprint_daily, carbon_footprint_monthly, carbon_footprint_annualy;

	vector<SolarPanel> dummyPanels = {
		SolarPanel(1, 95.0),
		SolarPanel(2, 105.0),
		SolarPanel(3, 90.0)
	};

	double Energy_Intensity_daily, Energy_Intensity_monthly, Energy_Intensity_annualy;
	//Data Processing

		for (int i = 0; i < dummyPanels.size(); i++)
		{
			GreenPower_Daily += dummyPanels[i].getOutput();
		}


		for (int i = 0; i < pass.size(); i++)//Admin Loop
			for (int j = 0; j < pass[i].sections.size(); j++)//Section Loop
				for (int k = 0; k < pass[i].sections[j].rooms.size(); k++)//room Loop
					for (int m = 0; m < pass[i].sections[j].rooms[k].appliances.size(); m++)//appliances loop
					{
						netPower_daily += pass[i].sections[j].rooms[k].appliances[m].power;
						Appliance_Power.push_back(pair<string, double>(pass[i].sections[j].rooms[k].appliances[m].name, pass[i].sections[j].rooms[k].appliances[m].power));
					}


		MinPower = MaxPower = Appliance_Power[0].second;
	MinName = MaxName = Appliance_Power[0].first;
	for (int i = 0; i < Appliance_Power.size(); i++)
	{
		if (Appliance_Power[i].second > MaxPower)
		{
			MaxPower = Appliance_Power[i].second;
			MaxName = Appliance_Power[i].first;
		}
		if (Appliance_Power[i].second < MinPower)
		{
			MinPower = Appliance_Power[i].second;
			MinName = Appliance_Power[i].first;

		}
	}

		Predicted_daily_cost = netPower_daily * 7;
	carbon_footprint_daily = 0.82 * netPower_daily;
	Energy_Intensity_daily = netPower_daily / SIZE;
	Last_daily_cost = Energy_Intensity_daily - Energy_Intensity_daily * 0.15;
	pdaily = ((Energy_Intensity_daily - Last_daily_cost) / Energy_Intensity_daily) * 100;

		Predicted_monthly_cost = Predicted_daily_cost * 30;
	netPower_monthly = netPower_daily * 30;
	carbon_footprint_monthly = 30 * carbon_footprint_daily;
	GreenPower_Monthly = GreenPower_Daily * 30;
	Energy_Intensity_monthly = Energy_Intensity_daily * 30;
	Last_monthly_cost = Energy_Intensity_monthly + Energy_Intensity_monthly * 0.42;
	pmonthly = ((Energy_Intensity_monthly - Last_monthly_cost) / Energy_Intensity_monthly) * 100;

		Predicted_annual_cost = 12 * Predicted_monthly_cost;
	netPower_annualy = netPower_monthly * 12;
	carbon_footprint_annualy = carbon_footprint_monthly * (12);
	GreenPower_Annually = GreenPower_Monthly * 12;
	Energy_Intensity_annualy = Energy_Intensity_monthly * 30;
	Last_annual_cost = Energy_Intensity_annualy - Energy_Intensity_annualy * 0.1125;
	pannual = ((Energy_Intensity_annualy - Last_annual_cost) / Energy_Intensity_annualy) * 100;



	setColor(LightCyan, Black);
	cout << "		+--------------------------------------------------------------------------------------------------------+" << std::endl;
	cout << "		|                                             Analysis Report                                            |" << std::endl;
	cout << "		+--------------------------------------------------------------------------------------------------------+" << std::endl;
	cout << "		+----------------------------------------------Regular Power---------------------------------------------+" << std::endl;
	cout << "		|1.|               Daily Power Consumption           |       " << netPower_daily << "KWh                                     " << std::endl;
	cout << "		|2.|             Monthly Power Consumption           |       " << netPower_monthly << "KWh                                    " << std::endl;
	cout << "		|3.|            Annually Power Consumption           |       " << netPower_annualy << "KWh                                   " << std::endl;
	cout << "		|4.|            Max power consuming device           |       " << MaxName << "-" << MaxPower << "W                                    " << std::endl;
	cout << "		|5.|            Min power consuming device           |       " << MinName << "-" << MinPower << "W                                    " << std::endl;
	cout << "		+------------------------------------------------Expenses------------------------------------------------+" << std::endl;
	cout << "		|1.|                  Predicted Daily Cost           |       Rs." << Predicted_daily_cost << "                                    " << std::endl;
	cout << "		|2.|                Predicted Monthly Cost           |       Rs." << Predicted_monthly_cost << "                                   " << std::endl;
	cout << "		|3.|                Predicted Annually Cost          |       Rs." << Predicted_annual_cost << "                              " << std::endl;
	cout << "		|4.|                     Previous Day Cost           |       Rs." << setprecision(2) << Last_daily_cost << "                                       " << std::endl;
	cout << "		|5.|                   Previous Month Cost           |       Rs." << Last_monthly_cost << "                                 " << std::endl;
	cout << "		|6.|                        Last Year Cost           |       Rs." << Last_annual_cost << "                                 " << std::endl;
	cout << "		|7.|               Percentage change daily           |       " << pdaily << "%                                         " << std::endl;
	cout << "		|8.|             Percentage change monthly           |       " << pmonthly << "%                                        " << std::endl;
	cout << "		|9.|             Percentage change annualy           |       " << pannual << "%                                         " << std::endl;
	cout << "		+-----------------------------------------------Green Power----------------------------------------------+" << std::endl;
	cout << "		|1.|               Daily Power Consumption           |       " << GreenPower_Daily << "KWh                                 " << std::endl;
	cout << "		|2.|             Monthly Power Consumption           |       " << GreenPower_Monthly << "KWh                                   " << std::endl;
	cout << "		|3.|            Annually Power Consumption           |       " << GreenPower_Annually << "KWh                                 " << std::endl;
	cout << "		+---------------------------------------------Carbon Footprint-------------------------------------------+" << std::endl;
	cout << "		|1.|               Daily Carbon footprint            |       " << carbon_footprint_daily << "Kg                                  " << std::endl;
	cout << "		|2.|             Monthly Carbon footprint            |       " << carbon_footprint_monthly << "Kg                                  " << std::endl;
	cout << "		|3.|            Annually Carbon footprint            |       " << carbon_footprint_annualy << "Kg                                  " << std::endl;
	cout << "		+---------------------------------------------Energy Intensity-------------------------------------------+" << std::endl;
	cout << "		|1.|               Daily Energy Intensity            |       " << Energy_Intensity_daily << "KWh/Acre                                  " << std::endl;
	cout << "		|2.|             Monthly Energy Intensity            |       " << Energy_Intensity_monthly << "KWh/Acre                            " << std::endl;
	cout << "		|3.|            Annually Energy Intensity            |       " << Energy_Intensity_annualy << "KWh/Acre                            " << std::endl;
	cout << "		+--------------------------------------------------------------------------------------------------------+" << std::endl;
	setColor();
}