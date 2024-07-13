#include <iostream>
#include <string>
#include <vector>
#include <fstream>


/*
 An implementation of Horspool's String Matching algorithm.
 Returns true if the given "pattern" (a string of m characters) occurs at
 least once in the given "text" (a longer string of n characters).
 */
bool HorspoolStringMatching(std::string pattern, std::string text, bool isTest) {
    
    int m = pattern.length(); // the length of the pattern
    int n = text.length(); // the length of the text
    int alphabetSize = 52; // the alphabet size (lowercase and uppercase letters)
    
    /*
     The text is checked for unsupported characters. If any are found,
     the text is returned as a non-match.
     */
    for (int i = 0; i < n; i++) {
        /*
         The current character is checked to be out of the range of
         lower and uppercase letters in the ASCII table.
         */
        if ((text[i] < 65) || (text[i] > 122)) {
            return false;
        }
        /*
         The current character is checked to not be equal to
         special characters occurring between lower and uppercase
         letters in the ASCII table.
         */
        if((text[i] < 97) && (text[i] > 90)) {
            return false;
        }
    }
    
    /*
     The algorithm utilizes input enhancement for a time-for-space tradeoff.
     Shift sizes are pre-computed and stored in a shift table to make repetitive
     character comparisions unnecessary. The table is indexed by possible
     characters (lowercase and uppercase letters; special characters and
     numbers are not supported), and the table's entries indicate shift sizes.
     */
    
    // the shift table is created
    int shiftTable[alphabetSize];
    
    // the shift table is initialized with the pattern length
    for (int i = 0; i < alphabetSize; i++) {
        shiftTable[i] = m;
    }
    
    // the shift sizes are calculated for each character
    for (int j = 0; j < m - 1; j++) {
        
        /*
         The shift table is indexed by possible characters
         (lowercase and uppercase letters). Lowercase letters are stored
         in indices 0-25, and uppercase are stored in 26-51. To find the
         index corresponding with correct character, the character is first
         checked to be lower or uppercase. Because 'a' has a ASCII decimal
         value of 97, 'b' has a value of 98, and so on, subtracting 97 from any
         lowercase letter from a-z will yield the correct position for that character
         in indices 0-25. The same logic holds true for capital letters A-Z.
         */
        if (pattern[j] < 'a' || pattern[j] > 'z') {
            shiftTable[pattern[j] - 39] = m - 1 - j;
        } else {
            shiftTable[pattern[j] - 97] = m - 1 - j;
        }
    }
    
    /*
     The shift table is printed for the current pattern if testing is enabled.
     Used for testing.
     */
    if (isTest) {
        std::cout << "Shift table for pattern \"" << pattern << "\": ";
        for (int i = 0; i < alphabetSize; i++) {
            std::cout << shiftTable[i]; // the shift table is printed
        }
        // the current text is printed
        std::cout << " (Text: \"" << text << "\")" << std::endl;
    }
    
    /*
     Horspool's String Matching algorithm
     */
    
    int i = m - 1; // position of the pattern's right end
    while (i <= n - 1) {
        int k = 0;
        while ((k <= m - 1) && (pattern[m - 1 - k] == text[i - k])) {
            k = k + 1;
        }
        if (k == m) {
            return true;
        } else {
            if (text[i] < 'a' || text[i] > 'z') {
                i = i + shiftTable[text[i] - 39];
            } else {
                i = i + shiftTable[text[i] - 97];
            }
        }
    }
    return false;
}

/*
 Loads and returns a vector of strings that contains the texts
 (character sequences separated by a space or new line in
 a .txt file) that a given pattern occurs in.
 */
std::vector<std::string> matchPatternToTexts(std::string pattern, std::vector<std::string> allTexts, bool isTest) {
    
    /*
     Vector to be populated with every texts that has at least one occurrence of
     the pattern.
     */
    std::vector<std::string> matchingTexts;
    
    /*
     Each text in a file is processed and checked for an occurrence of
     the pattern. If there is a match, the text is added to the vector
     of matching texts to be returned.
     */
    for (auto itr = allTexts.begin(); itr != allTexts.end(); itr++) {
        std::string currentText = *itr; // the current text
        // the text is checked for an occurrence of the pattern
        if (HorspoolStringMatching(pattern, currentText, isTest)) {
            matchingTexts.push_back(currentText); // the text is added to the vector
        }
    }
    
    return matchingTexts; // the populated matching texts vector is returned
}

/*
 Loads and returns a vector of strings that contains every text
 (character sequences separated by a space or new line) in a .txt file.
 */
std::vector<std::string> textsFromFile(std::string fileName) {
    
    /*
     Vector to be populated with every text in a file.
     Texts are character sequences separated by a space or new line.
     */
    std::vector<std::string> texts;
    
    std::ifstream fin(fileName.c_str()); // an input stream is opened
    /*
     If there is an error opening the file a message is printed
     to the console and the vector of texts is returned empty.
     */
    if (!fin.is_open()) {
        std::cout << "Error opening file \"" << fileName << "\"" << std::endl;
        return texts;
    }
    
    std::string currentText; // the current text in the file
    /*
     While there are texts to be processed, they are added to
     the vector.
     */
    while (fin >> currentText) {
        texts.push_back(currentText);
    }
    
    return texts; // the populated vector containing every text is returned
}

