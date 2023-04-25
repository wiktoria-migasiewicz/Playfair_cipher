#include <iostream>
#include <cmath>
#include <algorithm>
#include <cctype>
#include <string>
#include <fstream>
#include <cstdlib>
#include <cstdio>

using namespace std;

const unsigned int ROWS = 5;
const unsigned int COLS = 5;
char tab[ROWS][COLS] = {{'\0'}};

//struktura przechowująca pozycje znaku
struct point 
{
    int x;
    int y;
};

void WelcomeMenu (void);
void Decision (string&, string&);
void RemovingSpace (string&, string&);
void ToUppercase (string&, string&);
void Replacing (string&, string&);
void AddingZ (string&, string&);
void RemovingRepeatingSigns (string&);
void MakingKeyTab (string&);
void PrintTab(void);
point* FindCoordinates(char);
string Encoding(string);
void EncodeByPlayfair(string&, string&);
string Decoding(string);
void GetKeyWord (string&);
void GetPlaintext (string&);
void SaveInFile (string&, string&, string&, string&);
void EndMenu(string&, string&, string&, string&);
void WholeProgram(string&, string&);
void Loop(string&, string&);

int main()
{
    string keyWord = {0}, plaintext = {0};
          
    cout << endl << "WELCOME" << endl <<endl << "This a program encoding and decoding in the Playfair cipher" << endl << endl;
          
    WholeProgram(keyWord, plaintext);
          
    Loop(keyWord, plaintext);
          
    return 0;
}

void WholeProgram(string& keyWord, string& plaintext)
{
    WelcomeMenu();
          
    Decision (keyWord, plaintext);
          
    RemovingSpace (keyWord, plaintext);
          
    ToUppercase (keyWord, plaintext);
          
    Replacing (keyWord, plaintext);
          
    AddingZ (keyWord, plaintext);
          
    RemovingRepeatingSigns (keyWord);
          
    MakingKeyTab (keyWord);
          
    PrintTab();
          
    string encodedText = Encoding (plaintext);
          
    cout << "ENCODED TEXT: " << encodedText << endl;
          
    string decodedText = Decoding (encodedText);
        
    cout << "DECODED TEXT: " << decodedText << endl;
          
    EndMenu(encodedText, decodedText, keyWord, plaintext);
}

void Loop(string& keyWord, string& plaintext)
{
    cout << endl << "Choose what would you like to do next, type:" << endl;
    cout << "C to code again" << endl;
    cout << "Q to quit the program" << endl << endl << "-> "; 
    char choice = {0};
    for (int i = {0}; i < 2; i++)
        {
            cin >> choice;
            if (choice == 'C')
                {
                    WholeProgram(keyWord, plaintext);  
                    cout << endl << endl << "Choose what would you like to do next, type:" << endl;
                    cout << "C to code again" << endl;
                    cout << "Q to quit the program" << endl << endl << "-> "; 
                }
            else if (choice == 'Q')
                {
                    exit(0);
                }
            else
                {
                    cout << "Wrong sign has been entered" << endl << endl << "You have one more try or else the program closes"; 
                    cout << endl << "->";
                }
        }
}

void GetKeyWord (string& keyWord)
{
    cout << endl << "Input your key word (no special characters) : " << endl << "-> ";
    getline (cin >> ws, keyWord);
}

void GetPlaintext (string& plaintext)
{
    cout << "Input your message (no special characters) :" << endl << "-> ";
    getline (cin >> ws, plaintext);
}

void WelcomeMenu (void)
{
    cout << "Choose what would you like to do and type:" << endl << endl;
    cout << "M to input the message manually" << endl;
    cout << "F to input the message from the file" << endl;
    cout << "Q to quit the program" << endl << endl << "-> "; 
}

void ReadingFile (string& plaintext)
{
    string fileName = {0};
    for (int i = {4}; i > 0 ;i--)
        {
            if (i == 1) 
                {
                    cout << endl << endl << "QUITTING THE PROGRAM..." << endl;
                    exit(0);
                }
                    cout << endl << "Input the name of your file" << endl << "-> ";
                    cin >> fileName;
                    ifstream ifhandle(fileName.c_str());
                    if (ifhandle)
                {
                    while (getline (ifhandle, plaintext)) 
                        {
                            cout << endl << "Your message: " << plaintext;
                        }
                    ifhandle.close();
                    break; 
                }
            else if (!ifhandle)
                {
                    cout << endl << "CANNOT OPEN FILE " << fileName ;
                    cout << endl << "You have " << i - 2 << " more tries";
                }
        }
}

