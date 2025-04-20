// Name:Logan Calder
// Date:04/03/2025
// Project 1:Lexical Analyzer
// Description:This program reads input from the user and parses characters into tokens. These are then printed out to the console.

#include <stdio.h>
#include <cctype>
#include <set>
#include <string>
#include <iostream>

using namespace std;

int main()
{
    set<string> keywords = {"auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register", "return", "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while"};
    set<char> operators = {'=', '|', '<', '>', '+', '-', '*', '/', '%', '&', '!', '.', '(', ')', '[', ']', '{', '}', ';', ':', ','};
    set<string> two_char_operators = {"<=", ">=", "==", "!=", "&&", "||", "++", "--", "+=", "-=", "*=", "/=", "%=", "...", "->"};

    int c;
    string buffer = "";

    while (true)
    {
        c = cin.get(); // get the next character

        // If end of file, break
        if (c == EOF)
            break;

        // If space, ignore and go on
        if (c == ' ')
        {
            continue;
        }

        // If its a digit, we want to keep reading til its not
        else if (isdigit(c))
        {
            buffer += c;
            while (isdigit(cin.peek()))
            {
                c = cin.get();
                buffer += c;
            }
            cout << "number:" << buffer << endl;
            buffer = "";
        }

        else if (isalpha(c) || c == '_')
        {
            buffer += c;

            while (isalpha(cin.peek()) || cin.peek() == '_')
            {
                c = cin.get();
                buffer += c;
            }

            if (keywords.find(buffer) != keywords.end())
            {
                cout << "keyword:" << buffer << endl;
            }
            else
            {
                cout << "identifier:" << buffer << endl;
            }
            buffer = "";
        }

        // If its a quote, we want to keep reading til its not
        else if (c == '\"')
        {
            c = cin.get();
            buffer += c;
            int store;
            string two_char = "";

            while (true)
            {
                store = c;
                c = cin.get();
                two_char = string(1, store) + string(1, c);
                if (c == '\"' && two_char != "\\\"")
                {
                    break;
                }
                buffer += c;
            }
            cout << "string:" << '\"' << buffer << '\"' << endl;
            buffer = "";
        }

        // If its a single quote, print the character
        else if (c == '\'')
        {
            c = cin.get();
            buffer += c;
            int store;
            string two_char = "";

            while (true)
            {
                store = c;
                c = cin.get();
                two_char = string(1, store) + string(1, c);
                if (c == '\"' && two_char != "\\\'")
                {
                    break;
                }
                buffer += c;
            }
            cout << "character:" << '\'' << buffer << '\"' << endl;
            buffer = "";
        }

        // Operator
        else if (operators.find(c) != operators.end())
        {
            // Check for potential three-character operator (...)
            int next_c = cin.get();
            if (next_c != EOF)
            {
                int next_next_c = cin.get();
                if (next_next_c != EOF)
                {
                    string three_char_op = string(1, c) + (char)next_c + (char)next_next_c;
                    if (three_char_op == "...")
                    {
                        cout << "operator:..." << endl;
                        continue;
                    }
                    else
                    {
                        cin.putback(next_next_c); // Put back the third character
                    }
                }
                else
                {
                    cin.putback(next_next_c); // Put back EOF
                }
            }

            // Check for potential two-character operators
            if (next_c != EOF)
            {
                string two_char_op = string(1, c) + (char)next_c;
                string current = "";
                if (two_char_op == "/*")
                {
                    c = cin.get();
                    while (cin.peek() != EOF)
                    {
                        current = string(1, c) + string(1, cin.peek());
                        if (current == "*/")
                        {
                            break;
                        }
                        c = cin.get();
                    }
                    c = cin.get();
                    continue;
                }

                else if (two_char_operators.find(two_char_op) != two_char_operators.end())
                {
                    cout << "operator:" << two_char_op << endl;
                    continue;
                }
                else
                {
                    cin.putback(next_c); // Put back the character if it's not part of a two-char operator
                }
            }
            cout << "operator:" << (char)c << endl;
        }

                // If its an alphabet, we want to keep reading until the end
    }
    return 0;
}
