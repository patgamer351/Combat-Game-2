//Basically The Combat Game I Created In Python Some Time Ago But Its Now In C++
//By Patrick Cornale


#include <iostream>     // Input and Output

#include <fstream>      //Files and Saves
#include <filesystem>

#include <ctime>        //Random Numbers


#ifdef __WIN32
	#define CLEAR system("cls")

#elif __APPLE__ || __unix__
		#define CLEAR system("clear");
#else
		#define CLEAR
		std::cout<<"Can't clear, but ima just test system(\"clear\")"<<std::endl;
		system("clear");
#endif


const std::string SavesLocation = "Saves";


class Player
{
public:
    static std::string CharacterName;

    static int Level;
    static int Class;

    static int Wins;
    static int Losses;

    static int Decision;
    static int hp;

    static int DamageDealt;
    static int HitChance;
    static int CritChance;
    static int LifeHealed;
    static int DodgeChange;
    static int BlockChance;
    static int FleeChance;
};

class Opponent
{
public:
    static int hp;

    static int DealDamage;
    static int HitChance;
    static int CritChance;
};


void text(const std::string &text)
{
    CLEAR;
    std::cout<<text;
    std::cin.ignore();
    std::cin.get();
}


int Attack()
{
    Player player;
    player.DamageDealt = rand()%18;

    if (player.Class == 1)
    {
        return player.DamageDealt * player.Level;
    }
    else
    {
        return player.DamageDealt;
    }
}


