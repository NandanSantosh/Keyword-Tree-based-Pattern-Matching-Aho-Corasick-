#include <iostream>    
#include <string>      // for std::string
#include <vector>      // for std::vector
#include <algorithm>   // for std::min
#include <chrono>      // for high_resolution_clock, duration_cast
#include <cstdlib>     // for srand, rand
#include <ctime>       // for time

using namespace std;
using namespace std::chrono;


string generateRandomString(int length) {

    const char charset[] = {'A', 'C', 'G', 'T'};
    string str = "";
    for (int i = 0; i < length; ++i) {
        str += charset[rand() % 4]; 
    }
    return str;
}
// -------------------------------------------------------------

int main() {
    // Seed random number generator
    srand(static_cast<unsigned int>(time(0)));

    int n, m;

    cout << "Naive Pattern Matching with Generated Data (A, C, G, T)" << endl;
    cout << "--------------------------------------------------------" << endl;
    
    cout << "Enter length of text (n): ";
    if (!(cin >> n) || n < 1) {
        cerr << "Invalid input for n." << endl;
        return 1;
    }
    
    cout << "Enter number of patterns (m): ";
    if (!(cin >> m) || m < 1) {
        cerr << "Invalid input for m." << endl;
        return 1;
    }

    // 1. Generate the main text
    cout << "Generating main text of length " << n << "..." << endl;
    string text = generateRandomString(n);

    // 2. Generate the patterns
    cout << "Generating " << m << " patterns (length 4-6)..." << endl;
    vector<string> patterns;
    for (int i = 0; i < m; ++i) {
        // Generate pattern length between 4 and 6
        int len = 4 + (rand() % 3); 
        patterns.push_back(generateRandomString(len));
    }

    cout << "Starting Naive Matching algorithm..." << endl;
    
    // Start timer (Measuring Algorithm Time)
    auto start = high_resolution_clock::now(); 

    // Initialize counts for m patterns
    vector<int> count(m, 0);
    int text_size = text.size();
    
    // 3. Naive Pattern Matching Logic (Restored)
    for(int k = 0; k < m; k++){
        const string& pattern = patterns[k];
        int pattern_size = pattern.size();
        
        // Loop through all possible starting positions in the text
        for(int i = 0; i + pattern_size <= text_size; i++){
            // Extract the substring of the current pattern size
            string current_substring = "";
            for(int j = i; j < i + pattern_size; j++){
                current_substring += text[j];
            }
            
            // Check for match
            if(pattern == current_substring){
                count[k]++;
            }
        }
    }

    auto stop = high_resolution_clock::now(); // Stop timer
    auto duration = duration_cast<microseconds>(stop - start);

    // Output Results
    cout << "\n--- FINAL COUNTS (Naive Match) ---" << endl;
    
    // Print all patterns if m is small, otherwise print a summary
    if (m <= 20) {
        for (int i = 0; i < patterns.size(); i++)
            cout << patterns[i] << " : " << count[i] << " times\n";
    } else {
        cout << "(Full output suppressed for large m: " << m << " patterns total)" << endl;
        cout << "First 5 patterns tracked:" << endl;
        for (int i = 0; i < min(5, (int)patterns.size()); i++)
             cout << patterns[i] << " : " << count[i] << " times\n";
    }

    cout << "\nAlgorithm Execution Time: " << duration.count() 
         << " microseconds\n";

    return 0;
}