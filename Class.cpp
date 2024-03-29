#include <iostream>
#include <vector>
using namespace std;
class Room{};
class PowerSource{
    unsigned int Qty;
    double PowerRating;
public:
    PowerSource(){}
    PowerSource(unsigned int q,double rate)
    {
        Qty=q;
        PowerRating=rate;
    }
};

class AdminBlock{
    vector<int> Sections;
    PowerSource Solar;
    PowerSource RegularSupply;
    vector<Room> Rooms;
public:
    AdminBlock(vector<int> Sections,
    PowerSource Solar,
    PowerSource RegularSupply,
    vector<Room> Rooms)
    {
        this->Sections=Sections;
        this->Solar=Solar;
        this->RegularSupply=RegularSupply;
        this->Rooms=Rooms;
    }
};

int main()
{
    return 0;
}
