from DESencrypt import *

def test_P8():
    start = "0123456789"
    end = P8(start)
    print("\n P8 _______")
    print("Expected: 52637498")
    print("Actual:  ",end)

def test_P10():
    start = "0123456789"
    end = P10(start)
    print("\n _______")
    print("Expected: 2416390875")
    print("Actual:  ",end)

def test_IP():
    start = "01234567"
    end1, end2 = IP(start)
    print("\n IP _______")
    print("Expected: 1520 3746")
    print("Actual:  ", end1,end2)

def test_IIP():
    start = "01234567"
    end1, end2 = IIP(start)
    print("\n IIP _______")
    print("Expected: 3024 6175")
    print("Actual:  ",end1,end2)

def test_cyclic_shift():
    left = "1100"
    right = "0011"
    shift = -1
    answer1, answer2 = cyclic_shift(left, right, shift)
    print("\nCyclic left shift _______")
    print("Expected:  1001 0110")
    print("Actual:   ", answer1, answer2)

def test_generate_two_keys():
    tb = "0011110101" #tenbit
    p1 = "1100110011" #after P10
    l1,r1 = "10011", "00111"
    l2,r2 = "01110", "11100"
    p8one = "00011111"
    p8two = "11111000"
    key1,key2 = generate_two_keys(tb)
    print("\ngenerate_two_keys _______")
    print("Expected:",p8one,p8two)
    print("Actual:  ",key1,key2)

def test_expand_four():
    start = "0110"
    end = expand_four(start)
    print("\nexpand_four _______")
    print("Expected: 00111100")
    print("Actual:  ",end)


def test_get_row_col():
    start = "0101"
    end1,end2 = get_row_col(start)
    print("\nget_row_col _______")
    print("Expected: 1 2")
    print("Actual:  ",end1,end2)


def test_map_bits():
    start1 = "0110"
    start2 = "01101001"
    final8 = "01010101"
    r , c = 1 , 2
    S0_results = "0101"
    end = map_bits(start1,start2)
    print("\n map_bits _______")
    print("Expected:",S0_results)
    print("Actual:  ",end)

def test_xor():
    start1 = "01"
    start2 = "11"
    end = xor(start1,start2)
    print("\ntest_xor _______")
    print("Expected: 10")
    print("Actual:  ",end)


def test_xor_map():
    # print("\n xor_map _______")
    # print("Expected: ")
    # print("Actual:  ")
    pass

def test_encrypt_it():
    # print("\n _______")
    # print("Expected: ")
    # print("Actual:  ")
    pass

def test_num_to_byte():
    start = 15
    end = num_to_byte(start)
    print("\nnum_to_byte _______")
    print("Expected: 1111")
    print("Actual:  ",end)
    

def test_DES_ENCRYPT():
    # print("\nDES_ENCRYPT _______")
    # print("Expected: ")
    # print("Actual:  ")
    pass

def test():
    test_P8()
    test_P10()
    test_IP()
    test_IIP()
    test_cyclic_shift()
    test_generate_two_keys()
    test_expand_four()
    test_get_row_col()
    test_map_bits()
    test_xor()
    test_xor_map()
    test_encrypt_it()
    test_num_to_byte()
    test_DES_ENCRYPT()


if __name__ == "__main__":
    test()
#Physics lab door key 160218
