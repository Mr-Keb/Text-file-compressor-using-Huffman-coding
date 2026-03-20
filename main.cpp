#include "HuffmanTree.hpp"
#include "Encoding.hpp"

int main(){
    std::string file, current_code;
    std::priority_queue<Node*, std::vector<Node*>, MyCompare> pq;
    std::vector<std::string> codes(256);
    std::ofstream archive;

    std::cout << "inserisci nome del file" << std::endl;
    std::cin >> file;

    std::vector<uint32_t> freq = counter(file);
    insert_in_queue(pq, freq);
    if(pq.empty()) return 0;

    Node* tree = build_Huffman_tree(pq);

    archive.open("archivio.txt", std::ios::binary);

    generate_codes(tree, codes, current_code);
    generate_header(pq, archive);
    compress(file, codes, archive);

    archive.close();
    return 0;
}