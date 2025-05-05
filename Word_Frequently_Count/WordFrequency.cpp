#include "WordFrequency.h"

struct set_comparator
{
    bool operator()(const pair<int, string>& p1, const pair<int, string>& p2) const
    {
        if (p1.first != p2.first)
            return p1.first > p2.first;
        else
            return p1.second < p2.second;
    }
};

WordFrequnecy::WordFrequnecy()
{

}

void WordFrequnecy::removePunctuation(string& str)
{
    for (char& c : str)
    {
        if (!isalnum(c) && c != '\'' && !isspace(c))
        {
            c = ' ';
        }
    }
}


void WordFrequnecy::toLowercase(string& str)
{

    size_t length = str.length();

    for (int i = 0; i < length; i++)
    {
        str[i] = tolower(str[i]);
    }
}


string WordFrequnecy::WriteParagraphinConsole()
{
    string paragraph;
    cout << " Write an English paragraph . \n ";
    getline(cin, paragraph);
    return paragraph;
}


string WordFrequnecy::ReadTheParagraphFromFile(string& filename)
{
    while (true)
    {
        filename = filename.append(".txt");
        ifstream file(filename);
        if (file.good())
        {
            if (!file.is_open())
            {
                cerr << "Failed to open file: " << filename << endl;
                return "";
            }

            string line;
            string paragraph;

            while (!file.eof())
            {
                getline(file, line);
                /*if (line.empty())
                {
                    break;
                }*/
                paragraph += line + "\n";
            }

            file.close();

            if (paragraph.empty())
            {
                cout << "The File " << filename << "is empty" << endl;
                return "";
            }
            else
            {
                return paragraph;
            }
            break;
        }
        else
        {
            cout << " the file you enterd is Not Found .\n";
            cout << " Do you want to continue ? (y/n)\n";
            char choice;
            cin >> choice;
            if (choice == 'Y' || choice == 'y')
            {
                cout << " enter the correct file name.\n";
                cin >> filename;
            }
           
        }
    }
}


void WordFrequnecy::WriteParagraphInFile(string& paragraph,string& filename)
{
    
    ofstream clearFile(filename);
    ofstream file(filename);

    clearFile.clear();

    if (!file.is_open())
    {
        cerr << "Failed to open file: " << filename << endl;
        return;
    }
    file << paragraph << endl;
    file.close();

    cout << " saved in file : " << filename << endl;
}


vector<string> WordFrequnecy::AutoCompleteWords(unordered_map<string, int>& WordFrequency, string& word)
{

    set<pair<int, string>, set_comparator> WordsToComplete;

    for (auto& w : WordFrequency)
    {
        if (w.first.find(word) != string::npos)
        {
            WordsToComplete.insert({ w.second, w.first });
        }
    }

    vector<string> suggestionWords;

    for (auto& words : WordsToComplete)
    {
        suggestionWords.push_back(words.second);
    }
    return suggestionWords;
}


//string WordFrequnecy::AutoCorrectWords(unordered_map<string, int>& WordFrequency, const string& word)
//{
//    set<pair<int, string>, set_comparator> WordsToComplete;
//
//    for (auto& w : WordFrequency)
//    {
//        if (w.first.find(word) != string::npos)
//        {
//            WordsToComplete.insert({ w.second, w.first });
//        }
//    }
//
//    if (WordsToComplete.empty())
//    {
//        return "";
//    }
//    else
//    {
//        return WordsToComplete.begin()->second;
//    }
//
//}


string WordFrequnecy::AutoCorrectWords(unordered_map<string, int>& WordFrequency, string& word)
{
    string WordToCorrect = word;
    toLowercase(WordToCorrect);

    set<pair<int, string>, set_comparator> s;
    for (auto& w : WordFrequency)
    {
        int NoOfEqualChars = 0;
        string CurrentWord = w.first;
        toLowercase(CurrentWord);

        if (WordToCorrect.length() == CurrentWord.length())
        {
            for (int i = 0; i < WordToCorrect.length(); i++)
            {
                if (WordToCorrect[i] == CurrentWord[i])
                {
                    NoOfEqualChars++;
                }

            }
            s.insert({ NoOfEqualChars, w.first });
        }

    }
    
   

    if (!s.empty())
    {
        return s.begin()->second;
    }
    else
    {
        return "";
    }

}

