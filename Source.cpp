#include <iostream>
#include <string>
#include <ctime>

// Constants
const int START_HEALTH = 100;
const int START_ATTACK = 20;
const int START_DEFENSE = 10;
const int COOLDOWN_TIME = 3;
const float BUFF_AMOUNT = 0.1f; // 10% extra
const int MAX_LOG_ENTRIES = 50; // For battle report logging

// ANSI escape codes for colors
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"

// Arena types
enum ArenaType { FIRE, ICE, JUNGLE };

// Character base class
class Character {
    friend class Arena;
protected:
    std::string name;
    int health;
    int attack;
    int defense;
    int cooldown;

public:
    Character(std::string n) {
        name = n;
        health = START_HEALTH;
        attack = START_ATTACK;
        defense = START_DEFENSE;
        cooldown = 0;
    }

    virtual ~Character() {}

    virtual void doAttack(Character& target) = 0;
    virtual void doSpecial(Character& target) = 0;

    void getHit(int damage) {
        if (damage > defense) {
            health = health - (damage - defense);
        }
        if (health < 0) {
            health = 0;
        }
    }

    bool checkAlive() {
        if (health > 0) {
            return true;
        }
        return false;
    }

    std::string getName() { return name; }
    int getHealth() { return health; }
    int getAttack() { return attack; }
    int getDefense() { return defense; }

    // Operator overloading
    int operator+(const Character& other) {
        return attack + other.attack; // Combine attack for combo
    }

    bool operator==(const Character& other) {
        return (health + attack + defense) == (other.health + other.attack + other.defense);
    }

    friend std::ostream& operator<<(std::ostream& os, const Character& c) {
        os << c.name << " (HP: " << c.health << ", ATK: " << c.attack << ", DEF: " << c.defense << ")";
        return os;
    }

    bool canUseSpecial() {
        if (cooldown == 0) {
            return true;
        }
        return false;
    }

    void setCooldown() {
        cooldown = COOLDOWN_TIME;
    }

    void updateCooldown() {
        if (cooldown > 0) {
            cooldown = cooldown - 1;
        }
    }
};

// Warrior class
class Warrior : public Character {
public:
    Warrior(std::string n) : Character(n) {}

    void doAttack(Character& target) {
        std::cout << YELLOW << name << " swings a sword!" << RESET << "\n";
        target.getHit(attack);
    }

    void doSpecial(Character& target) {
        if (canUseSpecial()) {
            std::cout << YELLOW << name << " does a big smash!" << RESET << "\n";
            target.getHit(attack * 2);
            setCooldown();
        }
        else {
            std::cout << RED << "Special not ready!" << RESET << "\n";
        }
    }
};

// Mage class
// Special Ability: Temporary Invisibility - Allows the Mage to dodge the next attack
class Mage : public Character {
private:
    bool invisible;
public:
    Mage(std::string n) : Character(n) {
        invisible = false;
    }

    void doAttack(Character& target) {
        if (invisible == false) {
            std::cout << YELLOW << name << " throws a fireball!" << RESET << "\n";
            target.getHit(attack);
        }
        else {
            std::cout << CYAN << name << " is hiding!" << RESET << "\n";
        }
    }

    void doSpecial(Character& target) {
        if (canUseSpecial()) {
            std::cout << CYAN << name << " turns invisible!" << RESET << "\n";
            invisible = true;
            setCooldown();
        }
        else {
            std::cout << RED << "Special not ready!" << RESET << "\n";
        }
    }

    void resetInvisible() {
        invisible = false;
    }

    bool getIsInvisible() { return invisible; }
};

// LegendaryCharacter class (Bonus Task)
// Special Ability: Heal - Restores health
class LegendaryCharacter : public Character {
public:
    LegendaryCharacter(std::string n) : Character(n) {
        health = START_HEALTH + 50; // Boosted stats
        attack = START_ATTACK + 10;
        defense = START_DEFENSE + 5;
    }

    void doAttack(Character& target) {
        std::cout << MAGENTA << name << " unleashes a legendary strike!" << RESET << "\n";
        target.getHit(attack);
    }

