#ifndef FILEPROCESSOR_H
#define FILEPROCESSOR_H

#include <string>
#include <fstream>

class FileProcessor {
public:
    explicit FileProcessor(const std::string& outputPath); // constructor to set output file path
    ~FileProcessor(); // destructor to handle cleanup
    bool readConfig(const std::string& inputPath, int& maxLevel, int& worldSize, int& powerLevel, 
                    int& percentCoins, int& percentNothing, int& percentGoombas, int& percentKoopas, int& percentMushrooms); // reads game config from file
    void log(const std::string& message); // writes a log message to the output file

private:
    std::string outputPath; // path for output file
    std::ofstream outputFile; // output file stream
    void openOutputFile(); // opens the output file for writing
    void closeOutputFile(); // closes the output file stream
};

#endif 
