#include "child.h"
#include <string>
#include <iostream>
using namespace std;
Child::Child() 
{

}

Child::Child(string first)
{
	first_ = first;
}

Child::Child(string first, string last)
{
	first_ = first;
	last_ = last;
}
Child::Child(string first, string last, int age)
{
	first_ = first;
	last_ = last;
	age_ = age;
}

Child::Child(const Child& child1)
{

	first_ = child1.first_;
	last_ = child1.last_;
	age_ = child1.age_;
}

Child::~Child()
{

}

string Child::get_first_() const
{
	return this->first_;
}

string Child::get_last_() const
{
	return this->last_;
}

int Child::get_age_() const
{
	return this->age_;
}

void Child::set_first_(string first)
{
	this->first_ = first;
}

void Child::set_last_(string last)
{
	this->last_ = last;
}

void Child::set_age_(int age)
{
	this->age_ = age;
}

bool Child::operator<(const Child& child1) const
{
	//comapares in order of lastname, firstname, and then age
	if (last_ < child1.last_)
	{
		return true;
	}
	else if (last_ == child1.last_)
	{
		if (first_ == child1.first_)
		{
			if (age_ < child1.age_)
			{
				return true;
			}
		}
		else if (first_ < child1.first_)
		{
			return true;
		}
	}
	return false;
}

bool Child::operator>(const Child& child1) const
{
	//comapares in order of lastname, firstname, and then age
	if (last_ > child1.last_)
	{
		return true;
	}
	else if (last_ == child1.last_)
	{
		if (first_ == child1.first_)
		{
			if (age_ > child1.age_)
			{
				return true;
			}
		}
		else if (first_ > child1.first_)
		{
			return true;
		}
	}
	return false;
}

bool Child::operator==(const Child& child1) const
{
	if ((this->last_ == child1.get_last_()) && (this->first_ == child1.get_first_()) && (this->age_ == child1.get_age_()))
	{
		return true;
	}
	return false;
}

bool Child::operator!=(const Child& child1) const
{
	return !(*this == child1);
}

Child Child::operator=(const Child& child1)
{
	this->last_ = child1.last_;
	this->first_ = child1.first_;
	this->age_ = child1.age_;
	return *this;
}

ostream& operator<<(ostream& out_stream, const Child& child1)
{
	cout << child1.first_ << child1.last_ << child1.age_;
	return out_stream;
}

istream& operator>>(istream& in_stream, Child& child1)
{
	in_stream >> child1.first_ >> child1.last_ >> child1.age_;
	return in_stream;
}
