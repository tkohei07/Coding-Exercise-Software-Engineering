#ifndef TRANSACTION_COMPARATOR_H
#define TRANSACTION_COMPARATOR_H

#include <vector>
#include <string>

using namespace std;

// For sorting the rows based on transaction timestamp
class TransactionComparator {
public:
    bool operator()(const vector<string> &row1, const vector<string> &row2);
};

#endif // TRANSACTION_COMPARATOR_H

