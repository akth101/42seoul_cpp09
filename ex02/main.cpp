#include "PmergeMe.hpp"
#include <iostream>
#include <vector>
#include <ctime>

int main(int argc, char **argv)
{
    if (argc < 2) {
        std::cout << "Error: no arguments provided" << std::endl;
        return 1;
    }
    try {
        VectorFJ vectorFJ;
        clock_t start = clock();
        std::vector<int> numbers = vectorFJ.parseInput(argc, argv);
        std::vector<int> sorted = vectorFJ.sort(numbers);
        clock_t end = clock();
        double duration = (static_cast<double>(end - start) / CLOCKS_PER_SEC) * 1000;
        vectorFJ.printVector(sorted);
        std::cout << "Time to process a range of " << numbers.size() 
              << " elements with std::vector : " 
              << duration << " ms" << std::endl;
    }
    catch (const std::invalid_argument& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    try {
        DequeFJ dequeFJ;
        clock_t start = clock();
        std::deque<int> numbers = dequeFJ.parseInput(argc, argv);
        std::deque<int> sorted = dequeFJ.sort(numbers);
        clock_t end = clock();
        double duration = (static_cast<double>(end - start) / CLOCKS_PER_SEC) * 1000;
        dequeFJ.printDeque(sorted);
        std::cout << "Time to process a range of " << numbers.size() 
                  << " elements with std::deque : " 
                  << duration << " ms" << std::endl;
    }
    catch (const std::invalid_argument& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}