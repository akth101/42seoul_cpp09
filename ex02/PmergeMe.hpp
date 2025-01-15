
#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <iostream>
#include <algorithm>
#include <deque>
#include <sstream>

class VectorFJ {
    private:
        void separateIntoGroups(const std::vector<int>& arr, 
                            std::vector<int>& winners, 
                            std::vector<int>& losers,
                            int& odd
                            );
        int binarySearch(const std::vector<int>& sorted, int range, int value);
        int findBinarySearchRange(const std::vector<int>& initial_winners, const std::vector<int>& winners, const std::vector<int>& losers, int jacob);
        std::vector<int> sortLosers(std::vector<int>& previous_winners, std::vector<int>& winners, std::vector<int>& losers);
        void insertLosers(std::vector<int>& winners, const std::vector<int>& losers, int& odd);
        std::vector<int> generateJacobsthalNumbers(int n);

    public:
        VectorFJ();
        VectorFJ(const VectorFJ& other);
        VectorFJ& operator=(const VectorFJ& other);
        ~VectorFJ();
        std::vector<int> sort(std::vector<int>& arr);
        std::vector<int> parseInput(int argc, char **argv);
        void printVector(const std::vector<int>& vec);
};

class DequeFJ {
    private:
        void separateIntoGroups(const std::deque<int>& arr, 
                            std::deque<int>& winners, 
                            std::deque<int>& losers,
                            int& odd
                            );
        int binarySearch(const std::deque<int>& sorted, int range, int value);
        int findBinarySearchRange(const std::deque<int>& initial_winners, const std::deque<int>& winners, const std::deque<int>& losers, int jacob);
        std::deque<int> sortLosers(std::deque<int>& previous_winners, std::deque<int>& winners, std::deque<int>& losers);
        void insertLosers(std::deque<int>& winners, const std::deque<int>& losers, int& odd);
        std::deque<int> generateJacobsthalNumbers(int n);

    public:
        DequeFJ();
        DequeFJ(const DequeFJ& other);
        DequeFJ& operator=(const DequeFJ& other);
        ~DequeFJ();
        std::deque<int> sort(std::deque<int>& arr);
        std::deque<int> parseInput(int argc, char **argv);
        void printDeque(const std::deque<int>& deq);
    };

#endif