string WordFrequnecy::AutoCompleteSentence(string& sentence, string& paragraph)
{

    string paragraph2 = paragraph;
    toLowercase(paragraph2);

    string completedSentence = sentence;

    size_t position = paragraph2.find(sentence);
    if (position != string::npos)
    {
        for (char& c : paragraph2.substr(position + sentence.length()))
        {
            if (c == ' ' || (!isalnum(c) && c != '\''))
                break;
            completedSentence += c;
        }
        return completedSentence;
    }
    else
    {
        return "";
    }

}

string WordFrequnecy::AutoCorrectSentence(unordered_map<string, int>& WordFrequency, string& sentence,string& paragraph)
{
    stringstream SentenceToCorrect(sentence);
    string Word;
    string CorrectedSentence;

    while (SentenceToCorrect >> Word)
    {
        CorrectedSentence += " " + AutoCorrectWords(WordFrequency, Word);
    }
    size_t position = paragraph.find(CorrectedSentence);
    if (position != string::npos)
    {
        return CorrectedSentence;
    }
    else
        return "";
}

void WordFrequnecy::display_Current_Paragrah(string& paragraph)
{
    cout << endl;
    cout << "Current paragraph:\n";
    cout << endl;
    cout << paragraph << endl;
}


void  WordFrequnecy::calculateWordsFrequencies(unordered_map <string, int>& WordFrequency, string paragraph)
{
    removePunctuation(paragraph);
    toLowercase(paragraph);

    stringstream words(paragraph);
    string word;
    while (words >> word)
    {
        WordFrequency[word]++;
    }
}


void  WordFrequnecy::displayWordFrequencies(unordered_map<string, int>& WordFrequency)
{
    unordered_map<string, int> ::iterator it;

    for (it = WordFrequency.begin(); it != WordFrequency.end(); it++)
    {
        cout << it->first << " : " << it->second << endl;
    }
}


void WordFrequnecy::displaySortedWordFrequencies(unordered_map<string, int>& WordFrequency)
{
    unordered_map<string, int> ::iterator it;

    set<pair<int, string>, set_comparator> s;

    for (auto& it : WordFrequency)
    {
        s.insert({ it.second, it.first });

    }

    set<pair<int, string>> ::iterator setIterator;

    int i = 1;

    for (setIterator = s.begin(); setIterator != s.end(); setIterator++)
    {
        cout << i << ")\t" << setIterator->second << " : " << setIterator->first << endl;

        i++;
    }
    cout << endl;

}


