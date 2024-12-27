// Created by GranthyGu on 2024/12/23

#ifndef MAP_LIST_HPP
#define MAP_LIST_HPP

/*
 * File: maplist.h
 * --------------------
 * This file exports a map class that has functions insert/delete/find
 * with a key (a string less than 60 digits) and a value (any classes).
 */

#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <climits>
#include <string>
#include <algorithm>

const int maxN = 600;

/*
 * class Node:
 * This class saves each input with a pair char[60] and a class, which represent
 * the key and the value, respectively.
 * The rank principle for Node is compare char at first and then class (can be compared).
 * The function writetoFile and readfromFile can achieve read and write functions of a node.
 */
template<typename T>
class Node {
public:
    char index[60];
    T value;
    Node() {}
    Node(std::string str, T value) : value(value) {
        for (int i = 0; i < str.length(); i++) {
            index[i] = str[i];
        }
        for (int i = str.length(); i < 60; i++)
        {
            index[i] = '\0';
        }
    }
    bool operator<(const Node<T>& other) {
        for (int i = 0; i < 60; i++) {
            if (index[i] != other.index[i]) {
                return index[i] < other.index[i];
            }
        }
        return value < other.value;
    }
    bool operator>(const Node<T>& other) {
        for (int i = 0; i < 60; i++) {
            if (index[i] != other.index[i]) {
                return index[i] > other.index[i];
            }
        }
        return value > other.value;
    }
    bool operator==(const Node<T>& other) const {
        for (int i = 0; i < 60; i++) {
            if (index[i] != other.index[i]) {
                return false;
            }
        }
        return (value == other.value);
    }
    Node<T>& operator=(const Node<T>& other) {
        for (int i = 0; i < 60; i++) {
            index[i] = other.index[i];
        }
        value = other.value;
        return *this;
    }
    void writetofile(std::fstream& File) {
        for (int i = 0; i < 60; i++) {
            File.write(reinterpret_cast<char *> (&index[i]), sizeof(char));
        }
        File.write(reinterpret_cast<char *>(&value), sizeof(T));
    }
    void readfromile(std::fstream& File) {
        for (int i = 0; i < 60; i++) {
            File.read(reinterpret_cast<char *> (&index[i]), sizeof(char));
        }
        File.read(reinterpret_cast<char *>(&value), sizeof(T));
    }
};

/* 
 * class Head_Node:
 * This class saves the head nodes of the chain, and saves their address in the file of 
 * head nodes.
 * To make sure it can find the next head node, it also saves the address of next head node.
 * To find values directly from the head node, it saves the address of the Nodes in the file of values.
 * To compare and find the nodes conveniently, it saves the first node it saves.
 * It also has assignment operator.
 * The function writeto and readfrom can write and read from the file of head nodes.
 */
template<typename T>
class Head_Node {
public:
    int size;
    long addrofvalues;
    long nextad;
    long adrofiteself;
    Node<T> nodeofhead;
    Head_Node() : size(0), addrofvalues(-1), nextad(-1), adrofiteself(-1) {}
    Head_Node(int size, long add1, long add2, long add3, Node<T> node) : size(size), addrofvalues(add1), nextad(add2), adrofiteself(add3), nodeofhead(node) {}
    void writeto(std::fstream& File_) {
        File_.write(reinterpret_cast<char *> (&size), sizeof(int));
        File_.write(reinterpret_cast<char *> (&addrofvalues), sizeof(long));
        File_.write(reinterpret_cast<char *> (&nextad), sizeof(long));
        File_.write(reinterpret_cast<char *> (&adrofiteself), sizeof(long));
        nodeofhead.writetofile(File_);
    }
    void readfrom(std::fstream& File_) {
        File_.read(reinterpret_cast<char *> (&size), sizeof(int));
        File_.read(reinterpret_cast<char *> (&addrofvalues), sizeof(long));
        File_.read(reinterpret_cast<char *> (&nextad), sizeof(long));
        File_.read(reinterpret_cast<char *> (&adrofiteself), sizeof(long));
        nodeofhead.readfromile(File_);
    }
    Head_Node<T>& operator=(const Head_Node<T>& other) {
        size = other.size;
        addrofvalues = other.addrofvalues;
        nextad = other.nextad;
        adrofiteself = other.adrofiteself;
        nodeofhead = other.nodeofhead;
        return *this;
    }
};

