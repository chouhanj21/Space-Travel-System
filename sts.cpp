#include <iostream>
#include <string>
#include <cmath>
#include <unordered_map>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

// GLOBAL DECLARATIONS

int TODAY = 0.0;
int K = 1000000000; // 1 million
int DATE = 0.0;
bool isLoggedIn = false;
string ACTIVE_TRAVELLER_NAME;
int ACTIVE_TRAVELLER_ID;
int ACTIVE_TYPE = 0;

// CLASS DECLARATIONS

class Planet
{
private:
    double x;
    double y;
    double z;
    string name;

public:
    Planet() {}
    Planet(double _x, double _y, double _z, string _name) : x(_x), y(_y), z(_z), name(_name) {}

    double *getCoordinates();
    string getName();
};

double *Planet::getCoordinates()
{
    double *coordinates = new double[3];
    coordinates[0] = x;
    coordinates[1] = y;
    coordinates[2] = z;
    return coordinates;
}

string Planet::getName()
{
    return name;
}

// DATABASE
vector<Planet> Planet_DB;

/**********************************************************************************************/
class Traveller
{
public:
    string Name;
    int TravellerID;
    vector<string> ticketsID;
    int setTravellerID();

    bool verifyID(int checkID);

    void displayTicketsID();
};

int Logout()
{
    cout << "Confirm logout (y/n): ";
    char confirm;
    cin >> confirm;
    if (confirm == 'y')
    {
        isLoggedIn = false;
        cout << "Logged out succesfully!" << endl;
        return 1;
    }
    else
    {
        return 0;
    }
}

int Traveller::setTravellerID()
{
    srand(time(0));
    int randomNum = rand() % 9000 + 1000;
    return randomNum;
}

bool Traveller::verifyID(int checkID)
{
    return TravellerID == checkID;
}

void Traveller::displayTicketsID()
{
    for (int i = 0; i < ticketsID.size(); i++)
    {
        cout << ticketsID[i] << " ";
    }
    cout << endl;
}




// The PASSENGER class borrows from the TRAVELLER class and has an additional field of Validity
class Passenger : public Traveller
{
public:
    int dateRegister;

    Passenger(){};

    Passenger(string _Name, int _dateRegister);

    bool isValid(int date);

    void RegisterPassenger();

private:
    int validity;
};

// DATABASE
vector<Passenger> Passengers_DB;

// MEMBER FUNCTIONS OF PASSENGER

Passenger::Passenger(string _Name, int _dateRegister)
{
    Name = _Name;
    TravellerID = setTravellerID();
    validity = 3650;
    dateRegister = _dateRegister;
}

bool Passenger::isValid(int date)
{
    return (date - dateRegister) <= validity;
}

void Passenger::RegisterPassenger()
{
    string _Name;
    int _dateRegister;
    cout << "Enter Passenger Name: ";
    cin >> _Name;
    cout << endl
         << "Enter today's date (int): ";
    cin >> _dateRegister;
    cout << endl
         << "Confirm registration(y/n): ";
    char confirm;
    cin >> confirm;
    if (confirm == 'y')
    {
        // Passenger passenger(_Name, _dateRegister);
        Name = _Name;
        dateRegister = _dateRegister;
        TravellerID = setTravellerID();
        cout << TravellerID << " is your ID (remember it for future reference)" << endl;
        Passengers_DB.push_back(*this);
        cout << "Registered successfully" << endl;
    }
}

// The ASTRONAUT class borrows from the TRAVELLER class and has an additional field of Experience
class Astronaut : public Traveller
{
public:
    int dateRegister;
    bool isAstronaut = true;
    bool isCommander = false;
    int experience;

    Astronaut(){};

    Astronaut(string _Name, int _dateRegister, int _experience);

    void RegisterAstronaut();

    int getExperience();
};

// DATABASE
vector<Astronaut> Astronauts_DB;

Astronaut::Astronaut(string _Name, int _dateRegister, int _experience)
{
    Name = _Name;
    dateRegister = _dateRegister;
    experience = _experience;
    TravellerID = setTravellerID();
}

