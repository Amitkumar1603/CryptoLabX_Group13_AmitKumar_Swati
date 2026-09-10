#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iomanip>
#include <cmath>

using namespace std;

string clean_ciphertext(string text){
    string result;

    for (char c :text){
        if(c>='a' && c<='z'){
            c=c-'a'+'A';
            }

        if(c>='A'&& c<='Z'){
            result += c;
            }
    }

    return result;
}

vector<string> find_repeated_patterns(string text){
    vector<string> patterns;

    for(int len=3;len<=5;len++){
    
        for(int i=0;i<=(int)text.length()-len;i++){
            string pattern = text.substr(i,len);

            int count=0;

            for(int j=i+1;j<=(int)text.length()-len;j++){
            
                if (text.substr(j,len)==pattern){
                    count++;
                    }
            }

            if(count>0){
                patterns.push_back(pattern);
                }
        }
    }

    sort(patterns.begin(), patterns.end());
    patterns.erase(unique(patterns.begin(), patterns.end()), patterns.end());

    return patterns;
}

vector<int> calculate_distances(string text, string pattern){
    vector<int> pos;
    vector<int> dis;

    for (int i=0;i<=(int)text.length()-(int)pattern.length(); i++){
        if(text.substr(i, pattern.length())==pattern){
            pos.push_back(i);
            }
    }

    for (int i=1;i<(int)pos.size();i++){
        dis.push_back(pos[i]-pos[i-1]);
        }

    return dis;
}

vector<int> find_factors(vector<int> distances){
    vector<int> factors;

    for(int d : distances){
    
        for(int i=2;i<=20;i++){
        
            if(d %i==0){
                factors.push_back(i);
                }
        }
    }

    return factors;
}

vector<pair<int, int>> kasiski_analysis(string text){

    vector<string>patterns=find_repeated_patterns(text);
    map<int, int> factor_count;

    for (string pattern:patterns){
        vector<int> distances = calculate_distances(text, pattern);
        vector<int> factors = find_factors(distances);

        for (int f : factors)
            factor_count[f]++;
    }

    vector<pair<int, int>> result;

    for (auto x : factor_count){
    
        result.push_back({x.first, x.second});
        }

    sort(result.begin(), result.end(),
         [](pair<int, int> a, pair<int, int> b)
         {
             return a.second > b.second;
         });

    return result;
}

double calculate_ic(string text){
    int n = text.length();

    if(n<=1)
        return 0;

    int count[26]={0};

    for (char c : text)
        count[c - 'A']++;

    double total = 0;

    for (int i = 0; i < 26; i++)
        total += count[i] * (count[i] - 1);

    return total / (n * (n - 1));
}

vector<string> split_into_groups(string text, int keyLength)
{
    vector<string> groups(keyLength);

    for (int i = 0; i < (int)text.length(); i++)
        groups[i % keyLength] += text[i];

    return groups;
}

void frequency_analysis(string group)
{
    int count[26] = {0};

    for (char c : group)
        count[c - 'A']++;

    cout << "A-Z Frequency:\n";

    for (int i = 0; i < 26; i++)
    {
        cout << char('A' + i) << " : "
             << count[i] << "\n";
    }
}

int find_shift(string group)
{
    double english[26] =
    {
        0.08167, 0.01492, 0.02782, 0.04253, 0.12702,
        0.02228, 0.02015, 0.06094, 0.06966, 0.00153,
        0.00772, 0.04025, 0.02406, 0.06749, 0.07507,
        0.01929, 0.00095, 0.05987, 0.06327, 0.09056,
        0.02758, 0.00978, 0.02360, 0.00150, 0.01974,
        0.00074
    };

    int count[26] = {0};

    for (char c : group)
        count[c - 'A']++;

    int n = group.length();

    double best = 1e18;
    int bestShift = 0;

    for (int shift = 0; shift < 26; shift++)
    {
        double chi = 0;

        for (int i = 0; i < 26; i++)
        {
            int cipherLetter = (i + shift) % 26;

            double expected = n * english[i];
            double observed = count[cipherLetter];

            if (expected > 0)
            {
                chi += (observed - expected) *
                       (observed - expected) /
                       expected;
            }
        }

        if (chi < best)
        {
            best = chi;
            bestShift = shift;
        }
    }

    return bestShift;
}

string find_key(string text, int keyLength)
{
    vector<string> groups = split_into_groups(text, keyLength);

    string key;

    for (string group : groups)
    {
        int shift = find_shift(group);
        key += char('A' + shift);
    }

    return key;
}

