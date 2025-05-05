
#include <iostream>
#include <string>
#include <vector>
#include "sstream"
#include "fstream"
#include <set>
#include <unordered_map>
#include "WordFrequency.h"


using namespace std;


int main()
{
    string paragraph;
    unordered_map <string, int> GlobalwordFrequency;
    unordered_map<string, int> LocalwordFrequency;

    WordFrequnecy wordFrequency;

    string filename;

    while (true)
    {


        cout << "1. write paragraph in conosle \n"
                "2. read paragraph from file \n";


        int option;
        cin >> option;

        if (option == 1)
        {
            cin.ignore();
            paragraph = wordFrequency.WriteParagraphinConsole();
            wordFrequency.calculateWordsFrequencies(GlobalwordFrequency, paragraph);
            break;
        }
        else if (option == 2)
        {
            cin.ignore();
            cout << " Enter The File Name . \n";
            cin >> filename;
            paragraph = wordFrequency.ReadTheParagraphFromFile(filename);
            wordFrequency.calculateWordsFrequencies(GlobalwordFrequency, paragraph);
            break;
        }
        else
        {
            cout << " invalid choice . \n";
        }
    }
    while (true)
    {

        cout << "****************************************************************\n";


        cout <<
            "1. Display the current paragraph.\n"
            "2. Update the paragraph.\n"
            "3. Display (Global) word frequencies.\n"
            "4. Display (Local) word frequencies.\n"
            "5. Display (Global)sorted word frequencies .\n"
            "6. Display (Local) sorted word frequencies .\n"
            "7. Search for a word and display its frequency(Global).\n"
            "8. Search for a word and display its frequency(Local).\n"
            "9. Display the (Global) rank of a word.\n"
            "10.Display the (Local) rank of a word. \n"
            "11.Display the (Global) rank of each word.\n"
            "12.Display the (Local) rank of each word. \n"
            "13.Continue writing in the paragraph.\n"
            "14.Exit.\n";

        int choice;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

      switch (choice)
      {
        case 1:
        {
            cout << endl;
            wordFrequency.display_Current_Paragrah(paragraph);

            break;
        }
        case 2:
        {
            cout << endl;
            wordFrequency.updateParagraph(GlobalwordFrequency, LocalwordFrequency, paragraph);
            break;
        }
        case 3:
        {
            cout << endl;
            cout << "            Global Word Frequencies \n";
            cout << "            ----------------------- \n";
            wordFrequency.displayWordFrequencies(GlobalwordFrequency);
            break;
        }
        case 4:
        {
            cout << endl;
            if (!LocalwordFrequency.empty())
            {
                cout << "            Local Word Frequencies \n";
                cout << "            ---------------------- \n";
                wordFrequency.displayWordFrequencies(LocalwordFrequency);
            }
            else
            {
                cout << " The Local Words is empty .\n";
            }
            break;
        }
        case 5:
        {
            cout << endl;
            cout << "            Sorted Words (Global) \n";
            cout << "            --------------------- \n";
            wordFrequency.displaySortedWordFrequencies(GlobalwordFrequency);
            break;
        }
        case 6:
        {
            cout << endl;
            if (!LocalwordFrequency.empty())
            {
                cout << "            Sorted Words (Local) \n";
                cout << "            -------------------- \n";
                wordFrequency.displaySortedWordFrequencies(LocalwordFrequency);
            }
            else
            {
                cout << " The Local Words is empty .\n";
            }
            break;
        }
        case 7:
        {
            cout << endl;
            cout << "            Global search \n";
            cout << "            ------------- \n";
            wordFrequency.SearchWord(GlobalwordFrequency);
            break;
        }
        case 8:
        {
            cout << endl;
            if (!LocalwordFrequency.empty())
            {
                cout << "            Local search \n";
                cout << "            ------------ \n";
                wordFrequency.SearchWord(LocalwordFrequency);
            }
            else
            {
                cout << " The Local Words is empty .\n";
            }
            break;
        }
        case 9:
        {
            cout << endl;
            cout << "            The Global Rank \n";
            cout << "            --------------- \n";
            wordFrequency.displayTheRankOfTheWord(GlobalwordFrequency);
            break;
        }
        case 10:
        {
            cout << endl;
            if (!LocalwordFrequency.empty())
            {
                cout << "            The Local Rank \n";
                cout << "            -------------- \n";
                wordFrequency.displayTheRankOfTheWord(LocalwordFrequency);
            }
            else
            {
                cout << " The Local Words is empty .\n";
            }
            break;
        }
        case 11:
        {
            cout << endl;
            cout << "            The Global Rank \n";
            cout << "            --------------- \n";
            wordFrequency.displayRankingOfAllWord(GlobalwordFrequency);
            break;
        }
        case 12 : 
        {
            cout << endl;
            if (!LocalwordFrequency.empty())
            {
                cout << "            The Local Rank \n";
                cout << "            -------------- \n";
                wordFrequency.displayRankingOfAllWord(LocalwordFrequency);
            }
            else
            {
                cout << " The Local Words is empty .\n";
            }
            break;
        }
        case 13 : 
        {
            wordFrequency.continueWritingInParagraph(GlobalwordFrequency, LocalwordFrequency, paragraph);
            break;
        }
        case 14 :
        {
            wordFrequency.WriteParagraphInFile(paragraph, filename);
            return 0;
        }
        default:

            cout << "Invalid choice. enter a number from 1 to 14.\n";
      }

    }

    system("pause");

    return 0;
}