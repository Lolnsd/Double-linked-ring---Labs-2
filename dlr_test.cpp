#include <iostream>
#include <stdlib.h>
#include <string>
#include <map>
#include "dlr_test.h"

using namespace std;

#define cprint(a) cout<<a

int main()
{
    //If no errors, program should show nothing for these methods
    dlr<int, string> ring;
    test_size<int, string>(ring, 0);
    test_empty<int, string>(ring, true);
    test_push<int, string>(ring,1,"red", 1);
    test_push<int, string>(ring,2,"blue", 2);
    test_push<int, string>(ring,3,"yellow", 3);
    test_begin<int, string>(ring, 1, "red");
    test_cbegin<int, string>(ring, 1, "red");
    test_find<int, string>(ring,2,"blue", 1, true);
    test_find<int, string>(ring,4,"green",1,false);
    test_size<int, string>(ring, 3);
    test_empty<int, string>(ring, false);
    dlr<int, string>::iterator it = ring.find(2);
    test_value<int, string>(ring, it, 2, "blue");
    test_insert<int, string>(ring, it, 4, "green", 4);
    test_erase<int, string>(ring, 3,1,"red", 1, 3);
    test_pop<int, string>(ring, 1, "red", 2);
    testClearAll<int, string>(ring);





    cout << endl;
//ADDITIONAL FUNCTIONS

///////////////////////////////////////////////////////////////////
////////////////////////   <string, int>   ////////////////////////
///////////////////////////////////////////////////////////////////

    cout << "Test for <string, int>" << endl;
    dlr<string, int> a, b;

    a.push("apple", 1);
    a.push("banana", 2);
    a.push("pear", 3);
    a.push("pineapple", 4);
    a.push("grapes", 5);

    b = filter<string,int>(a,[](const string &str){return str.size() > 3;});

    cprint("a:");
    a.print();

    b.pop();
    b.pop();

    cprint("b:");
    b.print();

    dlr<string, int> result1;
    result1 = join<string, int>(a, b);

    cprint("result of joining a and b is: ");
    result1.print();
    cout << endl;

//////////////////////////////////////////////////////////////////
/////////////////////////   <int, int>   /////////////////////////
//////////////////////////////////////////////////////////////////

    cout << "Test for <int, int>" << endl;
    dlr<int, int> c, d;

    c.push(1, 101);
    c.push(2, 202);
    c.push(3, 303);
    c.push(4, 404);
    c.push(5, 505);

    d.push(1, 11);
    d.push(2, 22);
    d.push(3, 33);
    d.push(4, 44);
    d.push(5, 55);

    cprint("c:");
    c.print();

    d.pop();
    d.pop();

    cprint("d:");
    d.print();

    dlr<int, int> result2;
    result2 = join<int, int>(c, d);

    cprint("result of joining c and d is: ");
    result2.print();
    cout << endl;

///////////////////////////////////////////////////////////////////
////////////////////////   <int, string>   ////////////////////////
///////////////////////////////////////////////////////////////////

    cout << "Test for <int, string>" << endl;
    dlr<int, string> e, f;

    e.push(1, "hammer");
    e.push(2, "drill");
    e.push(3, "screwdriver");
    e.push(4, "crowbar");
    e.push(5, "shovel");

    cprint("e:");
    e.print();

    f.push(1, "axe");
    f.push(2, "mallet");
    f.push(3, "saw");
    f.push(4, "chisel");
    f.push(5, "pickaxe");

    f.pop();
    f.pop();

    cprint("f:");
    f.print();

    dlr<int, string> result3;
    result3 = join<int, string>(e, f);

    cprint("result of joining e and f is: ");
    result3.print();
    cout << endl;

////////////////////////////////////////////////////////////////////
///////////////////////   <string, string>   ///////////////////////
////////////////////////////////////////////////////////////////////

    cout << "Test for <string, string>" << endl;
    dlr<string, string> g, h;

    g.push("uno", "hammer");
    g.push("dos", "drill");
    g.push("tres", "screwdriver");
    g.push("cuatro", "crowbar");
    g.push("cinco", "shovel");

    cprint("g:");
    g.print();

    h.push("uno", "axe");
    h.push("dos", "mallet");
    h.push("tres", "saw");
    h.push("cuatro", "chisel");
    h.push("cinco", "pickaxe");

    h.pop();
    h.pop();

    cprint("h:");
    h.print();

    dlr<string, string> result4;
    result4 = join<string, string>(g, h);

    cprint("result of joining g and h is: ");
    result4.print();
    cout << endl;





    //Unique method
    
    cout << "Test for unique method" << endl;
    dlr<string, string> source;
    source.push("Ball", "black");
    source.push("Stick", "yellow");
    source.push("Ball", "blue");
    source.push("Flag","green");
    source.push("Light", "red");
    source.push("Stick", "brown");
    source.push("Flag","orange");
    
    dlr<string, string> output = unique<string, string>(source,[](const string &str, const string &i1, const string &i2) {
        return i1 + "+" + i2;
    });

    cprint("source:");
    source.print();

    cprint("output:");
    output.print();
    cout << endl;

    return 0;
}