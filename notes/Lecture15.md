# Units of information

* Bit: 1 bit
* Nibble: 4 bits
* Byte: 8 bits (smallest addressable bit, every byte has an address)
* half-word: 16 bits (a short in c, depends on native machine)
* word: 32-bits (can be 64, depends on native machine)

* right shift
    * logical shift in c (unsigned or positive signed) works perfect like division or multiplication
    * if arithmetic shift (signed negative) its implementation defined (by compiler and processor)
* left shfit

* & (and) is the same as multiplication with bitwise operations (a lot like set intersection)
* | (or) a lot like set union
* ^ (xor) is a lot like addition
* ~ (not)

## getting higher order nibble

shift left by 4

and with 00001111