void Astronaut::RegisterAstronaut()
{
    string _Name;
    int _dateRegister;
    int _experience;
    cout << "Enter Astronaut Name: ";
    cin >> _Name;
    cout << endl
         << "Enter today's date (int): ";
    cin >> _dateRegister;
    cout << "Enter years of experience: ";
    cin >> _experience;
    cout << endl
         << "Confirm registration(y/n): ";
    char confirm;
    cin >> confirm;
    if (confirm == 'y')
    {
        Name = _Name;
        dateRegister = _dateRegister;
        experience = _experience;
        TravellerID = setTravellerID();
        cout << TravellerID << " is your ID (remember it for future reference)" << endl;
        Astronauts_DB.push_back(*this);
        cout << "Registered successfully" << endl;
    }
}

int Astronaut::getExperience()
{
    return experience;
}

// The COMMANDER class borrows from the ASTRONAUT class and has an additional field of LicenseID
class Commander : public Astronaut
{
public:
    string LicenseID;
    bool isAstronaut = false;
    bool isCommander = true;

    Commander(){};

    Commander(string _Name, int _dateRegister, int _experience, string _LicenseID);

    void RegisterCommander();

    string getLicenseID();
};

// DATABASE
vector<Commander> Commanders_DB;

Commander::Commander(string _Name, int _dateRegister, int _experience, string _LicenseID)
{
    Name = _Name;
    dateRegister = _dateRegister;
    experience = _experience;
    LicenseID = _LicenseID;
}

void Commander::RegisterCommander()
{
    string _Name;
    int _dateRegister;
    int _experience;
    string _LicenseID;
    cout << "Enter Commander Name: ";
    cin >> _Name;
    cout << endl
         << "Enter today's date (int): ";
    cin >> _dateRegister;
    cout << "Enter years of experience: ";
    cin >> _experience;
    cout << "Enter your License number: ";
    cin >> _LicenseID;
    cout << endl
         << "Confirm registration(y/n): ";
    char confirm;
    cin >> confirm;
    if (confirm == 'y')
    {
        Name = _Name;
        dateRegister = _dateRegister;
        experience = _experience;
        LicenseID = _LicenseID;
        TravellerID = setTravellerID();
        cout << TravellerID << " is your ID (remember it for future reference)" << endl;
        Commanders_DB.push_back(*this);
        cout << "Registered successfully" << endl;
    }
}

// LOGIN FUNCTION

int Login()
{
    cout << "Logging in as: \n(1)Passenger\t(2)Astronaut\t(3)Commander (enter number): ";
    int type;
    cin >> type;
    cout << "Enter ID: ";
    int id;
    cin >> id;
    if (type == 1)
    {
        for (int i = 0; i < Passengers_DB.size(); i++)
        {
            if (Passengers_DB[i].TravellerID == id)
            {
                cout << "Logged in succesfully as Passenger!" << endl;
                ACTIVE_TRAVELLER_NAME = Passengers_DB[i].Name;
                ACTIVE_TYPE = 0;
                cout << "Welcome: " << ACTIVE_TRAVELLER_NAME << endl;
                // cout << "Active type: " << ACTIVE_TYPE << endl;
                ACTIVE_TRAVELLER_ID = Passengers_DB[i].TravellerID;
                isLoggedIn = true;
                return Passengers_DB[i].TravellerID;
            }
        }
    }
    else if (type == 2)
    {
        for (int i = 0; i < Astronauts_DB.size(); i++)
        {
            if (Astronauts_DB[i].TravellerID == id)
            {
                cout << "Logged in succesfully!" << endl;
                cout << "Welcome: " << Astronauts_DB[i].Name << endl;
                ACTIVE_TRAVELLER_NAME = Passengers_DB[i].Name;
                ACTIVE_TRAVELLER_ID = Passengers_DB[i].TravellerID;
                ACTIVE_TYPE = 1;
                isLoggedIn = true;
                return Astronauts_DB[i].TravellerID;
            }
        }
    }
    else
    {
        for (int i = 0; i < Commanders_DB.size(); i++)
        {
            if (Commanders_DB[i].TravellerID == id)
            {
                cout << "Logged in succesfully!" << endl;
                cout << "Welcome: " << Commanders_DB[i].Name << endl;
                ACTIVE_TRAVELLER_NAME = Passengers_DB[i].Name;
                ACTIVE_TRAVELLER_ID = Passengers_DB[i].TravellerID;
                ACTIVE_TYPE = 2;
                isLoggedIn = true;
                return Commanders_DB[i].TravellerID;
            }
        }
    }
    cout << "User not found! Please try again" << endl;
    return -1;
}

