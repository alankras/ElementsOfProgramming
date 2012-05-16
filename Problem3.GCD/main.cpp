#include "stdio.h"
#include "iostream"
#include "assert.h"
#include <vector>

using namespace std;

class Fraction{
private:
	int numerator;
	int denominator;
public:
	Fraction(){
		numerator = 0;
		denominator = 1;
	}

	Fraction(int numerator_, int denominator_) {
		numerator = numerator_;
		denominator = denominator_;
		reduction();
	}
	
	Fraction(int numerator_){
		numerator = numerator_;
		denominator = 1;
	}

	Fraction(const Fraction& fract){
		numerator = fract.getNumerator();
		denominator = fract.getDenominator();
	}

	Fraction reduction(){
		if (numerator == 0){
			denominator = 1;	
			return *this;
		}
		int dividor;
		int balance1;
		int balance2;
		int positiveNumerator = numerator;
		int positiveDenominator = denominator;
		if (numerator < 0) positiveNumerator = -positiveNumerator;
		if (denominator < 0) positiveDenominator = -positiveDenominator;
		if (positiveNumerator < positiveDenominator) dividor = positiveNumerator;
		else dividor = positiveDenominator;
		while (1){
			balance1 = numerator % dividor;
			balance2 = denominator % dividor;
			if ((balance1 == 0) && (balance2 == 0)){
				numerator = numerator / dividor;
				denominator = denominator / dividor;
				break;
			}
			dividor--;
		}
		return *this;
	}
	
	
	Fraction operator = (Fraction fract){
		numerator = fract.getNumerator();
		denominator = fract.getDenominator();		
		return *this;
	}

	Fraction operator = (int fract){
		numerator = fract;
		denominator = 1;		
		return *this;
	}


	Fraction operator + (const Fraction& fract) const{
		Fraction result;
		result.setNumerator(numerator * fract.getDenominator() + fract.getNumerator() * denominator);
		result.setDenominator(denominator * fract.getDenominator());
		result.reduction();
		return result;
	}
	
	Fraction operator + (int fract) const{
		Fraction tmp(fract);
		return *this + tmp;
	}

	Fraction operator - (const Fraction& fract) const{
		Fraction result;
		result.setNumerator(numerator * fract.getDenominator() - fract.getNumerator() * denominator);
		result.setDenominator(denominator * fract.getDenominator());
		result.reduction();
		return result;
	}
	
	Fraction operator - (int fract) const{
		Fraction tmp(fract);
		return *this - tmp;
	}

	Fraction operator * (Fraction& fract) const{
		Fraction result;
		result.setNumerator(numerator * fract.getNumerator());
		result.setDenominator(denominator * fract.getDenominator());
		result.reduction();
		return result;
	}

	Fraction operator * (int fract) const{
		Fraction tmp(fract);
		return *this * tmp;
	}
	
	Fraction operator / (Fraction& fract) const{
		Fraction result;
		result.setNumerator(numerator * fract.getDenominator());
		result.setDenominator(denominator * fract.getNumerator());
		result.reduction();
		return result;
	}
	
	Fraction operator / (int fract) const{
		Fraction tmp(fract);
		return *this / tmp;
	}

	bool operator < (const Fraction& fract) const {
		Fraction tmp = *this - fract; 
		if ((tmp.getNumerator() > 0) && (tmp.getDenominator() > 0)) return false; 
		if ((tmp.getNumerator() < 0) && (tmp.getDenominator() < 0)) return false;
		return true;
	}

	bool operator < (int fract) const {
		Fraction tmp(fract);
		return *this < tmp; 
	}

	bool operator > (const Fraction& fract) const {
		return fract < *this;
	}

	bool operator > (int fract) const {
		Fraction tmp(fract);
		return tmp < *this ; 
	}


	bool operator == (const Fraction& fract) const {
		if ((fract.getNumerator() == numerator) && (fract.getDenominator() == denominator)) return true;
		return false;
	}

	bool operator == (int fract) const {
		if ((numerator == fract) && (denominator == 1)) return true;
		return false;
	}

	bool operator != (const Fraction& fract) const {
		if ((fract.getNumerator() != numerator) || (fract.getDenominator() != denominator)) return true;
		return false;
	}
	
	bool operator != (int fract){
		if ((numerator == fract) && (denominator == 1)) return true;
		return false;
	}

	bool operator <= (const Fraction& fract) const {
		if ((*this < fract) || (*this == fract)) return true;
		return false;
	}