    void doSpecial(Character& target) {
        if (canUseSpecial()) {
            std::cout << MAGENTA << name << " uses healing aura!" << RESET << "\n";
            health = health + 30; // Heal self
            if (health > START_HEALTH + 50) {
                health = START_HEALTH + 50; // Cap at max
            }
            setCooldown();
        }
        else {
            std::cout << RED << "Special not ready!" << RESET << "\n";
        }
    }
};

// Arena class
class Arena {
private:
    std::string arenaName;
    ArenaType arenaType;
    Character* fighters[2];
    int numFighters;

public:
    Arena(std::string n, ArenaType t) {
        arenaName = n;
        arenaType = t;
        numFighters = 0;
        fighters[0] = nullptr;
        fighters[1] = nullptr;
    }

    void addFighter(Character* c) {
        if (numFighters < 2) {
            fighters[numFighters] = c;
            numFighters = numFighters + 1;
        }
    }

    void giveArenaBuff() {
        for (int i = 0; i < 2; i++) {
            if (fighters[i] != nullptr) {
                if (arenaType == FIRE) {
                    float extra = fighters[i]->getAttack() * BUFF_AMOUNT;
                    fighters[i]->attack = static_cast<int>(fighters[i]->getAttack() + extra);
                }
                if (arenaType == ICE) {
                    float extra = fighters[i]->getDefense() * BUFF_AMOUNT;
                    fighters[i]->defense = static_cast<int>(fighters[i]->getDefense() + extra);
                }
                if (arenaType == JUNGLE) {
                    float extra = fighters[i]->getHealth() * BUFF_AMOUNT;
                    fighters[i]->health = static_cast<int>(fighters[i]->getHealth() + extra);
                }
            }
        }
    }

    Character* getFighter(int i) {
        if (i < 2) {
            return fighters[i];
        }
        return nullptr;
    }

    std::string getName() { return arenaName; }
};

// Battle Report Logger (Bonus Task)
class BattleLogger {
private:
    std::string logEntries[MAX_LOG_ENTRIES];
    int numEntries;

public:
    BattleLogger() {
        numEntries = 0;
        for (int i = 0; i < MAX_LOG_ENTRIES; i++) {
            logEntries[i] = "";
        }
    }

    void addLog(std::string entry) {
        if (numEntries < MAX_LOG_ENTRIES) {
            logEntries[numEntries] = entry;
            numEntries = numEntries + 1;
        }
    }

    void showLog() {
        std::cout << BLUE << "\n========================================\n";
        std::cout << "           BATTLE REPORT\n";
        std::cout << "========================================\n" << RESET;
        for (int i = 0; i < numEntries; i++) {
            if (logEntries[i] != "") {
                std::cout << CYAN << " - " << logEntries[i] << "\n" << RESET;
            }
        }
        std::cout << BLUE << "========================================\n" << RESET;
    }
};

// Function to display stats with enhanced visuals
void displayStats(Character* c) {
    std::cout << GREEN << "----------------------------------------\n";
    std::cout << "  " << c->getName() << "'s Stats\n";
    std::cout << "----------------------------------------\n" << RESET;
    std::cout << "  Health: " << RED << c->getHealth() << RESET << "\n";
    std::cout << "  Attack: " << YELLOW << c->getAttack() << RESET << "\n";
    std::cout << "  Defense: " << BLUE << c->getDefense() << RESET << "\n";
    std::cout << "  Special ready? ";
    if (c->canUseSpecial()) {
        std::cout << GREEN << "Yes\n" << RESET;
    }
    else {
        std::cout << RED << "No\n" << RESET;
    }
    std::cout << GREEN << "----------------------------------------\n" << RESET;
}

// GameManager class
class GameManager {
private:
    Arena arena;
    Character* player1;
    Character* player2;
    BattleLogger logger;

public:
    GameManager(Character* p1, Character* p2) : arena("Fire Arena", FIRE), player1(p1), player2(p2) {
        arena.addFighter(player1);
        arena.addFighter(player2);
        arena.giveArenaBuff();
        logger.addLog("Battle starts in Fire Arena!");
    }

