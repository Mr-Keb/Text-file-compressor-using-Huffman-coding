#ifndef DECODING_HPP
#define DECODING_HPP

#include "Encoding.hpp"

std::priority_queue<Node*, std::vector<Node*>, MyCompare> decode_header(std::ifstream&);
void decode_tree(std::priority_queue<Node*, std::vector<Node*>, MyCompare>&, std::ifstream&, std::string);

#endif