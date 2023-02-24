#ifndef CALCULATE_CSV_H
#define CALCULATE_CSV_H

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

class ArrayCalculator {
    // For keeping track of the oldest non-zero transaction
    // Set unsigned int to avoid warnings when comparing with
    // ordered_transactions.size() in the calculateNegativePoint function
    unsigned int non_zero_idx;
public:
    ArrayCalculator(){
        non_zero_idx = 0;
    }

    void calculateNegativePoint(
        vector<pair<string, int>> &ordered_transactions
    );
    void calculateSpendingPoint(
        vector<pair<string, int>> &ordered_transactions, 
        int spent_point
    );
    void calculateAllPayersBalance(
        vector<pair<string, int>> &ordered_transactions, 
        unordered_map<string, int> &all_payers_balance
    );
};

#endif // CALCULATE_CSV_H

