#include <iostream>
#include "stdio.h"
#include <vector>
using namespace std;

int n;

vector<int> operator + (const vector<int> &V, const int a) {
	vector<int> result;
	result.resize(V.size());
	for(unsigned int i = 0; i < V.size(); i++){
		result[i] = (V[i] + a) % n;	
	}
	return result;
}

vector<int> operator + (const vector<int> &V, const vector<int> &V2) {
	vector<int> result;
	result.resize(V.size());
	for(unsigned int i = 0; i < V.size(); i++){
		result[i] = (V[i] + V2[i]) % n;	
	}
	return result;
}

vector<int> operator * (const vector<int> &V, const vector<int> &V2) {
	vector<int> result;
	result.resize(V.size());
	for(unsigned int i = 0; i < V.size(); i++){
		result[i] = (V[i] * V2[i]) % n;	
	}
	return result;
}

vector<int> operator * (vector<int> &V, int a) {
	vector<int> result;
	result.resize(V.size());
	for(unsigned int i = 0; i < V.size(); i++){
		result[i] = (V[i] * a) % n;	
	}
	return result;
}

vector<int> operator % (const vector<int> &V, const int n) {
	vector<int> result;
	result.resize(V.size());
	for(unsigned int i = 0; i < V.size(); i++){
		result[i] = V[i] % n;	
	}
	return result;
}

ostream& operator << (ostream& out , const vector<int>& V) {
	for(unsigned int i = 0; i < V.size(); ++i) {
		out << V[i] << endl;
	}
	return out;
}

template <class T> class Functor{
public:
	T operator()(T &x) {
		T cur = (x + x) % n;
		return cur;
	}
};

template <class T> T function(Functor<T> &func, T x){
	T current = x;
	for(int i = 0; i < n + 1; i++){
		current = func(current);
	}
	T element = func(current);
	int length = 1;
	while (element != current){
		element = func(element);
		length++;
	}
	T answer = 0;
	T z = x;
	for(int i = 0; i < length; i++){
		z = func(z);
	}
	while (x != z){
		x = func(x);
		z = func(z);
		answer++;
	}
	return answer;
}
template<class T>
T test(Functor<T> &func, T V, const int n){// результат н раз применения функтора к координатам вектора (то есть здесь я не считаю длины прециклов для кажлой координаты)
	for(int i = 0; i < n; i++){
		 V = func(V);
	}
	return V;
}

int main(){
	Functor<int> ff;
	Functor<vector<int> > f;
	vector<int> V;
	V.resize(3);
	V[0] = 1;
	V[1] = 2;
	V[2] = 3;
	cout << "print n\n";
	cin >> n;
	int x = 3;
	cout << "answer = " << function(ff, x) << endl;
	cout << "answer for vector:" << endl << test(f, V, 2);
	return 0;
}