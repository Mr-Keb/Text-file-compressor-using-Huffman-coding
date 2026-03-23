#include "HuffmanTree.hpp"

std::vector<uint32_t> counter(const std::string& file){
    //imposto a 256 perché in questo modo posso avere tutti i caratteri ASCII
    std::vector<uint32_t> freq(256, 0);
    std::ifstream MyFile;
    uint8_t byte;
    //apro il file in binario, modalità lettura
    MyFile.open(file, std::ios::binary | std::ios::in);
    
    if(!MyFile.is_open()){
        std::cout << "Specified file not found" << std::endl;
        return freq;
    }
    else{
        while(MyFile.read(reinterpret_cast<char*>(&byte), 1)){
            //converto in uint8_t perché la funzione get usa char, che sono su 8 bit ma sono signed
            uint8_t index = byte;
            //prendo la rappresentazione binaria del carattere corrispondente in ASCII e aumento l'indirizzo
            freq[index]++;
        }
        MyFile.close();
    }
    MyFile.close();

    return freq;
}
//funzione di debug
void print_table(const std::vector<uint32_t>& v) {
    for(size_t i = 0; i < v.size(); i++){
        std::cout << v[i] << ' ';
    }
    std::cout << ' ' << std::endl;
}

bool MyCompare::operator()(Node* l, Node* r){
    return l->frequency > r->frequency;
}

//popolo la queue inserendo in cima i caratteri con frequenza minore
void insert_in_queue(std::priority_queue<Node*, std::vector<Node*>, MyCompare>& pq, const std::vector<uint32_t>& v){
    for(size_t i = 0; i < v.size(); i++){
        if(v[i] != 0){
            Node* nodo = new Node (static_cast<uint8_t>(i), v[i]);
            pq.push(nodo);
        }
    }
}

//passo alla formazione dell'albero, unendo i caratteri con frequenza minore fino ad avere tutto connesso
Node* build_Huffman_tree(std::priority_queue<Node*, std::vector<Node*>, MyCompare> pq){
    if(pq.size() == 0) return nullptr;
    //size > 1 perché alla fine resta un solo elemento
    while(pq.size() > 1){
        //assegno a sinistra il primo elemento e lo cancello dalla coda
        Node* left = pq.top();
        pq.pop();
        //assegno a destra il secondo elemento e lo cancello
        Node* right = pq.top();
        pq.pop();
        //assegno il padre con frequenza = somma delle due e lo rimetto nella coda
        Node* parent = new Node(0, left->frequency + right->frequency);
        parent->left = left;
        parent->right = right;
        pq.push(parent);
    }

    Node* tree = pq.top();
    return tree;
}

void print_tree(Node* tree){
    if(!tree) return;
    if(!tree->left && !tree->right){
        std::cout << "Dato: " << tree->data << ", frequenza: " << tree->frequency << std::endl;
        return;   
    }

    print_tree(tree->left);
    print_tree(tree->right);
}

void destroy_tree(Node* tree){
    if(!tree) return;
    destroy_tree(tree->left);
    destroy_tree(tree->right);
    delete tree;
}