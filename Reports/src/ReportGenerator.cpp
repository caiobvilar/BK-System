#include "ReportGenerator.h"
#include <fstream>
#include <iostream>
#include <string>

ReportGenerator::ReportGenerator()
{
    // Constructor implementation
}

ReportGenerator::~ReportGenerator()
{
    // Destructor implementation
}

void ReportGenerator::generateReport(const std::string& reportName)
{
    std::ofstream reportFile(reportName);
    if (reportFile.is_open())
    {
        reportFile << "Report Content\n";
        reportFile.close();
        std::cout << "Report generated: " << reportName << std::endl;
    } else
    {
        std::cerr << "Unable to open file: " << reportName << std::endl;
    }
}

void ReportGenerator::printReport(const std::string& reportName)
{
    std::ifstream reportFile(reportName);
    if (reportFile.is_open())
    {
        std::string line;
        while (getline(reportFile, line))
        {
            std::cout << line << std::endl;
        }
        reportFile.close();
    } else
    {
        std::cerr << "Unable to open file: " << reportName << std::endl;
    }
}