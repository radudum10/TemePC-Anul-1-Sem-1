#include "gates.h"

#include <stdio.h>
#include <assert.h>

/* Task 1 - Bit by Bit */

uint8_t get_bit(uint64_t nr, uint8_t i)
{
    assert(i <= 8 * sizeof nr);

    uint8_t res = -1;

    /* TODO
     *
     * "res" should be 1 if the bit is active, else 0
     */
    
   res = (nr >> i) & 1;
    return res;
}


uint64_t flip_bit(uint64_t nr, uint8_t i)
{
    assert(i <= 8 * sizeof nr);

    uint64_t res = -1;

    /* TODO
     *
     * Return the "nr" with the ith bit flipped
     */
    
    res = nr ^ ((uint64_t) 1 << i);
    return res;
}


uint64_t activate_bit(uint64_t nr, uint8_t i)
{
    assert(i <= 8 * sizeof nr);

    uint64_t res = 0xFF;

    /* TODO
     *
     * Return the "nr" with the ith bit "1"
     */
    
    if (get_bit (nr, i) == 0)
    	res = flip_bit(nr, i);
    
    else
    	res = nr;
    return res;
}


uint64_t clear_bit(uint64_t nr, uint8_t i)
{
    assert(i <= 8 * sizeof nr);

    uint64_t res = -1;

     /* TODO
     *
     * Return the "nr" with the ith bit "0"
     */

    res = nr;
    
    if (get_bit (nr, i))
    	res = flip_bit(nr, i);
    
    else
    	res = nr;
    return res;
}


/* Task 2 - One Gate to Rule Them All */

uint8_t nand_gate(uint8_t a, uint8_t b)
{
    assert (a == 0 || a == 1);
    assert (b == 0 || b == 1);

    return !(a & b);
}


uint8_t and_gate(uint8_t a, uint8_t b)
{
    assert (a == 0 || a == 1);
    assert (b == 0 || b == 1);

    uint8_t res = -1;

    /* TODO - Use the nand gate to implement the and gate */
    
    res = !nand_gate(a, b);
    return res;
}


uint8_t not_gate(uint8_t a)
{
    assert (a == 0 || a == 1);

    uint8_t res = -1;

    /* TODO - Use the nand gate to implement the not gate */

    res = nand_gate(a, a);
    return res;
}


uint8_t or_gate(uint8_t a, uint8_t b)
{
    assert (a == 0 || a == 1);
    assert (b == 0 || b == 1);

    uint8_t res = -1;

    /* TODO - Use the previously defined gates to implement the or gate */
    
    res = nand_gate(!a, !b);
    return res;
}


uint8_t xor_gate(uint8_t a, uint8_t b)
{
    assert (a == 0 || a == 1);
    assert (b == 0 || b == 1);

    uint8_t res = -1;

    /* TODO - Use the previously defined gates to implement the xor gate */

    res = nand_gate(nand_gate(!a, b), nand_gate(a, !b));


    return res;
}


/* Task 3 - Just Carry the Bit */

uint8_t full_adder(uint8_t a, uint8_t b, uint8_t c)
{
    assert (a == 0 || a == 1);
    assert (b == 0 || b == 1);
    assert (c == 0 || c == 1);
    
    uint8_t res = -1;

    /* TODO - implement the full_adder using the previous gates
     * Since the full_adder needs to provide 2 results, you should
     * encode the sum bit and the carry bit in one byte - you can encode
     * it in whatever way you like
     */
    uint8_t Co;
    uint8_t s;
    // sum = XOR(a, b, c), Co = OR(ab, bc, ac)
    
    s = xor_gate(xor_gate(a,b), c);
    
    Co = or_gate(or_gate(and_gate(a, b), and_gate(a, c)), and_gate(b, c));

    res = (s << 1) | Co;

    return res;
}


uint64_t ripple_carry_adder(uint64_t a, uint64_t b)
{
    uint64_t res = -1;

     /* TODO
     * Use the full_adder to implement the ripple carry adder
     * If there is ANY overflow while adding "a" and "b" then the
     * result should be 0
     */

    res = 0;

    uint64_t Ci = 0; // transport
    
    uint64_t adder;
    
    uint64_t i;

    uint64_t s;

    for (i = 0; i < 64; i++) {

        // taking each bit from the number
        uint64_t bit_a = get_bit(a, i);
        uint64_t bit_b = get_bit(b, i);

        // sum using full adder
        adder = full_adder(bit_a, bit_b, Ci);

        // decoding the sum
        s = (adder >> 1) & 1;

        // adding to the result
        res = res | (s << i);

        // decoding the transport
        Ci = adder & (uint64_t) 1; 
        
    }

    if(Ci)
        return 0; // overflow exception

    return res;
}