	bool operator <= (int fract) const {
		if ((*this < fract) || (*this == fract)) return true;
		return false;
	}

	bool operator >= (const Fraction& fract) const {
		return fract <= *this;
	}

	bool operator >= (int fract) const {
		Fraction tmp(fract);
		return tmp <= *this;
	}

	bool IsInt() const{
		if (getDenominator() == 1) return true;
		else return false;
	}

	int getNumerator() const{
		return numerator;
	}

	int getDenominator() const{
		return denominator;
	}

	void setNumerator(int numerator_){
		numerator = numerator_;
	}

	void setDenominator(int denominator_){
		denominator = denominator_;
	}
};
//Polynomial
class Polinomial{
private:
	vector<Fraction> factor;

public:	
	Fraction& operator[](int i) {  
		return factor[i];
	}

	const Fraction& operator[](int i) const {
		return factor[i];
	}

	int degree() const{
		return static_cast<int>(factor.size()) - 1;
	}

	void setDegree(int degree){
		factor.resize(degree);
	}

	Polinomial(const Polinomial& p){
		factor.assign(p.degree(), 0);
		for(int i = 0; i < p.degree(); i++){
			factor[i] = p[i];
		}
	}

	Polinomial operator = (const Polinomial& p){
		factor.assign(p.degree(), 0);
		for(int i = 0; i < p.degree(); i++){
			factor[i] = p[i];
		}
		return *this;
	}

	bool operator != (int number)  const {
		if (number == 0){
			for(int i = 0; i < degree(); i++){
				if (factor[i].getNumerator() != 0) return true;
			}
			return false;
		}
		return false;
	}

	bool operator == (const Polinomial& p) const {
		if (!(*this < p) && (*this <= p)) return true;
		else return false;
	}

	bool operator == (int p) const {
		if (p == 0){
			for(unsigned int i = 0; i < factor.size(); i++){
				if (factor[i] != 0) return false;
			}
			return true;
		}
		else return false;
	}

	bool operator < (const Polinomial& p) const {
		if (degree() < p.degree()) return true;
		else if (degree() > p.degree()) return false;
		else{
			for(int i = p.degree() - 1; i > 0; i--){
				if (factor[i] < p[i]) return true;
				else if (factor[i] > p[i]) return false;	
			}
		}
		return false;
	}
	bool operator <= (const Polinomial& p) const {
		if (degree() < p.degree()) return true;
		else if (degree() > p.degree()) return false;
		else{
			for(int i = p.degree() - 1; i > 0; i--){
				if (factor[i] < p[i]) return true;
				else if (factor[i] > p[i]) return false;	
			}
		}
		return true;
	}

	Polinomial operator - (const Polinomial& p) const{
		Polinomial result;
		if (degree() > p.degree()){ 
			result.setDegree(degree());
			for(int i = 0; i < p.degree(); i++){
				result.setCertainFactor(i, factor[i] - p[i]);
			}
			for(int i = p.degree(); i < degree(); i++){
				result.setCertainFactor(i, factor[i]);
			}
		}
		else{
			result.setDegree(p.degree());
			for(int i = 0; i < degree(); i++){
				result.setCertainFactor(i, factor[i] - p[i]);
			}
			for(int i = degree(); i < p.degree(); i++){
				result.setCertainFactor(i, Fraction() - factor[i]);
			}
		}
		return result;
	}
	
	Polinomial operator * (Fraction& fract){
		for(int i = 0; i < degree(); i++){
			setCertainFactor(i, factor[i] * fract);
		}
		return *this;
	}

	Polinomial operator * (Polinomial& p){
		Polinomial result(degree() + p.degree() - 2);
		for(int i = 0; i < degree(); i++){
			for(int j = 0; j < p.degree(); j++){
				result.setCertainFactor(i + j, factor[i] * p[j] + result[i + j]);
			}
		}
		int i = 1;
		while(result[degree() - i].getNumerator() == 0){
			result.setDegree(result.degree() - 1); 
			i++;
		}
		return result;
	}


	Polinomial operator + (Polinomial& p){
		Polinomial result;
		if (degree() > p.degree()){ 
			result.setDegree(degree());
			for(int i = 0; i < p.degree(); i++){
				result.setCertainFactor(i, factor[i] + p[i]);
			}
			for(int i = p.degree(); i < degree(); i++){
				result.setCertainFactor(i, factor[i]);
			}
		}
		else{
			result.setDegree(p.degree());
			for(int i = 0; i < degree(); i++){
				result.setCertainFactor(i, factor[i] + p[i]);
			}
			for(int i = degree(); i < p.degree(); i++){
				result.setCertainFactor(i, Fraction() + factor[i]);
			}
		}
		return result;
	}

