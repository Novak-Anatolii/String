#include<iostream>
#include<Windows.h>
using namespace std;

//#define STRING_BASICS
//#define CONSTRUCTOR_CHECK
#define OPERATORS_CHECK



class String;     // class deklaration обь€вление класса
ostream& operator<<(ostream& os, const String& obj);

class String      // class deklaration обь€вление класса:
{
	int	 size;	//размер строки в байтах.
	char* str;	//адрес строки в динамической пам€ти
public:
	int get_size() const;
	const char* get_str() const;
	char* get_str();
	void set_size(int size);

	//			Constructors:
	String(int size = 80);
	String(const char str[]);
	String(const String& other);
	~String(); // деструктор

	//			Operators:
	String& operator=(const String& other);

	const char& operator[](int i) const;
	char& operator[](int i);

	//			Methods:
	int StrLen(char const* str) const;
	String& to_upper();
	String& to_lower();
	String& shrink();
	String& remove_spaces();
	bool is_palindrome() const;
	bool is_number()const;
	int to_int()const;
	void print();
};

//class definition - определение класса:

int String::get_size() const
{
	return size;
}
const char* String::get_str() const
{
	return str;
}
char* String::get_str()
{
	return str;
}
void String::set_size(int size)
{
	if (size > 0)
	{
		this->size = size;
	}
	else
	{
		this->size = 80;
	}
}

//			Constructors:
String::String(int size)
{
	set_size(size);	//«адаем размер строки
	this->str = new char[size] {};
	cout << "DefConstructor:\t" << this << endl;
}
String::String(const char str[])
{
	//cout << StrLen(str) << endl;
	this->size = StrLen(str) + 1;
	this->str = new char[size] {};
	for (int i = 0; str[i]; i++)this->str[i] = str[i];
	cout << "Constructor:\t" << this << endl;
}
String::String(const String& other)
{
	this->size = other.size;
	this->str = new char[size] {};
	for (int i = 0; other.str[i]; i++)this->str[i] = other.str[i];
	cout << "CopyConstructor:" << this << endl;
}
String::~String()
{
	delete[] this->str;
	cout << "Destructor:\t" << this << endl;
}

//			Operators:
String& String::operator=(const String& other)
{
	cout << "CopyAssignment:" << this << endl;
	if (this == &other)return *this;
	delete[] this->str;
	this->size = other.size;
	this->str = new char[size] {};
	for (int i = 0; other.str[i]; i++)this->str[i] = other.str[i];
	return *this;
}

const char& String::operator[](int i) const
{
	return str[i];
}

char& String::operator[](int i)//i - index
{
	return str[i];
}

//			Methods:
int String::StrLen(char const* str) const
{
	int i = 0;
	for (; str[i]; i++);
	return i;
}
String& String::to_upper()
{
	for (int i = 0; str[i]; i++)
	{
		if (
			str[i] >= 'a' && str[i] <= 'z' ||
			str[i] >= 'а' && str[i] <= '€'
			)
			str[i] -= 32;
	}
	return *this;
}
String& String::to_lower()
{
	for (int i = 0; str[i]; i++)
	{
		if (
			str[i] >= 'A' && str[i] <= 'Z' ||
			str[i] >= 'ј' && str[i] <= 'я'
			)
			str[i] += 32;
	}
	return *this;
}
String& String::shrink()
{
	for (int i = 0; str[i]; i++)
	{
		while (str[i] == ' ' && str[i + 1] == ' ')
		{
			for (int j = i; str[j]; j++)
			{
				str[j] = str[j + 1];
			}
		}
	}
	return *this;
}
String& String::remove_spaces()
{
	for (int i = 0; str[i]; i++)
	{
		while (str[i] == ' ')
		{
			for (int j = i; str[j]; j++)
			{
				str[j] = str[j + 1];
			}
		}
	}
	return *this;
}
bool String::is_palindrome() const
{
	String buffer = *this;
	buffer.to_lower().remove_spaces();
	int size = buffer.StrLen(buffer.get_str());
	cout << buffer << endl;
	for (int i = 0; i < size / 2; i++)
	{
		if (buffer.str[i] != buffer.str[size - 1 - i])
		{
			return false;
		}
	}
	return true;
}
bool String::is_number()const
{
	/*int i = 0;
	if (str[0] == '+' || str[0] == '-')i = 1;*/
	//		Ternary conditional operator:
	//		(condition) ? expression1 : expression2;
	//≈сли условие вернуло true, то оператор вернет expression1, 
	//≈сли условие вернуло false, то оператор вернет expression2.
	for (int i = (str[0] == '+' || str[0] == '-') ? 1 : 0; str[i]; i++)
	{
		if (str[i]<'0' || str[i]>'9')return false;
	}
	return true;
}
int String::to_int()const
{
	int number = 0;
	if (this->is_number())
	{
		bool minus = (str[0] == '-') ? true : false;
		for (int i = minus ? 1 : 0; str[i]; i++)
		{
			number *= 10;	//—двигаем число, дл€ того чтобы освободить место дл€ следующего разр€да.
			number += str[i] - 48;//записываем в число значение следующего разр€да.
		}
		if (minus)number = -number;
	}
	return number;
}
void String::print()
{
	cout << "str:" << str << endl;
	cout << "size:" << size << endl;
}

