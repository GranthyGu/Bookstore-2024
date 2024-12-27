
#include "maplist.hpp"
#include "error.hpp"
#include <iostream>
#include <climits>

int main() {
    maplist<int> bl("file_of_heads", "file_of_values");
    bl.openfile();
    int n;
    std::cin >> n;
    std::string operation;
    std::string index;
    int value;
    for (int i = 0; i < n; i++) {
        std::cin >> operation;
        if (operation == "insert") {
            std::cin >> index;
            std::cin >> value;
            bl.insert(index, value);
        }
        if (operation == "delete") {
            std::cin >> index;
            std::cin >> value;
            bl.remove(index, value);
        }
        if (operation == "find") {
            std::cin >> index;
            Node<int> minimal(index, 0);
            Node<int> maximal(index, INT_MAX);
            std::vector<Node<int>> tmp = bl.Find(maximal, minimal);
            for (int i = 0; i < tmp.size(); i++)
            {
                std::cout << tmp[i].value << ' ';
            }
            if (tmp.size() == 0)
            {
                std::cout << "null";
            }
            std::cout << std::endl;
        }
    }
    return 0;
}