	Polinomial operator % (Polinomial& p){
		Polinomial tmp = *this;
		if (degree() < p.degree()) return * this;
		else{
			Polinomial result(tmp.degree() - p.degree());
			while(tmp.degree() >= p.degree()){
				Fraction index = Fraction(1) / p[p.degree() - 1] * tmp[tmp.degree() - 1];
				Polinomial indexTmp(tmp.degree() - p.degree());
				indexTmp.setCertainFactor(indexTmp.degree() - 1, index);
				Polinomial current = p * indexTmp;
				tmp = tmp - current;
				tmp.setDegree(tmp.degree() - 1);
			}
		}
		return tmp;
	}

	Polinomial(){
		factor.assign(1, 0);
	}

	Polinomial(int degree){
		factor.assign(degree + 1, 0);
	}

	void setCertainFactor(size_t number, Fraction factor){
		if (number < this -> factor.size()){
			this -> factor[number] = factor;
		}
		else{
			this -> factor.resize(number + 1, 0);
			this -> factor[number] = factor;
		}
	}

	void PrintPolinomial() const{
		if (factor[0].IsInt() == true){
			cout << factor[0].getNumerator() << " + ";
		}
		else {
			cout << factor[0].getNumerator() << "/" << factor[0].getDenominator() << " + ";
		}
		for(unsigned int i = 1; i < factor.size() - 1; i++){
			if (factor[i].IsInt() == true) cout << factor[i].getNumerator() << "x^" << i << " + ";
			else{
				cout << factor[i].getNumerator() << "/" << factor[i].getDenominator() << "x^" << i << " + ";	
			}
		}
		if (factor[factor.size() - 1].IsInt() == true) cout << factor[factor.size() - 1].getNumerator() << "x^" << factor.size() -1;
		else cout << factor[factor.size() - 1].getNumerator() << "/" << factor[factor.size() - 1].getDenominator() << "x^" << factor.size() - 1;
		cout << endl;
	}
};

template<class T>
T GCD(T first, T second){
	while (second != 0){
		T tmp3 = second;
		second = first % second;
		first = tmp3;
	}
	return first;
}

int RemainderNonnegative(int number1, int number2){
	if (number1 < number2) return number1;
	if (number1 - number2 >= number2){
		number1 = RemainderNonnegative(number1, 2 * number2);
		if (number1 < number2) return number1;
	} 
	return number1 - number2;
}

int SimpleGCDForInt(int number1, int number2){
	while(true){
		if (number2 == 0) return number1;
		number1 = RemainderNonnegative(number1, number2);
		if (number1 == 0) return number2;
		number2 = RemainderNonnegative(number2, number1);
	}
}

void checkFunction(){
	Fraction f(1);
	Fraction g(6);
	Fraction d(11);
	Fraction e(7);
	Fraction c(14);
	Fraction b(8);
	///////////
	Fraction ff(2);
	Polinomial p4(1);
	Polinomial p5(2);
	p4.setCertainFactor(0, f);
	p4.setCertainFactor(1, f);
	p5.setCertainFactor(0, f);
	p5.setCertainFactor(1, ff);
	p5.setCertainFactor(2, f);
	Polinomial p1(3);
	Polinomial p2(3);
	p1[0] = g;
	p1.setCertainFactor(0, g);
	p1.setCertainFactor(1, d);
	p1.setCertainFactor(2, g);
	p1.setCertainFactor(3, f);
	p2.setCertainFactor(0, b);
	p2.setCertainFactor(1, c);
	p2.setCertainFactor(2, e);
	p2.setCertainFactor(3, f);
	cout << GCD<int>(30,42) << endl;
	Polinomial p3 = GCD<Polinomial>(p2, p1);
	Polinomial p6 = GCD<Polinomial>(p4, p5);
	p3.PrintPolinomial();
	p6.PrintPolinomial();
}

void testRandomIntegerSequence(int sead){
	srand(sead);
	int number1 = rand() % 1000;
	int number2 = rand() % 1000;
	assert(SimpleGCDForInt(number1, number2) == GCD<int>(number1, number2));
}

void testForInt(){
	for(int i = 0; i < 10000; i++){
		testRandomIntegerSequence(i);
	}
}
int main(){
	checkFunction();
	testForInt();
	return 0;
}