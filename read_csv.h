#ifndef READ_CSV_H
#define READ_CSV_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class CSVReader {
private:
    void checkPointFormat(const string &data);
    void checkTimeFormat(const string &data);
public:
    void readCSV(const string &filename, vector<vector<string>> &rows);
};

#endif // READ_CSV_H

