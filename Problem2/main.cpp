#include <stdio.h>
#include <iostream>
#include <assert.h>
#include <string>
#include <vector>
using namespace std;

int n,m;


template <class T>
class Matrix {
private:
	int numRows;
	int numColumns;
	vector<vector<T> > S;
public:
	Matrix<T>();
	Matrix<T>( const Matrix<T>& );
	Matrix<T>(int rows , int columns);
	~Matrix<T>() {
		FreeMemory();
	}
	vector<T>& operator[](int i)  {  
		return S[i];
	}
	const vector<T>& operator[](int i) const {
		return S[i];
	}


	Matrix<T>& operator = (const Matrix<T>& S2){
		FreeMemory();	
		numRows = S2.numRows;
		numColumns = S2.numColumns;
		S.resize(numRows);      
		for (int i = 0; i < numRows; i++)
			S[i].resize(numColumns);
		for( int i = 0;i < numRows;i++ ){
			for(int j = 0; j < numColumns; j++){
				S[i][j] = S2.S[i][j];
			}
		}
		return *this;
	}
	void FreeMemory(){
		for(int i = 0 ; i < numRows;i++){
			S[i].clear();
		}
		S.clear();
	}

	void Print()const {
		for (int i = 0; i < numRows; i++){
			for(int j = 0 ; j < numColumns; j++){
				printf("%.1d  ",S[i][j]);
			}
			printf("\n");
		}
	}
	Matrix<T> operator + (const Matrix<T>& A)const {  
		int columns = numColumns;
		int rows = numRows;
		assert(numRows == A.numRows);
		assert(numColumns == A.numColumns);
		Matrix<T> Summ(rows, columns);  
		for (int i = 0; i < rows; i++){
			for(int j = 0; j < columns; j++){
				Summ[i][j] = S[i][j] + A[i][j];
			}
		}
		return Summ;                  
	}

	Matrix<T> operator - (const Matrix<T>& A) const{ 
		assert(numRows == A.numRows);
		assert(numColumns == A.numColumns);
		int columns = numColumns;
		int rows = numRows;
		Matrix<T> Diff(rows,columns);  
		for (int i = 0; i < rows; i++){
			for(int j = 0; j < columns;j++){
				Diff[i][j] = S[i][j] - A[i][j];
			}
		}
		return Diff;       

	}

	Matrix<T> operator * (const Matrix<T>& A)const{ 
		int rows = numRows;
		assert(numColumns == A.numRows);
		int columns = A.numColumns;
		int secondColumns = numColumns;
		Matrix<T> Mull(rows,columns);
		for( int i = 0; i < rows; i++){
			for(int j = 0; j < columns; j++){
				for(int k = 0; k < secondColumns; k++){
					Mull[i][j] += S[i][k] * A[k][j];
				}
			}
		}
		return Mull;
	}

};

template <class T>
Matrix<T>::Matrix()
{		
	numRows = 0;
	numColumns = 0;
	S.resize(0);
}
template <class T>
Matrix<T>::Matrix( const Matrix<T>& copyMatrix){
	
	S.resize(copyMatrix.numRows);      
	for (int i = 0; i < copyMatrix.numRows; i++)
		S[i].resize(copyMatrix.numColumns);
	numColumns = copyMatrix.numColumns;
	numRows = copyMatrix.numRows;
	for(int i = 0;i < copyMatrix.numRows;i++){
		for(int j = 0; j < copyMatrix.numColumns; j++){
			S[i][j] = copyMatrix[i][j];
		}
	}
}
template <class T>
Matrix<T>::Matrix( int rows , int columns )
{	
	numRows = rows;
	numColumns = columns;
	S.resize(rows);      
	for (int i = 0; i < rows; i++)
		S[i].resize(columns);
	for( int i = 0;i < numRows;i++ ){
		for(int j = 0; j < numColumns; j++){
			S[i][j] = 0;
		}
	}
}

typedef Matrix<int> IMatrix;
IMatrix D;

template <class T>
class MultOperation {
public:
	T operator()(const T& x, const T& y) {
		return x*y;
	}
};

template <class T>
class SummOperation {
public:
	T operator()(const T& x, const T& y) {
		return x + y;
	}
};

template <class G, template <class > class BinaryOperation>
void calc (int x, int y, int mask, int next_mask, typename BinaryOperation<G> cover) {
	if (x == n)
		return;
	if (y >= m)
		D[x+1][next_mask] = cover(D[x][mask],D[x+1][next_mask]);
	else
	{
		int my_mask = 1 << y;
		if (mask & my_mask)
			calc (x, y+1, mask, next_mask, cover);
		else
		{
			calc (x, y+1, mask, next_mask | my_mask, cover);
			if (y+1 < m && ! (mask & my_mask) && ! (mask & (my_mask << 1)))
				calc (x, y+2, mask, next_mask, cover);
		}
	}
}

template <class T, template <class > class BinaryOperation>
T pow(T a, int n, typename BinaryOperation<T> f){
	T powA = a;
	int pos = 0;
	T res = powA;
	bool flag = true;
	while ((1 << pos) <= n){
			if (n & (1 << pos)){
				if (flag == true){
					res = powA;
					flag = false;
				}
				else res = f(res,powA);
			}
		pos++;
		powA = f(powA, powA);
	}
	return res;
}
void CheckFibonacci(){
	IMatrix A(2,2);
	A[0][0] = 1;
	A[0][1] = 1;
	A[1][0] = 1;
	A[1][1] = 0;
	int n;
	cout << "entered fibonacci index n\n";
	cin >> n;
	MultOperation<IMatrix> f;
	IMatrix matr = pow<IMatrix,MultOperation >(A,n,f);
	cout << "n fibonacci number:" << matr[1][0] << endl;
}

void CheckSumm(){
	MultOperation<int> fint;
	int a,n;
	cout << "entered number a\n";
	cin >> a;
	cout << "entered degree\n";
	cin >> n;
	a = pow<int,MultOperation >(a, n, fint);
	cout << "a in n degree:" << a << endl;
}
void CheckParket(){
	cout << "entered n\n";
	cin >> n;
	cout << "entred m\n";
	cin >> m;
	IMatrix C(n + 1, (1 << m));
	D = C;
	D[0][0] = 1;
	SummOperation<int> cover;
	for (int i = 0; i < n; ++i)
		for (int mask = 0; mask < (1 << m); ++mask){
			calc<int, SummOperation>(i, 0, mask, 0, cover);
		}
		cout <<"count different parket:" << D[n][0] << endl;
}

int main(){
	CheckFibonacci();	
	CheckSumm();
	CheckParket();
	return 0;
}