/************************************************************************************************/
// TICKETS
class Ticket
{
public:
    Planet sourcePlanet;
    Planet destinationPlanet;
    string travellerName;
    int travelDate;
    string TicketID;
    int bookedByType;

    Ticket() {}

    Ticket(Planet &_sourcePlanet, Planet &_destinationPlanet, string _travellerName, int travelDate);

    int BookTicket(string _travellerName);

    void PrintTicket();

    float getPrice();

    string getTicketID();

private:
    float price;
    float setPrice();
    string generateTicketID();
};

void ScheduleSpaceTravel(int _travelDate, Planet source, Planet destination);

void Ticket::PrintTicket()
{
    cout << "Ticket ID: " << TicketID << endl;
    cout << "Source Planet: " << sourcePlanet.getName() << endl;
    cout << "Destination Planet: " << destinationPlanet.getName() << endl;
    cout << "Traveller Name: " << travellerName << endl;
    cout << "Travel Date: " << travelDate << endl;
    cout << "Price: " << price << endl;
}

// DATABASE
vector<Ticket> Ticket_DB;

// MEMBER FUNCTION OF TICKET CLASS
Ticket::Ticket(Planet &_sourcePlanet, Planet &_destinationPlanet, string _travellerName, int _travelDate)
{
    sourcePlanet = _sourcePlanet;
    destinationPlanet = _destinationPlanet;
    travellerName = _travellerName;
    travelDate = _travelDate;
    TicketID = generateTicketID();
    price = setPrice();
}

float Ticket::setPrice()
{
    double *sourceCoordinates = sourcePlanet.getCoordinates();
    double *destinationCoordinates = destinationPlanet.getCoordinates();
    double distance = sqrt(pow(sourceCoordinates[0] - destinationCoordinates[0], 2) +
                           pow(sourceCoordinates[1] - destinationCoordinates[1], 2) +
                           pow(sourceCoordinates[2] - destinationCoordinates[2], 2));

    return (K * distance) / (travelDate - TODAY + 1);
}

float Ticket::getPrice()
{
    return price;
}

string Ticket::generateTicketID()
{
    string ticketID = "";
    srand(time(nullptr));
    for (int i = 0; i < 5; i++)
    {
        ticketID += (char)(65 + rand() % 26);
    }
    return ticketID;
}

string Ticket::getTicketID()
{
    return TicketID;
}

