#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <climits>
#include <string>
#include <algorithm>
using namespace std;

const int maxN = 500;

struct Node {
public:
    char index[60];
    int value;
    Node() : value(-1) {}
    Node(string str, int value) : value(value) {
        for (int i = 0; i < str.length(); i++) {
            index[i] = str[i];
        }
        for (int i = str.length(); i < 60; i++)
        {
            index[i] = '\0';
        }
    }
    bool operator<(const Node& other) {
        for (int i = 0; i < 60; i++) {
            if (index[i] != other.index[i]) {
                return index[i] < other.index[i];
            }
        }
        return value < other.value;
    }
    bool operator>(const Node& other) {
        for (int i = 0; i < 60; i++) {
            if (index[i] != other.index[i]) {
                return index[i] > other.index[i];
            }
        }
        return value > other.value;
    }
    bool operator==(const Node& other) const {
        for (int i = 0; i < 60; i++) {
            if (index[i] != other.index[i]) {
                return false;
            }
        }
        return (value == other.value);
    }
    Node& operator=(const Node& other) {
        for (int i = 0; i < 60; i++) {
            index[i] = other.index[i];
        }
        value = other.value;
        return *this;
    }
    void writetofile(fstream& File) {
        for (int i = 0; i < 60; i++) {
            File.write(reinterpret_cast<char *> (&index[i]), sizeof(char));
        }
        File.write(reinterpret_cast<char *>(&value), sizeof(int));
    }
    void readfromile(fstream& File) {
        for (int i = 0; i < 60; i++) {
            File.read(reinterpret_cast<char *> (&index[i]), sizeof(char));
        }
        File.read(reinterpret_cast<char *>(&value), sizeof(int));
    }
};

struct Head_Node {
public:
    int size;
    long addrofvalues;
    long nextad;
    long adrofiteself;
    Node nodeofhead;
    Head_Node() : size(0), addrofvalues(-1), nextad(-1), adrofiteself(-1) {}
    Head_Node(int size, long add1, long add2, long add3, Node node) : size(size), addrofvalues(add1), nextad(add2), adrofiteself(add3), nodeofhead(node) {}
    void writeto(fstream& File_) {
        File_.write(reinterpret_cast<char *> (&size), sizeof(int));
        File_.write(reinterpret_cast<char *> (&addrofvalues), sizeof(long));
        File_.write(reinterpret_cast<char *> (&nextad), sizeof(long));
        File_.write(reinterpret_cast<char *> (&adrofiteself), sizeof(long));
        nodeofhead.writetofile(File_);
    }
    void readfrom(fstream& File_) {
        File_.read(reinterpret_cast<char *> (&size), sizeof(int));
        File_.read(reinterpret_cast<char *> (&addrofvalues), sizeof(long));
        File_.read(reinterpret_cast<char *> (&nextad), sizeof(long));
        File_.read(reinterpret_cast<char *> (&adrofiteself), sizeof(long));
        nodeofhead.readfromile(File_);
    }
    Head_Node operator=(const Head_Node& other) {
        size = other.size;
        addrofvalues = other.addrofvalues;
        nextad = other.nextad;
        adrofiteself = other.adrofiteself;
        nodeofhead = other.nodeofhead;
        return other;
    }
};

