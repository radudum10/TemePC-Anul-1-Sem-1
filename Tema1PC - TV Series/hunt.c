#include "hunt.h"
#include <stdio.h>

/* Task 1 - Axii */

uint16_t find_spell(uint64_t memory)
{
    /*
     * The spell is 16 bits and they are in the memory exactly after 5
     * consecutive bits of 1:
     *
     *            high                                             low
     *                [][][x]...[x][x][x][1][1][1][1][1][]...[][][]
     *                    |----16bits---|
     *                          Spell
     *
     * There is only 1 group of 5 consecutive bits of 1 and the other groups
     * have less than consecutive bits of 1
     * Steps:
     * - find 5 consecutive bits of 1
     * - the NEXT 16 bits == spell
     */

    uint16_t res = -1;

    /* TODO */

    uint8_t bit_curent;
    uint8_t bit_anterior;
    uint8_t i;
    uint8_t k;
    uint8_t poz; 
    
    bit_anterior = memory & 1;
    k = 1;

    for (i = 1; i <= 63; i++) {
        bit_curent = (memory >> i) & 1;

            if (bit_curent == bit_anterior && bit_curent == 1)
                k++;
            else 
                k = 1;
            // reseting if there are not 2 bits of 1 consecutive

            if (k == 5) {
                poz = i + 1;
                break; 
            }
            // stopping when it finds 5 bits of 1 consecutive
        bit_anterior = bit_curent;
    }

    uint16_t spell_bit;
    
    k = 0;
    res = 0;

    for (i = poz; i <= poz + 15; i ++) {
        spell_bit = ((memory >> i) & 1) << k; 
        res = res | spell_bit;
        k++;
    }

    return res;
}


uint16_t find_key(uint64_t memory)
{
    /*
     * The key is 16 bits and they are in the memory exactly before 3
     * consecutive bits of 1:
     *
     *                high                                           low
     *                     [][][][1][1][1][x][x]...[x][x][]...[][][]
     *                                    |----16bits---|
     *                                           Key
     * Steps:
     * - find 3 consecutive bits of 1
     * - the PREVIOUS 16 bits == key
     */

    uint16_t res = -1;

    /* TODO */

    uint8_t bit_curent;
    uint8_t bit_anterior;
    uint8_t i;
    uint8_t k;
    uint8_t poz;
    
    bit_anterior = memory & 1;
    k = 1;

    for (i = 1; i <= 63; i++) {
        bit_curent = (memory >> i) & 1;

            if (bit_curent == bit_anterior && bit_curent == 1)
                k++;
            else 
                k = 1;

            if (k == 3) {
                poz = i - 18;
                // between the third bit of 1
                // and the start of the key, there are 18 bits
                break; 
            }

        bit_anterior = bit_curent;

    }
    uint16_t key_bit;
    
    k = 0;
    res = 0;

    for (i = poz; i <= poz + 15; i++) {
        key_bit = ((memory >> i) & 1) << k;
        res = res | key_bit;
        k++;
    }
    return res;
}


uint16_t decrypt_spell(uint16_t spell, uint16_t key)
{
    /*
     * Find the spell knowing that
     * spell_encrypted = spell_plaintext ^ key
     */

    uint16_t res = -1;

    res = spell ^ key;

    /* TODO */

    return res;
}


/* Task 2 - Sword Play */

uint32_t choose_sword(uint16_t enemy)
{
    /*
     * Help Geralt construct a sword that will give him an advantage in battle.
     * The steps we will follow:
     * - choose the corect sword
     * - brand the sword with the correct runes such that the equation
     * for that specific enemy type is true
     *
     * How does the sword look (Sword template):
     *  [][][][] [0][0][0]...[0][0][0] [][][][][][][][][][][][][][][][]
     *  -------- --------------------- --------------------------------
     *     Type    Does not matter      The "Value" such that the equation
     *                               from 2 holds depending on the enemy type
     *    4 bits      12 bits                     16 bits
     *
     * 1. Type of the sword:
     * - 1001 - Silver Sword - for monsters
     * - 0110 - Steel Sword - for humans
     *
     *  If the number of active bits from variable "enemy" is even == Monster
     *  else == Human
     *
     * 2.
     * Monster Equation:
     *    Value ^ (Enemy & (1 - Enemy)) = 0
     *
     * Human Equation:
     *    Value + Enemy = 0
     */

    uint32_t res = -1;

    /* TODO */

    uint8_t i;
    uint8_t k;
    k = 0;
    uint8_t enemy_currentbit;
    // counting the active bits
    for (i = 0; i <= 15; i++) {
        enemy_currentbit = (enemy >> i) & (uint8_t) 1;
        if (enemy_currentbit)
            k++;
    }

    uint8_t type;
    uint16_t value; 
    res = 0;

    if ((k & 1) == 0) {
        type = 9;
        // enemy type = monster
        // 1001(2) = 9(10)

        value = enemy & (1 - enemy);
        // the xor between value, (enemy & (1 - enemy)) is 0
        // only if value is equal to the expression

    }
    else {
        type = 6; 
        // enemy type = human
        // 0110(2) = 6

        value = - enemy;
    }

    uint32_t currentbit;
    k = 28;
    // putting the type on the last 4 bits
    for(i = 0; i <= 3; i++) {
        currentbit = ((type >> i) & 1) << k;
        res = res | currentbit; 
        k++;
    }

    k = 0;

    for(i = 0; i <= 15; i ++) {
        currentbit = ((value >> i) & (uint16_t) 1) << k;
        res = res | currentbit; 
        k++;
    }

    // putting the value on the first 16 bits

    return res;
}


