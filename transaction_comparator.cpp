#include "transaction_comparator.h"

// Sorts the rows based on third column
bool TransactionComparator::operator()(const vector<string>& row1, const vector<string>& row2) {
    return row1[2] < row2[2];
}

