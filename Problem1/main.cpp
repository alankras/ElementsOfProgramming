#include <iostream>
#include "stdio.h"
#include <vector>
#include <map>
#include <time.h>
#include <assert.h>
using namespace std;

vector<int> operator + (const vector<int> &V, const int a) {
	vector<int> result;
	result.resize(V.size());
	for(unsigned int i = 0; i < V.size(); i++){
		result[i] = (V[i] + a);	
	}
	return result;
}

vector<int> operator ++ (vector<int> &V) {
	for(unsigned int i = 0; i < V.size(); i++){
		V[i] = (V[i] + 1);	
	}
	return V;
}

vector<int> operator + (const vector<int> &V, const vector<int> &V2) {
	vector<int> result;
	result.resize(V.size());
	for(unsigned int i = 0; i < V.size(); i++){
		result[i] = (V[i] + V2[i]);	
	}
	return result;
}

bool operator != (const vector<int> &V, const vector<int> &V2) {
	vector<int> result;
	result.resize(V.size());
	for(unsigned int i = 0; i < V.size(); i++){
		if (V[i] != V2[i]) return true;	
	}
	return false;
}

vector<int> operator * (const vector<int> &V, const vector<int> &V2) {
	vector<int> result;
	result.resize(V.size());
	for(unsigned int i = 0; i < V.size(); i++){
		result[i] = (V[i] * V2[i]);	
	}
	return result;
}

vector<int> operator * (vector<int> &V, int a) {
	vector<int> result;
	result.resize(V.size());
	for(unsigned int i = 0; i < V.size(); i++){
		result[i] = (V[i] * a);	
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

template<class T> class GlobalFunctor{
public:
	T virtual operator() (const T &x) = 0;
};

template <class T> class Functor : public GlobalFunctor<T>{
public:
	Functor(int module) : module_(module) { }
	T operator()(const T &x) {
		T cur = (x + x) % module_;
		return cur;
	}
private:
	int module_;
};

template <class T> int function(GlobalFunctor<T> &func, T x, int n){
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
	int answer = 0;
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

template <class T> class GraphFunctor : public GlobalFunctor<T>{
private:
	map<T, T> nextElement;

public:
	GraphFunctor(int clength, int plength, T startElement){
		T count = startElement;
		T prev = startElement;
		for(int i = 0; i < plength; i++){
			T next = ++count;
			nextElement[prev] = next;
			prev = next;
		}
		T firstCycleElement = prev;
		for(int i = 0; i < clength - 1; i++){
			T next = ++count;
			nextElement[prev] = next;
			prev = next;
		}
		nextElement[prev] = firstCycleElement;
	}
	
	T operator()(const T &x) {
		T cur = nextElement[x];
		return cur;
	}
};

void testCycleIntegerSequence(int clength, int plength){
	GraphFunctor<int> f(clength, plength, 0);
	assert(function(f, 0, plength) == plength);
}

void testRandomIntegerSequence(int sead){
	srand(sead);
	testCycleIntegerSequence(rand() % 100, rand() % 100);
}

void testIntegerSequence(){
	for(int i = 0; i < 1000; i++){
		testRandomIntegerSequence(i);
	}
}

void testCycleVectorSequence(int clength, int plength){
	vector<int> tester(10, 5);
	for(int i = 0; i < 10; i++){
		tester[i] = i;
	}
	GraphFunctor<vector<int> > ff(clength, plength, tester);
	assert(function(ff, tester, plength) == plength);
}

void testRandomVectorSequence(int sead){
	srand(sead);
	testCycleVectorSequence(rand() % 100, rand() % 100);
}
void testVectorSequence(){
	testRandomVectorSequence(5);
}

int main(){
	Functor<int> ff(10);
	vector<int> V;
	V.resize(3);
	V[0] = 1;
	V[1] = 2;
	V[2] = 3;
	cout << "print n\n";
	int n;
	cin >> n;
	int x = 3;
	cout << "answer = " << function(ff, x, n) << endl;
	testIntegerSequence();
	testVectorSequence();
	return 0;
}