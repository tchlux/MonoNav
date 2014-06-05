#ifndef INCLUDED_CONSTANTS_H
#define INCLUDED_CONSTANTS_H

//HEX conversion
#define MAX_NUMERAL       10
#define MIN_DIGIT         '0'
#define MIN_LETTER        'A'
#define CHAR_LSB_MASK     0xF
#define HEX_CHAR_SHIFT    4

#define HASHCODE_SIZE     32
#define HEX_CHARS_PER_INT 8
#define BLOCS_PER_INT     4
#define HEX_PER_BLOCK     2
#define A_LOC             0
#define B_LOC             1
#define C_LOC             2
#define D_LOC             3


#define BLOCKS_IN_512     16
#define SHIFT_AMOUNT      8
#define CHARS_PER_BLOCK   4
#define BITS_IN_BYTE      8
#define BIT_MASK_32       0xFFFFFFFF
#define LONG_SHIFT        32
#define UINT_SIZE         BITS_IN_BYTE * sizeof(unsigned int)

#define INITIAL_A         0x67452301
#define INITIAL_B         0xEFCDAB89
#define INITIAL_C         0x98BADCFE
#define INITIAL_D         0x10325476
#define K_SIZE            64
#define NUM_ROUNDS        64
#define ROUNDS_PER_GROUP  64
#define GROUP_SIZE        16
#define GROUP_1           0
#define GROUP_2           1
#define GROUP_3           2
#define GROUP_4           3
#define SHIFT_SIZE        4

//Group specific information
#define GROUP_1_S         {7, 12, 17, 22}

#define GROUP_2_S         {5, 9, 14, 20}
#define G2_MULT           5
#define G2_ADD            1

#define GROUP_3_S         {4, 11, 16, 23}
#define G3_MULT           3
#define G3_ADD            5

#define GROUP_4_S         {6, 10, 15, 21}
#define G4_MULT           7
#define G4_ADD            0

#define EOS               '\0'

#define NOT_FOUND         -1
#endif
