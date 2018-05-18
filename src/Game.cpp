#include "../include/Game.hpp"

Game::Game() {
    m_logger = new Logger();
}

Game::~Game() {
    if (m_logger != nullptr) delete m_logger;
    if (m_enemy != nullptr) delete m_enemy;
    if (m_player != nullptr) delete m_player;
}

void Game::InitialiseCombat() {
    m_adventureDepth++;
    m_enemy = new Enemy("Monster", m_adventureDepth);
}

void Game::EndCombat() {
    m_player->Reward(m_enemy->GoldWorth(), m_enemy->ExpWorth());
    m_logger->WriteLine("You have been rewarded " + std::to_string(m_enemy->GoldWorth()) + "g and " + std::to_string(m_enemy->ExpWorth()) + "exp! Spend them in town.");
}

bool Game::ProcessCommand(std::string command, std::string mainArg, std::string fullArg) {
    // quit
    if (command == "exit" || command == "quit") {
        if (m_gameState == GAMESTATE_TOWN) {
            m_gameState = GAMESTATE_MENU;
            m_logger->WriteLine("Quit game. Goodbye, " + m_player->GetName() + "!");
        }
        else if (m_gameState == GAMESTATE_MENU) {
            m_logger->WriteLine("Bye!");
            return false;
        }
        else {
            //m_logger->WriteCommandNotFound(command);
        }
    }

    // help
    else if (command == "help") {
        m_logger->WriteHelp(m_gameState);
    }

    // else, play the game!

    // process input based on game state
    switch (m_gameState)
    {
        case GAMESTATE_TITLE:
            m_gameState = GAMESTATE_MENU;
            m_logger->WriteHelp(m_gameState);
            break;
        
        case GAMESTATE_MENU:
            if (command == "new") {
                if (fullArg.length() > 0) {
                    m_player = new Player(fullArg, 10);
                    m_gameState = GAMESTATE_TOWN;
                    m_logger->WriteLine("Welcome to town, " + m_player->GetName() +"!");
                }
                else {
                    m_logger->WriteLine("Please specify a name for the brave new hero!");
                }
            }
            else if (command == "load") {
                if (fullArg.length() > 0) {
                    m_logger->WriteLine("Not yet implemented!");
                }
                else {
                    m_logger->WriteLine("Please specify a name for the hero you wish to awaken!");
                }
            }
            else if (command == "about") {
                m_logger->WriteLine("GitHub: https://github.com/techniman/cpp-cli-rpg");
                m_logger->WriteLine("Programmer: Will Thomas, technimanx@googlemail.com, https://github.com/techniman");
            }
            else if (command != "help") {
                m_logger->WriteCommandNotFound(command);
            }
            break;

        case GAMESTATE_TOWN:
            if (command == "rest") {
                // player try to pay for inn
                // else annoyed innkeeper grr
                // if player is super injured and also unable to pay, then they are stuck forever to die on the streets. Whoops
                m_player->Heal(0);
                m_logger->WriteLine(m_player->GetName() + "'s health replenished through rest! HP: " + m_player->CurrentHealth());
                m_logger->WriteLine("Saving is not yet implemented!");
            }
            else if (command == "travel") {
                if (m_player->HPPercentage() >= 0.2f) {
                    m_gameState = GAMESTATE_COMBAT;
                    m_logger->WriteLine("You venture out into the wilderness.");
                    InitialiseCombat();
                }
                else {
                    m_logger->WriteLine("You should think about resting up, first! HP: " + m_player->CurrentHealth());
                }
            }
            else if (command != "help" && command != "exit" && command != "quit") {
                m_logger->WriteCommandNotFound(command);
            }
            break;

        case GAMESTATE_COMBAT:
            bool takenTurn;
            takenTurn = false;
            if (command == "attack") {
                // attack the monster rargh!
                // use equipped weapon to hurt opponent. attacking always ends the turn
                m_enemy->Damage(m_player->AttackDamage());
                m_logger->WriteLine("You dealt " + std::to_string(m_player->AttackDamage()) + " damage to the " + m_enemy->GetName() + ".");
                takenTurn = true;

                // if enemy is defeated, ask to carry on in the wilderness or return home
                if (!m_enemy->IsAlive()) {
                    m_logger->WriteLine("WIP: You defeated " + m_enemy->GetName() + "! Now you return to town.");
                    EndCombat();
                    takenTurn = false;
                    m_logger->Write("Would you like to continue? Y/n > ");
                    std::string confirm;
                    if (std::getline(std::cin, confirm)) {
                        if (confirm == "Y" || confirm == "yes") {
                            InitialiseCombat();
                        }
                        else {
                            m_gameState = GAMESTATE_TOWN;
                        }
                    }
                }
            }
            else if (command == "cast") {
                // cast a spell zap!
                // check spellbook for arg1
                // if exists, do it and end turn
                //takenTurn = true;
                // else report failure
                m_logger->WriteLine("Not yet implemented!");
            }
            else if (command == "consume") {
                // consume a thing nom!
                // check inventory for arg1
                // if exists, consume it and end turn
                //takenTurn = true;
                // else report failure
                m_logger->WriteLine("Not yet implemented!");
            }
            else if (command == "status") {
                m_logger->WriteLine(m_player->GetName() + "'s HP: " + m_player->CurrentHealth() + " and " + m_enemy->GetName() + "'s HP: " + m_enemy->CurrentHealth());
            }
            else if (command == "run") {
                // make a random check
                // roll under a certain chance to successfully run away
                m_logger->WriteLine("for now, this is 100% successful and safe because development.");
                m_gameState = GAMESTATE_TOWN;
                // else, just end turn
                //takenTurn = true;
            }
            else if (command != "help") {
                m_logger->WriteCommandNotFound(command);
            }

            if (takenTurn) {
                // let enemy have a turn, probably just attacks player
                m_player->Damage(m_enemy->AttackDamage());
                // report player and enemy statuses
                m_logger->WriteLine(m_player->GetName() + "'s HP: " + m_player->CurrentHealth() + " and " + m_enemy->GetName() + "'s HP: " + m_enemy->CurrentHealth());
            }
            break;

        default:
            m_logger->WriteError("INVALID_GAMESTATE");
            m_gameState = GAMESTATE_MENU;
            break;
    }
    return true;
}
