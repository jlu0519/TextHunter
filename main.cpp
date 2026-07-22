#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

// Converts string to lower case - Used in case-insensitive search.
std::string lower(const std::string& str)
{
    std::string lowercaseText;
    std::transform(str.begin(),str.end(),std::back_inserter(lowercaseText), tolower);         
    return lowercaseText;
}

void search(const std::string& fileName, std::ifstream& file, const std::string& txt, bool caseInsensitive,
        bool invertMatch, bool countOnly, bool lineNumbers, bool showFile)
{
    int lineNumber = 1;
    int countOfLineMatches{};
    std::string line;
    std::string searchTxt = txt;
    

    if(caseInsensitive)
    {
        searchTxt = lower(searchTxt);
    }

    while(std::getline(file,line))
    {
        if(caseInsensitive)
        {
            std::string lowercaseLine = lower(line);

            if(lowercaseLine.find(searchTxt) != std::string::npos)
            {
                std::cout << fileName << ":" << lineNumber << ":" << line << "\n";
            }
        }
        else if(invertMatch)
        {
            if(line.find(searchTxt) == std::string::npos)
            {
                std::cout << line << "\n";
            }
        }
        else if(countOnly)
        {
            if(line.find(searchTxt) != std::string::npos)
            {
                countOfLineMatches++;
            }
        }
        else if(lineNumbers)
        {
            if(line.find(searchTxt) != std::string::npos)
            {
                std::cout << lineNumber << ":" << line << "\n";
            }
        }
        else if(showFile)
        {
            if(line.find(searchTxt) != std::string::npos)
            {
                std::cout << fileName << ":" << line << "\n";
            }
        }
        else
        {
            if(line.find(searchTxt) != std::string::npos)
            {
                std::cout << line << "\n";
            }
        }
                
        lineNumber++;
    }

    if(countOnly)
    {
        std::cout << "Line Matches: " << countOfLineMatches << "\n";
    }
}

int main(int argc, char* argv[])
{
    std::vector<std::string> commandArguments;  
    std::vector<std::string> userFiles; 
    std::string searchTxt = "";

    // Flags / Options
    bool caseInsensitive {false};
    bool invertMatch {false};
    bool countOnly {false};
    bool lineNumbers {false};
    bool showFile {false};

    for(int i = 0; i < argc; ++i)
    {
       commandArguments.push_back(argv[i]);
    }
    
    if(argc <= 1)
    {
        std::cerr << "Error Invalid Syntax: Hint: swiftGrep [-flag] {searchtxt} {file1} [file2 ...]" << std::endl;
        return 1;
    }

    // Verify that both the file path and search pattern were provided
    // Store user-provided file path and search pattern
    if(commandArguments[1] == "-i") 
    {
        if(argc >= 4)
        {
            caseInsensitive = true;
            searchTxt = commandArguments[2];
            for(int i = 3; i < argc; ++i)
            {
                userFiles.push_back(commandArguments[i]);
            } 
        }
        else
        {
            std::cerr << "Error Invalid Syntax: Hint: swiftGrep [-flag] {searchtxt} {file1} [file2 ...]" << std::endl;
            return 1;
        }
    }
    else if(commandArguments[1] == "-v") 
    {
        if(argc >= 4)
        {
            invertMatch = true;
            searchTxt = commandArguments[2];
            for(int i = 3; i < argc; ++i)
            {
                userFiles.push_back(commandArguments[i]);
            } 
        }
        else
        {
            std::cerr << "Error Invalid Syntax: Hint: swiftGrep [-flag] {searchtxt} {file1} [file2 ...]" << std::endl;
            return 1;
        }
    }
    else if(commandArguments[1] == "-c") 
    {
        if(argc >= 4)
        {
            countOnly = true;
            searchTxt = commandArguments[2];
            for(int i = 3; i < argc; ++i)
            {
                userFiles.push_back(commandArguments[i]);
            } 
        }
        else
        {
            std::cerr << "Error Invalid Syntax: Hint: swiftGrep [-flag] {searchtxt} {file1} [file2 ...]" << std::endl;
            return 1;
        }
    }
    else if(commandArguments[1] == "-l") 
    {
        if(argc >= 4)
        {
            lineNumbers = true;
            searchTxt = commandArguments[2];
            for(int i = 3; i < argc; ++i)
            {
                userFiles.push_back(commandArguments[i]);
            } 
        }
        else
        {
            std::cerr << "Error Invalid Syntax: Hint: swiftGrep [-flag] {searchtxt} {file1} [file2 ...]" << std::endl;
            return 1;
        }
    }
    else if(commandArguments[1] == "-f") 
    {
        if(argc >= 4)
        {
            showFile = true;
            searchTxt = commandArguments[2];
            for(int i = 3; i < argc; ++i)
            {
                userFiles.push_back(commandArguments[i]);
            } 
        }
        else
        {
            std::cerr << "Error Invalid Syntax: Hint: swiftGrep [-flag] {searchtxt} {file1} [file2 ...]" << std::endl;
            return 1;
        }
    }
    else if(argc <= 2)
    {
        std::cerr << "Error Invalid Syntax: Hint: swiftGrep [-flag] {searchtxt} {file1} [file2 ...]" << std::endl;
        return 1;
    }
    else
    {
        searchTxt = commandArguments[1];
        for(int i = 2; i < argc; ++i)
        {
            userFiles.push_back(commandArguments[i]);
        } 
    }

    for(const auto& fileName : userFiles)
    {
        // Open file using the stream constructor
        std::ifstream file(fileName);

        // Checking if file can be opened successfully 
        if(!file.is_open()) 
        {
            std::cerr << "Error opening file " << fileName << "!" <<  std::endl;
            continue;
        }
        
        search(fileName, file, searchTxt, caseInsensitive, invertMatch, countOnly, lineNumbers, showFile);

    }

    return 0;
}