void WordFrequnecy::SearchWord(unordered_map <string, int>& WordFrequency)
{
    string wordToSearch;

    cout << "Enter the word to search: ";
    cin >> wordToSearch;
    toLowercase(wordToSearch);

    int option;
    cout << "1. Use Auto completeion \n"
        "2. Use Auto correction  \n";

    while (true)
    {
        cin >> option;

        if (option == 1)
        {
            auto found = WordFrequency.find(wordToSearch);
            if (found != WordFrequency.end())
            {
                cout << "Frequency of '" << wordToSearch << "': " << WordFrequency[wordToSearch] << endl;
                return;
            }
            else
            {
                vector<string> suggestionWords = AutoCompleteWords(WordFrequency, wordToSearch);
                if (!suggestionWords.empty())
                {
                    string completedWord;
                    cout << "Words You Can Mean ." << endl;
                    for (int i = 0; i < suggestionWords.size(); i++)
                    {
                        cout << i + 1 << ". " << suggestionWords[i] << endl;
                    }
                    cout << suggestionWords.size() + 1 << ".  another word " << endl;

                    int choice;
                    cout << "Enter your choice (1-" << suggestionWords.size() + 1 << "): ";
                    while (true)
                    {
                        cin >> choice;

                        if (choice >= 1 && choice <= suggestionWords.size() + 1)
                        {
                            if (choice != suggestionWords.size() + 1)
                            {
                                completedWord = suggestionWords[choice - 1];
                                cout << "Frequency of '" << completedWord << "': " << WordFrequency[completedWord] << endl;
                                return;
                            }
                            else
                            {
                                cout << "# enter the correct word .\n";
                                cin >> completedWord;
                                toLowercase(completedWord);
                                wordToSearch = completedWord;
                                auto found = WordFrequency.find(completedWord);
                                if (found != WordFrequency.end())
                                {
                                    cout << "Frequency of '" << completedWord << "': " << WordFrequency[completedWord] << endl;
                                    return;
                                }
                                break;
                            }
                        }
                        else
                        {
                            cout << "Invalid choice!" << endl;
                        }
                    }
                }


            }
            cout << " word (" << wordToSearch << ") not found . \n";
            break;
        }
        else if (option == 2)
        {
            string correctedWord = AutoCorrectWords(WordFrequency, wordToSearch);
            toLowercase(correctedWord);

            auto it = WordFrequency.find(wordToSearch);

            if (it != WordFrequency.end())
            {
                cout << "Frequency of '" << wordToSearch << "': " << WordFrequency[wordToSearch] << endl;
                return;
            }
            else
            {
                if (!correctedWord.empty())
                {
                    cout << "Do yon mean '" << correctedWord << "' (y/n) ? \n";
                    char choice;
                    while (true)
                    {
                        cin >> choice;
                        if (choice == 'y' || choice == 'Y')
                        {
                            cout << "Frequency of '" << correctedWord << "': " << WordFrequency[correctedWord] << endl;
                            return;
                        }
                        else if (choice == 'n' || choice == 'N')
                        {
                            cout << "# Enter the correct word #\n";
                            cin >> correctedWord;
                            toLowercase(correctedWord);
                            wordToSearch = correctedWord;
                            auto found = WordFrequency.find(correctedWord);
                            if (found != WordFrequency.end())
                            {
                                cout << "Frequency of '" << correctedWord << "': " << WordFrequency[correctedWord] << endl;
                                return;
                            }
                            break;
                        }
                        else
                        {
                            cout << " invalid choice , Enter yes or No . \n";
                        }
                    }
                }
            }
            cout << " word (" << wordToSearch << ") not found . \n";
            break;
        }
        else
        {
            cout << "invalid choice , enter 1 or 2 \n";
        }
    }
}


