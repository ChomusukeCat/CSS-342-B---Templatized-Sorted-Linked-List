/*
 * CSS 342 B
 * Child class is a class that stores string and int variables, meant to be used in List342
 * Steven Chau
 * November 10, 2020
 */
#pragma once
#include <string>
using namespace std;
class Child
{
public:
    Child();
    Child(string first);
    Child(string first, string last);
    Child(string first, string last, int age);
    Child(const Child& child1);
    ~Child();

    int get_age_() const;
    string get_first_() const;
    string get_last_() const;
    void set_first_(string first);
    void set_last_(string last);
    void set_age_(int age);

    bool operator<(const Child& child1) const;
    bool operator>(const Child& child1) const;
    bool operator==(const Child& child1) const;
    bool operator!=(const Child& child1) const;
    Child operator=(const Child& child1);

    friend ostream& operator<<(ostream& out_stream, const Child& child1);
    friend istream& operator>>(std::istream& in, Child& child1);

private:
    string first_ = "";
    string last_ = "";
    int age_ = 0;
};