class maplist {
private:
    string file_of_values;
    string file_of_heads;
    fstream File_v;
    fstream File_h;
public:
    maplist(string str1, string str2) : file_of_heads(str1), file_of_values(str2) {}
    void openfile() {
        File_v.open(file_of_values, ios::in | ios::out | ios::binary);
        if (!File_v) {
            File_v.close();
            File_v.clear(); 
            File_v.open(file_of_values, ios::out | ios::binary);
            File_v.close();
            File_v.open(file_of_values, ios::in | ios::out | ios::binary);
        }
        File_h.open(file_of_heads, ios::in | ios::out | ios::binary);
        if (!File_h) {
            File_h.close();
            File_h.clear();
            File_h.open(file_of_heads, ios::out | ios::binary);
            File_h.close();
            File_h.open(file_of_heads, ios::in | ios::out | ios::binary);
        }       
    }
    void split_head_node(Head_Node& hn) {
        vector<Node> values(hn.size);
        File_v.seekg(hn.addrofvalues);
        File_v.read(reinterpret_cast<char*>(values.data()), sizeof(Node) * hn.size);
        Node head_node_of_new = values[hn.size / 2];
        vector<Node> newvalues(values.begin() + hn.size / 2, values.end());
        values.resize(hn.size / 2);
        File_v.seekp(0, ios::end);
        long adofnew = File_v.tellp();
        File_v.write(reinterpret_cast<char*>(newvalues.data()), sizeof(Node) * newvalues.size());
        Node c;
        for (int i = 0; i < maxN - newvalues.size(); i++) {
            File_v.write(reinterpret_cast<char *>(&c), sizeof(Node));
        }
        File_v.seekp(hn.addrofvalues + sizeof(Node) * values.size());
        for (int i = 0; i < maxN - values.size(); i++) {
            File_v.write(reinterpret_cast<char *>(&c), sizeof(Node));
        }
        File_h.seekp(0, ios::end);
        long adr_of_newhn = File_h.tellp();
        Head_Node newhd(hn.size - hn.size / 2, adofnew, hn.nextad, adr_of_newhn, head_node_of_new);
        newhd.writeto(File_h);
        hn.size = hn.size / 2;
        hn.nextad = adr_of_newhn;
        File_h.seekp(hn.adrofiteself);
        hn.writeto(File_h);
    }
    void insert(string index, int value) {
        File_h.seekg(0, ios::end);
        if (File_h.tellg() == 0) {
            Node tmpp(index, value);
            Head_Node tmp(1, 0, -1, 0, tmpp);
            tmp.writeto(File_h);
            tmpp.writetofile(File_v);
            for (int i = 0; i < maxN - 1; i++) {
                Node t;
                t.writetofile(File_v);
            }
        } else {
            File_h.seekg(0, ios::beg);
            Node tmpp(index, value);
            bool found = false;
            Head_Node hn;
            Head_Node hn_before;
            hn.nextad = 0;
            int num = 0;
            while (true) {
                num++;
                hn_before = hn;
                hn.readfrom(File_h);
                if (hn.nodeofhead > tmpp) {
                    found = true;
                    break;
                }
                if (hn.nextad == -1) {
                    break;
                } else {
                    File_h.seekg(hn.nextad);
                }
            }
            if (!found) {
                vector<Node> values(hn.size);
                File_v.seekg(hn.addrofvalues);
                File_v.read(reinterpret_cast<char*>(values.data()), sizeof(Node) * hn.size);
                if (find(values.begin(), values.end(), tmpp) != values.end()) {
                    return;
                } else {
                    hn.size++;
                    File_h.seekp(hn.adrofiteself);
                    hn.writeto(File_h);
                    int i;
                    for (i = 0; i < values.size(); i++) {
                        if (values[i] > tmpp) {
                            break;
                        }
                    }
                    values.insert(values.begin() + i, tmpp);
                    File_v.seekp(hn.addrofvalues);
                    File_v.write(reinterpret_cast<char*>(values.data()), sizeof(Node) * hn.size);
                    if (hn.size == maxN) {
                        split_head_node(hn);
                    }
                    return;
                }
            }
            if (num == 1 && found) {
                hn.nodeofhead = tmpp;
                hn.size++;
                File_h.seekp(hn.adrofiteself);
                hn.writeto(File_h);
                vector<Node> values(hn.size - 1);
                File_v.seekg(hn.addrofvalues);
                File_v.read(reinterpret_cast<char*>(values.data()), sizeof(Node) * (hn.size - 1));
                values.insert(values.begin(), tmpp);
                File_v.seekp(hn.addrofvalues);
                File_v.write(reinterpret_cast<char*>(values.data()), sizeof(Node) * hn.size);
                if (hn.size == maxN) {
                    split_head_node(hn);
                }
                return;
            } else {
                vector<Node> values(hn_before.size);
                File_v.seekg(hn_before.addrofvalues);
                File_v.read(reinterpret_cast<char*>(values.data()), sizeof(Node) * hn_before.size);
                if (find(values.begin(), values.end(), tmpp) != values.end()) {
                    return;
                } else {
                    hn_before.size++;
                    File_h.seekp(hn_before.adrofiteself);
                    hn_before.writeto(File_h);
                    int i;
                    for (i = 0; i < values.size(); i++) {
                        if (values[i] > tmpp) {
                            break;
                        }
                    }
                    values.insert(values.begin() + i, tmpp);
                    File_v.seekp(hn_before.addrofvalues);
                    File_v.write(reinterpret_cast<char*>(values.data()), sizeof(Node) * hn_before.size);
                    if (hn_before.size == maxN) {
                        split_head_node(hn_before);
                    }
                    return;
                }
            }
        }
    }

