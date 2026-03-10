#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>

using namespace std;

// Base Class - Animal
class Animal {
protected:
    string name;
    int age;
    string species;

public:
    // Constructor to set up the animal
    Animal(string n, int a, string s) {
        name = n;
        age = a;
        species = s;
    }

    // Getters so we can access private/protected data later
    string getName() { return name; }
    int getAge() { return age; }
    string getSpecies() { return species; }

    virtual ~Animal() {} // Instructor said always include this for inheritance
};

// Subclasses for the specific animals
class Hyena : public Animal {
public:
    Hyena(string n, int a) : Animal(n, a, "Hyena") {}
};

class Lion : public Animal {
public:
    Lion(string n, int a) : Animal(n, a, "Lion") {}
};

class Tiger : public Animal {
public:
    Tiger(string n, int a) : Animal(n, a, "Tiger") {}
};

class Bear : public Animal {
public:
    Bear(string n, int a) : Animal(n, a, "Bear") {}
};

int main() {
    // Vectors and Maps to hold our data
    vector<Animal*> zooList;
    map<string, int> counts;

    // Opening the files
    ifstream inFile("arrivingAnimals.txt");
    ofstream outFile("newAnimals.txt");

    if (!inFile) {
        cout << "Could not find the input file!" << endl;
        return 1;
    }

    string line;
    // Reading the file line by line
    while (getline(inFile, line)) {
        string species = "";
        int age = 0;
        string name = "Unnamed"; // Default name for now

        // Check the line for specific animal types
        if (line.find("hyena") != string::npos) {
            species = "Hyena";
        } else if (line.find("lion") != string::npos) {
            species = "Lion";
        } else if (line.find("tiger") != string::npos) {
            species = "Tiger";
        } else if (line.find("bear") != string::npos) {
            species = "Bear";
        }

        // The first character in the line is usually the age
        // Subtraction converts the char digit to an actual int
        age = line[0] - '0';

        // Use 'new' to create the specific animal type
        if (species == "Hyena") {
            zooList.push_back(new Hyena(name, age));
            counts["Hyena"]++;
        } else if (species == "Lion") {
            zooList.push_back(new Lion(name, age));
            counts["Lion"]++;
        } else if (species == "Tiger") {
            zooList.push_back(new Tiger(name, age));
            counts["Tiger"]++;
        } else if (species == "Bear") {
            zooList.push_back(new Bear(name, age));
            counts["Bear"]++;
        }
    }

    // Writing the report to the output file
    outFile << "--- Zoo Population Report ---" << endl << endl;

    // Simple way to go through the map and print counts
    // We hardcode the species to keep the output organized by habitat
    string types[] = {"Hyena", "Lion", "Tiger", "Bear"};
    
    for (int i = 0; i < 4; i++) {
        string currentType = types[i];
        outFile << currentType << " Habitat:" << endl;
        outFile << "Total Count: " << counts[currentType] << endl;

        // Loop through the vector to find animals of this species
        for (int j = 0; j < zooList.size(); j++) {
            if (zooList[j]->getSpecies() == currentType) {
                outFile << " - " << zooList[j]->getName() << ", ";
                outFile << zooList[j]->getAge() << " years old" << endl;
            }
        }
        outFile << endl;
    }

    // Cleaning up memory (deleting the pointers)
    for (int k = 0; k < zooList.size(); k++) {
        delete zooList[k];
    }

    inFile.close();
    outFile.close();
    cout << "Report finished! Check newAnimals.txt" << endl;

    return 0;
}
