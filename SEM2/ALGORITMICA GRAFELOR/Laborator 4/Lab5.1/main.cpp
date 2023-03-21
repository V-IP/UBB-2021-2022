#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
using std::vector;

ifstream fin("date.in");
ofstream fout("date.out");

int main() {

	int n, x;
	vector<int> parinti;
	vector<int>prufer;
	fin >> n;
	//vectorul de parinti
	for (int i = 0; i < n; i++) {
		fin >> x;
		parinti.push_back(x);
	}
	vector<int>nrAparitii(n, 0);
	//initializez un vector in care am nr de aparitii al fiecarui nod in vectorul parinti
	for (int i = 0; i < n; i++) {
		if (parinti[i] != -1) {
			nrAparitii[parinti[i]]++;
		}
	}
	//Codare Prufer
	for (int j = 0; j < n - 1; j++) {
		int i = 0; //gasim prima frunza
		while (nrAparitii[i] != 0 && i < n) {
			i++;
		}
		prufer.push_back(parinti[i]);
		nrAparitii[i] = -1; //marcat
		nrAparitii[parinti[i]]--;
		//nr de aparitii ale parintilor scade pe masura ce eliminam nodurile frunza
	}
	fout << prufer.size() << endl;
	for (int i = 0; i < prufer.size(); i++) {
		fout << prufer[i] << " ";
	}
	fin.close();
	fout.close();
	return 0;
}
