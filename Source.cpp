#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <vector>

int main()
{
    // Bools used in compiling.
    bool wordScan = false; bool hasInput = false; bool inputScan = false; bool skipCheck = false; bool codeScan = false;
    int inputScanInt = 0;


    // Used to detect which file to use
    std::string fileName;
    std::cout << "Please enter the file name of the source code: ";
    std::cin >> fileName;

    // Create a text file
    std::ofstream ifCompiled("compiled.cpp");

    // Opens the file to read from it
    std::ifstream file;
    file.open(fileName);
    if (!file.is_open()) return 0;
    std::string word;

    // Array storing the file's previous words, for use in compiling
    std::vector<std::string> previousWords;
    int previousWord = 0;

    ifCompiled << "#include<string>" << std::endl << "#include<iostream>" << std::endl;
    ifCompiled << "int/**/main(){int page = 1; std::cout << \"Please enter a page to go to (Enter 1 to go to start page. Entering an invalid amount will start you at page 1):\";while (!(std::cin >> page)) {std::cin.clear();std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\\n');std::cout << \"Invalid input.  Try again.\\n>\";};int choice=0; while(1){";
    while (file >> word)
    {
        skipCheck = false;

        // Adds the previous word in the file to a vector array.
        previousWords.push_back(word);

        //################################################################################//
        // Page Declarations //
        // Declares what number to check for, based on if the previous word was page
        if (previousWord > 0) {
            if (previousWords[previousWord - 1] == "page" && wordScan == false && inputScan == false)
            {
                ifCompiled << word << "){std::cout << \"Page = \" << page << std::endl;";
            }
        }


        // Creates the if statement for the above function to them inject itself into, reading from the file which number it is.
        if (word == "page" && wordScan == false && inputScan == false)
        {
            hasInput = false;
            ifCompiled << "if (page == ";
        }
        //################################################################################//


        //################################################################################//
        // Input detect //
        if (word == "option") {
            inputScan = true;
            if (hasInput == false) {
                hasInput = true;
                ifCompiled << "std::cout << \">\"; while (!(std::cin >> choice)) {std::cin.clear();std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\\n');std::cout << \"Invalid input.  Try again.\\n>\";}";
            }
            ifCompiled << "if (choice == ";
            inputScanInt = 0;
        }

        if (inputScan == true) {
            if (inputScanInt == 1) {
                ifCompiled << word << "){";
            }
            else if (inputScanInt == 3) {
                ifCompiled << "page = " << word << ";}";
                inputScan = false;
            }
            inputScanInt += 1;
        }



        //################################################################################//
        // Word scan //
        // This one puts the text into the compiled file, and ends when it detects another "
        if (wordScan == true && inputScan == false) {
            if (word == "\"") {
                ifCompiled << "\" << std::endl;";
                wordScan = false;
                skipCheck = true;
            }
            else {
                ifCompiled << word << " ";
            }
        }

        // This one scans for the beginning of the text
        if (word == "\"" && wordScan == false && inputScan == false && skipCheck == false) {
            wordScan = true;
            ifCompiled << "std::cout << \"";
        }
        //################################################################################//



        //################################################################################//
        // Ending Functions //
        // Detects if a page has been ended
        else if (word == "endpage" && wordScan == false)
        {
            ifCompiled << "}";
        }


        // Ends the story wherever this command is present
        else if (word == "endstory" && wordScan == false)
        {
            ifCompiled << "std::cout << \"Press enter to exit...\\n\"; std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\\n');  std::cin.ignore(); return 0;}";
        }
        //################################################################################//


        // Ends the story wherever this command is present
        else if (word == "endstory" && wordScan == false)
        {
            ifCompiled << "std::cout << \"Press enter to exit...\\n\"; std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\\n');  std::cin.ignore(); return 0;}";
        }
        //################################################################################//
        
        //################################################################################//
        // Detect for C++ custom input //
        // Detects if user is injecting their own code

        //Detects if user is inputting custom code
        if (word == "{CODE}" && wordScan == false && codeScan == true)
        {
            codeScan = false;
        }

        else if (word == "{CODE}" && wordScan == false && codeScan == false)
        {      
            codeScan = true;
        }

        // Inputs user code
        else if (codeScan == true)
        {
            ifCompiled << word;
        }
        std::cout << codeScan;

        previousWord += 1;
    }

    ifCompiled << "else{page = 1;}} return 0;}";

    // Close the file
    ifCompiled.close();
    file.close();

    while (1) {};
}