ostream& operator<<(ostream& os, const String& obj)
{
	return os << obj.get_str();
}

istream& operator>>(istream& is, String& obj)
{
	return is >> obj.get_str();
}

String operator+(const String& left, const String& right)
{
	String res = left.get_size() + right.get_size() - 1;
	for (int i = 0; i < left.get_size() - 1; i++)
		//res.get_str()[i] = left.get_str()[i];
		res[i] = left[i];
	for (int i = 0; i < right.get_size() - 1; i++)
		//res.get_str()[i + left.get_size() - 1] = right.get_str()[i];
		res[i + left.get_size() - 1] = right.operator[](i);
	return res;
}

void InputLine(char str[], const int n)
{
	SetConsoleCP(1251);
	cin.getline(str, n);
	SetConsoleCP(866);
}

void main()
{
	setlocale(LC_ALL, "");
#ifdef STRING_BASICS
	/*char str[] = { 'H', 'e', 'l', 'l', 'o', '\0' };
	cout << str << endl;*/

	/*char str[] = "Hello";
	cout << str << endl;*/

	const int n = 20;
	char str[n] = {};
	cout << "Input line: ";
	//cin >> str;
	InputLine(str, n);
	cout << str << endl;
#endif // STRING_BASICS

#ifdef CONSTRUCTOR_CHECK
	String str;	//Default constructor
	str.print();
	cout << str << endl;

	String str1 = "Hello";
	cout << str1 << endl;
	//cout << typeid("Hello").name() << endl;

	String str2 = str1;		//Copy constructor
	cout << str2 << endl;

	str1 = str1;	//Copy assignment
	cout << str1 << endl;
#endif // CONSTRUCTOR_CHECK


#ifdef OPERATORS_CHECK
	String str1 = "ѕривет";
	String str2 = "ћир";
	String str3 = str1 + " " + str2;
	cout << str3 << endl;
	cout << str3.to_upper() << endl;
	/*for (int i = 0; i < 256; i++)
	{
	cout << i << "\t" << (char)i << endl;
	}*/
	//cout << 'A' - 'a' << endl;

	String str = "јргентина манит негра";
	//cout << "¬ведите строку: ";
	//SetConsoleCP(1251);
	//cin.getline(str.get_str(), str.get_size());
	//SetConsoleCP(866);
	//cout << str << endl;
	////cout << str.shrink() << endl;
	//cout << str.is_palindrome() << endl;
	//cout << str.is_number() << endl;
	//cout << str.to_int()*2 << endl;
	for (int i = 0; str[i]; i++)cout << str[i] << "  "; cout << endl;
	str[5] = '@';
	cout << str << endl;
#endif
}