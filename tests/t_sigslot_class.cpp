#include <sigslot/sigslot.h>

#include <iostream>

using sigslot::signal;
using sigslot::emit;

class A
{
public:
    A() = delete;
    A(const A &) = delete;
    A & operator=(const A &) = delete;

    A(const std::string & s);
    std::string _s;
};

A::A(const std::string & s) : _s(s) {}

std::ostream & operator<<(std::ostream & os, const A & a)
{
    return (os << a._s);
}

class B
{
public:
    void foo(const std::string & s);
    void bar(const A & a);

    void on_foo(signal<std::string>::slot fct);
    void on_bar(signal<const A &>::slot fct); 

private:
    signal<std::string> sig_foo;
    signal<const A &> sig_bar;
};

void B::foo(const std::string & s)
{
    emit(sig_foo, s);
}

void B::bar(const A & a)
{
    sig_bar.emit(a);
}

inline void B::on_foo(signal<std::string>::slot fct)
{
    sig_foo.connect(fct);
}

inline void B::on_bar(signal<const A &>::slot fct)
{
    sig_bar.connect(fct);
}

int main(int argc, char *argv[])
{
    auto printer = [] (const auto & val) { std::cout << val << std::endl; };

    std::string s("No, I am your father!");
    A a("He told me you killed him.");

    B b;
    b.on_foo(printer);
    b.on_bar(printer);

    b.bar(a);
    b.foo(s);

    return 0;
}
