#include <iostream >
#include <fstream>
#include <vector>

using namespace std;
using std::vector;
ifstream fin("date.in");
ofstream fout("date.out");

//gasesc nodul minim care nu se afla in secventa
int gaseste_minim(vector<int>prufer) {
	int n = prufer.size();
	vector<int> aux(n + 1, 0);
	for (int i = 0; i < prufer.size(); i++) {
		aux[prufer[i]]++;
	}

	int i = 0;
	while (aux[i] != 0) {
		i++;
	}
	return i;
}

int main(int argc, char* argv[]) {
	int n, x;
	fin >> n;
	vector<int>prufer;
	for (int i = 0; i < n; i++) {
		fin >> x;
		prufer.push_back(x);
	}
	vector<int>parinti(n + 1, -1);

	//decodarea Prufer
	for (int j = 0; j < n; j++) {
		int minim = gaseste_minim(prufer);
		parinti[minim] = prufer[0];
		prufer.erase(prufer.begin());
		prufer.push_back(minim);
	}

	fout << parinti.size() << endl;
	for (int i = 0; i < parinti.size(); i++) {
		fout << parinti[i] << " ";
	}


	fin.close();
	fout.close();
	return 0;
}
