
#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <string>
#include <map>

class BitcoinExchange
{
    private:
        std::map<std::string, float> _data;
        std::string _firstDate;
        std::string _lastDate;
        bool isValidData(const std::string &date, float value, std::string kind);
        bool isNumeric(const std::string &str);
        bool isValidDate(const std::string &year, const std::string &month, const std::string &day);
        bool isDateBoundaryFormatNormal(const std::string& date);
        float stringToFloat(const std::string& str);
        void setDateRange(const std::string &filename);
        bool isDateInRange(const std::string &inputDate);
        bool isLeapYear(const int &year);
        BitcoinExchange();
    public:
        BitcoinExchange(const std::string &filename);
        BitcoinExchange(const BitcoinExchange &other);
        BitcoinExchange &operator=(const BitcoinExchange &other);
        ~BitcoinExchange();
        std::map<std::string, float> getData() const;
        void parseData(const std::string &filename);
        void handleInput(const std::string &filename);
};

#endif
