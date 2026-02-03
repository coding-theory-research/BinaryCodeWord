#include <iostream>
#include "BinaryCodeWord/BinaryCodeWord.hpp"

int main() {
    BinaryCodeWord a(8);
    BinaryCodeWord b(8);

    a.setBit(0, 1);
    a.setBit(3, 1);

    b.setBit(3, 1);
    b.setBit(4, 1);

    std::cout << "Codeword a : "<<a<<std::endl;
    std::cout << "Codeword b : "<<b<<std::endl;
    BinaryCodeWord c = a + b;   // XOR
    std::cout<<"c = a + b"<<std::endl;
    std::cout << "Codeword c : "<<c<<std::endl;
    a += b;                     // in-place XOR (great for repeated XOR operations)

    std::cout << "c bits: ";
    for (int i = 0; i < c.length(); ++i) std::cout << c.getBit(i);
    std::cout << "\n";

    std::cout << "a == c? " << (a == c ? "true" : "false") << "\n";
    return 0;
}
