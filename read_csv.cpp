#include "error_messages.h"
#include "read_csv.h"

void CSVReader::checkPointFormat(const string &data){
    try {
        stoi(data);
    } catch (const invalid_argument &e) {
        throw runtime_error(ErrorMessages::kPointFormatError);
    }
}

void CSVReader::checkTimeFormat(const string &data){
    istringstream ss(data);
    tm tm = {};
    ss >> get_time(&tm, "%Y-%m-%dT%H:%M:%SZ");
    if(ss.fail()){
        throw runtime_error(ErrorMessages::kTimeFormatError);
    }
}

void CSVReader::readCSV(const string &filename, vector<vector<string>> &rows){
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error(ErrorMessages::kFileOpenError);
    }

    string line;
    // For skiping the header ("payer","points","timestamp")
    bool skip_header_flg = true;
    while (getline(file, line)) {
        if (line.empty()) {
            // Skips empty lines
            continue;
        }
        if(skip_header_flg){
            skip_header_flg = false;
            continue;
        }

        vector<string> row;
        stringstream ss(line);
        string data;

        int col_num = 0;
        while (getline(ss, data, ',')) {
            switch (col_num) {
                case 0:
                    // Does nothing
                    break;
                case 1:
                    checkPointFormat(data);
                    break;
                case 2:
                    // Eliminates the double quotes to check the time format
                    data.erase(remove(data.begin(), data.end(), '\"'), data.end());
                    checkTimeFormat(data);
                    break;
                default:
                    // If the number of columns is more than 3,
                    // skips the remaining columns.
                    break;
            }
            row.push_back(data);
            col_num++;
        }
        rows.push_back(row);
    }
    file.close();
}

