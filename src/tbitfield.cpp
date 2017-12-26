
// Битовое поле

#include "tbitfield.h"

#define BITS_IN_ONE_MEM (sizeof(TELEM) * 8)

TBitField::TBitField(int len)
{
	if (len < 0)
		throw("Error");

	BitLen = len;
	MemLen = (BitLen + BITS_IN_ONE_MEM - 1) / BITS_IN_ONE_MEM;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = 0;
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if (n < 0)
		throw("Error");

	if (n > BitLen)
		throw("Error");

	int res = 0;
	res = (n / BITS_IN_ONE_MEM);
		return res;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if (n < 0)
		throw("Error");

	if (n > BitLen)
		throw("Error");

	TELEM mask = 1 << (n % BITS_IN_ONE_MEM);

  return mask;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if (n < 0)
		throw("Error");

	if (n > BitLen)
		throw("Error");

	TELEM mask = GetMemMask(n);
	int i = 0;
	i = GetMemIndex(n);
	pMem[i] = pMem[i] | mask;
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n < 0)
		throw("Error");

	if (n > BitLen)
		throw("Error");

	TELEM mask = GetMemMask(n);
	int i = GetMemIndex(n);
	pMem[i] = pMem[i] & ~mask;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if (n < 0)
		throw("Error");

	if (n > BitLen)
		throw("Error");

	/*if ((pMem[GetMemIndex(n)] & GetMemMask(n)) == 0)
		return 0;
	else
		return 1;*/
	
	TELEM mask = GetMemMask(n);
	int i = GetMemIndex(n);
	TELEM res = pMem[i] & mask;
	if (res > 0)
		return 1;
	else
		return 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (BitLen != bf.BitLen)
		delete[] pMem;

	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];

  return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (MemLen != bf.MemLen)
		return 0;
	else if (BitLen != bf.BitLen)
		return 0;
	else
	{
		for (int i = 0; i < MemLen - 1; i++)
		if (pMem[i] != bf.pMem[i])
			return 0;

		for (int i = (MemLen - 1)*BITS_IN_ONE_MEM; i < BitLen; i++)
		{
			int a = GetBit(i);
			int b = bf.GetBit(i);

			if (a != b)
				return 0;
		}

		return 1;
	}
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if (MemLen != bf.MemLen)
		throw ("Error");
	else if (BitLen != bf.BitLen)
		return false;

	if (*this == bf) 
		return 0;
	else 
		return 1;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int min = (BitLen > bf.BitLen) ? bf.BitLen : BitLen;
	int max = (BitLen < bf.BitLen) ? bf.BitLen : BitLen;
	int minMemLen = (MemLen > bf.MemLen) ? bf.MemLen : MemLen;
	TBitField res(max);

	for (int i = 0; i < minMemLen; i++)
		res.pMem[i] = pMem[i] | bf.pMem[i];

	/*for (int i = ((GetMemIndex(min) - 1)*BITS_IN_ONE_MEM); i < ((GetMemIndex(min)*BITS_IN_ONE_MEM) - 1); i++)
	{
		int a = GetBit(i);
		int b = bf.GetBit(i);
		if (a + b >= 1)
			res.SetBit(i);
	}*/
	if (min = bf.BitLen)
	{
		for (int i = minMemLen; i < res.MemLen; i++)
			res.pMem[i] = pMem[i];
	}
	else 
		for (int i = minMemLen; i < res.MemLen; i++)
			res.pMem[i] = bf.pMem[i];

  return res;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int min = (BitLen > bf.BitLen) ? bf.BitLen : BitLen;
	TBitField res(min);

	for (int i = 0; i < res.MemLen; i++)
		res.pMem[i] = pMem[i] & bf.pMem[i];

	/*for (int i = (res.MemLen - 1)*BITS_IN_ONE_MEM; i < res.BitLen; i++)
		{
		int a = GetBit(i);
		int b = bf.GetBit(i);
		if (a + b == 2)
			res.SetBit(i);
		}*/

  return res;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField res(BitLen);

	for (int i = 0; i < BitLen; i++)
	{
		if (GetBit(i) == 0)
			res.SetBit(i);
	//	else
	//		res.ClrBit(i);
	}
	
  return res;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	int i;
	cin >> i;
	for (; i > -1; cin >> i)
		bf.SetBit(i);
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	cout << "{";
	for (int k = bf.BitLen; k > 0; k--)
		cout << bf.GetBit(k);
	cout << "}\n";
	return ostr;
}
