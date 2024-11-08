#include <iostream>
using std::cout;
using std::cin;

void greetings(void);

int main()
{
    greetings();
    return 0;
}

void greetings(void)
{
    
    std::string name;

    cout << "Enter your name: ";

    std::getline(std::cin, name);
    //cin >> name;
    cout << "\n hi  " << name << " \n";


}

