#include "Encoding.hpp"

//funzione che scende lungo l'albero e per ogni carattere forma una nuova stringa di bit, mettendo 0 quando va a sinitra e 1 a destra
std::vector<std::string> generate_codes (Node* tree, std::vector<std::string>& codes, std::string current_code){
    if(!tree) return codes;
    
    if(!tree->left && !tree->right) {
        codes[tree->data] = current_code;
        return codes;
    }

    generate_codes(tree->left, codes, current_code + '0');
    generate_codes(tree->right, codes, current_code + '1');

    return codes;
}

void generate_header(std::priority_queue<Node*, std::vector<Node*>, MyCompare> pq, std::ofstream& arch){
    //scrivo la grandezza della coda, serivrà alla ricostruzione del file
    uint16_t size = pq.size();
    //faccio il cast della variabile
    arch.write(reinterpret_cast<const char*>(&size), sizeof(size));

    //scrivo la coppia dato, frequenza per il decoder
    while(!pq.empty()){
        arch.write(reinterpret_cast<const char*>(&pq.top()->data), sizeof(pq.top()->data));
        arch.write(reinterpret_cast<const char*>(&pq.top()->frequency), sizeof(pq.top()->frequency));
        pq.pop();
    }
}

void compress(std::string filename, const std::vector<std::string>& codes, std::ofstream& outfile){
    //uso un buffer perché posso scrivere minimo un byte
    uint8_t buffer = 0;
    int bit_count = 0;

    std::ifstream file;
    file.open(filename, std::ios::binary);
    uint8_t ch;

    while(file.read(reinterpret_cast<char*>(&ch), 1)){
        //inserimento usando il carattere come indice
        for(size_t i = 0; i < codes[ch].size(); i++){
            //se trovo 1 accendo il bit che mi serve nella posizione cercata
            if(codes[ch][i] == '1'){
                buffer |= (1 << (7 - bit_count));
            }
            bit_count++;
            
            //controllo dopo l'inserimento se ho saturato il buffer e lo svuoto
            if(bit_count == 8){
                outfile.write(reinterpret_cast<const char*>(&buffer), 1);
                bit_count = 0;
                buffer = 0;
            }
        }
    }
    //scrive eventuali bit rimasti nel buffer aggiungendo abbastanza zeri alla fine
    if(bit_count > 0){
        outfile.write(reinterpret_cast<const char*>(&buffer), 1);
    }

    file.close();
}