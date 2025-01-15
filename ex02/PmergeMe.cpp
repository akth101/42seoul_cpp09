#include "PmergeMe.hpp"

/* VectorFJ */

VectorFJ::VectorFJ() {}

VectorFJ::VectorFJ(const VectorFJ& other) {
    (void)other;
}

VectorFJ& VectorFJ::operator=(const VectorFJ& other) {
    (void)other;
    return *this;
}

VectorFJ::~VectorFJ() {}

std::vector<int> VectorFJ::parseInput(int argc, char **argv) {
   std::vector<int> numbers;
   for (int i = 1; i < argc; ++i) {
       std::istringstream converter(argv[i]);
       int number;
       if (!(converter >> number) || !converter.eof())
           throw std::invalid_argument("Error: invalid number format");
       if (number < 0)
           throw std::invalid_argument("Error: negative number provided");
       numbers.push_back(number);
   }
    if (numbers.size() <= 1)
        throw std::invalid_argument("Error: not enough numbers");
   return numbers;
}

void VectorFJ::separateIntoGroups(const std::vector<int>& arr,
                                 std::vector<int>& winners,
                                 std::vector<int>& losers,
                                 int& odd) {
    for (size_t i = 0; i < arr.size() - 1; i += 2) {
        if (arr[i] > arr[i + 1]) {
            winners.push_back(arr[i]);
            losers.push_back(arr[i + 1]);
        } else {
            winners.push_back(arr[i + 1]);
            losers.push_back(arr[i]);
        }
    }
    if (arr.size() % 2 != 0) {
        odd = arr.back();
    }
}

std::vector<int> VectorFJ::sortLosers(std::vector<int>& previous_winners, 
                                     std::vector<int>& winners, 
                                     std::vector<int>& losers) {
    std::vector<std::pair<int, int> > original_pairs;
    for (size_t i = 0; i < previous_winners.size(); i++) {
        original_pairs.push_back(std::make_pair(previous_winners[i], losers[i]));
    }

    std::vector<int> new_losers;
    for (size_t i = 0; i < winners.size(); i++) {
        for (size_t j = 0; j < original_pairs.size(); j++) {
            if (original_pairs[j].first == winners[i]) {
                new_losers.push_back(original_pairs[j].second);
                original_pairs.erase(original_pairs.begin() + j);

                break;
            }
        }
    }
    return new_losers;
}

std::vector<int> VectorFJ::sort(std::vector<int>& arr) {
    if (arr.size() <= 1)
        return arr;
    std::vector<int> winners;
    std::vector<int> losers;
    int odd = -1;
    separateIntoGroups(arr, winners, losers, odd);
    std::vector<int> previous_winners = winners;
    winners = sort(winners);
    std::vector<int> new_losers = sortLosers(previous_winners, winners, losers);
    insertLosers(winners, new_losers, odd);

    return winners;
}

std::vector<int> VectorFJ::generateJacobsthalNumbers(int n) {
    std::vector<int> jacobsthal;
    jacobsthal.push_back(1);
    jacobsthal.push_back(3);

    int next = 0;
    while ((next = jacobsthal.back() + 2 * jacobsthal[jacobsthal.size() - 2]) <= n) {
        jacobsthal.push_back(next);
    }
    
    return jacobsthal;
}

int VectorFJ::binarySearch(const std::vector<int>& sorted, int range, int value) {
    if (range == -1) {
        return std::lower_bound(sorted.begin(), sorted.end(), value) - sorted.begin();
    }
    std::vector<int>::const_iterator it = std::lower_bound(sorted.begin(), sorted.begin() + range, value);
    if ((it == sorted.begin() + range) && (value != *(sorted.begin() + range) && value > *(sorted.begin() + range))) {
        return it - sorted.begin() + 1;
    } else {
        return it - sorted.begin();
    }
    return (-1);
}

