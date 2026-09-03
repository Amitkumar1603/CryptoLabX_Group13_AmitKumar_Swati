#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <cctype>

using namespace std;

string encrypt_text(string text, string key)
{
    string result = "";

    for (int i = 0; i < text.length(); i++)
    {
        char c = text[i];

        if (isalpha(c))
        {
            c = toupper(c);
            result += key[c - 'A'];
        }
        else
        {
            result += c;
        }
    }

    return result;
}

void frequency_analysis(string text)
{
    int count[26] = {0};
    int total = 0;

    for (int i = 0; i < text.length(); i++)
    {
        char c = text[i];

        if (isalpha(c))
        {
            c = toupper(c);
            count[c - 'A']++;
            total++;
        }
    }

    vector<pair<char, int>> letters;

    for (int i = 0; i < 26; i++)
    {
        letters.push_back({char('A' + i), count[i]});
    }

    sort(letters.begin(), letters.end(),
         [](pair<char, int> a, pair<char, int> b)
         {
             return a.second > b.second;
         });

    cout << "\n========== FREQUENCY ANALYSIS ==========\n";
    cout << "Letter\tCount\tPercentage\n";

    for (int i = 0; i < 26; i++)
    {
        if (letters[i].second > 0)
        {
            double p = (letters[i].second * 100.0) / total;

            cout << letters[i].first << "\t"
                 << letters[i].second << "\t"
                 << p << "%\n";
        }
    }
}

void word_frequency_analysis(string text)
{
    map<string, int> words;
    string word = "";

    for (int i = 0; i <= text.length(); i++)
    {
        if (i < text.length() && isalpha(text[i]))
        {
            word += toupper(text[i]);
        }
        else
        {
            if (word != "")
            {
                words[word]++;
                word = "";
            }
        }
    }

    cout << "\n========== WORD ANALYSIS ==========\n";

    cout << "\nOne letter words:\n";

    for (auto x : words)
    {
        if (x.first.length() == 1)
            cout << x.first << " = " << x.second << endl;
    }

    cout << "\nTwo letter words:\n";

    for (auto x : words)
    {
        if (x.first.length() == 2)
            cout << x.first << " = " << x.second << endl;
    }

    cout << "\nThree letter words:\n";

    for (auto x : words)
    {
        if (x.first.length() == 3)
            cout << x.first << " = " << x.second << endl;
    }

    cout << "\nRepeated words:\n";

    for (auto x : words)
    {
        if (x.second > 1)
            cout << x.first << " = " << x.second << endl;
    }
}

string get_pattern(string word)
{
    map<char, int> value;
    int number = 1;
    string pattern = "";

    for (int i = 0; i < word.length(); i++) {
        char c = word[i];

        if (value.find(c) == value.end())
        {
            value[c] = number;
            number++;
        }

        pattern += char('0' + value[c]);
    }

    return pattern;
}

void pattern_analysis(string text)
{
    string word = "";

    cout << "\n========== PATTERN ANALYSIS ==========\n";

    for (int i = 0; i <= text.length(); i++)
    {
        if (i < text.length() && isalpha(text[i]))
        {
            word += toupper(text[i]);
        }
        else
        {
            if (word != "")
            {
                cout << word << " -> "
                     << get_pattern(word) << endl;

                word = "";
            }
        }
    }
}

string apply_substitution(string text, string sub)
{
    string result = "";

    for (int i = 0; i < text.length(); i++)
    {
        char c = text[i];

        if (isalpha(c))
        {
            c = toupper(c);

            if (sub[c - 'A'] == '?')
                result += '_';
            else
                result += sub[c - 'A'];
        }
        else
        {
            result += c;
        }
    }

    return result;
}

void display_partial_plaintext(string text, string sub)
{
    cout << "\nPartial plaintext:\n";
    cout << apply_substitution(text, sub) << endl;
}

bool verify_solution(string plaintext, string ciphertext, string key)
{
    string new_cipher = encrypt_text(plaintext, key);

    if (new_cipher == ciphertext)
        return true;

    return false;
}

int main()
{
    ifstream file("plaintext.txt");

    if (!file)
    {
        cout << "File not found\n";
        return 0;
    }

    string plaintext = "";
    string line;

    while (getline(file, line))
    {
        plaintext += line;
        plaintext += "\n";
    }

    file.close();

    string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string key = "QWERTYUIOPASDFGHJKLZXCVBNM";

    string ciphertext = encrypt_text(plaintext, key);

    cout << "MONOALPHABETIC SUBSTITUTION CIPHER\n";

    cout << "\nPlaintext:\n";
    cout << plaintext;

    cout << "\nKey:\n";
    cout << "Plain : " << alphabet << endl;
    cout << "Cipher: " << key << endl;

    cout << "\nCiphertext:\n";
    cout << ciphertext << endl;

    frequency_analysis(ciphertext);

    word_frequency_analysis(ciphertext);

    pattern_analysis(ciphertext);

    string sub(26, '?');

    cout << "\n========== CRYPTANALYSIS ==========\n";
    cout << "Enter 0 to stop\n";

    while (true)
    {
        char cipher_letter;
        char plain_letter;

        cout << "\nCipher letter: ";
        cin >> cipher_letter;

        if (cipher_letter == '0')
            break;

        cout << "Plain letter: ";
        cin >> plain_letter;

        cipher_letter = toupper(cipher_letter);
        plain_letter = toupper(plain_letter);

        sub[cipher_letter - 'A'] = plain_letter;

        display_partial_plaintext(ciphertext, sub);
    }

    cout << "\n========== FINAL PLAINTEXT ==========\n";
    cout << apply_substitution(ciphertext, sub) << endl;

    cout << "\n========== RECOVERED KEY ==========\n";

    for (int i = 0; i < 26; i++)
    {
        if (sub[i] != '?')
        {
            cout << char('A' + i)
                 << " -> "
                 << sub[i] << endl;
        }
    }

    cout << "\n========== VERIFICATION ==========\n";

    if (verify_solution(plaintext, ciphertext, key))
        cout << "Verification successful\n";
    else
        cout << "Verification failed\n";

    return 0;
}
