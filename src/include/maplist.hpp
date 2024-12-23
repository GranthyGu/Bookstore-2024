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
    Node();
    Node(std::string str, T value);
    bool operator<(const Node<T>& other);
    bool operator>(const Node<T>& other);
    bool operator<=(const Node<T>& other);
    bool operator>=(const Node<T>& other);
    bool operator==(const Node<T>& other) const;
    Node<T>& operator=(const Node<T>& other);
    void writetofile(std::fstream& File);
    void readfromile(std::fstream& File);
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
    Head_Node();
    Head_Node(int size, long add1, long add2, long add3, Node<T> node);
    void writeto(std::fstream& File_);
    void readfrom(std::fstream& File_) ;
    Head_Node<T>& operator=(const Head_Node<T>& other);
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
    maplist(std::string str1, std::string str2);
    void openfile();
    void split_head_node(Head_Node<T>& hn);
    void insert(std::string index, T value);
    void remove(std::string index, T value);
    void Find(std::string index, Node<T> maximal, Node<T> minimal);
};

#endif     //MAP_LIST_HPP