/* Task 3 - The Witcher Trials */

uint32_t trial_of_the_grasses(uint16_t cocktail)
{
    /*
     * To become a witcher one must survive a cocktail of different
     * herbs. The body should generate the correct antibodies to
     * neutralize the given cocktail.
     *
     *
     * The antibodies need to respect the following properties:
     *   (antibodies_high & cocktail) ^ (antibodies_low | cocktail) = 0
     *   antibodies_low & antibodies_high = 0
     *   antibodies_low | antibodies_high = cocktail
     *
     * Where:
     *  [][][]...[][][] | [][][]...[][][]
     *  ---------------   ---------------
     *  antibodies_high    antibodies_low
     *      16 bits           16 bits
     *      -------------------------
     *              antibodies
     */

    uint32_t res = -1;

    res = (uint32_t) cocktail << 16;

    return res;
}


uint8_t trial_of_forrest_eyes(uint64_t map)
{
    /*
     * For the next trail, the candidate is tied up and blindfolded.
     * They are also taken to a forest and they should return until
     * the next morning.
     *
     * The candidate knows that there are 4 possibilities for the forest:
     * Brokilon, Hindar, Wolven Glade and Caed Dhu.
     *
     * The candidate also knows those forests by heart, but first you
     * need to identify the forest.
     *
     * The characteristics for 3 of the forests are as follows:
     * - Brokilon - has ONLY groups of 4 trees (or a forest without any tree)
     *   Ex: a group of 4 trees: "...00111100..."
     * - Hindar - has ONLY 2 trees in the MIDDLE
     * - Wolven Glade - FULL of trees
     *
     * The "map" variable encodes the following information:
     * - 1 tree
     * - 0 patch of grass
     *
     * You should put in the "res" variable the index for the identified
     * forrest.
     * - Brokilon - index 0
     * - Hindar - index 1
     * - Wolven Glade - index 2
     * - Caed Dhu - index 3
     */

    uint8_t res = -1;

    /* TODO */

    uint8_t i;
    uint8_t bit_curent;
    uint8_t k;

    if (map == -1) {
        res = 2;
        return res;
    }

    // -1 => the forest has only trees

    if (map == 0) {
        res = 0;
        return res;
    }
    // Brokilon
    k = 0;

    for (i = 0; i <= 63; i++) {
        bit_curent = (map >> i) & (uint64_t) 1;
        if (bit_curent == 1)
            k++;
    }

    if (k == 2) {
        res = 1;
        return res;
    }

    // forest with 2 trees = Hindar

    if (k % 4 != 0) {
        res = 3;
        return res;
    }

    k = 0;

    for (i = 0; i <= 63; i++) {
        bit_curent = (map >> i) & (uint64_t) 1;
        if(bit_curent == 1)
            k++;
        // counting the active bits

        else if (k == 4)
            k = 0;

        // if the bit is 0, it counts the num. of elements of the group
        // if there are 4 elements, it is valid for Brokilon

        else if (k != 0) {
            res = 3;
            return res;
        }
        // otherwise it's a Caed Dhu forest
    }
    res = 0;

     return res;
}


uint8_t trial_of_the_dreams(uint32_t map)
{
    /*
     * For this final trial, the candidates go into a trance and when
     * they woke up they would be a fully fledged witcher.
     *
     * For this task, you need to help the witcher find the number
     * of steps that would take the candidate from the dream realm to
     * the real world.
     *
     * The "map" variable would have only 2 bits of 1:
     * - candidate location
     * - portal location
     *
     * You should put in the "res" variable the distance from the
     * candidate position to the portal.
     *
     *  Ex:
     *  [0][0][0][0][0][0]....[1][0][0][0][0][1][0]....[0][0][0]
     *
     *  res = 5
     */

    uint8_t res = -1;

    /* TODO */
    uint8_t i;
    uint8_t position;
    uint8_t portal;
    uint8_t current_bit;
    uint8_t k;

    k = 1;

    for (i = 0; i <= 31; i++) {
        current_bit = (map >> i) & (uint32_t) 1;

            if (current_bit == 1 && k == 1) {
                position = i;
                k++;
            }

            else if (current_bit == 1 && k == 2) {
                portal = i;
                break; 
            }
    }

    res = portal - position;

    return res;
}