#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

// --- BASE CLASS ---
class Animal {
public:
    string name, species, ID, birthDate, color, gender, origin;
    int age;

    // Critical Method: genBirthDay (ISO 8601 Format)
    void genBirthDay(string line) {
        int birthYear = 2026 - age; 
        string day = "-01-01"; // Default

        if (line.find("spring") != string::npos) day = "-03-21";
        else if (line.find("summer") != string::npos) day = "-06-21";
        else if (line.find("fall") != string::npos) day = "-09-21";
        else if (line.find("winter") != string::npos) day = "-12-21";

        this->birthDate = to_string(birthYear) + day;
    }

    virtual void genUniqueID(int count) = 0; 
    virtual ~Animal() {}
};

// --- SUBCLASSES ---
class Hyena : public Animal {
public:
    Hyena(string n, int a) { name = n; species = "Hyena"; age = a; }
    void genUniqueID(int count) override { ID = "Hy0" + to_string(count); }
};

class Lion : public Animal {
public:
    Lion(string n, int a) { name = n; species = "Lion"; age = a; }
    void genUniqueID(int count) override { ID = "Li0" + to_string(count); }
} ;

class Tiger : public Animal {
public:
    Tiger(string n, int a) { name = n; species = "Tiger"; age = a; }
    void genUniqueID(int count) override { ID = "Ti0" + to_string(count); }
};

class Bear : public Animal {
public:
    Bear(string n, int a) { name = n; species = "Bear"; age = a; }
    void genUniqueID(int count) override { ID = "Be0" + to_string(count); }
};

int main() {
    vector<Animal*> zooCheckIn;
    map<string, int> speciesCount;
    string line;

    // --- EXCEPTION HANDLING ---
    try {
        ifstream inputFile("arrivingAnimals.txt");
        if (!inputFile) throw runtime_error("Could not open arrivingAnimals.txt");

        while (getline(inputFile, line)) {
            // Simple parsing for age (first character)
            int age = line[0] - '0';
            Animal* temp = nullptr;

            // Logic to create specific objects
            if (line.find("hyena") != string::npos) {
                speciesCount["hyena"]++;
                temp = new Hyena("Kamari", age); // In final version, pull name from animalNames.txt
                temp->genUniqueID(speciesCount["hyena"]);
            } 
            else if (line.find("lion") != string::npos) {
                speciesCount["lion"]++;
                temp = new Lion("Simba", age);
                temp->genUniqueID(speciesCount["lion"]);
            }
            else if (line.find("tiger") != string::npos) {
                speciesCount["tiger"]++;
                temp = new Tiger("Rajah", age);
                temp->genUniqueID(speciesCount["tiger"]);
            }
            else if (line.find("bear") != string::npos) {
                speciesCount["bear"]++;
                temp = new Bear("Baloo", age);
                temp->genUniqueID(speciesCount["bear"]);
            }

            if (temp) {
                temp->genBirthDay(line);
                // Extract gender (simple check)
                temp->gender = (line.find("female") != string::npos) ? "female" : "male";
                zooCheckIn.push_back(temp);
            }
        }
        inputFile.close();

        // --- OUTPUT REPORT ---
        ofstream report("zooPopulation.txt");
        
        // Example: Habitats grouped as requested
        string habitats[] = {"Hyena", "Lion", "Tiger", "Bear"};
        for (string h : habitats) {
            report << h << " Habitat:" << endl;
            for (Animal* a : zooCheckIn) {
                if (a->species == h) {
                    report << a->ID << "; " << a->name << "; birth date " << a->birthDate 
                           << "; " << a->gender << "; " << a->age << " years old" << endl;
                }
            }
            report << endl;
        }
        report.close();
        cout << "Success! zooPopulation.txt has been generated." << endl;

    } catch (const exception& e) {
        cerr << e.what() << endl;
        return 1;
    }

    // Cleanup memory
    for (Animal* a : zooCheckIn) delete a;

    return 0;
}