#include "pch.h"
#include "park_unit.h"
#include <cstring>
#include <vector>
#include <fstream>
#include <string>



park_unit::park_unit()
{
	m_parent = NULL;		//if pointer to parent is not given (new parking system root)
	m_depthLevel = 4;
}

park_unit::park_unit(park_unit *parent)
{
	if (parent) m_depthLevel = parent->m_depthLevel -= 1;
	else m_depthLevel = 4;	//default: 0 is parking place, 1- sector, 2- floor, 3 - building, 4 - system
	m_parent = parent;		//if pointer to parent is given (overload)
}

park_unit::~park_unit()
{
	if (m_children.empty())
	{
		cout << endl << "m_children bylo puste\n";
	}
	else
	{
		for (auto &i : m_children) delete i;
	}
	m_children.clear();
}

void park_unit::printID()
{
	if (m_parent) m_parent->printID();
	cout << m_childID << ".";
}
void park_unit::addChildUnit()
{
		m_children.push_back(new park_unit(this)); 
		switch (m_depthLevel) {
		case 4: m_children.back()->m_childID = BuildingNames[m_children.size()-1];
			break;
		case 3: m_children.back()->m_childID = LevelNames[m_children.size()-1];
			break;
		case 2: m_children.back()->m_childID = SectorNames[m_children.size()-1];
			break;
		case 1: m_children.back()->m_childID = PlaceNames[m_children.size()-1];
			break;
		}
		printID();
		cout << " \t\t-> Adding new child no.  ";
		m_children.back()->printID();
		cout << endl;
}

void park_unit::removeChildren()
{
	printID();
	cout << "\t\t-> deleting all children:" << endl;
	
	if (!m_children.empty())
	{
		for (auto &i : m_children) i->removeChildren();
	}
}

void park_unit::removeChildUnit()
{
	printID();
	cout << "\t\t-> deleting child no.  ";
	m_children.back()->printID();
	cout << endl;
	
	delete &(m_children.back());
	m_children.pop_back();

}


void park_unit::placeTaken()
{
	isTaken = true;
	//if (m_parent) m_parent->takenPlacesCounter++;
}

void park_unit::placeFreed()
{
	isTaken = false;
	//if (m_parent) m_parent->takenPlacesCounter--;
}

void park_unit::removeChildUnit(int childID)
{
	delete &(m_children[childID]);
}
void park_unit::getDataFromFiles() {
			string str;
		ifstream file0("PlaceNames.txt");
		while (getline(file0, str)) {
			PlaceNames.push_back(str);
		}
		ifstream file1("SectorNames.txt");
		while (getline(file1, str)) {
			SectorNames.push_back(str);
		}
		ifstream file2("LevelNames.txt");
		while (getline(file2, str)) {
			LevelNames.push_back(str);
		}
		ifstream file3("BuildingNames.txt");
		while (getline(file3, str)) {
			BuildingNames.push_back(str);
		}
}

park_unit * park_unit::getChild(int i)
{
	return m_children[i];
}

park_unit* accessData(string buildingID, string levelID, string SectorID, string PlaceID)//TBD
{
	return 0;
};
