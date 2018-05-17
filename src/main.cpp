#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <iostream>

template<typename Out>
void split(const std::string &s, char delim, Out result) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        *(result++) = item;
    }
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

enum GAME_STATE
{
    GAME_STATE_TITLE = 0,
    GAME_STATE_MENU = 1,
    GAME_STATE_TOWN = 2,
    GAME_STATE_COMBAT = 3
};
unsigned int g_gameState = GAME_STATE_MENU;

class Creature {
protected:
    std::string name;
    unsigned int currentHp;
    unsigned int maxHp;

public:
    Creature(std::string name) {
        this->name = name;
        maxHp = 10;
        currentHp = maxHp;
    }

    // true if player survives damage; false otherwise, and hp set to 0.
    bool Damage(unsigned int damage) noexcept {
        if (currentHp > damage) {
            currentHp -= damage;
            return true;
        }
        currentHp = 0;
        return false;
    }

    // increases hp by [healing], limited by player's maxHp.
    void Heal(unsigned int healing) noexcept {
        currentHp += healing;
        if (currentHp > maxHp) {
            currentHp = maxHp;
        }
    }

    float HealthPercentage() const noexcept {
        return (float)currentHp / (float)maxHp;
    }

    unsigned int CurrentHP() const noexcept {
        return currentHp;
    }

    unsigned int MaxHP() const noexcept {
        return maxHp;
    }

    // returns "[current] / [max]"
    std::string CurrentHealth() const noexcept {
        return std::to_string(CurrentHP()) + " / " + std::to_string(MaxHP());
    }

    std::string Name() const noexcept {
        return name;
    }
};

// like a creature that can spend exp and gold
class PlayerState : public Creature {
    private:
        unsigned int currentExp;
        unsigned int currentGold;
        // SRD:
        //  fighter is p24
        //  exp reqs table is p56
        //  equipment is p62
        //  
        //  //human has +1 to each ability score
        //  fighter hp: 10 + con mod
        //  fighter hp per level: (1d10 or 6) + con mod
        //  assuming a strength of 18, that would be +4 to damage
        //  assume a con of 16, gives +3
        //  assume chain mail, longsword and a shield
        //  chain mail: AC 16, req Str 15
        //  no, give 'em leather armour to start with: AC 11+dexmod
        //  shield: AC+2
        unsigned int defense = 13;
        //  shortsword: 1d6 damage
        //  longsword: 1d8 damage
        //  greatsword: 2d6 damage

    public:
        PlayerState() : Creature("") { }

        // ctor
        PlayerState(std::string name) : Creature(name) {
            currentExp = 0;
            currentGold = 0;
        }

        // dctor; should be fine to be empty
        ~PlayerState() {

        }

        // true if player has sufficient gold; false otherwise.
        bool Pay(unsigned int goldCost) noexcept {
            if (currentGold >= goldCost) {
                currentGold -= goldCost;
                return true;
            }
            return false;
        }

        // true if player has sufficient exp; false otherwise.
        bool LevelUp(unsigned int expCost) noexcept {
            if (currentExp >= expCost) {
                currentExp -= expCost;
                return true;
            }
            return false;
        }

        // increases gold by [gold], and exp by [experience].
        void Reward(unsigned int gold, unsigned int experience) noexcept {
            currentGold += gold;
            currentExp += experience;
        }

        unsigned int Attack = 8; // avg longsword = 4, + strmod = 4
};
PlayerState g_playerState;

// like a creature with exp and gold
class EnemyState : public Creature {
    private:

    public:
        EnemyState() : Creature("") { }

        EnemyState(std::string name) : Creature(name) {

        }

        unsigned int goldWorth = 5;
        unsigned int expWorth = 10;

        unsigned int Attack = 3;
};
EnemyState g_enemyState;

void InitialiseCombat() {
    g_enemyState = EnemyState("Enemy");
}

void EndCombat() {
    g_playerState.Reward(g_enemyState.goldWorth, g_enemyState.expWorth);
}

void Write(std::string out) {
    std::cout << out;
}

void WriteLine(std::string out) {
    std::cout << out << std::endl;
}

void WriteHelp() {
    WriteLine("Available commands are:");
    
    switch (g_gameState)
    {
        case GAME_STATE_MENU:
            WriteLine("new <name>: start a new game (with name [name])");
            WriteLine("load <name>: load an existing game with name <name>");
            //WriteLine("contact: print contact details for the developer (hello! we're friendly!)");
            WriteLine("about: show general information about the game; who developed it and why");
            // exit: exit the game
            break;

        case GAME_STATE_TOWN:
            WriteLine("rest: restore your health, heal your wounds, and save the game");
            WriteLine("travel: go out in search of adventure and danger");
            // buy <item>: attempt to buy <item>
            // sell <item>: sell <item>
            // don <equipment>: attempt to don <equipment>
            // doff <equipment>: attempt to doff <equipment>
            // learn/levelup/skillup: attempt to spend exp
            // quit: quit to the menu (alias: exit)
            break;

        case GAME_STATE_COMBAT:
            WriteLine("attack: hit the damn thig with your hitty stick");
            WriteLine("cast <spell>: cast <spell> at the target");
            WriteLine("consume <item>: verb a consumable item");
            WriteLine("run: attempt to flee from your opponent");
            break;

        default:
            break;
    }

    WriteLine("exit: quit the game. currently works everywhere, todo: improve this");
    WriteLine("help: this handy help message :)");
}

void WriteCommandNotFound(std::string unknownCommand) {
    WriteLine("I'm afraid that " + unknownCommand + " is not a valid command; try 'help'. Sorry!");
}