void Decision (string& keyWord, string& plaintext)
{
    char decision = {0};
    for (int i = {0}; i < 2; i++)
        {
            cin >> decision;
            cout << endl;
            if (decision == 'M' )
                {
                    GetPlaintext (plaintext);
                    GetKeyWord (keyWord);
                    break;
                } 
            else if (decision == 'F')
                {
                    ReadingFile (plaintext);
                    GetKeyWord (keyWord);
                    break;
                }
            else if (decision == 'Q')
                {
                    cout << endl << "QUITTING...";
                    exit(0);
                }
            else 
                {
                    if ( i == 1)
                        {
                            cout << "QUITTING..." << endl;
                            exit (0);
                        }
                    cout << "Wrong sign has been entered" << endl << endl << "You have one more try"; 
                    cout << endl << "->";
                }
        }
}

void EndMenu (string& encodedText, string& decodedText, string& keyWord, string& plaintext)
{
    cout << endl << "To save your code type: " << endl << endl << "S to save" << endl << "Q to quit right now" << endl << endl << "->";
    char decision = {0};
    string fileName = {0};
    for (int i = {0}; i < 2; i++)
        {
                cin >> decision;
            if (decision == 'S' )
                {
                    SaveInFile (encodedText, decodedText, keyWord, plaintext);
                    break;
                } 
            else if (decision == 'Q')
                {
                    cout << endl << "QUITTING...";
                    exit(0);
                }
            else 
                {
                    if ( i == 1)
                        {
                            cout << "QUITTING..." << endl;
                            exit (0);
                        }
                    cout << endl << "Wrong sign has been entered" << endl << endl << "You have one more try";
                    cout << endl << "->";
                }
        }   
}

void SaveInFile (string& encodedText, string& decodedText, string& keyWord, string& plaintext)
{
    ofstream ofhandle("output.txt");
    ofhandle << "KEYWORD: " << keyWord << endl << "PLAINTEXT: " << plaintext << endl;
    ofhandle << "ENCODED TEXT: " << encodedText << endl << "DECODED TEXT: " << decodedText;
    cout << "Your code has been saved in a file named output.txt" << endl;
}

void EncodeByPlayfair(string& keyWord, string& plaintext)
{
    void ToUppercase (string& keyWord, string& plaintext);
    void RemovingSpace (string& keyWord, string& plaintext);
    void Replacing (string& keyWord, string& plaintext);
    void AddingZ (string& keyWord, string& plaintext);
    void RemovingRepeatingSigns (string& keyWord);
    void MakingKeyTab (string& keyWord);
    void PrintTab(void);
    string Encoding(string plaintext);
}

void ToUppercase (string& keyWord, string& plaintext)
{
    for (unsigned int i = 0; i < keyWord.size(); i++)
    {
        if (keyWord.at(i) >= 'a' && keyWord.at(i) <= 'z')
            {
                keyWord.at(i) = keyWord.at(i) - 32;
            }
    }    
    for (unsigned int i = 0; i < plaintext.size(); i++)
    {
        if (plaintext.at(i) >= 'a' && plaintext.at(i) <= 'z')
            {
                plaintext.at(i) = plaintext.at(i) - 32;
            }
    }    
}

void RemovingSpace (string& keyWord, string& plaintext)
{
    keyWord.erase(remove(keyWord.begin(), keyWord.end(), ' '), keyWord.end());
    plaintext.erase(remove(plaintext.begin(), plaintext.end(), ' '), plaintext.end());
}

//zamieniam j na i, bo nie starczy miejsca dla 26 liter w tablicy 5x5
void Replacing (string& keyWord, string& plaintext)
{
    replace(keyWord.begin(), keyWord.end(), 'J', 'I');
    replace(plaintext.begin(), plaintext.end(), 'J', 'I');
}

// dodaje z do tekstu jawnego o nieparzystej ilości znaków
void AddingZ (string& keyWord, string& plaintext)
{
    if (plaintext.length() % 2 != 0) 
        {
            plaintext += 'Z';
        }
}

//w kluczu usuwam powtarzające się znaki
void RemovingRepeatingSigns (string& keyWord)
{
    for( unsigned int i = 0; i <= keyWord.size() - 1; i++ )
    {
        for( unsigned int a = i + 1; a <= keyWord.size() - 1; a++ )
        {
            if( keyWord.at(i) == keyWord.at(a) )
            {
                keyWord.erase( a, 1 );
                a = a - 1;
            }
        }
    }
}

//wpisywanie klucza do tablicy
void MakingKeyTab (string& keyWord)
{
    string control = "";
    string alfabet = "ABCDEFGHIKLMNOPQRSTUVWXYZ";
    int x = 0, y = 0;
    size_t position;
    for (char sign : keyWord) 
        {
            position = control.find(sign);
            if (position == string::npos) 
                {
                    if (y == 5) 
                        {
                            cout << "ERROR! - INVALID SIGNS IN TAB" << endl;
                            return;
                        }
                    //dodajemy znak do kontrolnego stringa i tablicy
                    control += sign;
                    tab[x][y] = sign;
                    x++;
                    if (x == 5) 
                        {
                            x = 0;
                            y++;
                        }
                }
        }
    for (char sign : alfabet) 
        {
            position = control.find(sign);
            if (position == string::npos) 
                {
                    if (y == 5)
                        {
                            cout << endl << "ERROR! - INVALID SIGNS IN TAB" << endl;
                            exit(0);
                        }
                    control += sign;
                    tab[x][y] = sign;
                    x++;
                    if (x == 5) 
                        {
                            x = 0;
                            y++;
                        }
                    }
        }
}

