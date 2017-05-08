#include <fstream>

using namespace std;

int numStringMatching(string filename, string toSearch) {
	int k = 0;
	vector<int> pi;
	pi.resize(toSearch.length());
	pi.at(0) = 0;
	for (int q = 1; q < toSearch.length(); q++) {
		while (k > 0 && toSearch.at(k + 1) != toSearch.at(q))
			k = pi[k];
		if (toSearch.at(k + 1) == toSearch.at(q))
			k++;
		pi.at(q) = k;
	}
	int res = 0;
	ifstream myfile;
	myfile.open(filename);
	string line;
	while (getline(myfile, line)) {
		int q = 0;
		for (int i = 0; i < line.length(); i++) {
			while (q > 0 && toSearch.at(q) != line.at(i))
				q = pi[q - 1];
			if (toSearch.at(q) == line.at(i))
				q++;
			if (q == (toSearch.length())) {
				res++;
				q = pi.at(q - 1);
			}
		}
	}
	myfile.close();
	return res;
}

float numApproximateStringMatching(string filename, string toSearch) {
	int res = 0;
	ifstream myfile;
	myfile.open(filename);
	string line;
	int nPalavras = 0;
	while (myfile >> line) {
		nPalavras++;
		vector<vector<int>> matrix;
		matrix.resize(line.size() + 1);
		for (int i = 0; i < line.size() + 1; i++) {
			matrix.at(i).resize(toSearch.size() + 1);
		}
		for (int i = 0; i < line.size() + 1; i++) {
			for (int j = 0; j < toSearch.size() + 1; j++) {
				if (i == 0)
					matrix.at(i).at(j) = j;
				else {
					if (j == 0)
						matrix.at(i).at(j) = i;
					else {
						if (line.at(i - 1) == toSearch.at(j - 1))
							matrix.at(i).at(j) = matrix.at(i - 1).at(j - 1);
						else {
							int min = 0;
							if (matrix.at(i - 1).at(j - 1)
									< matrix.at(i - 1).at(j))
								min = matrix.at(i - 1).at(j - 1);
							else
								min = matrix.at(i - 1).at(j);
							if (matrix.at(i).at(j - 1) < min)
								min = matrix.at(i).at(j - 1);
							matrix.at(i).at(j) = min + 1;
						}
					}
				}
			}
		}
		res += matrix.at(line.size()).at(toSearch.size());

	}
	myfile.close();
	return (float) res / nPalavras;

}
