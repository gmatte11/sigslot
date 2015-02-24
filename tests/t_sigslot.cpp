#include <sigslot/sigslot.h>
#include <iostream>
#include <string>

namespace ss = sigslot;

void say_hello()
{
    std::cout << "Hello, World!" << std::endl;
}

int main(int argc, char *argv[])
{
    ss::signal<bool> s1;
    ss::signal<std::string> s2;
    ss::signal<> s3;

    s1.connect([] (bool b) { std::cout << "It is " << std::string((b) ? "true" : "false") << std::endl; });
    s2.connect([] (const std::string & s) { std::cout << "str = " << s << std::endl; });
    s3.connect(&say_hello);

    ss::emit(s1, true);
    ss::emit(s1, false);

    s2.emit("Foo");
    s2.emit("Bar is better than Foo!");

    ss::emit(s3);

    return 0;
}
