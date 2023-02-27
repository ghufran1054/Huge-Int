#pragma once
#include<iostream>
#include<string>
#include<fstream>
using namespace std;
class hugeInt
{
	
	int* Ds;
	int size;
	bool isNeg;
	void deepCopy(const hugeInt& N);
	hugeInt shrink();
	hugeInt quantityWiseSubtract(const hugeInt& N2)const;
	hugeInt quantityWiseAdd(const hugeInt& N2)const;
	static hugeInt Unity();
	bool quantityWiseLess(const hugeInt& N2)const;
	bool quantityWiseGreat(const hugeInt& N2)const;
	bool quantityWiseEqual(const hugeInt& N2)const;
	void strToHugeInt(const string& num);

public:
	static int base;
	hugeInt(istream& rdr);
	hugeInt(const hugeInt& N);
	hugeInt(int _size = 1);
	hugeInt(const char* N);
	hugeInt abs()const;
	hugeInt operator-()const;
	bool operator<(const hugeInt& N2)const;
	bool operator<=(const hugeInt& N2)const;
	bool operator>(const hugeInt& N2)const;
	bool operator>=(const hugeInt& N2)const;
	bool operator==(const hugeInt& N2)const;
	bool operator!=(const hugeInt& N2)const;
	hugeInt operator+(const hugeInt& N2)const;
	hugeInt operator-(const hugeInt& N2)const;
	const hugeInt& operator=(const hugeInt& N);
	const hugeInt& operator+=(const hugeInt& N);
	const hugeInt& operator-=(const hugeInt& N);
	hugeInt operator*(const hugeInt& N2);
	const hugeInt& operator*=(const hugeInt& N2);
	hugeInt operator/(const hugeInt& N2);
	const hugeInt& operator/=(const hugeInt& N2);
	hugeInt operator%(const hugeInt& N2);
	const hugeInt& operator%=(const hugeInt& N2);
	hugeInt& operator++();
	hugeInt& operator--();
	hugeInt operator++(int);
	hugeInt operator--(int);
	int& operator[](int index);
	int operator[](int index)const;
	friend ostream& operator<<(ostream&, const hugeInt& N);
	friend istream& operator>>(istream&, hugeInt& N);
	~hugeInt();
};



