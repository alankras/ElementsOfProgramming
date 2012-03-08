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
	int count_stroka;
	int count_stolbec;
	T** S;
public:
	Matrix<T>();
	Matrix<T>( const Matrix<T>& );
	Matrix<T>(int n , int n2);
	~Matrix<T>() {
		for(int i = 0 ; i < count_stroka;i++){
			delete S[i];
		}
		delete[] S;
	}
	T* operator[](int i)  {  
		return S[i];
	}
	const T* operator[](int i) const {
		return S[i];
	}


	Matrix<T>& operator = (const Matrix<T>& S2){
		for(int i = 0 ; i < count_stroka;i++){
			delete S[i];
		}
		delete[] S ;
		
		count_stroka = S2.count_stroka;
		count_stolbec = S2.count_stolbec;
		
		S = new T* [count_stroka];      
		for (int i = 0; i < count_stroka; i++)
			S[i] = new T [count_stolbec];
		for( int i = 0;i < count_stroka;i++ ){
			for(int j = 0; j < count_stolbec; j++){
				S[i][j] = S2.S[i][j];
			}
		}
		return *this;
	}

	void Print()const {
		for (int i = 0; i < count_stroka; i++){
			for(int j = 0 ; j < count_stolbec; j++){
				printf("%.1d  ",S[i][j]);
			}
			printf("\n");
		}
	}
	Matrix<T> operator + (const Matrix<T>& A)const {  
		int n2 = count_stolbec;
		int n = count_stroka;
		assert(count_stroka == A.count_stroka);
		assert(count_stolbec == A.count_stolbec);
		Matrix<T> Summ(n,n2);  
		for (int i = 0; i < n;i++){
			for(int j = 0; j < n2;j++){
				Summ[i][j] = S[i][j] + A[i][j];
			}
		}
		return Summ;                  
	}

	Matrix<T> operator - (const Matrix<T>& A) const{ 
		assert(count_stroka == A.count_stroka);
		assert(count_stolbec == A.count_stolbec);
		int n2 = count_stolbec;
		int n = count_stroka;
		Matrix<T> Diff(n,n2);  
		for (int i = 0; i < n;i++){
			for(int j = 0; j < n2;j++){
				Diff[i][j] = S[i][j] - A[i][j];
			}
		}
		return Diff;       

	}

	Matrix<T> operator * (const Matrix<T>& A)const{ 
		int n = count_stroka;
		assert(count_stolbec == A.count_stroka);
		int n2 = A.count_stolbec;
		int n3 = count_stolbec;
		Matrix<T> Mull(n,n2);
		for( int i = 0; i < n; i++){
			for(int j = 0; j < n2; j++){
				for(int k = 0; k < n3; k++){
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
	count_stroka = 0;
	count_stolbec = 0;
	S = NULL;
}
template <class T>
Matrix<T>::Matrix( const Matrix<T>& p){
	
	S = new T* [p.count_stroka];      
	for (int i = 0; i < p.count_stroka; i++)
		S[i] = new T [p.count_stolbec];
	count_stolbec = p.count_stolbec;
	count_stroka = p.count_stroka;
	for(int i = 0;i < p.count_stroka;i++){
		for(int j = 0; j < p.count_stolbec;j++){
			S[i][j] = p[i][j];
		}
	}
}
template <class T>
Matrix<T>::Matrix( int n , int n2 )
{	
	count_stroka = n;
	count_stolbec = n2;
	S = new T* [n];      
	for (int i = 0; i < n; i++)
		S[i] = new T [n2];
	for( int i = 0;i < count_stroka;i++ ){
		for(int j = 0; j < count_stolbec; j++){
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

int main(){
	IMatrix A(2,2);
	A[0][0] = 7;
	A[0][1] = 3;
	A[1][0] = 4;
	A[1][1] = 6;
	A.Print();
	MultOperation<IMatrix> f;
	SummOperation<int> fint;
	int a = 4;
	IMatrix matr = pow<IMatrix,MultOperation >(A,2,f);
	matr.Print();
	
	a = pow<int,SummOperation >(a,4,fint);
	cout << a << endl ;
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
		cout << D[n][0];
	return 0;
}