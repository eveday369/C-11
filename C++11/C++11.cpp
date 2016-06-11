#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <array>
#include <memory>
#include <functional>

using namespace std;

// struct
struct Person {
	int age;
	char* name[10];
};

// class
class CPerson
{
public:
	CPerson() :age(1), name("anonymous") {}
	CPerson(int age, string name) :age(age), name(name) {}
	~CPerson() {};
public:
	int GetAge() { return age; }
	string GetName() { return name; }
private:
	int age;
	string name;
};

template<typename T, typename F>
auto execute(const T& value, F func) -> decltype(func(value))
{
	return func(value);
}

string number2String(const int i)
{
	switch (i)
	{
	case 1:
		return "one";
		break;
	case 2:
		return "two";
		break;
	case 3:
		return "three";
		break;
	case 4:
		return "four";
		break;
	default:
		return "unknown";
	}
}

void Foo(int& i)
{
	cout << "passed value: " << i << endl;
}

void Foo(const int& i)
{
	cout << "passed value: " << i << endl;
}

void ForwardThis(int&& i)
{
	Foo(i);
}

int main(int argc, char* argv[])
{
	cout << "auto type" << endl;
	// char* type
	auto name = "JohnL";
	cout << name << endl;

	// int type
	auto iNum = 1;
	cout << iNum << endl;

	// pointer
	auto* piNum = &iNum;
	cout << *piNum << endl;

	// reference
	auto& riNum = iNum;
	cout << riNum << endl;
	riNum = 10;
	cout << riNum << endl;
	cout << *piNum << endl;

	// object type
	auto* p1 = new Person;
	auto* p2 = new CPerson;

	cout << "Age : " << p2->GetAge() << endl;
	cout << endl;

	//
	// uniform initializer
	//
	vector<CPerson> vec
	{
		{21, "Smith"}, {39, "John"}, {23, "Mary"}, {45, "Ted"}, {29, "±Ë¡ÿøµ"}
	};

	cout << "range based for" << endl;

	//
	// range based for
	//
	for (auto i : vec)
	{
		cout << "Name :" << i.GetName().data() << " Age :" << i.GetAge() << endl;
	}

	cout << endl << "for_each" << endl;;
	
	//
	// for_each
	//
	for_each(vec.begin(), vec.end(), [](CPerson p)
	{
		cout << "Name :" << p.GetName().data() << " Age :" << p.GetAge() << endl;
	});

	cout << endl << "decltype" << endl;

	cout << execute(3, number2String) << endl;

	//
	// array
	//
	cout << endl << "std::array" << endl;
	array<Person, 5> person =
	{
		Person{ 21, "Smith" }, Person{ 39, "John" }, Person{ 23, "Mary" }, Person{ 45, "Ted" }, Person{ 29, "±Ë¡ÿøµ" }
	};

	for_each(person.begin(), person.end(), [](Person p)
	{
		cout << "Name :" << *p.name << " Age :" << p.age << endl;
	});

	//
	// smart pointer
	//
	cout << endl << "smart pointer" << endl;
	// unique_ptr
	unique_ptr<CPerson> pp1(new CPerson{ 21, "Smith"});
	unique_ptr<CPerson> pp2 = move(pp1);

	cout << "unique_ptr" << endl;
	cout << pp2->GetAge() << pp2->GetName() << endl << endl;
	pp2.reset();
	pp1.reset();

	// shared_ptr, weak_ptr
	shared_ptr<Person> sp1(new Person{ 39, "John" });
	shared_ptr<Person> sp2 = move(sp1);
	weak_ptr<Person> wp1 = sp2;
	{
		shared_ptr<Person> sp3 = wp1.lock();
		cout << "weak_ptr->" << *sp3->name << endl;
	} // sp3 ∆ƒ±´

	cout << endl << "shared_ptr" << endl;
	cout << sp2->age << *sp2->name << endl << endl;;
	sp2.reset();
	sp1.reset();

	//
	// lambda
	//
	[](string hello) {cout << endl << "hello " << hello << endl; }("world");

	array<int, 10> intList= { 1,2,3,4,5,6,7,8,9,10 };
	int evenSum = 0, oddSum = 0;
	for_each(intList.begin(), intList.end(), [&](int i)
	{
		if (i % 2 == 0)
			evenSum += i;
		else
			oddSum += i;
	});
	cout << "sum of evens :" << evenSum << endl;
	cout << "sum of odds :" << oddSum << endl << endl;

	auto ShowArray = [=]()
	{
		for_each(intList.begin(), intList.end(), [](int n)
		{
			cout << n << ' ';
		});
		cout << endl;
	};

	ShowArray();

	sort(intList.begin(), intList.end(), greater<int>());
	auto ShowSort = [=]()
	{
		for_each(intList.begin(), intList.end(), [](int n)
		{
			cout << n << ' ';
		});
		cout << endl;
	};

	ShowSort();
	ShowArray();

	//
	// L-Value, R-Value
	//
	int a = 10;
	int&& ra = 20;

	cout << "Original L-Value " << a << ", Reference :" << ra << endl;
	ra = a;
	cout << "Modified L-Value " << a << ", Reference :" << ra << endl;

	//
	// perfect forwarding
	//
	int aa = 1;
	ForwardThis(move(aa));
	ForwardThis(move(1));

	return 0;
}