int VectorFJ::findBinarySearchRange(const std::vector<int>& initial_winners, const std::vector<int>& winners, const std::vector<int>& losers, int jacob) {
    int range = 0;

    int currentLoser = losers[jacob - 1];
    (void)currentLoser;
    int pairWinner = initial_winners[jacob - 1];

    for (size_t i = 0; i < winners.size(); i++)
    {
        if (winners[i] < pairWinner)
            range++;
        else
            return range;
    }
    return (0);
}

void VectorFJ::insertLosers(std::vector<int>& winners, const std::vector<int>& losers, int& odd) {
    if (losers.empty())
        return;
    std::vector<int> initial_winners = winners;
    winners.insert(winners.begin(), losers[0]);
    
    std::vector<int> jacobsthal = generateJacobsthalNumbers(losers.size());
    size_t currentJacobsthal, previousJacobsthal, inserted = 1;
    for (size_t i = 1; i < jacobsthal.size(); ++i) {
        currentJacobsthal = jacobsthal[i];
        previousJacobsthal = jacobsthal[i - 1];
        for (size_t jacob = currentJacobsthal; jacob > previousJacobsthal; --jacob) {
            if (jacob - 1 < losers.size() && jacob > 1) {
                int currentLoser = losers[jacob - 1];
                int range = (jacob - 1) - 1 + inserted;
                int insertPosition = binarySearch(winners, range, currentLoser);
                winners.insert(winners.begin() + insertPosition, currentLoser);
                inserted++;
            }
        }
    }
    for (size_t jacob = losers.size(); jacob > static_cast<size_t>(jacobsthal.back()); --jacob) {
        if (jacob - 1 < losers.size() && jacob > 1) {
            int currentLoser = losers[jacob - 1];
            int range = (jacob - 1) - 1 + inserted;
            int insertPosition = binarySearch(winners, range, currentLoser);
            winners.insert(winners.begin() + insertPosition, currentLoser);
            inserted++;
        }
    }
    if (odd != -1) {
        int insertPosition = binarySearch(winners, -1, odd);
        winners.insert(winners.begin() + insertPosition, odd);
    }
}

void VectorFJ::printVector(const std::vector<int>& vec) {
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;
}


/* DequeFJ */

DequeFJ::DequeFJ() {}

DequeFJ::DequeFJ(const DequeFJ& other) {
    (void)other;
}

DequeFJ& DequeFJ::operator=(const DequeFJ& other) {
    (void)other;
    return *this;
}

DequeFJ::~DequeFJ() {}

std::deque<int> DequeFJ::parseInput(int argc, char **argv) {
   std::deque<int> numbers;
   for (int i = 1; i < argc; ++i) {
       std::istringstream converter(argv[i]);
       int number;
       if (!(converter >> number) || !converter.eof())
           throw std::invalid_argument("Error: invalid number format");
       if (number < 0)
           throw std::invalid_argument("Error: negative number provided");
       numbers.push_back(number);
   }
    if (numbers.size() <= 1)
        throw std::invalid_argument("Error: not enough numbers");
   return numbers;
}

void DequeFJ::separateIntoGroups(const std::deque<int>& arr,
                                 std::deque<int>& winners,
                                 std::deque<int>& losers,
                                 int& odd) {
    for (size_t i = 0; i < arr.size() - 1; i += 2) {
        if (arr[i] > arr[i + 1]) {
            winners.push_back(arr[i]);
            losers.push_back(arr[i + 1]);
        } else {
            winners.push_back(arr[i + 1]);
            losers.push_back(arr[i]);
        }
    }
    if (arr.size() % 2 != 0) {
        odd = arr.back();
    }
}

std::deque<int> DequeFJ::sortLosers(std::deque<int>& previous_winners,
                                  std::deque<int>& winners,
                                  std::deque<int>& losers) {
   std::deque<std::pair<int, int> > original_pairs;
   for (size_t i = 0; i < previous_winners.size(); i++) {
       original_pairs.push_back(std::make_pair(previous_winners[i], losers[i]));
   }

   std::deque<int> new_losers;
   for (size_t i = 0; i < winners.size(); i++) {
       for (size_t j = 0; j < original_pairs.size(); j++) {
           if (original_pairs[j].first == winners[i]) {
               new_losers.push_back(original_pairs[j].second);
               original_pairs.erase(original_pairs.begin() + j);
               break;
           }
       }
   }
   return new_losers;
}


