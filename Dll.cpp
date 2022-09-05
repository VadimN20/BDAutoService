// Dll.cpp : Определяет экспортируемые функции для DLL.
//

#include "framework.h"
#include "Dll.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <typeinfo>

vector<Zapchast*> vec;
vector<Zapchast*> sortVector;

DLL_API void initializationData() {
	string str;
	int key;
	ifstream file("DBCars.txt");
	while (getline(file, str)) {
		key = stoi(str.substr(0, 1));
		str.erase(0, str.find("/") + 1);
		switch (key)
		{
		case 1:
			vec.push_back(new Zapchast(str));
			break;
		case 2:
			vec.push_back(new Usluga(str));
			break;
		}
	}
	file.close();
}

DLL_API void addRecord(const string& name, const string& date, long price, int category) {
	int id = vec.size() + 1;
	switch (category)
	{
	case 0:
		vec.push_back(new Zapchast(id, name, date, price));
		break;
	case 1:
		vec.push_back(new Usluga(id, name, date, price));
		break;
	}
	ofstream file("DBCars.txt", ios_base::app);
	file << vec.back()->getDBString() << "\n";
	file.close();
}

void reloadSort() {
	for (auto it : sortVector)
		delete it;
	sortVector.clear();
	for (auto it : vec) {
		sortVector.push_back((*it).copy());
	}
}


DLL_API void sortDataBase (bool isR) {
	reloadSort();
	sort(sortVector.begin(), sortVector.end(), [](Zapchast* l, Zapchast* r) {
		return l->price < r->price;
		});
	if (!isR) {
		reverse(sortVector.begin(), sortVector.end());
	}
}

DLL_API string getRecord(int i) {
	return vec.at(i)->getString();
}

DLL_API string getSortRecord(int i) {
	return sortVector.at(i)->getString();
}

DLL_API int sizeVec() {
	return vec.size();
}

DLL_API int sizeSortVector() {
	return sortVector.size();
}

DLL_API void deleteRecord(string& name) {
	Zapchast* left = new Zapchast(1, name, "", 1);
	auto it = find_if(vec.begin(), vec.end(), [&](Zapchast* right) {
		return *left == *right;
		});
	delete left;
	delete *it;
	vec.erase(it);
	ofstream file("DBCars.txt", std::ios_base::out | std::ios_base::trunc);
	for (int i = 0; i < vec.size(); i++) {
		vec.at(i)->id = i + 1;
		file << vec.at(i)->getDBString() << "\n";
	}
	file.close();
}

DLL_API void findRecord(string& name) {
	for (auto it : sortVector)
		delete it;
	sortVector.clear();
	Zapchast* left = new Zapchast(1, name, "", 1);
	auto it = vec.begin();
	while (it != vec.end()) {
		it = find_if(it, vec.end(), [&](Zapchast* right) {
			return *left == *right;
			});
		if (it != vec.end())
		{
			sortVector.push_back((*it)->copy());
			it++;
		}
	}
	delete left;
}

DLL_API void cleanMemory() {
	for (auto it : vec)
		delete it;
	for (auto it : sortVector)
		delete it;
}