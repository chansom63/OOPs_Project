#include <iostream>
#include <string.h>
#include <vector>
#include <stdio.h>
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

class ComplaintRecord;
class Complaints{
    string complaintID;
    string complainant;
    char PhNo[11];
    string Description;
    string FaultLocation;
    char Date[9];
    bool status;
    friend class ComplaintRecord;

public:
    Complaints(string complaintID,
    string complainant,
    char PhNo[11],
    string Description,
    char Date[8],
    bool status,
    string FaultLocation)
    {
        this->complaintID=complaintID;
        this->complainant=complainant;
        strcpy(this->PhNo,PhNo);
        this->Description=Description;
        strcpy(this->Date,Date);
        this->status=status;
        this->FaultLocation=FaultLocation;
    }
};

class ComplaintRecord{
    vector<Complaints> List;
public:
    ComplaintRecord()
    {
        Complaints c1("CN001","Somesh Chandra","6745910345","Projector not Working","25-03-24",0,"LT-II 203");
        Complaints c2("CN002","Amit","7459160345","Sound System not Working","28-03-24",1,"LT-I 106");
        Complaints c3("CN003","Aman","4591034985","Fan not Working","31-03-24",0,"CSE LAB-C123A");
        Complaints c4("CN004","Sam","5910376945","System-21 not Working","05-04-24",0,"CEF GENERIC");
        List.push_back(c1);
        List.push_back(c2);
        List.push_back(c3);
        List.push_back(c4);
    }

    void display()
    {
        char selector;int check=0;
        cout<<"\n\n---------------------------------Complaint Portal----------------------------------------------";
        if(List.size()==0){cout<<"\nNo complaints exist"; return;}
        cout<<"\nEnter the following keys to view Complaints:-"<<endl
        <<"1.View Pending complaints."<<endl
        <<"2.View Resolved complaints."<<endl
        <<"3.View all Complaints"<<endl
        <<"Press the key:"<<endl;
        cin>>selector;

        //Checker block
        while(!check)
        {
           switch(selector)
           {
           case '1':
           case '2':
           case '3':
            check=1;break;
           default:
            fflush(stdin);
            cout<<"\nInvalid input"<<endl
            <<"Press the key again:";
            cin>>selector;
           }
        }
            switch(selector)
            {
            case '1':
                 for(int i=0;i<List.size();i++)
                { if(List[i].status!=0) continue;
            cout<<"\nComplaint ID:"<<List[i].complaintID;
            cout<<"\nComplainant:"<<List[i].complainant;
            cout<<"\nPhoneNo.:"<<List[i].PhNo;
            cout<<"\nDescription:"<<List[i].Description;
            cout<<"\nDate Of Complaint:"<<List[i].Date;
            cout<<"\nFault Location:"<<List[i].FaultLocation;
            cout<<"\nstatus:";
            (List[i].status)?cout<<"Resolved":cout<<"Pending";

            cout<<endl<<endl;
            }break;



            case '2':
                 for(int i=0;i<List.size();i++)
                {if(List[i].status!=1) continue;
            cout<<"\nComplaint ID:"<<List[i].complaintID;
            cout<<"\nComplainant:"<<List[i].complainant;
            cout<<"\nPhoneNo.:"<<List[i].PhNo;
            cout<<"\nDescription:"<<List[i].Description;
            cout<<"\nDate Of Complaint:"<<List[i].Date;
            cout<<"\nFault Location:"<<List[i].FaultLocation;
            cout<<"\nstatus:";
            (List[i].status)?cout<<"Resolved":cout<<"Pending";

            cout<<endl<<endl;
            }break;



            case '3':
                 for(int i=0;i<List.size();i++)
                {
            cout<<"\nComplaint ID:"<<List[i].complaintID;
            cout<<"\nComplainant:"<<List[i].complainant;
            cout<<"\nPhoneNo.:"<<List[i].PhNo;
            cout<<"\nDescription:"<<List[i].Description;
            cout<<"\nDate Of Complaint:"<<List[i].Date;
            cout<<"\nFault Location:"<<List[i].FaultLocation;
            cout<<"\nstatus:";
            (List[i].status)?cout<<"Resolved":cout<<"Pending";

            cout<<endl<<endl;
                }break;


            default:
                cout<<"\nInvalid Input";
            }


         cout<<"\n\n-----------------------------------------------------------------------------------------------";
    }};


int main()
{
    ComplaintRecord R;
    R.display();
    return 0;

}

}
