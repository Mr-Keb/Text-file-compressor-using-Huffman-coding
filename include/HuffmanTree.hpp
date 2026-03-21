#ifndef HUFFMAN_TREE_HPP
#define HUFFMAN_TREE_HPP

#include <iostream>
#include <queue>
#include <vector>
#include <cstdint>
#include <fstream>

struct Node{
    uint8_t data;
    uint32_t frequency;

    Node* left, *right;

    Node (uint8_t d, uint32_t f) : data (d), frequency (f), left (nullptr), right (nullptr){} 
};

//uso una struct perché la priority queue vuole come comparatore un oggetto funzione
struct MyCompare{
    bool operator()(Node* l, Node* r);
};

void insert_in_queue(std::priority_queue<Node*, std::vector<Node*>, MyCompare>&, const std::vector<uint32_t>&);
Node* build_Huffman_tree(std::priority_queue<Node*, std::vector<Node*>, MyCompare>);
//funzione di debug
void print_tree(Node*);
void destroy_tree(Node*);

//per leggere il file e avere come ritorno un vettore di 256 posizioni, usando uint32 posso gestire file fino a 4GiB
std::vector<uint32_t> counter(const std::string&);
//funzione debug
void print_table (const std::vector<uint32_t>&);

#endif