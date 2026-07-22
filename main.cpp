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

void search(const std::string& fileName, std::ifstream& file, const std::string& txt, bool caseInsensitive)
{
    int lineNumber = 1;
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
        else
        {
            if(line.find(searchTxt) != std::string::npos)
            {
                std::cout << fileName << ":" << lineNumber << ":" << line << "\n";
            }
        }
        lineNumber++;
    }
}

int main(int argc, char* argv[])
{
    std::vector<std::string> commandArguments;  
    std::vector<std::string> userFiles; 
    std::string searchTxt = "";
    bool caseInsensitive {false};

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
    else if(argc <= 2)
    {
        std::cerr << "Error Invalid Syntax: Hint: swiftGrep [-flag] {searchtxt} {file.txt}" << std::endl;
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
        
        search(fileName, file, searchTxt, caseInsensitive);

    }

    return 0;
}
