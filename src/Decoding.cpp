#include "Decoding.hpp"

std::priority_queue<Node*, std::vector<Node*>, MyCompare> decode_header(std::ifstream& file){
    uint16_t file_size;
    std::priority_queue<Node*, std::vector<Node*>, MyCompare> pq;
    std::vector<uint32_t> freq(256, 0);

    if(file.good()){
        file.read(reinterpret_cast<char*>(&file_size), 2);
        if(!file) return pq;
    }
    else{
        return pq;
    }
    //scendo nel file a prendere le codifiche dei vari caratteri
    for(size_t i = 0; i < file_size; i++){
        uint8_t data;
        uint32_t frequency;

        file.read(reinterpret_cast<char*>(&data), 1);
        file.read(reinterpret_cast<char*>(&frequency), 4);

        freq[data] = frequency;
    }
    insert_in_queue(pq, freq);
    return pq;
}

void decode_tree(std::priority_queue<Node*, std::vector<Node*>, MyCompare>& pq, std::ifstream& file){
    Node* tree = build_Huffman_tree(pq);
    uint32_t total_char = tree->frequency;
    uint32_t decoded_count = 0;
    Node* current = tree;

    std::ofstream output("decrypted.txt", std::ios::binary);

    while(decoded_count < total_char){
        uint8_t byte;
        file.read(reinterpret_cast<char*>(&byte), 1);
        //per il byte scendo lungo l'albero per trovare il carattere
        for(size_t j = 0; j < 8; j++){
            if(byte & (1 << (7 - j))){
                current = current->right;
            }
            else{
                current = current->left;
            }

            if(!current->left && !current->right){
                char c = current->data;
                current = tree;
                output.put(c);
                decoded_count++;
            }

            if(decoded_count == total_char) break;
        }
    }
    output.close();
    destroy_tree(tree);
}