
#include "BitcoinExchange.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const std::string &filename)
    : _firstDate(""), _lastDate("") {
    parseData(filename);
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other)
    : _data(other._data), _firstDate(other._firstDate), _lastDate(other._lastDate) {}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other) {
    if (this != &other) {
        _firstDate = other._firstDate;
        _lastDate = other._lastDate;
        _data = other._data;
    }
    return *this;
}

BitcoinExchange::~BitcoinExchange() {}

void BitcoinExchange::parseData(const std::string &filename) {
    setDateRange(filename);
    std::ifstream file(filename.c_str());
    if (!file.is_open())
        throw std::runtime_error("Error: could not open file.");
    std::string line;
    std::getline(file, line);
    if (line != "date,exchange_rate")
        throw std::runtime_error("Error: wrong file format");
    while (std::getline(file, line)) {
        std::string date = line.substr(0, line.find(','));
        float value = stringToFloat(line.substr(line.find(',') + 1));
        if (!isValidData(date, value, "data"))
            throw std::runtime_error("Error: invalid data.csv");
        _data[date] = value;
    }
    file.close();
}

bool BitcoinExchange::isNumeric(const std::string& str) {
    for (std::string::const_iterator it = str.begin(); it != str.end(); ++it) {
        if (!isdigit(*it)) {
            return false;
        }
    }
    return !str.empty();
}

bool BitcoinExchange::isValidDate(const std::string& year, const std::string& month, const std::string& day) {
    const int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    int y, m, d;
    std::stringstream yearStream(year), monthStream(month), dayStream(day);
    yearStream >> y;
    monthStream >> m;
    dayStream >> d;
    if (monthStream.fail() || dayStream.fail()) {
        return false;
    }
    if (m == 2 && isLeapYear(y)) {
        return d <= 29;
    }
    if (m < 1 || m > 12) {
        return false;
    }
    if (d < 1 || d > daysInMonth[m - 1]) {
        return false;
    }
    return true;
}

void BitcoinExchange::setDateRange(const std::string& filename) {
    std::ifstream file(filename.c_str());
    if (!file.is_open())
        throw std::runtime_error("Error: could not open file.");
    std::string line;
    std::getline(file, line);
    if (std::getline(file, line)) {
        std::istringstream iss(line);
        std::getline(iss, _firstDate, ',');
    } else {
        file.close();
        throw std::runtime_error("Error: empty file");
    }
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::getline(iss, _lastDate, ',');
    }
    if (!isDateBoundaryFormatNormal(_firstDate)) {
        throw std::runtime_error("Error: First date Boundary is not correct.");
    }
    if (!isDateBoundaryFormatNormal(_lastDate)) {
        throw std::runtime_error("Error: Last date Boundary is not correct.");
    }
    file.close();
}

bool BitcoinExchange::isDateBoundaryFormatNormal(const std::string& date) {
    if (date.size() != 10) {
        std::cerr << "Error: invalid date length. date: " << date << std::endl; 
        return false;
    }
    std::string year = date.substr(0, 4);
    std::string month = date.substr(5, 2);
    std::string day = date.substr(8, 2);
    if (year.empty() || month.empty() || day.empty()) {
        std::cerr << "Error: invalid date format. date: " << date << std::endl;
        return false;
    }
    if (year.size() != 4 || month.size() != 2 || day.size() != 2) {
        std::cerr << "Error: invalid date format. date: " << date << std::endl;
        return false;
    }
    if (date[4] != '-' || date[7] != '-') {
        std::cerr << "Error: invalid date format. date: " << date << std::endl;
        return false;
    }
    if (!isNumeric(year) || !isNumeric(month) || !isNumeric(day)) {
        std::cerr << "Error: invalid date format. date: " << date << std::endl;
        return false;
    }
    if (!isValidDate(year, month, day)) {
        std::cerr << "Error: month or day is out of range. date: " << date << std::endl;
        return false;
    }
    return (true);
}

bool BitcoinExchange::isDateInRange(const std::string &inputDate) {
    return (inputDate >= _firstDate && inputDate <= _lastDate);
}

bool BitcoinExchange::isLeapYear(const int &year) {
   return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
}

bool BitcoinExchange::isValidData(const std::string &date, float value, std::string kind) {
    if (date.size() != 10) {
        std::cerr << "Error: invalid date length. date: " << date << std::endl; 
        return false;
    }
    std::string year = date.substr(0, 4);
    std::string month = date.substr(5, 2);
    std::string day = date.substr(8, 2);
    if (year.empty() || month.empty() || day.empty()) {
        std::cerr << "Error: invalid date format. date: " << date << std::endl;
        return false;
    }
    if (year.size() != 4 || month.size() != 2 || day.size() != 2) {
        std::cerr << "Error: invalid date format. date: " << date << std::endl;
        return false;
    }
    if (date[4] != '-' || date[7] != '-') {
        std::cerr << "Error: invalid date format. date: " << date << std::endl;
        return false;
    }
    if (!isNumeric(year) || !isNumeric(month) || !isNumeric(day)) {
        std::cerr << "Error: invalid date format. date: " << date << std::endl;
        return false;
    }
    if (!isValidDate(year, month, day)) {
        std::cerr << "Error: month or day is out of range. date: " << date << std::endl;
        return false;
    }
    if (!isDateInRange(date)) {
        std::cerr << "Error: out of range. date: " << date << std::endl;
        return false;
    }
    if (value < 0) {
        std::cerr << "Error: not a positive number." << std::endl;
        return false;
    }
    if (kind == "input" && (value > 1000)) {
        std::cerr << "Error: too large number." << std::endl;
        return false;
    }
    return true;
}

void BitcoinExchange::handleInput(const std::string &filename) {
    std::ifstream file(filename.c_str());
    if (!file.is_open())
        throw std::runtime_error("Error: could not open file.");
    std::string line;
    std::getline(file, line);
    if (line != "date | value")
        throw std::runtime_error("Error: wrong file format");
    while (std::getline(file, line)) {
        std::string date = line.substr(0, 10);
        float value = stringToFloat(line.substr(line.find('|') + 2));
        if (!isValidData(date, value, "input"))
            continue;
        std::map<std::string, float>::const_iterator it = _data.lower_bound(date);
        if (it->first != date)
            --it;
        std::cout << date << " => " << value << " = " << it->second * value << std::endl;
    }
    file.close();
}

float BitcoinExchange::stringToFloat(const std::string& str) {
    std::istringstream iss(str);
    float result;
    if (!(iss >> result)) {
        throw std::invalid_argument("Error: cannot convert string to float. str: " + str);
    }
    return result;
}
