#include "BookManager.hpp"
#include "maplist.hpp"
#include "error.hpp"
#include <iostream>

int main() {
    BookManager bm;
    bm.select("123456");
    bm.modify("apple|pear", 3);
    bm.modify("12345", 0);
    bm.modify("apple and pear", 1);
    bm.modify("Granthy", 2);
    bm.modify("123.99", 4);
    bm.import("1314");
    bm.Show();
}