/*
 Prints a report to the console for a single file, displaying information
 such as the total number of texts in the file, the total number of texts
 containing an occurrence of the pattern, and a list of all matching texts.
 */
void report(std::string pattern, std::string fileName, bool isTest) {
    
    // a test identifier is printed if the file is being run for application testing
    if (isTest) {
        std::cout << " **TEST**" << std::endl;
    }
    
    /*
     A report is printed for the file, including information such as the 
     total number of texts in the file, the total number of matching
     texts, and a list of all matching texts.
     */
    
    // prints report header
    std::cout << "--- Report for \"" << fileName << "\" ---" << std::endl;
    
    // every text in the file
    std::vector<std::string> allTexts = textsFromFile(fileName);
    
    // every texts with at least one occurrence of the pattern
    std::vector<std::string> matchingTexts = matchPatternToTexts(pattern, allTexts, isTest);
    
    // prints the current pattern
    std::cout << "Pattern to match: \"" << pattern << "\"" << std::endl;
    
    // prints the number of texts in the file
    std::cout << "Number of texts in file: " << allTexts.size() << std::endl;
    
    // prints the number of texts matching the pattern
    std::cout << "Number of texts with occurrence of pattern in file: " << matchingTexts.size() << std::endl;
    std::cout << std::endl;
    
    // prints a list of all pattern-matching texts in the file
    std::cout << "Texts containing the pattern \"" << pattern << "\":" << std::endl;
    for (auto itr = matchingTexts.begin(); itr != matchingTexts.end(); itr++) {
        std::string currentText = *itr;
        std::cout << "-> " << currentText << std::endl;
    }
    std::cout << "--- End of Report ---" << std::endl; // prints report end
    std::cout << std::endl;
}

/*
 Runs the application on each .txt file in a vector of file names.
 A file is parsed, a vector is populated with every "text" in
 the file (character sequences separated by a space or new line),
 and the "pattern" is matched against each text. If a text contains
 at least one occurrance of the pattern, it is added to a list of
 matching texts which is then reported to the console in a report
 for that file.
 */
void run(std::string pattern, std::vector<std::string> fileNames, bool isTest) {
    
    /*
     The pattern is checked for unsupported characters. If any are found,
     the text is returned as a non-match.
     */
    bool isInvalidPattern = false;
    for (int i = 0; i < pattern.length(); i++) {
        /*
         The current character is checked to be out of the range of
         lower and uppercase letters in the ASCII table.
         */
        if ((pattern[i] < 65) || (pattern[i] > 122)) {
            isInvalidPattern = true;
        }
        /*
         The current character is checked to not be equal to
         special characters occurring between lower and uppercase
         letters in the ASCII table.
         */
        if((pattern[i] < 97) && (pattern[i] > 90)) {
            isInvalidPattern = true;
        }
        if (isInvalidPattern) {
            std::cout << "Invalid pattern. Acceptable characters are lower and uppercase letters (a-z, A-Z). Numbers and special characters are not supported/allowed." << std::endl;
            std::exit(0);
        }
    }
    
    /*
     A report is generated for each file.
     */
    for (auto itr = fileNames.begin(); itr != fileNames.end(); itr++) {
        
        std::string currentFile = *itr; // the current file being processed in the vector
        report(pattern, currentFile, isTest);
    }
}

/*
 The main method of the application. Files to process and the pattern
 to match to file's texts are specified.
 */
int main(int argc, const char * argv[]) {
    
    // *--- INPUT ---*
    
    /*
     File names in this list will be processed and have a report generated.
     */
    std::vector<std::string> inputFileNames {"inputfiles/sample.txt",
        "inputfiles/sample2.txt"};
    std::string pattern = "the"; // the pattern to be matched against each text in every file
    
    // runs the application with given file names and pattern to match
    run(pattern, inputFileNames, false);
    
    // *------*
    
    
    // *--- TESTING ---*
    
    /*
     File names in this list will be processed and have a report generated with testing
     enabled. These files are used to test the application.
     */
//    std::vector<std::string> testFileNames {"testfiles/testSingleLine.txt",
//        "testfiles/testMultipleLines.txt",
//        "testfiles/testMultipleTextSameLine.txt",
//        "testfiles/testMixedCase.txt",
//        "testfiles/testUnsupportedCharacters.txt",
//        "testfiles/testPatternBeginningOfText.txt",
//        "testfiles/testPatternMiddleOfText.txt",
//        "testfiles/testPatternEndOfText.txt",
//        "testfiles/testIncompletePatternBeginningOfText.txt",
//        "testfiles/testIncompletePatternMiddleOfText.txt",
//        "testfiles/testIncompletePatternEndOfText.txt"};
    
//    pattern = "the"; // the pattern "the" is used for testing
    
    /*
     Runs the application with given file names and pattern to match for testing.
     Because isTest is true, the shift table will be printed for the pattern for each
     text processed.
     */
//    run(pattern, testFileNames, true);
    
    // *------*
    
    
    return 0;
}