int Ticket::BookTicket(string _travellerName)
{
    if (isLoggedIn)
    {
        cout << "Welcome to booking ticket portal!" << endl;
        cout << "Enter source planet's name: ";
        string sourceName;
        cin >> sourceName;
        cout << "Enter destination planet's name: ";
        string destinationName;
        cin >> destinationName;
        transform(sourceName.begin(), sourceName.end(), sourceName.begin(), ::toupper);
        transform(destinationName.begin(), destinationName.end(), destinationName.begin(), ::toupper);
        Planet _sourcePlanet;
        Planet _destinationPlanet;
        int count = 0;
        for (int i = 0; i < Planet_DB.size(); i++)
        {
            if (Planet_DB[i].getName() == sourceName)
            {
                _sourcePlanet = Planet_DB[i];
                break;
            }
            count++;
        }
        if (count == Planet_DB.size())
        {
            cout << "We don't cater to this source planet. Try again!" << endl;
            return 0;
        }
        count = 0;
        for (int i = 0; i < Planet_DB.size(); i++)
        {
            if (Planet_DB[i].getName() == destinationName)
            {
                _destinationPlanet = Planet_DB[i];
                break;
            }
            count++;
        }
        if (count == Planet_DB.size())
        {
            cout << "We don't cater to this destination planet. Try again!" << endl;
            return 0;
        }

        sourcePlanet = _sourcePlanet;
        destinationPlanet = _destinationPlanet;
        travellerName = _travellerName;

        cout << "Enter date of travel (int): ";
        int date;
        cin >> date;
        travelDate = date;

        string _TicketID = generateTicketID();
        TicketID = _TicketID;
        price = this->setPrice();

        Ticket_DB.push_back(*this);
        // cout << "Active type: " << ACTIVE_TYPE << endl;

        if (ACTIVE_TYPE == 0)
        {
            bookedByType = 0;
            Passenger passenger;
            for (int i = 0; i < Passengers_DB.size(); i++)
            {
                if (Passengers_DB[i].Name == _travellerName)
                {
                    passenger = Passengers_DB[i];
                    passenger.ticketsID.push_back(_TicketID);
                    break;
                }
            }
            cout << "Ticket Booked succesfully! The price is: " << getPrice() << " on: " << travelDate << endl;
            cout << "Ticket ID: " << TicketID << endl;
            ScheduleSpaceTravel(date, _sourcePlanet, _destinationPlanet);
        }
        else if (ACTIVE_TYPE == 1)
        {
            bookedByType = 1;
            Astronaut astronaut;
            for (int i = 0; i < Astronauts_DB.size(); i++)
            {
                if (Astronauts_DB[i].Name == _travellerName)
                    astronaut = Astronauts_DB[i];
                astronaut.ticketsID.push_back(TicketID);
            }
            cout << "Ticket ID: " << TicketID << endl;
        }
        else
        {
            bookedByType = 2;
            Commander commander;
            for (int i = 0; i < Commanders_DB.size(); i++)
            {
                if (Commanders_DB[i].Name == _travellerName)
                    commander = Commanders_DB[i];
                commander.ticketsID.push_back(TicketID);
            }
            cout << "Ticket ID: " << TicketID << endl;
        }

        return 1;
    }
    else
    {
        cout << "Please login first!" << endl;
        return 0;
    }
}

int CancelTicket()
{
    if (isLoggedIn)
    {
        string ticketID;
        cout << "Enter ticketID to be cancelled: ";
        cin >> ticketID;
        cout << endl;
        Ticket ticket_temp;
        int count = 0;
        for (int i = 0; i < Ticket_DB.size(); i++)
        {
            if (Ticket_DB[i].getTicketID() == ticketID)
            {
                ticket_temp = Ticket_DB[i];
                break;
            }
            count++;
        }
        if (count == Ticket_DB.size())
        {
            cout << "No such ticket exists!" << endl;
            return 0;
        }
        cout << "Confirm cancellation? (y/n): ";
        char confirm;
        cin >> confirm;
        if (confirm == 'y')
        {
            if (ACTIVE_TYPE == 0)
            {
                string name = ticket_temp.travellerName;
                Passenger passenger;
                for (int i = 0; i < Passengers_DB.size(); i++)
                {
                    if (Passengers_DB[i].Name == name)
                        passenger = Passengers_DB[i];
                }
                for (int i = 0; i < passenger.ticketsID.size(); i++)
                {
                    if (passenger.ticketsID[i] == ticketID)
                    {
                        passenger.ticketsID.erase(passenger.ticketsID.begin() + i);
                        break;
                    }
                }
            }
            else if (ACTIVE_TYPE == 1)
            {
                string name = ticket_temp.travellerName;
                Astronaut astronaut;
                for (int i = 0; i < Astronauts_DB.size(); i++)
                {
                    if (Astronauts_DB[i].Name == name)
                        astronaut = Astronauts_DB[i];
                }
                for (int i = 0; i < astronaut.ticketsID.size(); i++)
                {
                    if (astronaut.ticketsID[i] == ticketID)
                    {
                        astronaut.ticketsID.erase(astronaut.ticketsID.begin() + i);
                        break;
                    }
                }
            }
            else
            {
                string name = ticket_temp.travellerName;
                Commander commander;
                for (int i = 0; i < Commanders_DB.size(); i++)
                {
                    if (Commanders_DB[i].Name == name)
                        commander = Commanders_DB[i];
                }
                for (int i = 0; i < commander.ticketsID.size(); i++)
                {
                    if (commander.ticketsID[i] == ticketID)
                    {
                        commander.ticketsID.erase(commander.ticketsID.begin() + i);
                        break;
                    }
                }
            }
            for (int i = 0; i < Ticket_DB.size(); i++)
            {
                if (Ticket_DB[i].getTicketID() == ticketID)
                {
                    Ticket_DB.erase(Ticket_DB.begin() + i);
                    break;
                }
            }
            cout << "Ticket cancelled successfully!" << endl;
            return 1;
        }
        else
        {
            cout << "Ticket cancellation cancelled!" << endl;
            return 0;
        }
    }
    else
    {
        cout << "Please login first!" << endl;
        return 0;
    }
}

