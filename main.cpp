#include "HuffmanTree.hpp"
#include "Encoding.hpp"
#include "Decoding.hpp"

int main(){
    int key;

    do{
        std::cout << "Select feature to use:" << std::endl;
        std::cout << "1. File compression" << std::endl;
        std::cout << "2. File decompression" << std::endl;
        std::cout << "3. Exit program" << std::endl;
        std::cin >> key;
        //utilizzo uno switch case in modo tale che alla fine di ogni scope di ogni case tutte le variabili statiche vengano distrutte,
        //per l'albero uso il distruttore
        switch (key){

            case 1:{
                std::string file, current_code;
                std::ofstream archive;
                std::priority_queue<Node*, std::vector<Node*>, MyCompare> pq;
                std::vector<std::string> codes(256);

                std::cout << "Insert file name:" << std::endl;
                std::cin >> file;

                std::vector<uint32_t> freq = counter(file);
                insert_in_queue(pq, freq);
                if(pq.empty()){
                    std::cout << "Empty file, try another file" << std:: endl;
                    continue;
                }

                Node* tree = build_Huffman_tree(pq);

                archive.open(file + ".huf", std::ios::binary);

                generate_codes(tree, codes, current_code);
                generate_header(pq, archive);
                compress(file, codes, archive);

                archive.close();
                destroy_tree(tree);
                break;
            }

            case 2:{
                std::string file;
                std::ifstream archive;
                std::priority_queue<Node*, std::vector<Node*>, MyCompare> pq;

                std::cout << "Insert file name:" << std::endl;
                std::cin >> file;

                archive.open(file + ".huf", std::ios::binary);

                pq = decode_header(archive);

                if(pq.empty()){
                    std::cout << "File may be corrupted" << std:: endl;
                    continue;
                }

                decode_tree(pq, archive);

                archive.close();
                break;
            }

            case 3: break;

            default:{
                std::cout << "Key not recognized!" << std::endl;
                break;
            }
        }
        
    }while(key != 3);
    return 0;
}