void WordFrequnecy::displayTheRankOfTheWord(unordered_map <string, int>& WordFrequency)
{

    string Word;
    cout << "Enter the word to rank: ";
    cin >> Word;
    toLowercase(Word);

    unordered_map <string, int> ::iterator it;
    set<pair<int, string>, set_comparator> s;

    for (auto& it : WordFrequency)
    {
        s.insert({ it.second, it.first });
    }

    int option;
    cout << "1. Use Auto completeion \n"
            "2. Use Auto correction  \n";

    int rank = 1;

    while (true)
    {
        cin >> option;

        if (option == 1)
        {
            set<pair<int, string>> ::iterator set_iterator = s.begin();
            auto found = WordFrequency.find(Word);
            if (found != WordFrequency.end())
            {

                while (set_iterator != s.end())
                {
                    if (set_iterator->second == Word)
                    {
                        cout << " Rank of " << Word << " : " << rank << endl;
                        return;
                    }
                    set_iterator++;
                    rank++;
                }

            }
            else
            {
                vector<string> suggestionWords = AutoCompleteWords(WordFrequency, Word);
                if (!suggestionWords.empty())
                {
                    string completedWord;
                    cout << "Words You Can Mean ." << endl;
                    for (int i = 0; i < suggestionWords.size(); i++)
                    {
                        cout << i + 1 << ". " << suggestionWords[i] << endl;
                    }
                    cout << suggestionWords.size() + 1 << ".  another word " << endl;

                    int choice;
                    cout << "Enter your choice (1-" << suggestionWords.size() + 1 << "): ";
                    while (true)
                    {
                        cin >> choice;

                        if (choice >= 1 && choice <= suggestionWords.size() + 1)
                        {
                            if (choice != suggestionWords.size() + 1)
                            {
                                completedWord = suggestionWords[choice - 1];

                                set_iterator = s.begin();
                                while (set_iterator != s.end())
                                {
                                    if (set_iterator->second == completedWord)
                                    {
                                        cout << " Rank of " << completedWord << " : " << rank << endl;
                                        return;
                                    }
                                    set_iterator++;
                                    rank++;
                                }
                            }
                            else
                            {
                                cout << "# enter the correct word .\n";
                                cin >> completedWord;
                                Word = completedWord;
                                toLowercase(completedWord);
                                auto found = WordFrequency.find(completedWord);
                                if (found != WordFrequency.end())
                                {
                                    set_iterator = s.begin();
                                    while (set_iterator != s.end())
                                    {
                                        if (set_iterator->second == completedWord)
                                        {
                                            cout << " Rank of " << completedWord << " : " << rank << endl;
                                            return;
                                        }
                                        set_iterator++;
                                        rank++;
                                    }
                                }
                                break;
                            }
                        }
                        else
                        {
                            cout << "Invalid choice .\n";
                        }
                    }
                }
            }
            cout << " word (" << Word << ") not found . \n";
            break;
        }
        else if (option == 2)
        {
            set<pair<int, string>> ::iterator set_iterator = s.begin();

            string correctedWord = AutoCorrectWords(WordFrequency, Word);


            while (set_iterator != s.end())
            {
                if (set_iterator->second == correctedWord)
                {
                    if (correctedWord == Word)
                    {
                        cout << " Rank of " << correctedWord << " : " << rank << endl;
                        return;
                    }

                    else
                    {
                        cout << "Do yon mean '" << correctedWord << "' (y/n) ? \n";
                        char choice;
                        while (true)
                        {
                            cin >> choice;
                            if (choice == 'y' || choice == 'Y')
                            {
                                cout << " Rank of " << correctedWord << " : " << rank << endl;
                                return;
                            }
                            else if (choice == 'n' || choice == 'N')
                            {
                                cout << "# Enter the correct word #\n";
                                cin >> correctedWord;
                                toLowercase(correctedWord);
                                Word = correctedWord;
                                set_iterator = s.begin();
                                rank = 1;

                                break;
                            }
                            else
                            {
                                cout << " invalid choice , Enter yes or No . \n";
                            }
                        }
                        continue;
                    }

                }
                rank++;
                set_iterator++;
            }
            cout << " word (" << Word << ") not found . \n";
            break;
        }
        else
        {
            cout << "Invalid choice . \n";
        }

    }

}


void WordFrequnecy::displayRankingOfAllWord(unordered_map <string, int>& WordFrequency)
{
    unordered_map <string, int> ::iterator it;

    set<pair<int, string>, set_comparator> s;
    for (auto& it : WordFrequency)
    {
        s.insert({ it.second, it.first });
    }

    set<pair<int, string>> ::iterator set_iterator;

    int rank = 1;

    for (set_iterator = s.begin(); set_iterator != s.end(); set_iterator++)
    {
        cout << " Rank of (" << set_iterator->second << ") : " << rank << endl;
        rank++;
    }

}


