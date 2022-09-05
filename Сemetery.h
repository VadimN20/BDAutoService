#pragma once
#include <string>
using namespace std;

class Zapchast {
public:
    int id;
    string name;
    string date;
    long price;
    Zapchast(int id, const string& name, const string& date, long price) {
        this->name = name;
        this->date = date;
        this->price = price;
        this->id = id;
    }
    Zapchast(string& obj) {
        id = stoi(obj.substr(0, obj.find("/")));
        obj.erase(0, obj.find("/") + 1);
        name = obj.substr(0, obj.find("/"));
        obj.erase(0, obj.find("/") + 1);
        date = obj.substr(0, obj.find("/"));
        obj.erase(0, obj.find("/") + 1);
        price = stoi(obj.substr(0, obj.find("/")));
    }
    Zapchast(const Zapchast& obj) {
        name = obj.name;
        date = obj.date;
        price = obj.price;
        id = obj.id;
    }
    friend bool operator== (const Zapchast& l, const Zapchast& r) {
        auto it = r.name.find(l.name);
        if (it != string::npos)
            return  true;
        else
            return false;
    }

    virtual Zapchast* copy() {
        return new Zapchast(*this);
    }
    virtual string getDBString() {
        return "1/" + to_string(id) + "/" + name + "/" + date + "/" + to_string(price);
    }
    virtual string getString() {
        return to_string(id) + ": Запчасть - " + name + ", дата: " + date + ", цена: " + to_string(price) + " руб";
    }
    virtual ~Zapchast() {}
};

class Usluga : public Zapchast {
public:
    Usluga(int id, const string& name, const string& date, long price) : Zapchast(id, name, date, price) {}
    Usluga(string& obj) : Zapchast(obj) {}
    Usluga(const Usluga& obj) : Zapchast(obj) {}
    Usluga* copy() {
        return new Usluga(*this);
    }
    string getDBString() {
        return "2/" + to_string(id) + "/" + name + "/" + date + "/" + to_string(price);
    }
    virtual string getString() {
        return to_string(id) + ": Услуга - " + name + ", дата: " + date + ", цена: " + to_string(price) + " руб";
    }
    ~Usluga() {}
};