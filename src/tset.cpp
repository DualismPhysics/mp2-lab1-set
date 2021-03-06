
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(mp)
{
	MaxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.BitField)
{
	MaxPower = s.MaxPower;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf)
{
	MaxPower = bf.GetLength();
}

TSet::operator TBitField()
{
  return BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
  return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
	if (Elem < 0)
		throw ("Error");
	if (Elem > MaxPower)
		throw ("Error");

	if (BitField.GetBit(Elem) == 1)
		return 1;
	else
		return 0;
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	if (Elem < 0)
		throw ("Error");
	if (Elem > MaxPower)
		throw ("Error");

	BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	if (Elem < 0)
		throw ("Error");
	if (Elem > MaxPower)
		throw ("Error");

	BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
	BitField = s.BitField;
	MaxPower = s.MaxPower;
  return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
	if (MaxPower != s.MaxPower)
		return 0;
	else if (BitField != s.BitField)
		return 0;
	else
		return 1;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	if (BitField == s.BitField)
		return 0;
	else
		return 1;
}

TSet TSet::operator+(const TSet &s) // объединение
{
	if (MaxPower >= s.MaxPower)
	{
		TSet Temp(MaxPower);
		Temp.BitField = BitField | s.BitField;
		return Temp;
	}
	else
	{
		TSet Temp(s.MaxPower);
		Temp.BitField = BitField | s.BitField;
		return Temp;
	}
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	TSet Temp(*this);
	if (Temp.IsMember(Elem) != 1)
		Temp.InsElem(Elem);
	return Temp;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	TSet Temp(*this);
	if (Temp.IsMember(Elem) == 1)
		Temp.DelElem(Elem);
	return Temp;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	if (MaxPower >= s.MaxPower)
	{
		TSet Temp(s.MaxPower);
		Temp.BitField = BitField & s.BitField;
		return Temp;
	}
	else
	{
		TSet Temp(MaxPower);
		Temp.BitField = BitField & s.BitField;
		return Temp;
	}
}

TSet TSet::operator~(void) // дополнение
{
	BitField = ~BitField;
	TSet Temp(BitField);
	return Temp;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	int i;
	cin >> i;
	for (; i > -1; cin >> i)
		s.BitField.SetBit(i);
	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	cout << "{";
	for (int i = 0; i < s.MaxPower; i++)
		cout << s.BitField.GetBit(i);
	cout << "}\n";
	return ostr;
}