string vigenere_decrypt(string text, string key)
{
    string result;

    for (int i = 0; i < (int)text.length(); i++)
    {
        int c = text[i] - 'A';
        int k = key[i % key.length()] - 'A';

        int p = (c - k + 26) % 26;

        result += char('A' + p);
    }

    return result;
}

string vigenere_encrypt(string text, string key)
{
    string result;

    for (int i = 0; i < (int)text.length(); i++)
    {
        int p = text[i] - 'A';
        int k = key[i % key.length()] - 'A';

        int c = (p + k) % 26;

        result += char('A' + c);
    }

    return result;
}

bool verify(string original, string encrypted)
{
    return original == encrypted;
}

int choose_key_length(string text)
{
    vector<pair<int, int>> kasiski = kasiski_analysis(text);

    double bestScore = -1;
    int bestLength = 2;

    for (int keyLength = 2; keyLength <= 20; keyLength++)
    {
        vector<string> groups = split_into_groups(text, keyLength);

        double averageIC = 0;

        for (string group : groups)
            averageIC += calculate_ic(group);

        averageIC /= groups.size();

        int factorVotes = 0;

        for (auto x : kasiski)
        {
            if (x.first == keyLength)
            {
                factorVotes = x.second;
                break;
            }
        }

        double score = averageIC * 100 + factorVotes * 0.15;

        if (score > bestScore)
        {
            bestScore = score;
            bestLength = keyLength;
        }
    }

    return bestLength;
}

void display_frequency_tables(string text, int keyLength)
{
    vector<string> groups = split_into_groups(text, keyLength);

    for (int i = 0; i < keyLength; i++)
    {
        cout << "\nGroup " << i + 1 << ":\n";

        cout << groups[i] << "\n\n";

        frequency_analysis(groups[i]);
    }
}

int main()
{
    string ciphertext1 =
        "DAZFI SFSPA VQLSN PXYSZ WXALC DAFGQ UISMT PHZGA "
        "MKTTF TCCFX "
        "KFCRG GLPFE TZMMM ZOZDE ADWVZ WMWKV GQSOH QSVHP "
        "WFKLS LEASE "
        "PWHMJ EGKPU RVSXJ XVBWV POSDE TEQTX OBZIK WCXLW "
        "NUOVJ MJCLL "
        "OEOFA ZENVM JILOW ZEKAZ EJAQD ILSWW ESGUG KTZGQ "
        "ZVRMN WTQSE "
        "OTKTK PBSTA MQVER MJEGL JQRTL GFJYG SPTZP GTACM "
        "OECBX SESCI "
        "YGUFP KVILL TWDKS ZODFW FWEAA PQTFS TQIRG MPMEL "
        "RYELH QSVWB "
        "AWMOS DELHM UZGPG YEKZU KWTAM ZJMLS EVJQT GLAWV "
        "OVVXH KWQIL "
        "IEUYS ZWXAH HUSZO GMUZQ CIMVZ UVWIF JJHPW VXFSE "
        "TZEDF";

     
   

    string ciphertext;

    
     ciphertext = ciphertext1;

    ciphertext = clean_ciphertext(ciphertext);

    cout << "\nClean Ciphertext:\n";
    cout << ciphertext << "\n";

    cout << "\nLength of Ciphertext: "
         << ciphertext.length() << "\n";

    cout << "\nKASISKI ANALYSIS\n";

    vector<pair<int, int>> kasiski = kasiski_analysis(ciphertext);

    cout << "\nPossible Key Lengths:\n";

    for (auto x : kasiski){
        cout << "Length " << x.first
             << " -> " << x.second
             << " votes\n";
    }

    int keyLength = choose_key_length(ciphertext);

    cout << "\nEstimated Key Length: "
         << keyLength << "\n";

    cout << "\nINDEX OF COINCIDENCE\n";

    vector<string> groups = split_into_groups(ciphertext, keyLength);

    for (int i = 0; i < keyLength; i++)
    {
        cout << "Group " << i + 1
             << " IC = "
             << fixed << setprecision(4)
             << calculate_ic(groups[i])
             << "\n";
    }

    cout << "\nFREQUENCY ANALYSIS\n";

    display_frequency_tables(ciphertext, keyLength);

    string key = find_key(ciphertext, keyLength);

    cout << "\nRecovered Key: "
         << key << "\n";

    string plaintext = vigenere_decrypt(ciphertext, key);

    cout << "\nRecovered Plaintext:\n";
    cout << plaintext << "\n";

    string encrypted = vigenere_encrypt(plaintext, key);

    cout << "\nVerification:\n";

    if (verify(ciphertext, encrypted))
        cout << "Verification Successful\n";
    else
        cout << "Verification Failed\n";

    return 0;
}
