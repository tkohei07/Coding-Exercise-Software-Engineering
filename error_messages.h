#ifndef ERROR_MESSAGES_H
#define ERROR_MESSAGES_H

#include <string>

using namespace std;

namespace ErrorMessages {
const string kFileOpenError = "Error: Could not open file.";

const string kInvalidArgumentError = "Error: Invalid argument.";

const string kTimeFormatError = "Error: Date data in the file is not correct.";
const string kPointFormatError = "Error: Point data in the file is not an integer.";
const string kInvalidTransactionError = "Error: The data in the file is not correct.";
const string kInsufficientPointsError = "Error: The amount of points in the file is insufficient.";
}

#endif

