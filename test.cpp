#define _CRT_SECURE_NO_WARNINGS 
#include<iostream>
using namespace std;

namespace yiming
{
	class string
	{
	public:
		typedef char* iterator;
		typedef const char* const_iterator;
		iterator begin()
		{
			return _str;
		}

		iterator end()
		{
			return _str + _size;
		}

		const_iterator begin() const
		{
			return _str;
		}

		const_iterator end() const
		{
			return _str + _size;
		}

		string(const char* str = "")
			:_size(strlen(str))
			, _capacity(_size)
		{
			cout << "string(char* str)-构造" << endl;
			_str = new char[_capacity + 1];
			strcpy(_str, str);
		}

		// 拷贝构造
		string(const string& s)
			:_str(nullptr)
		{
			cout << "string(const string& s) -- 拷贝构造" << endl;
			reserve(s._capacity);
			for (auto ch : s)
			{
				push_back(ch);
			}
		}

		void swap(string& tmp)
		{
			std::swap(_str, tmp._str);
			std::swap(_size, tmp._size);
			std::swap(_capacity, tmp._capacity);
		}

		// 移动构造
		string(string&& s)
		{
			cout << "string(string&& s) -- 移动构造" << endl;
			swap(s);
		}

		string& operator=(const string& s)
		{
			cout << "string& operator=(const string& s) -- 拷贝赋值" << endl;
			if (this != &s)
			{
				_str[0] = '\0';
				_size = 0;
				reserve(s._capacity);
				for (auto ch : s)
				{
					push_back(ch);
				}
			}
			return *this;
		}

		// s4 = yiming::string("yyyyy");
		string& operator=(string&& s)
		{
			cout << "string& operator=(string&& s) -- 移动赋值" << endl;

			swap(s);
			return *this;
		}

		void reserve(size_t n)
		{
			if (n > _capacity)
			{
				char* tmp = new char[n + 1];
				if (_str)
				{
					strcpy(tmp, _str);
					delete[] _str;
				}
				_str = tmp;
				_capacity = n;
			}
		}

		void push_back(char ch)
		{
			if (_size >= _capacity)
			{
				size_t newcapacity = _capacity == 0 ? 4 : _capacity *
					2;
				reserve(newcapacity);
			}
			_str[_size] = ch;
			++_size;
			_str[_size] = '\0';
		}

		char& operator[](size_t pos)
		{
			//assert(pos < _size);
			return _str[pos];
		}

		string& operator+=(char ch)
		{
			push_back(ch);
			return *this;
		}
		const char* c_str() const
		{
			return _str;
		}

		size_t size() const
		{
			return _size;
		}



		bool operator<(const string& s) const
		{
			return strcmp(_str, s._str) < 0;
		}
	private:
		char* _str = nullptr;
		size_t _size = 0;
		size_t _capacity = 0;
	};

	string addStrings(string num1, string num2)
	{
		string str;
		cout << &str << endl;
		int end1 = num1.size() - 1, end2 = num2.size() - 1;
		int next = 0;
		while (end1 >= 0 || end2 >= 0)
		{
			int val1 = end1 >= 0 ? num1[end1--] - '0' : 0;
			int val2 = end2 >= 0 ? num2[end2--] - '0' : 0;
			int ret = val1 + val2 + next;
			next = ret / 10;
			ret = ret % 10;
			str += ('0' + ret);
		}
		if (next == 1)
			str += '1';
		reverse(str.begin(), str.end());

		cout << "******************************" << endl;

		return str;
	}
}


//int main()
//{
//	//yiming::string s1("xxxxx");
//	//// 拷贝构造
//	//yiming::string s2 = s1;
//	//// 构造+移动构造，优化后直接构造
//	//yiming::string s3 = yiming::string("yyyyy");
//
//	//// 移动构造
//	//yiming::string s4 = move(s1);
//
//	//cout << "******************************" << endl;
//
//	//yiming::string s5("yyyyyyyyyyyyyyyyy");
//	//s3 = s5;
//	//s4 = yiming::string("yyyyy");
//
//	//const string& r1 = "1111111";
//
//	/*yiming::string ret = yiming::addStrings("11111", "2222");
//	cout << &ret << endl;
//	cout << ret.c_str() << endl;*/
//
//	yiming::string ret;
//	ret = yiming::addStrings("11111", "2222");
//	//cout << &ret << endl;
//	cout << ret.c_str() << endl;
//
//	return 0;
//}


#include<list>
#include<set>




 由于引用折叠限定，f1实例化以后总是一个左值引用
template<class T>
void f1(T& x)
{}

// 由于引用折叠限定，f2实例化后可以是左值引用，也可以是右值引用，万能引用
template<class T>
void f2(T&& x)
{}

int main()
{
	typedef int& lref;
	//typedef int&& rref;
	using rref = int&&;

	int n = 0;

	lref& r1 = n; // r1 的类型是 int&
	lref&& r2 = n; // r2 的类型是 int&
	rref& r3 = n; // r3 的类型是 int&
	rref&& r4 = 1; // r4 的类型是 int&&

	// 没有折叠->实例化为void f1(int& x)
	f1<int>(n);
	//f1<int>(0); // 报错

	// 折叠->实例化为void f1(int& x)
	f1<int&>(n);
	//f1<int&>(0); // 报错

	// 折叠->实例化为void f1(int& x)
	f1<int&&>(n);
	//f1<int&&>(0); // 报错

	// 折叠->实例化为void f1(const int& x)
	f1<const int&>(n);
	f1<const int&>(0);

	// 折叠->实例化为void f1(const int& x)
	f1<const int&&>(n);
	f1<const int&&>(0);

	// 没有折叠->实例化为void f2(int&& x)
	//f2<int>(n); // 报错
	f2<int>(0);

	// 折叠->实例化为void f2(int& x)
	f2<int&>(n);
	//f2<int&>(0); // 报错

	// 折叠->实例化为void f2(int&& x)
	//f2<int&&>(n); // 报错
	f2<int&&>(0);

	return 0;
}