/***********************************************************************************************/

// SPACE TRAVEL CLASS
class SpaceTravel
{
public:
    int travelDate;
    vector<Ticket> Travel_tickets;
    Astronaut astronaut;
    Commander commander;
    bool isScheduled = false;

    SpaceTravel(){};

    SpaceTravel(int _astronautID, int _commanderID, vector<Ticket> _tickets, int _travelDate);

    void AddTraveller(Passenger _passenger);

    void ListTravellers();

    void SetAstronaut(int _astronautID);

    void SetCommander(int _commanderID);

    int getTravelDate();
};

// DATABASE
vector<SpaceTravel> SpaceTravel_DB;

SpaceTravel::SpaceTravel(int _astronautID, int _commanderID, vector<Ticket> _tickets, int _travelDate)
{
    Astronaut _astronaut;
    Commander _commander;
    // that is a space travel class is created if there are atleast 2 tickets booked with same source and destination planet on same date
    // and atleast 1 astronaut and 1 commander are registered
    int count = 0;
    for (int i = 0; i < Astronauts_DB.size(); i++)
    {
        if (Astronauts_DB[i].TravellerID == _astronautID)
        {
            _astronaut = Astronauts_DB[i];
            break;
        }
        count++;
    }
    if (count == Astronauts_DB.size())
    {
        cout << "No such astronaut exists!" << endl;
        return;
    }
    count = 0;
    for (int i = 0; i < Commanders_DB.size(); i++)
    {
        if (Commanders_DB[i].TravellerID == _commanderID)
        {
            _commander = Commanders_DB[i];
            break;
        }
        count++;
    }
    if (count == Commanders_DB.size())
    {
        cout << "No such commander exists!" << endl;
        return;
    }
    astronaut = _astronaut;
    commander = _commander;
    Travel_tickets = _tickets;
    travelDate = _travelDate;
}

void SpaceTravel::AddTraveller(Passenger _passenger)
{
    if (Travel_tickets.size() == 10)
    {
        cout << "No more tickets can be booked!" << endl;
        return;
    }
    Ticket ticket;
    ticket.BookTicket(_passenger.Name);
    Travel_tickets.push_back(ticket);
    return;
}

void SpaceTravel::ListTravellers()
{
    cout << "The travellers are: " << endl;
    for (int i = 0; i < Travel_tickets.size(); i++)
    {
        cout << Travel_tickets[i].travellerName << endl;
    }
    return;
}

void SpaceTravel::SetAstronaut(int _astronautID)
{
    Astronaut _astronaut;
    int count = 0;
    for (int i = 0; i < Astronauts_DB.size(); i++)
    {
        if (Astronauts_DB[i].TravellerID == _astronautID)
        {
            _astronaut = Astronauts_DB[i];
            break;
        }
        count++;
    }
    if (count == Astronauts_DB.size())
    {
        cout << "No such astronaut exists!" << endl;
        return;
    }
    astronaut = _astronaut;
    return;
}

void SpaceTravel::SetCommander(int _commanderID)
{
    Commander _commander;
    int count = 0;
    for (int i = 0; i < Commanders_DB.size(); i++)
    {
        if (Commanders_DB[i].TravellerID == _commanderID)
        {
            _commander = Commanders_DB[i];
            break;
        }
        count++;
    }
    if (count == Commanders_DB.size())
    {
        cout << "No such commander exists!" << endl;
        return;
    }
    commander = _commander;
    return;
}