/* 
 * class maplist:
 * It saves all the key-value datas, just as a map.
 * We input two strings as the file names and initial a maplist.
 * 
 * Caution: after initialize the maplist we must do openfile to implement SECURE file opening!
 * Caution: we must definde the MAXIMAL and MINIMAL values of class T to find properly!
 * 
 * Then we can do insert, delete, find just as a map.
 */
template<typename T>
class maplist {
private:
    std::string file_of_values;
    std::string file_of_heads;
    std::fstream File_v;
    std::fstream File_h;
public:
    maplist() {}
    maplist(std::string str1, std::string str2) : file_of_heads(str1), file_of_values(str2) {}
    void openfile() {
        File_v.open(file_of_values, std::ios::in | std::ios::out | std::ios::binary);
        if (!File_v) {
            File_v.close();
            File_v.clear(); 
            File_v.open(file_of_values, std::ios::out | std::ios::binary);
            File_v.close();
            File_v.open(file_of_values, std::ios::in | std::ios::out | std::ios::binary);
        }
        File_h.open(file_of_heads, std::ios::in | std::ios::out | std::ios::binary);
        if (!File_h) {
            File_h.close();
            File_h.clear();
            File_h.open(file_of_heads, std::ios::out | std::ios::binary);
            File_h.close();
            File_h.open(file_of_heads, std::ios::in | std::ios::out | std::ios::binary);
        }       
    }
    void set_file_names(std::string str1, std::string str2) {
        this->file_of_heads = str1;
        this->file_of_values = str2;
    }
    void split_head_node(Head_Node<T>& hn) {
        std::vector<Node<T> > values(hn.size);
        File_v.seekg(hn.addrofvalues);
        File_v.read(reinterpret_cast<char*>(values.data()), sizeof(Node<T>) * hn.size);
        Node<T> head_node_of_new = values[hn.size / 2];
        std::vector<Node<T>> newvalues(values.begin() + hn.size / 2, values.end());
        values.resize(hn.size / 2);
        File_v.seekp(0, std::ios::end);
        long adofnew = File_v.tellp();
        File_v.write(reinterpret_cast<char*>(newvalues.data()), sizeof(Node<T>) * newvalues.size());
        Node<T> c;
        for (int i = 0; i < maxN - newvalues.size(); i++) {
            File_v.write(reinterpret_cast<char *>(&c), sizeof(Node<T>));
        }
        File_v.seekp(hn.addrofvalues + sizeof(Node<T>) * values.size());
        for (int i = 0; i < maxN - values.size(); i++) {
            File_v.write(reinterpret_cast<char *>(&c), sizeof(Node<T>));
        }
        File_h.seekp(0, std::ios::end);
        long adr_of_newhn = File_h.tellp();
        Head_Node<T> newhd(hn.size - hn.size / 2, adofnew, hn.nextad, adr_of_newhn, head_node_of_new);
        newhd.writeto(File_h);
        hn.size = hn.size / 2;
        hn.nextad = adr_of_newhn;
        File_h.seekp(hn.adrofiteself);
        hn.writeto(File_h);
    }
    void insert(std::string index, T value) {
        File_h.seekg(0, std::ios::end);
        if (File_h.tellg() == 0) {
            Node<T> tmpp(index, value);
            Head_Node<T> tmp(1, 0, -1, 0, tmpp);
            tmp.writeto(File_h);
            tmpp.writetofile(File_v);
            for (int i = 0; i < maxN - 1; i++) {
                Node<T> t;
                t.writetofile(File_v);
            }
            } else {
            File_h.seekg(0, std::ios::beg);
            Node<T> tmpp(index, value);
            bool found = false;
            Head_Node<T> hn;
            Head_Node<T> hn_before;
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
                std::vector<Node<T>> values(hn.size);
                File_v.seekg(hn.addrofvalues);
                File_v.read(reinterpret_cast<char*>(values.data()), sizeof(Node<T>) * hn.size);
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
                    File_v.write(reinterpret_cast<char*>(values.data()), sizeof(Node<T>) * hn.size);
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
                std::vector<Node<T>> values(hn.size - 1);
                File_v.seekg(hn.addrofvalues);
                File_v.read(reinterpret_cast<char*>(values.data()), sizeof(Node<T>) * (hn.size - 1));
                values.insert(values.begin(), tmpp);
                File_v.seekp(hn.addrofvalues);
                File_v.write(reinterpret_cast<char*>(values.data()), sizeof(Node<T>) * hn.size);
                if (hn.size == maxN) {
                    split_head_node(hn);
                }
                return;
            } else {
                std::vector<Node<T>> values(hn_before.size);
                File_v.seekg(hn_before.addrofvalues);
                File_v.read(reinterpret_cast<char*>(values.data()), sizeof(Node<T>) * hn_before.size);
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
                    File_v.write(reinterpret_cast<char*>(values.data()), sizeof(Node<T>) * hn_before.size);
                    if (hn_before.size == maxN) {
                        split_head_node(hn_before);
                    }
                    return;
                }
            }
        }
    }
    void remove(std::string index, T value) {
        File_h.seekg(0, std::ios::end);
        if (File_h.tellg() == 0) {
            return;
        }
        Node<T> c;
        File_h.seekg(0, std::ios::beg);
        Node<T> tmpp(index, value);
        bool found = false;
        Head_Node<T> hn;
        Head_Node<T> hn_before;
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
                std::vector<Node<T>> values(hn.size);
                File_v.seekg(hn.addrofvalues);
                File_v.read(reinterpret_cast<char*>(values.data()), sizeof(Node<T>) * hn.size);
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
                        File_h.open(file_of_heads, std::ios::in | std::ios::out | std::ios::binary);
                        File_v.open(file_of_values, std::ios::in | std::ios::out | std::ios::binary);
                    } else {
                        hn.nodeofhead = values[1];
                        values.erase(it);
                        hn.size--;
                        File_h.seekp(hn.adrofiteself);
                        hn.writeto(File_h);
                        File_v.seekp(hn.addrofvalues);
                        File_v.write(reinterpret_cast<char*>(values.data()), sizeof(Node<T>) * hn.size);
                        File_v.write(reinterpret_cast<char*>(&c), sizeof(Node<T>));
                    }
                    return;
                } else {
                    values.erase(it);
                    hn.size--;
                    File_h.seekp(hn.adrofiteself);
                    hn.writeto(File_h);
                    File_v.seekp(hn.addrofvalues);
                    File_v.write(reinterpret_cast<char*>(values.data()), sizeof(Node<T>) * hn.size);
                    File_v.write(reinterpret_cast<char*>(&c), sizeof(Node<T>));
                    return;
                }
            }
        }
        if (!found)
        {
            std::vector<Node<T>> values(hn.size);
            File_v.seekg(hn.addrofvalues);
            File_v.read(reinterpret_cast<char*>(values.data()), sizeof(Node<T>) * hn.size);
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
                    File_v.write(reinterpret_cast<char*>(values.data()), sizeof(Node<T>) * hn.size);
                    File_v.write(reinterpret_cast<char*>(&c), sizeof(Node<T>));
                }
            }
            else {
                values.erase(it);
                hn.size--;
                File_h.seekp(hn.adrofiteself);
                hn.writeto(File_h);
                File_v.seekp(hn.addrofvalues);
                File_v.write(reinterpret_cast<char*>(values.data()), sizeof(Node<T>) * hn.size);                    
                File_v.write(reinterpret_cast<char*>(&c), sizeof(Node<T>));
            }
            return;
        }
        std::vector<Node<T>> values(hn_before.size);
        File_v.seekg(hn_before.addrofvalues);
        File_v.read(reinterpret_cast<char*>(values.data()), sizeof(Node<T>) * hn_before.size);
        auto it = find(values.begin(), values.end(), tmpp);
        if (it == values.end()) {
            return;
        } 
        if (it == values.begin()) {
            if (values.size() == 1 && num == 2) {
                File_h.seekp(0, std::ios::beg);
                hn.adrofiteself = 0;
                hn.writeto(File_h);
                return;
            }
            if (values.size() == 1 && num >= 3) {
                File_h.seekg(hn_before_position);
                Head_Node<T> tmp;
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
            File_v.write(reinterpret_cast<char*>(values.data()), sizeof(Node<T>) * hn_before.size);
            File_v.write(reinterpret_cast<char*>(&c), sizeof(Node<T>));
            return;
        }
        values.erase(it);
        hn_before.size--;
        File_h.seekp(hn_before.adrofiteself);
        hn_before.writeto(File_h);
        File_v.seekp(hn_before.addrofvalues);
        File_v.write(reinterpret_cast<char*>(values.data()), sizeof(Node<T>) * hn_before.size);
        File_v.write(reinterpret_cast<char*>(&c), sizeof(Node<T>));
        return;
    }
    std::vector<Node<T>> Find(Node<T> maximal, Node<T> minimal) {
        bool found = false;
        std::vector<Head_Node<T>> All;
        std::vector<Node<T>> e;
        File_h.seekg(0, std::ios::end);
        if (File_h.tellg() == 0) {
            return e;
        }
        File_h.seekg(0, std::ios::beg);
        while (true) {
            Head_Node<T> tmp;
            tmp.readfrom(File_h);
            All.push_back(tmp);
            if (tmp.nextad == -1) {
                break;
            }
            File_h.seekg(tmp.nextad);
        }
        int first = 0;
        int last = All.size();
        for (int i = 0; i < All.size(); i++) {
            if (All[i].nodeofhead < minimal) {
                first = i;
            } else {
                break;
            }
        }
        for (int i = All.size() - 1; i >= 0; i--) {
            if (All[i].nodeofhead > maximal) {
                last = i;
            } else {
                break;
            }
        }
        std::vector<Node<T>> outcome;
        for (int i = first; i < last; i++) {
            File_v.seekg(All[i].addrofvalues);
            std::vector<Node<T>> values(All[i].size);
            File_v.read(reinterpret_cast<char*>(values.data()), sizeof(Node<T>) * All[i].size);
            for (int j = 0; j < values.size(); j++) {
                if ((values[j] > minimal || values[j] == minimal) && (values[j] < maximal || values[j] == maximal)) {
                    outcome.push_back(values[j]);
                }
            }
        }
        return outcome;
    }
    Node<T> Findminimal() {
        Head_Node<T> tmpp;
        File_h.seekg(0, std::ios::end);
        if (File_h.tellg() == 0) {
            return tmpp.nodeofhead;
        }
        File_h.seekg(0, std::ios::beg);
        tmpp.readfrom(File_h);
        return tmpp.nodeofhead;
    }
    Node<T> Findmaximal() {
        File_h.seekg(0, std::ios::end);
        Head_Node<T> tmp;
        Node<T> e;
        if (File_h.tellg() == 0) {
            return e;
        }
        File_h.seekg(0, std::ios::beg);
        while (true) {
            tmp.readfrom(File_h);
            if (tmp.nextad == -1) {
                break;
            }
            File_h.seekg(tmp.nextad);
        }
        File_v.seekg(tmp.addrofvalues);
        Node<T> maximal;
        for (int i = 0; i < tmp.size; i++) {
            maximal.readfromile(File_v);
        }
        return maximal;
    }
};

#endif     //MAP_LIST_HPP