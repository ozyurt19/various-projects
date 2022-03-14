using namespace std;
#include <string>

#ifndef PERSON_H
#define PERSON_H


class Person{
    protected:
    string name;
    string surname;
    public:
    Person(const string& = "default_name", const string& = "default_surname");
};

class Passenger : public Person{
    int cash;
    bool ticket;
    Passenger * next;
    public:
    Passenger(const string& = "default_name", const string& = "default_surname", int = 0);
    bool buyTicket(int);
    int get_cash(){return cash;};
    void set_cash(int in){cash = in;};
    bool get_ticket(){return ticket;};
    string get_name(){return name;};
    void set_next(Passenger * in){next = in;};
    string get_surname(){return surname;};
};

class Astronaut : public Person{
    int numMissions = 0;
    Astronaut * next;
    public:
    Astronaut(const string& = "default_name", const string& = "default_surname", int = 0);
    void completeMission(){numMissions++;};
    Astronaut * get_next(){return next;};
    void set_next(Astronaut * in){next = in;};
    string get_name(){return name;};
    int get_num_missions(){return numMissions;};
    string get_surname(){return surname;};
    void set_name(string in){name = in;};
    void set_surname(string in){surname = in;};
    void set_num_missions(int in){numMissions = in;};
};

#endif /* PERSON_H */