void WordFrequnecy::DeleteFromParagraph(unordered_map <string, int>& GlobalWordFrequency, unordered_map <string, int>& LocalWordFrequency, string& paragraph)
{
    while (true)
    {
        cout << "1. Delete specific sentence \n"
            "2. Delete the paragraph \n";

        int choice;

        cin >> choice;
        cin.ignore();

        if (choice == 1)
        {
            string paragraph2 = paragraph;
            toLowercase(paragraph2);


            string sentenceToDelete;
            cout << "Enter the sentence to delete: ";
            getline(cin, sentenceToDelete);
            toLowercase(sentenceToDelete);

            string completed_sentence = AutoCompleteSentence(sentenceToDelete, paragraph);
            toLowercase(completed_sentence);

            while (true)
            {
                size_t position = paragraph2.find(completed_sentence);
                if (position != string::npos && !completed_sentence.empty())
                {

                    if (completed_sentence == sentenceToDelete)
                    {
                        removePunctuation(completed_sentence);
                        stringstream sentence(completed_sentence);
                        string word;

                        while (sentence >> word)
                        {
                            if (GlobalWordFrequency[word] == 1)
                            {
                                GlobalWordFrequency.erase(word);
                                LocalWordFrequency.erase(word);
                            }
                            else
                            {
                                GlobalWordFrequency[word]--;
                                if (!LocalWordFrequency.empty())
                                {
                                    if (LocalWordFrequency[word] == 1)
                                    {
                                        LocalWordFrequency.erase(word);
                                    }
                                    else
                                    {
                                        LocalWordFrequency[word]--;
                                    }
                                }

                            }
                        }

                        paragraph.erase(position, completed_sentence.length());

                        cout << " deleted successfully .\n";
                        return;
                    }
                    else
                    {
                        cout << "Do yon mean '" << completed_sentence << "' (y/n) ? \n";
                        char choice;
                        while (true)
                        {
                            cin >> choice;
                            if (choice == 'y' || choice == 'Y')
                            {

                                removePunctuation(completed_sentence);
                                stringstream sentence(completed_sentence);
                                string word;

                                while (sentence >> word)
                                {
                                    if (GlobalWordFrequency[word] == 1)
                                    {
                                        GlobalWordFrequency.erase(word);
                                        LocalWordFrequency.erase(word);
                                    }
                                    else
                                    {
                                        GlobalWordFrequency[word]--;
                                        if (!LocalWordFrequency.empty())
                                        {
                                            if (LocalWordFrequency[word] == 1)
                                            {
                                                LocalWordFrequency.erase(word);
                                            }
                                            else
                                            {
                                                LocalWordFrequency[word]--;
                                            }
                                        }
                                    }

                                }
                                paragraph.erase(position, completed_sentence.length());

                                cout << " deleted successfully .\n";
                                return;


                            }
                            else if (choice == 'n' || choice == 'N')
                            {
                                cout << "# Enter the correct sentence #\n";
                                cin.ignore();
                                getline(cin, completed_sentence);
                                toLowercase(completed_sentence);
                                sentenceToDelete = completed_sentence;
                                break;
                            }
                            else
                            {
                                cout << " invalid choice , Enter yes or no .\n";
                            }
                        }

                    }


                }

                else
                {
                    cout << "Sentence not found.\n";
                    break;
                }
            }

            break;

        }


        else if (choice == 2)
        {

            GlobalWordFrequency.clear();
            LocalWordFrequency.clear();
            paragraph.clear();
            cout << " deleted successfully .\n";
            break;
        }
        else
        {
            cout << " invalid choice , enter 1 or 2 . \n";
        }

    }
}


