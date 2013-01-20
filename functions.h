#ifndef __FUNCTIONS__H__
#define __FUNCTIONS__H__

#include<iostream>
#include<fstream>
#include<queue>
#include<vector>
#include<string>
#include<map>

using namespace std;

struct byte
 {
    unsigned char bit1: 1;
    unsigned char bit2: 1;
    unsigned char bit3: 1;
    unsigned char bit4: 1;
    unsigned char bit5: 1;
    unsigned char bit6: 1;
    unsigned char bit7: 1;
    unsigned char bit8: 1;
 };

struct node
{
    int count;
    char ch;
    node* left;
    node* right;
    string code;
    bool operator< (const node& x) const {return count > x.count;}
};

void preorder(node *act,string code,string bit,string* coding);
string code();
string decode();

#endif
