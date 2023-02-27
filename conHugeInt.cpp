#include "conHugeInt.h"

int hugeInt::base = 10;
hugeInt::hugeInt(int _size)
{
	this->size = _size;
	this->Ds = new int[_size] {};
	this->isNeg = false;
}

hugeInt::hugeInt(const char* N)
{
	this->strToHugeInt(N);
}

void hugeInt::strToHugeInt(const string& num)
{
	int si = 0;
	this->isNeg = false;
	if (num[0] == '+')
	{
		this->size = num.size() - 1;
		this->Ds = new int[num.size() - 1];
		si++;
	}
	else if (num[0] == '-')
	{
		si++;
		this->isNeg = true;
		this->size = num.size() - 1;
		this->Ds = new int[num.size() - 1];
	}
	else
	{
		this->size = num.size();
		this->Ds = new int[num.size()];
	}
	for (int di = 0; num[si] != '\0'; di++, si++)
	{
		if (isalpha(num[si]))
		{
			this->Ds[this->size - 1 - di] = toupper(num[si]) - 55;
		}
		else
			this->Ds[this->size - 1 - di] = num[si] - '0';
	}
	*this = this->shrink();
}
hugeInt::hugeInt(istream& rdr)
{
	this->size = 0, isNeg = false;
	this->Ds = nullptr;
	rdr >> *this;

}
hugeInt::hugeInt(const hugeInt& N)
{
	this->deepCopy(N);
}
const hugeInt& hugeInt::operator=(const hugeInt& N)
{
	if (this != &N)
	{
		delete[]this->Ds;
		this->deepCopy(N);
	}
	return *this;
}
hugeInt hugeInt::Unity()
{
	hugeInt I(1);
	I[0] = 1;
	return I;

}
void hugeInt::deepCopy(const hugeInt& N)
{
	this->size = N.size;
	this->Ds = new int[N.size];
	this->isNeg = N.isNeg;
	for (int i = 0; i < N.size; i++)
		(*this)[i] = N[i];
}
int& hugeInt::operator[](int index)
{
	return  Ds[index];
}
int hugeInt::operator[](int index)const
{

	return (index >= 0 && index < this->size ? Ds[index] : 0);
}

hugeInt hugeInt::operator-()const
{
	hugeInt R = *this;
	R.isNeg = !R.isNeg;
	return R;
}
hugeInt hugeInt::abs()const
{
	hugeInt R = *this;
	if (this->isNeg)
		return -R;
	return R;
}
hugeInt hugeInt::quantityWiseAdd(const hugeInt& N2)const
{
	hugeInt R(this->size + 1);
	int carry = 0;
	for (int i = 0; i < R.size; i++)
	{
		int sum = (*this)[i] + N2[i] + carry;
		R[i] = sum % base;
		carry = sum / base;
	}
	return R.shrink();
}
hugeInt hugeInt::quantityWiseSubtract(const hugeInt& N2)const
{
	hugeInt R(this->size);
	int borrow = 0;
	for (int i = 0; i < R.size; i++)
	{
		int dif = (*this)[i] - N2[i] - borrow;
		borrow = (dif < 0 ? 1 : 0);
		R[i] = (dif < 0 ? dif + base : dif);
	}
	return R.shrink();
}

ostream& operator<<(ostream& out, const hugeInt& N)
{
	if (N.isNeg)
		out << "-";
	for (int i = N.size - 1; i >= 0; i--)
	{
		if (N[i] > 9)
		{
			out << char(N[i] + 55);
		}
		else
			out << N[i];
	}
	return out;
}


bool hugeInt::quantityWiseLess(const hugeInt& N2)const
{
	if (this->size < N2.size)
		return true;
	else if (this->size > N2.size)
		return false;
	for (int i = this->size - 1; i >= 0; i--)
	{
		if ((*this)[i] < N2[i])
			return true;
		else if ((*this)[i] > N2[i])
			return false;
	}
	return false;
}

bool hugeInt::quantityWiseGreat(const hugeInt& N2)const
{
	return N2.quantityWiseLess(*this);
}

bool hugeInt::quantityWiseEqual(const hugeInt& N2)const
{
	return (quantityWiseGreat(N2) == false && quantityWiseLess(N2) == false);
}

hugeInt hugeInt::shrink()
{
	int count = 0, newSize = this->size;
	for (int i = this->size - 1; (*this)[i] == 0 && i > 0; i--)
	{
		newSize--;
	}

	hugeInt R(newSize);
	R.isNeg = this->isNeg;
	for (int i = 0; i < newSize; i++)
		R[i] = (*this)[i];
	if (R.size == 1 && R[0] == 0)
		R.isNeg = false;
	return R;



}

