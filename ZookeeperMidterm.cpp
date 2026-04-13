#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// 1. The Foundation (Base Class)
class Animal {
public:
    std::string name, species, ID;
    int age;

    Animal() : name("Unknown"), species("Unknown"), age(0), ID("00") {}
    virtual ~Animal() {} // Helps the compiler keep track of memory
};

// 2. The Specific Animals (Sub-classes)
class Hyena : public Animal {
public:
    Hyena(std::string n, int a) {
        name = n;
        species = "Hyena";
        age = a;
        ID = "Hy01";
    }
};

class Lion : public Animal {
public:
    Lion(std::string n, int a) {
        name = n;
        species = "Lion";
        age = a;
        ID = "Li01";
    }
};

// 3. The Entry Point (The "Main" function)
int main() {
    std::ifstream inputFile("arrivingAnimals.txt");
    std::ofstream report("zooPopulation.txt");
    
    if (!inputFile.is_open()) {
        std::cout << "Error: Place arrivingAnimals.txt in this folder!" << std::endl;
        return 1;
    }

    std::string line;
    std::vector<Animal*> zooCheckIn;

    std::cout << "Processing animals..." << std::endl;

    while (getline(inputFile, line)) {
        // Corrected find logic
        if (line.find("hyena") != std::string::npos) {
            zooCheckIn.push_back(new Hyena("Shenzi", 4)); 
        } else if (line.find("lion") != std::string::npos) {
            zooCheckIn.push_back(new Lion("Simba", 12));
        }
    }

    report << "Zookeeper's Challenge - Daily Arrival Report\n";
    report << "-------------------------------------------\n";
    for (Animal* a : zooCheckIn) {
        report << a->ID << "; " << a->name << "; " << a->age << " years old; Species: " << a->species << "\n";
    }

    std::cout << "Success! Check zooPopulation.txt" << std::endl;

    // Clean up
    inputFile.close();
    report.close();
    return 0;
}