std::deque<int> DequeFJ::sort(std::deque<int>& arr) {
    if (arr.size() <= 1)
        return arr;
    std::deque<int> winners;
    std::deque<int> losers;
    int odd = -1;
    separateIntoGroups(arr, winners, losers, odd);
    std::deque<int> previous_winners = winners;
    winners = sort(winners);
    std::deque<int> new_losers = sortLosers(previous_winners, winners, losers);
    insertLosers(winners, new_losers, odd);

    return winners;
}

std::deque<int> DequeFJ::generateJacobsthalNumbers(int n) {
    std::deque<int> jacobsthal;
    jacobsthal.push_back(1);
    jacobsthal.push_back(3);

    int next = 0;
    while ((next = jacobsthal.back() + 2 * jacobsthal[jacobsthal.size() - 2]) <= n) {
        jacobsthal.push_back(next);
    }
    
    return jacobsthal;
}

int DequeFJ::binarySearch(const std::deque<int>& sorted, int range, int value) {
    if (range == -1) {
        return std::lower_bound(sorted.begin(), sorted.end(), value) - sorted.begin();
    }
    std::deque<int>::const_iterator it = std::lower_bound(sorted.begin(), sorted.begin() + range, value);
    if ((it == sorted.begin() + range) && (value != *(sorted.begin() + range) && value > *(sorted.begin() + range))) {
        return it - sorted.begin() + 1;
    } else {
        return it - sorted.begin();
    }
    return (-1);
}

int DequeFJ::findBinarySearchRange(const std::deque<int>& initial_winners, const std::deque<int>& winners, const std::deque<int>& losers, int jacob) {
    int range = 0;

    int currentLoser = losers[jacob - 1];
    (void)currentLoser;
    int pairWinner = initial_winners[jacob - 1];

    for (size_t i = 0; i < winners.size(); i++)
    {
        if (winners[i] < pairWinner)
            range++;
        else
            return range;
    }
    return (0);
}

void DequeFJ::insertLosers(std::deque<int>& winners, const std::deque<int>& losers, int& odd) {
    if (losers.empty())
        return;
    std::deque<int> initial_winners = winners;
    winners.insert(winners.begin(), losers[0]);
    
    std::deque<int> jacobsthal = generateJacobsthalNumbers(losers.size());
    size_t currentJacobsthal, previousJacobsthal, inserted = 1;
    for (size_t i = 1; i < jacobsthal.size(); ++i) {
        currentJacobsthal = jacobsthal[i];
        previousJacobsthal = jacobsthal[i - 1];
        for (size_t jacob = currentJacobsthal; jacob > previousJacobsthal; --jacob) {
            if (jacob - 1 < losers.size() && jacob > 1) {
                int currentLoser = losers[jacob - 1];
                int range = (jacob - 1) - 1 + inserted;
                int insertPosition = binarySearch(winners, range, currentLoser);
                winners.insert(winners.begin() + insertPosition, currentLoser);
                inserted++;
            }
        }
    }
    for (size_t jacob = losers.size(); jacob > static_cast<size_t>(jacobsthal.back()); --jacob) {
        if (jacob - 1 < losers.size() && jacob > 1) {
            int currentLoser = losers[jacob - 1];
            int range = (jacob - 1) - 1 + inserted;
            int insertPosition = binarySearch(winners, range, currentLoser);
            winners.insert(winners.begin() + insertPosition, currentLoser);
            inserted++;
        }
    }
    if (odd != -1) {
        int insertPosition = binarySearch(winners, -1, odd);
        winners.insert(winners.begin() + insertPosition, odd);
    }
}

void DequeFJ::printDeque(const std::deque<int>& deq) {
    for (size_t i = 0; i < deq.size(); ++i) {
        std::cout << deq[i] << " ";
    }
    std::cout << std::endl;
}