void WordFrequnecy::EditInParagraph(unordered_map <string, int>& GlobalWordFrequency, unordered_map <string, int>& LocalWordFrequency, string& paragraph)
{

    string paragraph2 = paragraph;
    toLowercase(paragraph2);

    string old_sentence;
    string new_sentence;

    cout << " enter the old sentece to edit : \n";
    getline(cin, old_sentence);
    toLowercase(old_sentence);

    cout << AutoCorrectSentence(GlobalWordFrequency, old_sentence,paragraph2) << endl;

    string completed_sentence = AutoCompleteSentence(old_sentence, paragraph);
    toLowercase(completed_sentence);

    while (true)
    {
        size_t position = paragraph2.find(old_sentence);

        if (position != string::npos && !old_sentence.empty())
        {
            if (completed_sentence == old_sentence)
            {
                cout << " enter the New sentece to edit : \n";
                getline(cin, new_sentence);

                paragraph.replace(position, completed_sentence.length(), new_sentence);


                removePunctuation(new_sentence);
                toLowercase(new_sentence);

                removePunctuation(completed_sentence);
                stringstream replaced_sentence(completed_sentence);
                string old_word;
                while (replaced_sentence >> old_word)
                {
                    if (GlobalWordFrequency[old_word] == 1)
                    {
                        GlobalWordFrequency.erase(old_word);
                        LocalWordFrequency.erase(old_word);
                    }
                    else
                    {
                        GlobalWordFrequency[old_word]--;
                        if (!LocalWordFrequency.empty())
                        {
                            if (LocalWordFrequency[old_word] == 1)
                            {
                                LocalWordFrequency.erase(old_word);
                            }
                            else
                            {
                                LocalWordFrequency[old_word]--;
                            }
                        }
                    }
                }

                calculateWordsFrequencies(GlobalWordFrequency, new_sentence);
                calculateWordsFrequencies(LocalWordFrequency, new_sentence);

                cout << " Edited successfully . \n";
                return;
            }
            else
            {
                cout << "Do yon mean '" << completed_sentence << "' (y/n) ? \n";
                char choice;
                while (true)
                {
                    cin >> choice;
                    if (choice == 'y' || choice == 'Y')
                    {
                        cin.ignore();
                        cout << " enter the New sentece to edit : \n";
                        getline(cin, new_sentence);

                        paragraph.replace(position, completed_sentence.length(), new_sentence);


                        removePunctuation(new_sentence);
                        toLowercase(new_sentence);

                        removePunctuation(completed_sentence);
                        stringstream replaced_sentence(completed_sentence);
                        string old_word;
                        while (replaced_sentence >> old_word)
                        {
                            if (GlobalWordFrequency[old_word] == 1)
                            {
                                GlobalWordFrequency.erase(old_word);
                                LocalWordFrequency.erase(old_word);
                            }
                            else
                            {
                                GlobalWordFrequency[old_word]--;
                                if (!LocalWordFrequency.empty())
                                {
                                    if (LocalWordFrequency[old_word] == 1)
                                    {
                                        LocalWordFrequency.erase(old_word);
                                    }
                                    else
                                    {
                                        LocalWordFrequency[old_word]--;
                                    }
                                }
                            }
                        }

                        calculateWordsFrequencies(GlobalWordFrequency, new_sentence);
                        calculateWordsFrequencies(LocalWordFrequency, new_sentence);

                        cout << " Edited successfully . \n";
                        return;
                    }
                    else if (choice == 'n' || choice == 'N')
                    {
                        cout << "# Enter the correct sentence #\n";
                        cin.ignore();
                        getline(cin, completed_sentence);
                        toLowercase(completed_sentence);
                        old_sentence = completed_sentence;
                        break;
                    }
                    else
                    {
                        cout << " invalid choice , Enter Yes or No . \n";
                    }
                }

            }

        }
        else
        {
            cout << "Sentence not found.\n";
            break;
        }
    }
}


void WordFrequnecy::continueWritingInParagraph(unordered_map <string, int>& GlobalWordFrequency, unordered_map<string, int>& LocallWordFrequency, string& paragraph)
{
    cout << paragraph << endl;

    stringstream words;
    string writeLine;

    cout << "Writing ... \n";
    while (true)
    {
        getline(cin, writeLine);

        if (writeLine.empty())
            break;

        words << writeLine;

    }

    calculateWordsFrequencies(LocallWordFrequency, words.str());
    calculateWordsFrequencies(GlobalWordFrequency, words.str());

    paragraph += "\n" + words.str();
}


void WordFrequnecy::updateParagraph(unordered_map <string, int>& GlobalWordFrequency, unordered_map <string, int>& LocalWordFrequency, string& paragraph)
{
    int choice;

    while (true)
    {
        cout << "1. Edit \n"
            "2. Delete \n";

        cin >> choice;

        if (choice == 1)
        {
            cin.ignore();
            EditInParagraph(GlobalWordFrequency, LocalWordFrequency, paragraph);
            break;
        }
        if (choice == 2)
        {
            cin.ignore();
            DeleteFromParagraph(GlobalWordFrequency, LocalWordFrequency, paragraph);
            break;
        }
        else
        {
            cout << "Invalid choice. enter 1 to Edit in paragraph , 2 to delete sentence .\n";
        }

    }

}