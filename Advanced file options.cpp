// Advanced file options.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cstring>
#include <fstream>
#include <ctype.h>
using namespace std;

const int descriptsize = 81, datearray = 3;

struct Item 
{
    char Description[descriptsize];
    int Quantity;
    float Wholesale;
    float Retail;
    int Date[datearray];
};

int DateValidation(int step)
{
    int userinput;
    cin >> userinput;
    switch (step)
    {
    case 0:
        if (!cin || userinput < 1 || userinput > 12)
        {
            char run = 'y';

            while (run == 'y')
            {
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cout << "\nThat is not a valid input, please input a month as a whole number from 1 to 12\n";
                cin >> userinput;
                if (userinput > 0 && userinput < 13)
                    run = 'n';
            }
        }
        break;
       
    case 1:
        if (!cin || userinput < 1 || userinput > 31)
        {
            char run = 'y';

            while (run == 'y')
            {
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cout << "\nThat is not a valid input, please input a the day of the month as a number\n";
                cin >> userinput;
                if (userinput > 0 && userinput < 32)
                    run = 'n';
            }
        }
        break;

    case 2:
        if (!cin || userinput < 1900 || userinput > 2021)
        {
            char run = 'y';

            while (run == 'y')
            {
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cout << "\nThat is not a valid input, please input the year as a number\n";
                cin >> userinput;
                if (userinput > 1900 && userinput < 2022)
                    run = 'n';
            }
        }
        break;
    }
    return (userinput);
}

float inputDollars() 
{

    float userinput;
    cin >> userinput;

    if (!cin || userinput < 0) 
    {
        char run = 'y';

        while (run == 'y') 
        {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            cout << "\nThat is not a valid dollar amount, please input a number 0 or greater\n"; 
            cin >> userinput;
            if (userinput >= 0) 
                run = 'n';
        }
    }

    return (userinput);
}

int inputQuantity()
{

    int userinput;
    cout << "\nPlease input the item quantity as a whole number\n";
    cin >> userinput;

    if (!cin || userinput < 0)
    {
        char run = 'y';

        while (run == 'y')
        {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "\nThat is not a valid quantity, please input a whole number 0 or greater\n";
            cin >> userinput;
            if (userinput >= 0)
                run = 'n';
        }
    }

    return (userinput);
}

int main()
{
    Item CurrentRecord = { "", 0, 0, 0, 0 };
    bool run = true;
    int userselect;
    long recordnumber;

    fstream file("record.txt", ios::in | ios::out| ios::binary);
    
    

    while (run == true)
    {
        cout << "\nPlease select a menu option:\n";
        cout << "1: New Record\n";
        cout << "2: Display Record\n";
        cout << "3: Change Record\n";
        cout << "4: Close Program\n\n";
        cin >> userselect;
        switch (userselect)
        {
        case 1:
            cout << "\nPlease enter the item description:\n";
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cin.getline(CurrentRecord.Description,descriptsize);
            CurrentRecord.Quantity = inputQuantity();
            cout << "\nPlease enter the Wholesale Value in dollars as a number\n";
            CurrentRecord.Wholesale = inputDollars();
            cout << "\nPlease enter the Retail Value in dollars as a number\n";
            CurrentRecord.Retail = inputDollars();
            cout << "\nPlease enter date the item was added to inventory\n\n";
            cout << "Enter the Month as a number: ";
            CurrentRecord.Date[0] = DateValidation(0);
            cout << "\nEnter the Day as a number: ";
            CurrentRecord.Date[1] = DateValidation(1);
            cout << "\nEnter the Year as a number: ";
            CurrentRecord.Date[2] = DateValidation(2);

            file.seekp(ios::end);
            file.write(reinterpret_cast<char*>(&CurrentRecord), sizeof(CurrentRecord));

            userselect = 0;
            break;
        case 2:

            cout << "\nInput a record number to display:\n";
            cin >> recordnumber;

            file.seekg(recordnumber * sizeof(CurrentRecord), ios::beg);
            file.read(reinterpret_cast<char*>(&CurrentRecord), sizeof(CurrentRecord));

            cout << endl << CurrentRecord.Description;
            cout << "\nWholesale Value: " << CurrentRecord.Wholesale;
            cout << "\nRetail Value: " << CurrentRecord.Retail;
            cout << "\nDate Added:" << CurrentRecord.Date[0] << "/" << CurrentRecord.Date[1] << "/" << CurrentRecord.Date[2];
            cout << endl;
     
            userselect = 0;
            break;
        case 3:
   
            cout << "\nInput a record number to display then change:\n";
            cin >> recordnumber;

            file.seekg(recordnumber * sizeof(CurrentRecord), ios::beg);
            file.read(reinterpret_cast<char*>(&CurrentRecord), sizeof(CurrentRecord));

            cout << endl << CurrentRecord.Description;
            cout << "\nWholesale Value: " << CurrentRecord.Wholesale;
            cout << "\nRetail Value: " << CurrentRecord.Retail;
            cout << "\nDate Add:" << CurrentRecord.Date[0] << "/" << CurrentRecord.Date[1] << "/" << CurrentRecord.Date[2];

            cout << "\nPlease enter the new values:\n";
            cout << "Item description: ";
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cin.getline(CurrentRecord.Description, descriptsize);
            CurrentRecord.Quantity = inputQuantity();
            cout << "\nPlease enter the Wholesale Value in dollars as a number\n";
            CurrentRecord.Wholesale = inputDollars();
            cout << "\nPlease enter the Retail Value in dollars as a number\n";
            CurrentRecord.Retail = inputDollars();
            cout << "\nPlease enter date the item was added to inventory:\n";
            cout << "Enter the Month as a number: ";
            CurrentRecord.Date[0] = DateValidation(0);
            cout << "\nEnter the Day as a number: ";
            CurrentRecord.Date[1] = DateValidation(1);
            cout << "\nEnter the Year as a number: ";
            CurrentRecord.Date[2] = DateValidation(2);

            file.seekp(recordnumber * sizeof(CurrentRecord), ios::beg);
            file.write(reinterpret_cast<char*>(&CurrentRecord), sizeof(CurrentRecord));

       

            userselect = 0;
            break;
        case 4:
            run = false;
            file.close();
            break;

        default:
            cout << "\nPlease select a menu option:\n";
            cout << "1: New Record\n";
            cout << "2: Display Record\n";
            cout << "3: Change Record\n";
            cout << "4: Close Program\n";
            cin >> userselect;
            break;
        }

    }
    file.close();

    cout << "\nPress any key to finish ";
    cin.ignore(20, '\n'); 
    cin.get();

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
