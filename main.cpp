#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

class Player {
public:
    string name;
    int health;

    Player(string n) : name(n), health(3) {}

    void attack(Player &opponent) {
        int damage = 1;
        opponent.health -= damage;
        cout << name << " attacks " << opponent.name << " for " << damage << " damage!\n";
    }

    void defend() {
        int heal = 1;
        health += heal;
        cout << name << " defends and heals for " << heal << " health!\n";
    }

    bool isAlive() const {
        return health > 0;
    }
};

void gameLoop(Player &player1, Player &player2) {
    while (player1.isAlive() && player2.isAlive()) {
        cout << "\n" << player1.name << "'s health: " << player1.health << "\n";
        cout << player2.name << "'s health: " << player2.health << "\n";

        cout << player1.name << "'s turn! (1: Attack, 2: Defend, L to finish): ";
        string input;
        cin >> input;
        if (input == "L" || input == "l") break;
        int choice = stoi(input);
        if (choice == 1) {
            player1.attack(player2);
        } else if (choice == 2) {
            player1.defend();
        }

        if (!player2.isAlive()) break;

        cout << player2.name << "'s turn! (1: Attack, 2: Defend, L to finish): ";
        cin >> input;
        if (input == "L" || input == "l") break;
        choice = stoi(input);
        if (choice == 1) {
            player2.attack(player1);
        } else if (choice == 2) {
            player2.defend();
        }
    }

    cout << "\nGame Over.\n";
    if (player1.health > player2.health) {
        cout << player1.name << " wins with " << player1.health << " health left!\n";
    } else if (player2.health > player1.health) {
        cout << player2.name << " wins with " << player2.health << " health left!\n";
    } else {
        cout << "It's a tie!\n";
    }
}

int main() {
    srand(static_cast<unsigned>(time(0)));

    cout << "Enter name for Player 1: ";
    string name1;
    cin >> name1;
    Player player1(name1);

    cout << "Enter name for Player 2: ";
    string name2;
    cin >> name2;
    Player player2(name2);

    gameLoop(player1, player2);

    return 0;
}