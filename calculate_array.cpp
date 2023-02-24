#include "calculate_array.h"
#include "error_messages.h"

// Calculates the negative point(cur_point) of the transactions 
// by subtracting from the oldest non-zero point(non_zero_point).
// Even if the point is zero, it will not be removed
// non_zero_idx keeps track of the oldest non-zero transaction
void ArrayCalculator::calculateNegativePoint(
    vector<pair<string, int>> &ordered_transactions)
{
    for(unsigned int cur_idx = 0; cur_idx < ordered_transactions.size(); cur_idx++){
        int &cur_point = ordered_transactions[cur_idx].second;
        if(cur_point >= 0)
        {
            continue;
        }
        // Continues to subtract from the oldest non-zero point(non_zero_point) 
        // until the negative point is zero(cur_point)
        while(cur_point != 0){
            int &non_zero_point = ordered_transactions[non_zero_idx].second;
            if(non_zero_point >= abs(cur_point))
            {
                non_zero_point += cur_point;
                cur_point = 0;
            }
            // If the absolute value of negative point (current points) 
            // is greater than the oldest point,
            // subtracts the oldest point from negative point 
            // and moves on to the next transaction
            // cur_point is negative.
            else
            {
                cur_point += non_zero_point;
                non_zero_point = 0;
                non_zero_idx++;
                
                // If the negative value is more than the sum of previous values, 
                // it throws an error
                // (Example) "DANNON",300, "UNILEVER",200, "DANNON",-600
                if(cur_idx == non_zero_idx){
                    throw runtime_error(ErrorMessages::kInvalidTransactionError);
                }
            }
        }
    }
}

// Calculates the remaining point balance for each payer 
// after deducting the spent points
// non_zero_idx keeps track of the oldest non-zero transaction
void ArrayCalculator::calculateSpendingPoint(
    vector<pair<string, int>> &ordered_transactions,
    int spent_point)
{
    // (Note)
    // I considered combining this method with calculateNegativePoint() to handle
    // subtracting points from the oldest non-zero transaction in a single method,
    // but this would make the code less readable by increasing complexity.
    while(spent_point != 0){
        int &non_zero_point = ordered_transactions[non_zero_idx].second;
        if(non_zero_point >= spent_point)
        {
            non_zero_point -= spent_point;
            spent_point = 0;
        }
        // If the spent point is greater than the oldest value,
        // subtracts the oldest value from the spent point 
        // and moves on to the next transaction
        else
        {
            spent_point -= non_zero_point;
            non_zero_point = 0;
            non_zero_idx++;
        }
        // If the spent_point is more than the sum of points, 
        // it throws an error
        if(ordered_transactions.size() == non_zero_idx)
        {
            throw runtime_error(ErrorMessages::kInsufficientPointsError);
        }
    }
}

// Calculates the balance for each payer 
// by adding up their remaining points from the ordered transactions
void ArrayCalculator::calculateAllPayersBalance(
    vector<pair<string, int>> &ordered_transactions, 
    unordered_map<string, int> &all_payers_balance)
{
    for(pair<string, int> transaction : ordered_transactions)
    {
        all_payers_balance[transaction.first] += transaction.second;
    }
}

