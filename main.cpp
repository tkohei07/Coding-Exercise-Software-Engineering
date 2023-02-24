#include <iostream>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>

#include "calculate_array.h"
#include "error_messages.h"
#include "transaction_comparator.h"
#include "read_csv.h"

using namespace std;

int main(int argc, char* argv[]) {

    // Checks the number of arguments
    if (argc != 3) 
    {
        cerr << ErrorMessages::kInvalidArgumentError << endl;
        return 1;
    }

    // Checks the first argument can be converted to an integer
    int spent_point;
    try {
        spent_point = stoi(argv[1]);
    } catch (const invalid_argument &e) {
        cerr << ErrorMessages::kInvalidArgumentError << endl;
        return 1;
    }

    CSVReader csv_reader;
    const string filename = argv[2];
    vector<vector<string>> transaction_array;
    
    csv_reader.readCSV(filename, transaction_array);

    // Sorts the transaction_array based on transaction timestamp in acending order
    // using TransactionComparator class
    TransactionComparator comparator;
    sort(transaction_array.begin(), transaction_array.end(), comparator);
    
    // Converts transaction_array to vector<pair<string, int>>
    // to make the code easy to understand
    vector<pair<string, int>> ordered_transactions;
    for(vector<string> transaction : transaction_array)
    {
        ordered_transactions.push_back({transaction[0], stoi(transaction[1])});
    }

    ArrayCalculator array_calculator;
    
    // Calculates the negative point of the transactions 
    // by subtracting from the oldest non-zero transaction.
    // (Example) (Left data is older)
    // Before: "DANNON",300, "UNILEVER",200, "DANNON",-200
    // After: "DANNON",100, "UNILEVER",200, "DANNON",0
    array_calculator.calculateNegativePoint(ordered_transactions);
    
    // Calculates the remaining point balance for each payer after deducting the spent points.
    // (Example) spent_point = 5000
    // Before : "DANNON",100, "UNILEVER",200, "DANNON",0, "MILLER COORS",10000, "DANNON",1000
    // After: "DANNON",0, "UNILEVER",0, "DANNON",0, "MILLER COORS",5300, "DANNON",1000
    array_calculator.calculateSpendingPoint(ordered_transactions, spent_point);

    // Calculates the balance for each payer
    // by adding up their remaining points from the ordered_transactions
    unordered_map<string, int> all_payers_balance;
    array_calculator.calculateAllPayersBalance(ordered_transactions, all_payers_balance);

    // Outputs the balance
    for(auto payers_balance : all_payers_balance)
    {
        cout << payers_balance.first << ": " << payers_balance.second << endl;
    }

    return 0;
}

