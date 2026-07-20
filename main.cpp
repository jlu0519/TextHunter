#include <iostream>
#include <fstream>
#include <string>

int main(){
 
    std::cout << "Enter a filename to search!\n";

    std::string userFile;

    std::getline(std::cin, userFile);

    // Open file using the stream constructor
    std::ifstream file(userFile);

    // Checking if file can be opened successfully 
    if(!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    std::string line;
    // Condition checks if a line was successfully read
    while(std::getline(file,line)) {
        // Process your line here
        std::cout << line << "\n";
    }

    // Closes automatically when "file" goes out of scope
    // but you can call close() explicitly if needed.
    file.close();
    return 0;
}

    


    
