#include "FileProcessor.h"
#include <iostream>

FileProcessor::FileProcessor(const std::string& outputPath) : outputPath(outputPath) {
    openOutputFile();
}

FileProcessor::~FileProcessor() {
    closeOutputFile();
}

bool FileProcessor::readConfig(const std::string& inputPath, int& maxLevel, int& worldSize, int& powerLevel, 
                               int& percentCoins, int& percentNothing, int& percentGoombas, int& percentKoopas, int& percentMushrooms) {
    std::ifstream inputFile(inputPath);
    if (!inputFile.is_open()) {
        std::cerr << "Failed to open input file: " << inputPath << std::endl;
        return false;
    }

    inputFile >> maxLevel >> worldSize >> powerLevel 
              >> percentCoins >> percentNothing >> percentGoombas >> percentKoopas >> percentMushrooms;

    inputFile.close();
    return true;
}


void FileProcessor::log(const std::string& message) {
    if (outputFile.is_open()) {
        outputFile << message << std::endl;
    } else {
        std::cerr << "Output file is not open for logging." << std::endl;
    }
}

void FileProcessor::openOutputFile() {
    outputFile.open(outputPath, std::ios::out);
    if (!outputFile.is_open()) {
        throw std::runtime_error("Failed to open output file: " + outputPath);
    }
}

void FileProcessor::closeOutputFile() {
    if (outputFile.is_open()) {
        outputFile.close();
    }
}
