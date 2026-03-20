#ifndef ENCODING_HPP
#define ENCODING_HPP

#include "HuffmanTree.hpp"
#include <string>
#include <vector>
#include <cstdint>

std::vector<std::string> generate_codes(Node*, std::vector<std::string>&, std::string);
void generate_header(std::priority_queue<Node*, std::vector<Node*>, MyCompare>, std::ofstream&);
void compress(std::string, const std::vector<std::string>&, std::ofstream&);

#endif