bool hugeInt::operator<(const hugeInt& N2)const
{
	if (this->isNeg && !N2.isNeg)
		return true;
	else if (!this->isNeg && N2.isNeg)
		return false;
	if (this->isNeg == N2.isNeg && this->isNeg == true)
		return this->quantityWiseGreat(N2);
	else
		return this->quantityWiseLess(N2);

}
bool hugeInt::operator==(const hugeInt& N2)const
{
	return this->quantityWiseEqual(N2) && (this->isNeg == N2.isNeg);
}
bool hugeInt::operator!=(const hugeInt& N2)const
{
	return !(*this == N2);
}
bool hugeInt::operator<=(const hugeInt& N2)const
{
	return (*this < N2 || *this == N2);
}
bool hugeInt::operator>(const hugeInt& N2)const
{
	return N2 < *this;
}

bool hugeInt::operator>=(const hugeInt& N2)const
{
	return (*this > N2 || *this == N2);
}



hugeInt hugeInt::operator+(const hugeInt& N2)const
{
	hugeInt R;
	if ((*this).isNeg == N2.isNeg)
	{
		if (this->quantityWiseGreat(N2))
		{
			R = this->quantityWiseAdd(N2);
			R.isNeg = N2.isNeg;
		}
		else
		{
			R = N2.quantityWiseAdd(*this);
			R.isNeg = N2.isNeg;
		}
	}
	else
	{
		if (this->quantityWiseGreat(N2))
		{
			R = this->quantityWiseSubtract(N2);
			R.isNeg = this->isNeg;
		}
		else
		{
			R = N2.quantityWiseSubtract(*this);
			R.isNeg = N2.isNeg;
		}
	}

	if (R.size == 1 && R[0] == 0)
		R.isNeg = false;
	return R;
}


hugeInt hugeInt::operator-(const hugeInt& N2)const
{
	hugeInt I = -N2;
	return *this + I;
}



const hugeInt& hugeInt::operator+=(const hugeInt& N)
{
	return *this = *this + N;
}

const hugeInt& hugeInt::operator-=(const hugeInt& N)
{
	return *this = *this - N;
}

hugeInt hugeInt::operator*(const hugeInt& N2)
{
	hugeInt N2copy = N2.abs(), finalAns, Zero, unit = "1";

	while (N2copy != Zero)
	{
		hugeInt count = unit, R = (*this).abs();
		while ((count + count) <= N2copy)
		{
			R += R;
			count += count;
		}
		N2copy -= count;
		finalAns += R;
	}
	finalAns.isNeg = (this->isNeg == N2.isNeg ? false : true);
	return finalAns;
}

hugeInt hugeInt::operator/(const hugeInt& N2)
{
	hugeInt Zero;
	if (N2 == Zero)
		throw "Division by zero not Possible";

	hugeInt thisCopy = this->abs(), finalAns, N2abs = N2.abs();


	while (thisCopy >= N2abs)
	{
		hugeInt count = "1", R = N2abs;
		while ((R + R) <= thisCopy)
		{
			R += R;
			count += count;
		}
		finalAns += count;
		thisCopy -= R;
	}

	finalAns.isNeg = ((this->isNeg == N2.isNeg) || finalAns == Zero ? false : true);
	return finalAns;

}

const hugeInt& hugeInt::operator/=(const hugeInt& N2)
{
	return *this = *this / N2;
}
const hugeInt& hugeInt::operator*=(const hugeInt& N2)
{
	return *this = *this * N2;
}

hugeInt hugeInt::operator%(const hugeInt& N2)
{
	hugeInt Zero;
	if (N2 == Zero)
		throw "Mod by Zero not possible";
	hugeInt thisCopy = this->abs(), finalAns, N2abs = N2.abs();


	while (thisCopy >= N2abs)
	{
		hugeInt count = "1", R = N2abs;
		while ((R + R) <= thisCopy)
		{
			R += R;
			count += count;
		}
		thisCopy -= R;
	}

	if (thisCopy != Zero)
		thisCopy.isNeg = this->isNeg;

	return thisCopy;
}

const hugeInt& hugeInt::operator%=(const hugeInt& N2)
{
	return *this = *this % N2;
}
hugeInt& hugeInt::operator++()
{
	hugeInt Unit = "1";
	*this += Unit;
	return *this;
}
hugeInt& hugeInt::operator--()
{
	hugeInt Unit = "1";
	*this -= Unit;
	return *this;
}
hugeInt hugeInt::operator--(int)
{
	hugeInt R = *this;
	hugeInt Unit = "1";
	*this -= Unit;
	return R;
}
hugeInt hugeInt::operator++(int)
{
	hugeInt R = *this;
	hugeInt Unit = "1";
	*this += Unit;
	return R;
}

istream& operator>>(istream& in, hugeInt& N)
{
	string num = "";
	getline(in, num);
	delete[]N.Ds;
	N.strToHugeInt(num);
	return in;
}

hugeInt::~hugeInt()
{
	delete[]this->Ds;
}