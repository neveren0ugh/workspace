#include <iostream>
#include <fstream>
#include <string>
#include <vector>


using namespace std;

bool is_mt(ifstream& pFile)
{
	return pFile.peek() == ifstream::traits_type::eof();
}

int main(int argc, char* argv[])
{
	
	cout << "this program encrypts file 'input.txt' using caesar method" << endl;
	int enc_lvl;
	while (cout << "enter the encryption level\n" && !(cin >> enc_lvl)) {
		cin.clear();
		cin.ignore();
		cout << "invalid input, please enter integer value.\n";
	}

    ifstream f("input.txt");
	string line = *argv;
	vector <string> new_file;
    if (!f) {
        cout << "error opening file!" << endl;
        system("pause");
        return 1;
    }
	if (is_mt(f)) {
		if (argc == 0) {
			cout << "No input" << endl;
			return 0;
		}
		for (int i = 0; i < argc; i++) {
			if (isalpha((int)argv[i])) {
				if (islower((int)argv[i]))
					line[i] = ((int)argv[i] + enc_lvl - 97) % 26 + 97; // encryption
				else
					line[i] = ((int)argv[i] + enc_lvl - 65) % 26 + 65; // encryption
			}
			cout << line[i];
		}
	}
	else {
		while (f) {
			string tmp;
			getline(f, tmp);
			for (int i = 0; i < tmp.length(); i++) {
				if (isalpha(tmp[i])) {
					if (islower(tmp[i]))
						tmp[i] = (tmp[i] + enc_lvl - 97) % 26 + 97; // encryption
					else
						tmp[i] = (tmp[i] + enc_lvl - 65) % 26 + 65; // encryption
				}

			}
			new_file.push_back(tmp);
		}
		f.close();

		ofstream ff;
		ff.open("caesars.txt");
		if (!ff) {
			cout << "error opening file!" << endl;
			system("pause");
			return 1;
		}

		for (auto element : new_file) {
			ff << element << endl;
		}
		ff.close();
	}
	/*char hih = 65;
	cout << hih << endl;*/
	return 0;
}
