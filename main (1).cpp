#include <iostream>
#include <vector>
#include <time.h>
#include <cstdlib>
#include <unistd.h>
#include <chrono>

using namespace std;

template<typename T>
struct matrix{
	vector<vector<T>>data;
	int filas, columnas;
	matrix(int f, int c):filas(f),columnas(c){
		T v = (T)rand() / RAND_MAX;
		v = (T)1 + v *((T)10 - (T)1);
		data = vector<vector<T>>(f, vector<T>(c,v));
	}
	void clear(){
		for(int i = 0; i < filas; i++)
			for(int j = 0; j < columnas; j++)
				data[i][j]=(T)0;
	}
	void print()
	{
		for(auto i : data)
			{
				for(auto j : i)
					{
						cout << j << " ";
					}
				cout << endl;
			}
		cout<<endl;
	}
};

int main() {
	srand(time(0));
	int B = 75;
	int N = 300;
	matrix<double> m1(N,N);
	//m1.print();
	matrix<double> m2(N,N);
	//m2.print();
	matrix<double> res(N,N);
	res.clear();
	
	/*Multiplicación tradicional*/
	auto start = chrono::steady_clock::now();

	for(int i = 0; i < m1.filas; i++){
		for(int j = 0; j < m2.columnas; j++){
			for(int k = 0; k < m1.columnas; k++){
					res.data[i][j] += m1.data[i][k] * m2.data[k][j];
			}
		}
	}
	
    auto end = chrono::steady_clock::now();

    cout << " (tradicional: ): " << chrono::duration_cast
            <chrono::milliseconds>(end - start).count()
         << " ms" << endl;
	//res.print();
	res.clear();

	/*Multiplicación por bloques*/

	start = chrono::steady_clock::now();
    for (int i = 0; i < N; i += B) {
        for (int j = 0; j < N; j += B) {
            for (int k = 0; k < N; k += B) {
                // BLOCK MULTIPLICATION
             for (int ii = i; ii < i + B; ii++) {
                    for (int jj = j; jj < j + B; jj++) {
                        for (int kk = k; kk < k + B; kk++) {
                            res.data[ii][jj] += m1.data[ii][kk] * m2.data[kk][jj];
                        }
                    }
                }
            }
        }
    }
    end = chrono::steady_clock::now();

    cout << " (bloques: ): " << chrono::duration_cast
            <chrono::milliseconds>(end - start).count()
         << " ms" << endl;

	//res.print();

	
}