    void startGame() {
        std::cout << MAGENTA << "\n========================================\n";
        std::cout << "         Welcome to Fantasy Arena\n";
        std::cout << "========================================\n" << RESET;
        std::cout << "Select your character:\n";
        std::cout << CYAN << "  [1] " << player1->getName() << "\n";
        std::cout << "  [2] " << player2->getName() << "\n" << RESET;
        int choice;
        std::cout << "Enter 1 or 2: ";
        std::cin >> choice;
        Character* activePlayer = (choice == 1) ? player1 : player2;
        Character* opponent = (choice == 1) ? player2 : player1;

        std::string logMessage = "Player selected " + activePlayer->getName();
        logger.addLog(logMessage);

        std::cout << YELLOW << "\nBattle starts in " << arena.getName() << "!\n" << RESET;
        displayStats(player1);
        displayStats(player2);

        int turn = 0;
        while (player1->checkAlive() && player2->checkAlive()) {
            std::cout << BLUE << "\n========================================\n";
            std::cout << "          Turn " << turn + 1 << "\n";
            std::cout << "========================================\n" << RESET;
            std::cout << activePlayer->getName() << "'s move!\n";
            std::cout << GREEN << "Options:\n" << RESET;
            std::cout << "  [1] Attack\n";
            std::cout << "  [2] Use Special\n";
            std::cout << "Choose: ";
            int action;
            std::cin >> action;

            if (action == 1 || action == 2) {
                if (action == 1) {
                    activePlayer->doAttack(*opponent);
                    logger.addLog(activePlayer->getName() + " attacks " + opponent->getName());
                }
                else {
                    activePlayer->doSpecial(*opponent);
                    logger.addLog(activePlayer->getName() + " uses special on " + opponent->getName());
                }
            }
            else {
                std::cout << RED << "Invalid! Attacking anyway.\n" << RESET;
                activePlayer->doAttack(*opponent);
                logger.addLog(activePlayer->getName() + " attacks (default) " + opponent->getName());
            }

            Mage* mage = dynamic_cast<Mage*>(opponent);
            if (mage && mage->getIsInvisible()) {
                std::cout << CYAN << opponent->getName() << " dodged!\n" << RESET;
                logger.addLog(opponent->getName() + " dodged attack");
                mage->resetInvisible();
            }

            activePlayer->updateCooldown();
            displayStats(player1);
            displayStats(player2);

            // Switch turns
            Character* temp = activePlayer;
            activePlayer = opponent;
            opponent = temp;
            turn = turn + 1;
        }

        if (player1->checkAlive()) {
            std::cout << GREEN << "\n========================================\n";
            std::cout << "         " << player1->getName() << " wins!\n";
            std::cout << "========================================\n" << RESET;
            logger.addLog(player1->getName() + " wins the battle!");
        }
        else {
            std::cout << GREEN << "\n========================================\n";
            std::cout << "         " << player2->getName() << " wins!\n";
            std::cout << "========================================\n" << RESET;
            logger.addLog(player2->getName() + " wins the battle!");
        }

        logger.showLog();
    }
};

int main() {
    std::cout << MAGENTA << "========================================\n";
    std::cout << "        Character Selection\n";
    std::cout << "========================================\n" << RESET;
    std::cout << "Choose your character:\n";
    std::cout << CYAN << "  [1] Warrior\n";
    std::cout << "  [2] Mage\n";
    std::cout << "  [3] Legendary\n" << RESET;
    std::cout << "Enter choice: ";
    int charChoice;
    std::cin >> charChoice;

    Character* player1;
    if (charChoice == 1) {
        player1 = new Warrior("Bob the Warrior");
    }
    else if (charChoice == 2) {
        player1 = new Mage("Alice the Mage");
    }
    else {
        player1 = new LegendaryCharacter("Draco the Legend");
    }

    std::cout << "\nChoose opponent:\n";
    std::cout << CYAN << "  [1] Warrior\n";
    std::cout << "  [2] Mage\n";
    std::cout << "  [3] Legendary\n" << RESET;
    std::cout << "Enter choice: ";
    std::cin >> charChoice;

    Character* player2;
    if (charChoice == 1) {
        player2 = new Warrior("Enemy Warrior");
    }
    else if (charChoice == 2) {
        player2 = new Mage("Enemy Mage");
    }
    else {
        player2 = new LegendaryCharacter("Enemy Legend");
    }

    GameManager game(player1, player2);
    game.startGame();

    // Clean up
    delete player1;
    delete player2;

    return 0;
}