//wyświetlanie wypelnionej tablicy w konsoli
void PrintTab(void) 
{
    cout << endl;
    for (int i = 0; i < 5; i++) 
        {
            for (int j = 0; j < 5; j++) 
                {
                    cout << tab[j][i] << " | ";
                }
            cout << endl;
        }
    cout << endl;
}

//przypisywanie pozycji w tabeli do koordynatów   
point* FindCoordinates(char sign)
{
    for (int i = 0; i < 5; i++) 
        {
            for (int j = 0; j < 5; j++) 
                {
                    if (tab[j][i] == sign) 
                        {
                            point* coordinates = new point;
                            coordinates->x = j;
                            coordinates->y = i;
                            return coordinates;
                        }
                }
        }
        return nullptr;
}

string Encoding(string plaintext)
{
    point* coordinates_of_first;
    point* coordinates_of_second;
    string encrypted_text = "";  
    for (unsigned int x = 0; x < plaintext.length(); x += 2)
        {
            coordinates_of_first = FindCoordinates(plaintext.at(x));
            coordinates_of_second = FindCoordinates(plaintext.at(x + 1));
            //jesli nie ma wskaznika wychodzimy z programu
            if (coordinates_of_first == nullptr || coordinates_of_second == nullptr)
                {
                    cout << "ERROR - END OF CODING" << endl;
                    return "";
                }
            //jesli dwa znaki sa w tej samej kolumnie 
            if (coordinates_of_first->x == coordinates_of_second->x) 
                {
                    encrypted_text += tab[coordinates_of_first->x][(coordinates_of_first->y + 1) % 5];
                    encrypted_text += tab[coordinates_of_second->x][(coordinates_of_second->y + 1) % 5];
                }
            //jesli dwa znaki sa w tym samym wierszu
            else if (coordinates_of_first->y == coordinates_of_second->y) 
                {
                    encrypted_text += tab[(coordinates_of_first->x + 1) % 5][coordinates_of_first->y];
                    encrypted_text += tab[(coordinates_of_second->x + 1) % 5][coordinates_of_second->y];
                }
            else 
                {
                    encrypted_text += tab[coordinates_of_second->x][coordinates_of_first->y];
                    encrypted_text += tab[coordinates_of_first->x][coordinates_of_second->y];
                }
        }     
    return encrypted_text;
}

string Decoding(string encoded_string)
{
    point* coordinates_of_first;
    point* coordinates_of_second;
    string plaintext = "";
    for (unsigned int x = 0; x < encoded_string.length(); x += 2) 
        {
            coordinates_of_first = FindCoordinates(encoded_string.at(x));
            coordinates_of_second = FindCoordinates(encoded_string.at(x + 1));
            //jesli nie ma wskaznika wychodzimy z programu
            if (coordinates_of_first == nullptr || coordinates_of_second == nullptr) 
                {
                    cout << "ERROR - END OF CODING" << endl;
                    return "";
                }
            //jesli dwa znaki sa w tej samej kolumnie                        
            if (coordinates_of_first->x == coordinates_of_second->x) 
                {
                    if (coordinates_of_first->y - 1 < 0)
                        {
                            plaintext += tab[coordinates_of_first->x][4];
                        }
                    else 
                        {
                            plaintext += tab[coordinates_of_first->x][coordinates_of_first->y - 1];
                        }
                    if (coordinates_of_second->y - 1 < 0) 
                        {
                            plaintext += tab[coordinates_of_second->x][4];
                        }
                    else 
                        {
                            plaintext += tab[coordinates_of_second->x][coordinates_of_second->y - 1];
                        }
                }
            //jesli dwa znaki sa w tym samym wierszu    
            else if (coordinates_of_first->y == coordinates_of_second->y) 
                {
                    if (coordinates_of_first->x - 1 < 0)
                        {
                            plaintext += tab[4][coordinates_of_first->y];
                        } 
                    else 
                        {
                            plaintext += tab[coordinates_of_first->x - 1][coordinates_of_first->y];
                        }   
                    if (coordinates_of_second->x - 1 < 0) 
                        {
                            plaintext += tab[4][coordinates_of_second->y];
                        }  
                    else 
                        {
                            plaintext += tab[coordinates_of_second->x - 1][coordinates_of_second->y];
                        }                   
                }
            else
                {
                    plaintext += tab[coordinates_of_second->x][coordinates_of_first->y];
                    plaintext += tab[coordinates_of_first->x][coordinates_of_second->y];
                }
        }
    return plaintext ;        
}

 

