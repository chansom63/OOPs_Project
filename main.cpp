#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>
#include <limits>
#include <iomanip>
#include <cstdlib>
#include <unordered_map>
#include <limits>
const int SIZE=160;

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

class Appliances;
class Room;
class Sections;
class Admin;
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

void Analysis(vector<Admin>&pass);

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
class Appliances
{
	string name;
	double power;
	unsigned int qty;
	bool status;
	bool conditions;
	int maintenanceInterval;
	time_t lastMaintenance;
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
		lastMaintenance = time(0);

	}
	// member functions here
	void getInterval(int interval) {
		maintenanceInterval = interval;
	}
	void performEarthingMaintenance() {
		time_t now = time(0);
		cout << "Performing earthing maintenance for appliance: " << name << endl;
		lastMaintenance = now; // Update last maintenance timestamp
		cout << "Earthing maintenance completed for appliance: " << name << endl;
	}


	bool isMaintenanceDue() const {
		time_t now = time(0);
		int daysSinceLastMaintenance = (now - lastMaintenance) / (60 * 60 * 24); // Convert seconds to days
		return daysSinceLastMaintenance >= maintenanceInterval;
	}
	void DynamicScheduling() {
		cout << "Performing dynamic scheduling of maintenance tasks..." << endl;

		cout << "Appliance Name: " << name << endl;
		cout << "Last Maintenance: " << timeToString(lastMaintenance) << endl;

		cout << "Maintenance Interval: " << maintenanceInterval << " days" << endl;

		if (isMaintenanceDue()) {
			cout << "Maintenance is due. Performing maintenance..." << endl;
			performEarthingMaintenance(); // You need to implement this method in the Appliance class
			cout << "Maintenance completed." << endl;
		}
		else {
			cout << "Maintenance is not due yet." << endl;
		}
		cout << endl;
	}

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
friend void Analysis(vector<Admin> &pass);
};




// Report function


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
	void DynamicScheduling() {
		for (auto& app : appliances) {
			app.DynamicScheduling();
		}
	}
	friend class Sections;
	friend void Analysis(vector<Admin> &pass);
};