bool Flee()
{
    Player player;

    if (player.Class != 4)
    {
        player.FleeChance = rand() % 100;
    }
    else
    {
        player.FleeChance = rand()%100 + player.Level;
    }
    if (player.FleeChance > 80)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void win()
{
    Player player;

    std::ofstream WinsFile;
    WinsFile.open(SavesLocation+'/'+player.CharacterName+'/'+"Wins.txt");
    WinsFile << 0;
    WinsFile.close();
}


void loss()
{

}


void Battle()
{
    Player player;
    Opponent opponent;

    player.hp = 100;

    opponent.hp = 100*player.Level;

    while (true)
    {
        CLEAR;
        std::cout<<"You're on "<<player.hp<<" hp"<<std::endl;
        std::cout<<"Your opponent is on "<<opponent.hp<<" hp"<<std::endl;
        std::cout<<"1.Attack 2.Block 3.Heal Yourself 4.Flee: ";
        std::cin>>player.Decision;
        switch (player.Decision)
        {
        case 1: // attack
            break;
        case 2: // block
            break;
        case 3: // heal
            break;
        case 4: // flee
            if (Flee() == true)
            {
                std::cout<<"You Fleed";
            }
            else
            {
                std::cout<<"You Failed To Escape";
            }
            break;
        default:
            std::cout<<"You stood there confused...";
            break;
        }

        if (rand()%100 < 20)
        {
            if (rand()%100 > 80)
            {
                //crit
            }
            else
            {
                // no crit
            }
        }
        else
        {
            std::cout<<"Your opponnent missed";
        }

        if (opponent.hp <= 0)
        {
            text("Your opponent fainted");
            // win();
        }
        else if (player.hp <= 0)
        {
            text("You fainted");
            // loss();
        }
        
    }
}


void LoadSave()
{
    CLEAR;
    Player player;

    std::cout<<"Enter your Character's name: ";
    std::cin>>player.CharacterName;

    if (std::filesystem::exists(SavesLocation+'/'+player.CharacterName))
    {

        std::ifstream ClassFile(SavesLocation+'/'+player.CharacterName+'/'+"Class.txt");
        while (ClassFile >> player.Wins){}
        ClassFile.close();


        std::ifstream LevelFile(SavesLocation+'/'+player.CharacterName+'/'+"Level.txt");
        while (LevelFile >> player.Wins){}
        LevelFile.close();


        text(player.CharacterName+" has been found");

        Battle();
    }
    else
    {
        text("That character does not exist. ");
    }
}


void NewSave()
{
    Player player;

    std::filesystem::create_directory(SavesLocation);

    CLEAR;
    std::cout<<"What will be your character's name?: ";
    std::cin>>player.CharacterName;
    if (std::filesystem::exists(SavesLocation+'/'+player.CharacterName)) // checks if the character already exists 
    {
        text("That character already exists!");
    }
    else
    {
        std::filesystem::create_directories(SavesLocation+'/'+player.CharacterName);

        CLEAR;
        std::cout<<"What class shall "<<player.CharacterName<<" be"<<std::endl;
        std::cout<<"1, Warrior\n2, Tank\n3, Mage\n4, Assassin\nClass:";
        std::cin>>player.Class;

        std::ofstream ClassFile;
        ClassFile.open(SavesLocation+'/'+player.CharacterName+'/'+"Class.txt");
        ClassFile << player.Class;
        ClassFile.close();

        player.Level = 1;
        std::ofstream LevelFile;
        LevelFile.open(SavesLocation+'/'+player.CharacterName+'/'+"Level.txt");
        LevelFile << player.Level;
        LevelFile.close();

        std::ofstream WinsFile;
        WinsFile.open(SavesLocation+'/'+player.CharacterName+'/'+"Wins.txt");
        WinsFile << 0;
        WinsFile.close();

        std::ofstream LossesFile;
        LossesFile.open(SavesLocation+'/'+player.CharacterName+'/'+"Losses.txt");
        LossesFile << 0;
        LossesFile.close();

        text("Player Created! ");
    }
    Battle();
}


void DeleteSave()
{
    CLEAR;
    Player player;

    std::cout<<"Enter the name of the character you would like to delete: ";
    std::cin>>player.CharacterName;
    if (std::filesystem::exists(SavesLocation+'/'+player.CharacterName))
    {
        std::filesystem::remove_all(SavesLocation+'/'+player.CharacterName);
        CLEAR;
        text("Done!");
    }
    else
    {
        text(player.CharacterName+" couldn't be found");
    }
}


void Statistics()
{
    // float kdr;
    Player player;

    CLEAR;
    std::cout<<"Enter your Character's name: ";
    std::cin>>player.CharacterName;

    std::ifstream WinsFile(SavesLocation+'/'+player.CharacterName+"/Wins.txt");
    while (WinsFile >> player.Wins){}
    WinsFile.close();

    std::ifstream LossesFile(SavesLocation+'/'+player.CharacterName+"/Losses.txt");
    while (LossesFile >> player.Losses){}
    LossesFile.close();

    switch (player.Wins) // uses correct grammar 
    {
    case 0:
        std::cout<<player.CharacterName<<" has won no battles"<<std::endl;
        break;
    case 1:
        std::cout<<player.CharacterName<<" has won 1 battle"<<std::endl;
        break;
    default:
        std::cout<<player.CharacterName<<" has won "<<player.Wins<<" battles"<<std::endl;
        break;
    }

    switch (player.Losses) // uses correct grammar ...
    {
    case 0:
        std::cout<<player.CharacterName<<" has never lost a battle"<<std::endl;
        break;
    case 1:
        std::cout<<player.CharacterName<<" has lost 1 battle"<<std::endl;
        break;
    default:
        std::cout<<player.CharacterName<<" has lost "<<player.Losses<<" battles"<<std::endl;
        break;
    }

    std::cin.ignore();
    std::cin.get();
}


int menu()
{
    int selection;

    do
    {
        CLEAR;
        std::cout<<"COMBAT GAME\n1, Load Save\n2, Create New Save\n3, Delete Save\n4, Statistics\nSelect: ";
        std::cin>>selection;
    } while (!(selection > 0 && selection < 5));
    return selection;
}


int main()
{
    srand(time(NULL));

    while (true)
    {
        switch (menu())
        {
        case 1:
            LoadSave();
            break;
        case 2:
            NewSave();
            break;
        case 3:
            DeleteSave();
            break;
        case 4:
            Statistics();
            break;
        default:
            return 1;
        }
    }
}
