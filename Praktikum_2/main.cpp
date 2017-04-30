#include "Ringpuffer.h"

void printIntro()
{
    std::cout << "---------------------------" << std::endl;
    std::cout << "Ringpuffer Solutions inc." << std::endl;
    std::cout << "---------------------------" << std::endl;
}

void printOptions()
{
    std::cout << "1) Backup einfuege" << std::endl;
    std::cout << "2) Backup suchen" << std::endl;
    std::cout << "3) Alle backups ausgeben" << std::endl;
}

int getInputInt(int min, int max)
{
    int ret;

    bool firstRun = true;

    do
    {
        std::cout << "?> ";

        //error handling incase user entered a string or integers too high, low in value
        if(!firstRun)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        firstRun = false;
    }
    while(!(std::cin >> ret) || (ret < min) || (ret > max));

    return ret;
}

std::string getInputStr(const std::string& prefix)
{
    std::string res;

    if(prefix.length() == 0)
        ;
    else
        std::cout << prefix << " ";
    std::cout << "?> ";

    std::cin >> res;
    return res;
}

void addData(Ringpuffer& puffer)
{
    std::cout << "+Neuen Datensatz einfuegen" << std::endl;
    std::string description = getInputStr("Beschreibung");
    std::string data = getInputStr("Daten");

    puffer.addNode(description, data);
}

RingNode* searchData(Ringpuffer& puffer)
{
    std::cout << "+Nach welchen Daten soll gesucht werden?" << std::endl;
    std::string description = getInputStr("");
    return puffer.search(description);
}

int main(void)
{
    Ringpuffer puffer;

    printIntro();

    while(true)
    {
        printOptions();
        int option = getInputInt(1, 3);

        RingNode* found = nullptr;

        switch (option) {
            case 1:
                addData(puffer);
                break;
            case 2:
                found = searchData(puffer);
                if(found != nullptr)
                {
                    std::cout << "+ Datensatz gefunden" << std::endl;
                    puffer.print(std::cout, found);
                }
                else
                {
                    std::cout <<"+ Datensatz konnte nicht gefunden werden!" << std::endl;
                }
                break;
            case 3:
                puffer.print();
                break;
            default:
                return -1;
                //this shouldn't occur
        }
    }
}