int SpaceTravel::getTravelDate()
{
    return travelDate;
}

void ScheduleSpaceTravel(int _travelDate, Planet source, Planet destination)
{
    vector<Ticket> tickets;
    for (int i = 0; i < Ticket_DB.size(); i++)
    {
        if ((Ticket_DB[i].sourcePlanet.getName() == source.getName()) && (Ticket_DB[i].destinationPlanet.getName() == destination.getName()) && (Ticket_DB[i].travelDate == _travelDate) && (Ticket_DB[i].bookedByType == 0))
        {
            tickets.push_back(Ticket_DB[i]);
        }
    }
    if (tickets.size() <= 2)
    {
        cout << "Not enough tickets to instantiate a SpaceTravel." << endl;
        return;
    }

    SpaceTravel spaceTravel;
    spaceTravel.travelDate = _travelDate;
    spaceTravel.Travel_tickets = tickets;
    spaceTravel.isScheduled = true;

    int index1 = rand() % Astronauts_DB.size();
    int index2 = rand() % Commanders_DB.size();

    spaceTravel.SetAstronaut(Astronauts_DB[index1].TravellerID);
    spaceTravel.SetCommander(Commanders_DB[index2].TravellerID);

    cout << "SpaceTravel scheduled successfully!" << endl;
    SpaceTravel_DB.push_back(spaceTravel);
    return;
}
/****************************************************************************/
int main()
{

    // Creating Planets
    Planet Mercury(0, 0, 0, "MERCURY");
    Planet Venus(0, 5, 3, "VENUS");
    Planet Earth(1, 7, 6, "EARTH");
    Planet Mars(3, 9, 6, "MARS");
    Planet Jupiter(4, 10, 8, "JUPITER");

    // saving in Planet_DB
    Planet_DB.push_back(Mercury);
    Planet_DB.push_back(Venus);
    Planet_DB.push_back(Earth);
    Planet_DB.push_back(Mars);
    Planet_DB.push_back(Jupiter);

    // Some Astronauts and Commanders instantiated
    Astronaut astronaut1("John Smith", 3, 12);
    Astronaut astronaut2("Taylor Wilson", 6, 6);

    Commander commander1("Sr. Goodrow Calls", 41, 15, "ICS456");
    Commander commander2("Jr. Goodrow Calls", 41, 15, "ICS446");

    Astronauts_DB.push_back(astronaut1);
    Astronauts_DB.push_back(astronaut2);
    Commanders_DB.push_back(commander1);
    Commanders_DB.push_back(commander2);

    isLoggedIn = 1;
    // Passenger instantiated
    Passenger p1 ("A1", 45);
    Passenger p2 ("A2", 45);
    Passenger p3 ("A3", 45);
    Passenger p4 ("A4", 45);
    Passenger p5 ("A5", 45);
    Passenger p6 ("A6", 45);
    Passenger p7 ("A7", 45);
    Passenger p8 ("A8", 45);
    Passenger p9 ("A9", 45);
    Passenger p10 ("A10", 45);
    Passenger p11 ("A11", 45);

    Passengers_DB.push_back(p1);
    Passengers_DB.push_back(p2);
    Passengers_DB.push_back(p3);
    Passengers_DB.push_back(p4);
    Passengers_DB.push_back(p5);
    Passengers_DB.push_back(p6);
    Passengers_DB.push_back(p7);
    Passengers_DB.push_back(p8);
    Passengers_DB.push_back(p9);
    Passengers_DB.push_back(p10);
    Passengers_DB.push_back(p11);

    Ticket ticket1(Earth, Mars, "A1", 54);
    Ticket ticket2(Earth, Mars, "A2", 54);
    Ticket ticket3(Earth, Mars, "A3", 54);

    ticket1.BookTicket("A1");
    ticket1.BookTicket("A2");
    ticket1.BookTicket("A3");

    cout << "Interactive session!" << endl;

    isLoggedIn = 0;

    while (true)
    {
        cout << "Welcome to the Space Travel Agency!" << endl;
        cout << "0. List of catered planets" << endl;
        cout << "1. Register a new traveller" << endl;
        cout << "2. Login as a traveller" << endl;
        cout << "3. Logout" << endl;
        cout << "4. Booking system" << endl;
        cout << "else... Exit the program" << endl;

        int choice;
        cin >> choice;
        if (choice == 0)
        {
            for (int i = 0; i < Planet_DB.size(); i++)
            {
                cout << Planet_DB[i].getName() << endl;
            }
            continue;
        }
        else if (choice == 1)
        {
            cout << "1. Register as an Astronaut" << endl;
            cout << "2. Register as a Commander" << endl;
            cout << "3. Register as a Passenger" << endl;
            int choice2;
            cin >> choice2;
            if (choice2 == 1)
            {
                Astronaut astronaut;
                astronaut.RegisterAstronaut();
            }
            else if (choice2 == 2)
            {
                Commander commander;
                commander.RegisterCommander();
            }
            else if (choice2 == 3)
            {
                Passenger passenger;
                passenger.RegisterPassenger();
            }
            continue;
        }
        else if (choice == 2)
        {
            int login_status = Login();
            if (login_status == -1)
            {
                continue;
            }
        }
        else if (choice == 3)
        {
            int logout_status = Logout();
            continue;
        }
        else if (choice == 4)
        {
            while (true)
            {
                if (isLoggedIn)
                {
                    cout << "Welcome " << ACTIVE_TRAVELLER_NAME << " to the booking system" << endl;
                    cout << "1. View TicketIDs of all tickets booked yet." << endl;
                    cout << "2. Book Ticket" << endl;
                    cout << "3. Cancel Ticket" << endl;
                    cout << "4. Print individual ticket details" << endl;
                    cout << "else... Exit here!" << endl;
                    int choice3;
                    cin >> choice3;
                    if (choice3 == 1)
                    {
                        if (ACTIVE_TYPE == 0)
                        {
                            Passenger traveller;
                            for (int i = 0; i < Passengers_DB.size(); i++)
                            {
                                if (Passengers_DB[i].TravellerID == ACTIVE_TRAVELLER_ID)
                                    traveller = Passengers_DB[i];
                            }
                            traveller.displayTicketsID();
                        }
                        else if (ACTIVE_TYPE == 1)
                        {
                            Astronaut traveller;
                            for (int i = 0; i < Astronauts_DB.size(); i++)
                            {
                                if (Astronauts_DB[i].TravellerID == ACTIVE_TRAVELLER_ID)
                                    traveller = Astronauts_DB[i];
                            }
                            traveller.displayTicketsID();
                        }
                        else
                        {
                            Commander traveller;
                            for (int i = 0; i < Commanders_DB.size(); i++)
                            {
                                if (Commanders_DB[i].TravellerID == ACTIVE_TRAVELLER_ID)
                                    traveller = Commanders_DB[i];
                            }
                            traveller.displayTicketsID();
                        }
                        continue;
                    }
                    else if (choice3 == 2)
                    {
                        Ticket ticket;
                        ticket.BookTicket(ACTIVE_TRAVELLER_NAME);
                        continue;
                    }
                    else if (choice3 == 3)
                    {
                        CancelTicket();
                        continue;
                    }
                    else if (choice3 == 4)
                    {
                        string ticket_id;
                        cout << "Enter the ticket ID: ";
                        cin >> ticket_id;
                        cout << endl;
                        int count = 0;
                        Ticket ticket;
                        for (int i = 0; i < Ticket_DB.size(); i++)
                        {
                            if (Ticket_DB[i].TicketID == ticket_id)
                            {
                                ticket = Ticket_DB[i];
                                break;
                            }
                            count++;
                        }
                        if (count == Ticket_DB.size())
                        {
                            cout << "No ticket found with this ID." << endl;
                            continue;
                        }
                        ticket.PrintTicket();
                        continue;
                    }
                    else
                    {
                        break;
                    }
                }
                else
                {
                    cout << "Plese login first." << endl;
                    break;
                }
            }
            continue;
        }
        else
        {
            break;
        }
    }
    return 0;
}