class Sections
{
	vector<Room> rooms;
	vector<Appliances> appliances;
	string name;
public:
	Sections(vector<Room> r, vector<Appliances> a,string name)
	{
		rooms = r;
		appliances = a;
		this->name=name;
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
	void DynamicScheduling() {
		for (auto& room : rooms) {
			room.DynamicScheduling();
		}
	}
	friend class Admin;
	friend void Analysis(vector<Admin> &pass);
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
	PowerSource Solar;
	PowerSource RegularSupply;
	vector<Room> Rooms;
public:

	vector<Sections> sections;
	Admin(vector<Sections> section,
		PowerSource solar,
		PowerSource regularSupply,
		vector<Room> rooms,string name)
	{
		sections = section;
		Solar = solar;
		RegularSupply = regularSupply;
		Rooms = rooms;
		this->name=name;
	}
	// member functions here
	void report()
	{
		for (auto& section : sections)
		{
			section.report();
		}
	}
	void DynamicScheduling() {
		for (auto& section : sections) {
			section.DynamicScheduling();
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
    Appliances bulb("bulb", 20, 2, true, true);
	Appliances fan("fan", 30, 1, true, true);
	Appliances ac("ac", 1500, 1, false, false);
	Appliances laptop("laptop", 200, 10, true, true);
	Appliances printer("printer", 100, 1, false, false);

	// Create rooms and add appliances to them
	Room room101({ bulb, fan }, "room101", 1);
	Room room102({ fan, ac }, "room102", 1);
	Room room201({ bulb, laptop, fan }, "room201", 1);
	Room room202({ fan }, "room202", 1);
	Room room301({ bulb, fan, printer, laptop }, "room301", 1);

	// Create sections and add rooms to them
	Sections sectionA({ room101, room102 }, { bulb, fan }, "sectiona");
	Sections sectionB({ room201, room202 }, { printer, laptop }, "sectionb");
	Sections sectionC({ room301 }, { ac, bulb, fan }, "sectionc");

	// Create admins and add sections to them
	Admin admin1({ sectionA, sectionB }, PowerSource(3, 2), PowerSource(3, 2), {room101}, "Admin1");
	Admin admin2({ sectionC }, PowerSource(3, 2), PowerSource(3, 2), {}, "Admin2");

     vector<Admin> pass = { admin1, admin2 };
	while (true)
	{
	    Analysis(pass);

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

void Analysis(vector<Admin>&pass)
{
    //Data inputs
    double netPower_daily=0,netPower_annualy,netPower_monthly,GreenPower_Daily=0,GreenPower_Monthly,GreenPower_Annualy;

    vector<pair<string,double>> Appliance_Power;
    string MinName,MaxName;
    double MinPower,MaxPower;
    double Predicted_daily_cost,Predicted_monthly_cost, Predicted_annual_cost;

     double Last_daily_cost,Last_monthly_cost, Last_annual_cost, pdaily, pmonthly, pannual;

    double carbon_footprint_daily, carbon_footprint_monthly, carbon_footprint_annualy;

    vector<SolarPanel> dummyPanels = {
		SolarPanel(1, 95.0),
		SolarPanel(2, 105.0),
		SolarPanel(3, 90.0)
	};

	double Energy_Intensity_daily,Energy_Intensity_monthly, Energy_Intensity_annualy;
	//Data Processing

	/*!!1.Data processing of solar maintenance*/
	for(int i=0;i<dummyPanels.size();i++)
    {
        GreenPower_Daily+=dummyPanels[i].getOutput();
    }


    /*!!2.Data processing of appliance maintenance*/
    for(int i=0;i<pass.size();i++)//Admin Loop
        for(int j=0;j<pass[i].sections.size();j++)//Section Loop
            for(int k=0;k<pass[i].sections[j].rooms.size();k++)//room Loop
                for(int m=0;m<pass[i].sections[j].rooms[k].appliances.size();m++)//appliances loop
                    {netPower_daily+=pass[i].sections[j].rooms[k].appliances[m].power;
                        Appliance_Power.push_back(pair<string,double> (pass[i].sections[j].rooms[k].appliances[m].name,pass[i].sections[j].rooms[k].appliances[m].power));
                    }


    /*!!3.Minimum and maximum calculation*/
    MinPower=MaxPower=Appliance_Power[0].second;
    MinName=MaxName=Appliance_Power[0].first;
    for(int i=0;i<Appliance_Power.size();i++)
    {
        if(Appliance_Power[i].second>MaxPower)
        {
            MaxPower=Appliance_Power[i].second;
            MaxName=Appliance_Power[i].first;
        }
        if(Appliance_Power[i].second<MinPower)
        {
            MinPower=Appliance_Power[i].second;
            MinName=Appliance_Power[i].first;

        }
    }

    /*Daily data*/
     Predicted_daily_cost=netPower_daily*7;
     carbon_footprint_daily=0.82*netPower_daily;
     Energy_Intensity_daily=netPower_daily/SIZE;
     Last_daily_cost=Energy_Intensity_daily-Energy_Intensity_daily*0.15;
     pdaily=((Energy_Intensity_daily-Last_daily_cost)/Energy_Intensity_daily)*100;

    /*Monthly data*/
    Predicted_monthly_cost=Predicted_daily_cost*30;
    netPower_monthly=netPower_daily*30;
    carbon_footprint_monthly=30*carbon_footprint_daily;
    GreenPower_Monthly=GreenPower_Daily*30;
    Energy_Intensity_monthly=Energy_Intensity_daily*30;
    Last_monthly_cost=Energy_Intensity_monthly+Energy_Intensity_monthly*0.42;
    pmonthly=((Energy_Intensity_monthly-Last_monthly_cost)/Energy_Intensity_monthly)*100;

    /*Annual data*/
    Predicted_annual_cost=12*Predicted_monthly_cost;
    netPower_annualy=netPower_monthly*12;
    carbon_footprint_annualy=carbon_footprint_monthly*(12);
    GreenPower_Monthly=GreenPower_Monthly*12;
    Energy_Intensity_annualy=Energy_Intensity_monthly*30;
    Last_annual_cost=Energy_Intensity_annualy-Energy_Intensity_annualy*0.1125;
    pannual=((Energy_Intensity_annualy-Last_annual_cost)/Energy_Intensity_annualy)*100;




    cout << "+--------------------------------------------------------------------------------------------------------+" << std::endl;
	cout << "|                                             Analysis Report                                            |" << std::endl;
	cout << "+--------------------------------------------------------------------------------------------------------+" << std::endl;
	cout << "+----------------------------------------------Regular Power---------------------------------------------+" << std::endl;
    cout << "|1.|               Daily Power Consumption           |       "<<netPower_daily<<"KWh                                     |" << std::endl;
    cout << "|2.|             Monthly Power Consumption           |       "<<netPower_monthly<<"KWh                                    |" << std::endl;
    cout << "|3.|            Annually Power Consumption           |       "<<netPower_annualy<<"KWh                                   |" <<std::endl;
    cout << "|4.|            Max power consuming device           |       "<<MaxName<<"-"<<MaxPower<<"KWh                                  |" <<std::endl;
    cout << "|5.|            Min power consuming device           |       "<<MinName<<"-"<<MinPower<<"KWh                                  |" <<std::endl;
    cout << "+------------------------------------------------Expenses------------------------------------------------+" << std::endl;
    cout << "|1.|                  Predicted Daily Cost           |       Rs."<<Predicted_daily_cost<<"                                    |" <<std::endl;
    cout << "|2.|                Predicted Monthly Cost           |       Rs."<<Predicted_monthly_cost<<"                                   |" <<std::endl;
    cout << "|3.|                Predicted Monthly Cost           |       Rs."<<Predicted_annual_cost<<"                              |" <<std::endl;
    cout << "|4.|                     Previous Day Cost           |       Rs."<<setprecision(2)<<Last_daily_cost<<"                                       |" <<std::endl;
    cout << "|5.|                   Previous Month Cost           |       Rs."<<Last_monthly_cost<<"                                 |" <<std::endl;
    cout << "|6.|                        Last Year Cost           |       Rs."<<Last_annual_cost<<"                                 |" <<std::endl;
    cout << "|7.|               Percentage change daily           |       "<<pdaily<<"%                                         |" <<std::endl;
    cout << "|8.|             Percentage change monthly           |       "<<pmonthly<<"%                                        |" <<std::endl;
    cout << "|9.|             Percentage change annualy           |       "<<pannual<<"%                                         |" <<std::endl;
    cout << "+-----------------------------------------------Green Power----------------------------------------------+" << std::endl;
    cout << "|1.|               Daily Power Consumption           |       "<<GreenPower_Daily<<"KWh                                 |" << std::endl;
    cout << "|2.|             Monthly Power Consumption           |       "<<GreenPower_Monthly<<"KWh                                   |" << std::endl;
    cout << "|3.|            Annually Power Consumption           |       "<<GreenPower_Annualy<<"KWh                                 |" <<std::endl;
    cout << "+---------------------------------------------Carbon Footprint-------------------------------------------+" << std::endl;
    cout << "|1.|               Daily Carbon footprint            |       "<<carbon_footprint_daily<<"Kg                                  |" << std::endl;
    cout << "|2.|             Monthly Carbon footprint            |       "<<carbon_footprint_monthly<<"Kg                                  |" << std::endl;
    cout << "|3.|            Annually Carbon footprint            |       "<<carbon_footprint_annualy<<"Kg                                  |" <<std::endl;
    cout << "+---------------------------------------------Energy Intensity-------------------------------------------+" << std::endl;
    cout << "|1.|               Daily Energy Intensity            |       "<<Energy_Intensity_daily<<"KWh/Acre                                  |" << std::endl;
    cout << "|2.|             Monthly Energy Intensity            |       "<<Energy_Intensity_monthly<<"KWh/Acre                            |" << std::endl;
    cout << "|3.|            Annually Energy Intensity            |       "<<Energy_Intensity_annualy<<"KWh/Acre                            |" <<std::endl;
    cout << "+--------------------------------------------------------------------------------------------------------+" << std::endl;
}