    void remove(string index, int value) {
        File_h.seekg(0, ios::end);
        if (File_h.tellg() == 0) {
            return;
        }
        Node c;
        File_h.seekg(0, ios::beg);
        Node tmpp(index, value);
        bool found = false;
        Head_Node hn;
        Head_Node hn_before;
        long hn_before_position = 0;
        hn.nextad = 0;
        int num = 0;
        while (true) {
            num++;
            hn_before_position = hn_before.adrofiteself;
            hn_before = hn;
            hn.readfrom(File_h);
            if (hn.nodeofhead > tmpp) {
                found = true;
                break;
            }
            if (hn.nextad == -1) {
                break;
            } else {
                File_h.seekg(hn.nextad);
            }
        }
        if (num == 1)
        {
            if (found) {
                return;
            } else {
                vector<Node> values(hn.size);
                File_v.seekg(hn.addrofvalues);
                File_v.read(reinterpret_cast<char*>(values.data()), sizeof(Node) * hn.size);
                auto it = find(values.begin(), values.end(), tmpp);
                if (it == values.end()) {
                    return;
                }
                if (it == values.begin())
                {
                    if (values.size() == 1)
                    {
                        File_h.close();
                        File_v.close();
                        File_h.open(file_of_heads, std::ios::out | std::ios::binary | std::ios::trunc);
                        File_v.open(file_of_values, std::ios::out | std::ios::binary | std::ios::trunc);
                        File_h.close();
                        File_v.close();
                        File_h.open(file_of_heads, ios::in | ios::out | ios::binary);
                        File_v.open(file_of_values, ios::in | ios::out | ios::binary);
                    } else {
                        hn.nodeofhead = values[1];
                        values.erase(it);
                        hn.size--;
                        File_h.seekp(hn.adrofiteself);
                        hn.writeto(File_h);
                        File_v.seekp(hn.addrofvalues);
                        File_v.write(reinterpret_cast<char*>(values.data()), sizeof(Node) * hn.size);
                        File_v.write(reinterpret_cast<char*>(&c), sizeof(Node));
                    }
                    return;
                } else {
                    values.erase(it);
                    hn.size--;
                    File_h.seekp(hn.adrofiteself);
                    hn.writeto(File_h);
                    File_v.seekp(hn.addrofvalues);
                    File_v.write(reinterpret_cast<char*>(values.data()), sizeof(Node) * hn.size);
                    File_v.write(reinterpret_cast<char*>(&c), sizeof(Node));
                    return;
                }
            }
        }
        if (!found)
        {
            vector<Node> values(hn.size);
            File_v.seekg(hn.addrofvalues);
            File_v.read(reinterpret_cast<char*>(values.data()), sizeof(Node) * hn.size);
            auto it = find(values.begin(), values.end(), tmpp);
            if (it == values.end()) {
                return;
            } 
            if (it == values.begin())
            {
                if (values.size() == 1)
                {
                    hn_before.nextad = hn.nextad;
                    File_h.seekp(hn_before.adrofiteself);
                    hn_before.writeto(File_h);
                } else {
                    hn.nodeofhead = values[1];
                    values.erase(it);
                    hn.size--;
                    File_h.seekp(hn.adrofiteself);
                    hn.writeto(File_h);
                    File_v.seekp(hn.addrofvalues);
                    File_v.write(reinterpret_cast<char*>(values.data()), sizeof(Node) * hn.size);
                    File_v.write(reinterpret_cast<char*>(&c), sizeof(Node));
                }
            }
            else {
                values.erase(it);
                hn.size--;
                File_h.seekp(hn.adrofiteself);
                hn.writeto(File_h);
                File_v.seekp(hn.addrofvalues);
                File_v.write(reinterpret_cast<char*>(values.data()), sizeof(Node) * hn.size);                    
                File_v.write(reinterpret_cast<char*>(&c), sizeof(Node));
            }
            return;
        }
        vector<Node> values(hn_before.size);
        File_v.seekg(hn_before.addrofvalues);
        File_v.read(reinterpret_cast<char*>(values.data()), sizeof(Node) * hn_before.size);
        auto it = find(values.begin(), values.end(), tmpp);
        if (it == values.end()) {
            return;
        } 
        if (it == values.begin())
        {
            if (values.size() == 1 && num == 2)
            {
                File_h.seekp(0, ios::beg);
                hn.adrofiteself = 0;
                hn.writeto(File_h);
                return;
            }
            
            if (values.size() == 1 && num >= 3)
            {
                File_h.seekg(hn_before_position);
                Head_Node tmp;
                tmp.readfrom(File_h);
                tmp.nextad = hn_before.nextad;
                File_h.seekp(hn_before_position);
                tmp.writeto(File_h);
                return;
            }
            hn_before.nodeofhead = values[1];
            values.erase(it);
            hn_before.size--;
            File_h.seekp(hn_before.adrofiteself);
            hn_before.writeto(File_h);
            File_v.seekp(hn_before.addrofvalues);
            File_v.write(reinterpret_cast<char*>(values.data()), sizeof(Node) * hn_before.size);
            File_v.write(reinterpret_cast<char*>(&c), sizeof(Node));
            return;
        }
        values.erase(it);
        hn_before.size--;
        File_h.seekp(hn_before.adrofiteself);
        hn_before.writeto(File_h);
        File_v.seekp(hn_before.addrofvalues);
        File_v.write(reinterpret_cast<char*>(values.data()), sizeof(Node) * hn_before.size);
        File_v.write(reinterpret_cast<char*>(&c), sizeof(Node));
        return;
    }
    void Find(string index) {
        Node maximal(index, INT_MAX);
        Node minimal(index, 0);
        bool found = false;
        File_h.seekg(0, ios::end);
        if (File_h.tellg() == 0) {
            cout << "null" << endl;
            return;
        }
        File_h.seekg(0, ios::beg);
        vector<Head_Node> All;
        while (true) {
            Head_Node tmp;
            tmp.readfrom(File_h);
            All.push_back(tmp);
            if (tmp.nextad == -1)
            {
                break;
            }
            File_h.seekg(tmp.nextad);
        }
        int first = 0;
        int last = All.size();
        for (int i = 0; i < All.size(); i++)
        {
            if (All[i].nodeofhead < minimal)
            {
                first = i;
            } else {
                break;
            }
        }
        for (int i = All.size() - 1; i >= 0; i--)
        {
            if (All[i].nodeofhead > maximal)
            {
                last= i;
            } else {
                break;
            }
        }
        bool flag = false;
        for (int i = first; i < last; i++) {
            File_v.seekg(All[i].addrofvalues);
            vector<Node> values(All[i].size);
            File_v.read(reinterpret_cast<char*>(values.data()), sizeof(Node) * All[i].size);
            for (int j = 0; j < values.size(); j++)
            {
                if ((values[j] > minimal || values[j] == minimal) && (values[j] < maximal || values[j] == maximal))
                {
                    flag = true;
                    cout << values[j].value << ' ';
                }
            }
        }
        if (!flag) {
            cout << "null" << endl;
        } else {
            cout << endl;
        }
    }
};

int main() {
    maplist bl("file_of_heads", "file_of_values");
    bl.openfile();
    int n;
    cin >> n;
    string operation;
    string index;
    int value;
    for (int i = 0; i < n; i++) {
        cin >> operation;
        if (operation == "insert") {
            cin >> index;
            cin >> value;
            bl.insert(index, value);
        }
        if (operation == "delete") {
            cin >> index;
            cin >> value;
            bl.remove(index, value);
        }
        if (operation == "find") {
            cin >> index;
            bl.Find(index);
        }
    }
    return 0;
}