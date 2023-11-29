#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

int main() {
    ifstream ifs("../tools/data.json");
    string line;

    // Check if the file is open
    if (!ifs.is_open()) {
        cout << "Error opening file" << endl;
        return 1;
    } else {
        cout << "File opened correctly" << endl;
    }

    while (getline(ifs, line)) {
        if (line.find("name") != string::npos) {
            string name = line.substr(line.find(":") + 3, line.size() - line.find(":") - 5);
            getline(ifs, line);
            string description = line.substr(line.find(":") + 3, line.size() - line.find(":") - 5);
            getline(ifs, line);
            string date = line.substr(line.find(":") + 3, line.size() - line.find(":") - 5);
            getline(ifs, line);
            string slide = line.substr(line.find(":") + 3, line.size() - line.find(":") - 5);
            getline(ifs, line);
            string es = line.substr(line.find(":") + 3, line.size() - line.find(":") - 5);
            getline(ifs, line);
            string category = line.substr(line.find(":") + 3, line.size() - line.find(":") - 5);
            string filename = "es" + es + "_" + date + ".cpp";

            // Create the file first


            ofstream ofs("../examples/" + filename);
            // Check if the file is open
            if (!ofs.is_open()) {
                cout << "Error opening file: " << strerror(errno) << endl;
                return 1;
            } else {
                cout << "File opened correctly" << endl;
            }

            ofs << "#include \"../include/magic/magic.hpp\"\n\n";
            ofs << "using namespace std;\n";
            ofs << "using namespace magic;\n\n";
            ofs << "/*\n";
            ofs << " * " << name << "\n";
            ofs << " * " << description << "\n*/\n\n";
            ofs << "int main() {\n";
            ofs << "    return 0;\n";
            ofs << "}\n";
            ofs.close();
        }
    }
    ifs.close();
    return 0;
}