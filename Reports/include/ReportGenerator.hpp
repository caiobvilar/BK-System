#ifndef REPORTGENERATOR_HPP
#define REPORTGENERATOR_HPP

#include <string>
#include <vector>

class ReportGenerator
{
  public:
    ReportGenerator();
    ~ReportGenerator();

    void generatePDFReport(const std::string& filename,
                           const std::vector<std::string>& data);
    void generateJSONReport(const std::string& filename,
                            const std::vector<std::string>& data);

  private:
    void writeToFile(const std::string& filename, const std::string& content);
    std::string convertToJSON(const std::vector<std::string>& data);
    std::string convertToPDF(const std::vector<std::string>& data);
};

#endif // REPORTGENERATOR_HPP