void WriteError(std::string errorMessage) {
    WriteLine("The game has encountered an error: " + errorMessage + "! Please send this message to the developer, and tell them what you were doing beforehand. You can find contact details with the 'about' command at the main menu. Thank you! <3");
}

// arguments are ignored
int main(int argc, char ** args) {
    // intro
    WriteLine("C++-based command-line RPG, by Will Thomas.");
    WriteLine("Still in-development, so if anything breaks, please let me know! Cheers, and enjoy!");

    // TODO: should change the loop to just interpret commands and send command & arguments to game object

    // begin game loop
    std::string lineIn;
    Write("\n> ");
    while (std::getline(std::cin, lineIn)) {
        std::vector<std::string> input = split(lineIn, ' ');
        std::string command = input.at(0);
        
        // quit
        if (command == "exit" || command == "quit") {
            if (g_gameState == GAME_STATE_TOWN) {
                g_gameState = GAME_STATE_MENU;
                WriteLine("Quit game. See you later, " + g_playerState.Name() + "!");
            }
            else if (g_gameState == GAME_STATE_MENU) {
                WriteLine("Bye!");
                break;
            }
            else {
                WriteCommandNotFound(command);
            }
        }

        // help
        if (command == "help") {
            WriteHelp();
        }

        // else, play the game!

        // process input based on game state
        switch (g_gameState)
        {
            case GAME_STATE_TITLE:
                g_gameState = GAME_STATE_MENU;
                WriteHelp();
                break;
            
            case GAME_STATE_MENU:
                if (command == "new") {
                    if (input.size() > 1) {
                        g_playerState = PlayerState(input.at(1));
                        g_gameState = GAME_STATE_TOWN;
                        WriteLine("Welcome to town, " + g_playerState.Name() +"!");
                    }
                    else {
                        WriteLine("Please specify a name for the brave new hero!");
                    }
                }
                else if (command == "load") {
                    if (input.size() > 1) {
                        WriteLine("Not yet implemented!");
                    }
                    else {
                        WriteLine("Please specify a name for the hero you wish to awaken!");
                    }
                }
                else if (command == "about") {
                    WriteLine("GitHub: https://github.com/techniman/cpp-cli-rpg");
                    WriteLine("Programmer: Will Thomas, technimanx@googlemail.com, https://github.com/techniman");
                }
                else if (command != "help") {
                    WriteCommandNotFound(command);
                }
                break;

            case GAME_STATE_TOWN:
                if (command == "rest") {
                    // player try to pay for inn
                    // else annoyed innkeeper grr
                    // if player is super injured and also unable to pay, then they are stuck forever to die on the streets. Whoops
                    g_playerState.Heal(g_playerState.MaxHP());
                    WriteLine(g_playerState.Name() + "'s health replenished through rest! HP: " + g_playerState.CurrentHealth());
                    WriteLine("Saving is not yet implemented!");
                }
                else if (command == "travel") {
                    if (g_playerState.HealthPercentage() >= 0.2f) {
                        g_gameState = GAME_STATE_COMBAT;
                        WriteLine("You venture out into the wilderness.");
                    }
                    else {
                        WriteLine("You should think about resting up, first! HP: " + g_playerState.CurrentHealth());
                    }
                }
                else if (command != "help") {
                    WriteCommandNotFound(command);
                }
                break;

            case GAME_STATE_COMBAT:
                bool takenTurn;
                takenTurn = false;
                if (command == "attack") {
                    // attack the monster rargh!
                    // use equipped weapon to hurt opponent. attacking always ends the turn
                    g_enemyState.Damage(g_playerState.Attack);
                    WriteLine("You dealt " + std::to_string(g_playerState.Attack) + " damage to the " + g_enemyState.Name() + ".");
                    takenTurn = true;

                    // if enemy is defeated, ask to carry on in the wilderness or return home
                    if (g_enemyState.CurrentHP() == 0) {
                        WriteLine("WIP: You defeated " + g_enemyState.Name() + "! Now you return to town.");
                        takenTurn = false;
                        g_gameState = GAME_STATE_TOWN;
                    }
                }
                else if (command == "cast") {
                    // cast a spell zap!
                    // check spellbook for arg1
                    // if exists, do it and end turn
                    //takenTurn = true;
                    // else report failure
                    WriteLine("Not yet implemented!");
                }
                else if (command == "consume") {
                    // consume a thing nom!
                    // check inventory for arg1
                    // if exists, consume it and end turn
                    //takenTurn = true;
                    // else report failure
                    WriteLine("Not yet implemented!");
                }
                else if (command == "run") {
                    // make a random check
                    // roll under a certain chance, successfully run away
                    WriteLine("for now, this is 100% successful and safe because development.");
                    g_gameState = GAME_STATE_TOWN;
                    // else, just end turn
                    //takenTurn = true;
                }
                else if (command != "help") {
                    WriteCommandNotFound(command);
                }

                if (takenTurn) {
                    // let enemy have a turn, probably just attacks player
                    g_playerState.Damage(g_enemyState.Attack);
                    // report player and enemy statuses
                    WriteLine(g_playerState.Name() + "'s HP: " + g_playerState.CurrentHealth() + " and " + g_enemyState.Name() + "'s HP: " + g_enemyState.CurrentHealth());
                }
                break;

            default:
                WriteError("INVALID_GAME_STATE");
                g_gameState = GAME_STATE_MENU;
                break;
        }

        // begin the next line to prompt user input
        Write("\n> ");
    }

    return 0;
}
