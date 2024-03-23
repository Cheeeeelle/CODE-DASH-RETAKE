#include <iostream>
#include <string>

using namespace std;

struct Pokemon {
    string name;
    string type;
    int level;
    Pokemon* next;
};


void DisplayMenu() {
    cout << "Menu:\n";
    cout << "1. Catch\n";
    cout << "2. Type (Sorting)\n";
    cout << "3. Inventory Pokemon\n";
    cout << "4. Build Team\n";
    cout << "5. Exit\n";
    cout << "Choose an option: ";
}

void CatchPokemon(Pokemon*& inventory) {
   string name, type;
    int level;

    cout << "Enter the name of the Pokemon: ";
    cin >> name;
    cout << "Enter the type of the Pokemon: ";
    cin >> type;
    cout << "Enter the level of the Pokemon: ";
    cin >> level;

    Pokemon* newPokemon = new Pokemon;
    newPokemon->name = name;
    newPokemon->type = type;
    newPokemon->level = level;
    newPokemon->next = nullptr;

    if (!inventory) {
        inventory = newPokemon;
    }
    else {
        Pokemon* current = inventory;
        while (current->next) {
            current = current->next;
        }
        current->next = newPokemon;
    }

    cout << "You caught a " << name << "!\n";
}

void TypeSorting(Pokemon* inventory) {
    string type;
    if (!inventory) {
        cout << "Inventory is empty.\n";
        return;
    }

    cout << "Enter the type of Pok?mon you want to display (earth, fire, water): ";
    cin >> type;

    int count = 1;
    Pokemon* current = inventory;
    while (current) {
        if (current->type == type) {
            cout << count << ". Name: " << current->name << ", Type: " << current->type << ", Level: " << current->level << "\n";
            count++;
        }
        current = current->next;
    }

    if (count == 1) {
        cout << "No " << type << " type Pok?mon found in inventory.\n";
    }
}

void DisplayInventory(Pokemon* inventory) {
    if (!inventory) {
        cout << "Inventory is empty.\n";
        return;
    }

    Pokemon* earthList = nullptr;
    Pokemon* fireList = nullptr;
    Pokemon* waterList = nullptr;


    Pokemon* current = inventory;
    while (current) {
        Pokemon* next = current->next;

        if (current->type == "earth") {
            current->next = earthList;
            earthList = current;
        }
        else if (current->type == "fire") {
            current->next = fireList;
            fireList = current;
        }
        else if (current->type == "water") {
            current->next = waterList;
            waterList = current;
        }

        current = next;
    }


    int count = 1;
    current = earthList;
    while (current) {
        cout << count << ". Name: " << current->name << ", Type: " << current->type << ", Level: " << current->level << "\n";
        current = current->next;
        count++;
    }

    current = fireList;
    while (current) {
        cout << count << ". Name: " << current->name << ", Type: " << current->type << ", Level: " << current->level << "\n";
        current = current->next;
        count++;
    }

    current = waterList;
    while (current) {
        cout << count << ". Name: " << current->name << ", Type: " << current->type << ", Level: " << current->level << "\n";
        current = current->next;
        count++;
    }
}
void BuildTeam(Pokemon* inventory) {
    if (!inventory) {
        cout << "Inventory is empty. Cannot build a team.\n";
        return;
    }

    cout << "Select 5 Pokemon for your team:\n";
    DisplayInventory(inventory);

    Pokemon* team[5] = { nullptr };

    for (int i = 0; i < 5; ++i) {
        int choice;
        cout << "Select Pokemon " << i + 1 << ": ";
        cin >> choice;

        int count = 5;
        Pokemon* current = inventory;
        while (current && count < choice) {
            current = current->next;
            count++;
        }

        if (!current) {
            cout << "Invalid selection. Try again.\n";
            --i;
            continue;
        }

        team[i] = current;
    }

    cout << "Your team has been selected:\n";
    for (int i = 0; i < 5; ++i) {
        if (team[i]) {
            cout << i + 1 << ". Name: " << team[i]->name << ", Type: " << team[i]->type << ", Level: " << team[i]->level << "\n";
        }
    }
}

int main() {
    Pokemon* inventory = nullptr; 

    bool exit = false;
    while (!exit) {
        DisplayMenu();

        int choice;
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1:
            CatchPokemon(inventory);
            break;
        case 2:
            TypeSorting(inventory);
            break;
        case 3:
            DisplayInventory(inventory);
            break;
        case 4:
            BuildTeam(inventory);
            break;
        case 5:
            exit = true;
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    }


    Pokemon* current = inventory;
    while (current) {
        Pokemon* next = current->next;
        delete current;
        current = next;
    }

    return 0;
}
