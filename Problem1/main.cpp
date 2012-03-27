#include <iostream>
#include "stdio.h"
#include <vector>
#include <map>
#include <time.h>
#include <assert.h>
using namespace std;

vector<int> operator + (const vector<int> &v, const int a) {
	vector<int> result;
	result.resize(v.size());
	for(unsigned int i = 0; i < v.size(); i++){
		result[i] = (v[i] + a);	
	}
	return result;
}

vector<int> operator ++ (vector<int> &v) {
	for(unsigned int i = 0; i < v.size(); i++){
		v[i] = (v[i] + 1);	
	}
	return v;
}

vector<int> operator + (const vector<int> &v, const vector<int> &v2) {
	vector<int> result;
	result.resize(v.size());
	for(unsigned int i = 0; i < v.size(); i++){
		result[i] = (v[i] + v2[i]);	
	}
	return result;
}

vector<int> operator * (const vector<int> &v, const vector<int> &v2) {
	vector<int> result;
	result.resize(v.size());
	for(unsigned int i = 0; i < v.size(); i++){
		result[i] = (v[i] * v2[i]);	
	}
	return result;
}

vector<int> operator * (vector<int> &v, int a) {
	vector<int> result;
	result.resize(v.size());
	for(unsigned int i = 0; i < v.size(); i++){
		result[i] = (v[i] * a);	
	}
	return result;
}

vector<int> operator % (const vector<int> v, const int n) {
	vector<int> result;
	result.resize(v.size());
	for(unsigned int i = 0; i < v.size(); i++){
		result[i] = v[i] % n;	
	}
	return result;
}

ostream& operator << (ostream& out , const vector<int>& v) {
	for(unsigned int i = 0; i < v.size(); ++i) {
		out << v[i] << endl;
	}
	return out;
}

template<class T> class GlobalFunctor{
public:
	T virtual operator() (const T &x) const = 0;
	virtual int getModule() const = 0;
};

template <class T> class Functor : public GlobalFunctor<T>{
public:
	Functor(int module) : module_(module) { }
    T operator()(const T &x) const {
		T cur = (x + x) % module_;
		return cur;
	}
	int getModule() const{
		return module_;
	}
private:
	int module_;
};

template <class T, template<class> class D> 
int preCycleLength(const D<T> &func, T x){
	int n = func.getModule();
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
	int module;
public:
	GraphFunctor(int clength, int plength, T startElement){
		module = plength;
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
	
  	T operator()(const T &x) const {
		T cur = (nextElement.find(x)) -> second;
		return cur;
	}
	int getModule() const {
		return module;
	}
};

void testCycleIntegerSequence(int clength, int plength){
	GraphFunctor<int> f(clength, plength, 0);
	assert(preCycleLength(f, 0) == plength);
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
	assert(preCycleLength(ff, tester) == plength);
}

void testRandomVectorSequence(int sead){
	srand(sead);
	testCycleVectorSequence(rand() % 100, rand() % 100);
}
void testVectorSequence(){
	testRandomVectorSequence(5);
}

int main(){
	cout << "print n\n";
	int n;
	cin >> n;
	Functor<int> ff(n);
	vector<int> v;
	v.resize(3);
	v[0] = 1;
	v[1] = 2;
	v[2] = 3;	
	int x = 3;
	cout << "answer = " << preCycleLength<int, Functor>(ff, x) << endl;
	testIntegerSequence();
	testVectorSequence();
	return 0;
}