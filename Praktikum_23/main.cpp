#include "tree.h"

#include <fstream>

void printIntro()
{
    std::cout << "---------------------------" << std::endl;
    std::cout << "LambdaTree Solutions inc." << std::endl;
    std::cout << "---------------------------" << std::endl;
}

void printOptions()
{
    std::cout << "1) Datensatz einfuegen, manuell" << std::endl;
    std::cout << "2) Datensatz einfuegen, CSV datei" << std::endl;
    std::cout << "3) Datensatz loeschen" << std::endl;
    std::cout << "4) Suchen" << std::endl;
    std::cout << "5) Datenstruktur anzeigen" << std::endl;
}

int getInputInt(const std::string& prefix, int min, int max)
{
    int ret;

    bool firstRun = true;

    do
    {
        if(prefix.length() == 0)
            ;
        else
            std::cout << prefix << " ";

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

void addData(Tree& tree)
{
    std::cout << "+ Bitte geben sie den Datensatz ein" << std::endl;
    std::string name = getInputStr("Name");
    std::string alterStr = getInputStr("Alter");
    std::string einkommenStr = getInputStr("Einkommen");
    std::string plzStr = getInputStr("PLZ");

    int alter = std::stoi(alterStr);
    double einkommen = std::stod(einkommenStr);
    int plz = std::stoi(plzStr);

    tree.insertNode(name, alter, einkommen, plz);

    std::cout << "+ Ihr Datensatz wurde eingefuegt" << std::endl;
}

void searchTree(Tree& tree)
{
    std::cout << "+ Bitte geben Sie den zu suchenden Datensatz an" << std::endl;
    std::string name = getInputStr("Name");

    auto nodes = tree.search(name);

    std::cout << "+ Fundstellen:" << std::endl;

    for(size_t i = 0; i < nodes.size(); ++i)
    {
        Tree::printNode(nodes[i]);
    }
}

void deleteNode(Tree& tree)
{
    std::cout << "+ Bitte geben Sie den zu loeschenden Datensatz an" << std::endl;
    std::string posIdStr = getInputStr("PosID");

    int posId = std::stoi(posIdStr);
    bool success = tree.deleteNode(posId);
    if(success)
    {
        std::cout << "+ Datensatz wurde geloescht" << std::endl;
    }
    else
    {
        std::cout << "+ Dieser Datensatz existiert nicht" << std::endl;
    }
}

void insertCSV(Tree& tree)
{
    std::string fileName = "ExportZielAnalyse.csv";
    std::cout << "+ Import von \"" << fileName + "\"" << std::endl;

    std::ifstream file(fileName);
    while(file.good())
    {
        std::string name;
        std::string tmp;

        int age;
        double income;
        int plz;

        getline(file, name, ',');
        getline(file, tmp, ',');

        age = std::stoi(tmp);

        getline(file, tmp, ',');
        income = std::stod(tmp);

        getline(file, tmp, ',');
        plz = std::stoi(tmp);

        tree.insertNode(name, age, income, plz);
    }
}

int main(void)
{
    Tree tree;

    printIntro();

    //insertCSV(tree);
    //tree.printTree();

    while(true)
    {
        printOptions();
        int option = getInputInt("", 1, 5);

        switch (option) {
            case 1:
                addData(tree);
                break;
            case 2:
                insertCSV(tree);
                break;
            case 3:
                deleteNode(tree);
                break;
            case 4:
                searchTree(tree);
                break;
            case 5:
                tree.printTree(std::cout);
                break;
            default:
                return -1;
                //this shouldn't occur
        }
    }
}
