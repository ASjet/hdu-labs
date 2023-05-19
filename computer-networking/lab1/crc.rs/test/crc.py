#!/bin/env python3
import os, sys, random

binpath = "target/release/crcchk"

def crc_remainder(input_bitstring, polynomial_bitstring, initial_filler):
    """Calculate the CRC remainder of a string of bits using a chosen polynomial.
    initial_filler should be '1' or '0'.
    """
    polynomial_bitstring = polynomial_bitstring.lstrip('0')
    len_input = len(input_bitstring)
    initial_padding = (len(polynomial_bitstring) - 1) * initial_filler
    input_padded_array = list(input_bitstring + initial_padding)
    while '1' in input_padded_array[:len_input]:
        cur_shift = input_padded_array.index('1')
        for i in range(len(polynomial_bitstring)):
            input_padded_array[cur_shift + i] \
            = str(int(polynomial_bitstring[i] != input_padded_array[cur_shift + i]))
    return ''.join(input_padded_array)[len_input:]

def crc_check(input_bitstring, polynomial_bitstring, check_value):
    """Calculate the CRC check of a string of bits using a chosen polynomial."""
    polynomial_bitstring = polynomial_bitstring.lstrip('0')
    len_input = len(input_bitstring)
    initial_padding = check_value
    input_padded_array = list(input_bitstring + initial_padding)
    while '1' in input_padded_array[:len_input]:
        cur_shift = input_padded_array.index('1')
        for i in range(len(polynomial_bitstring)):
            input_padded_array[cur_shift + i] \
            = str(int(polynomial_bitstring[i] != input_padded_array[cur_shift + i]))
    return ('1' not in ''.join(input_padded_array)[len_input:])

def test(bin, msg, ptn):
  binresult = os.popen("{} {} {}".format(bin, msg, ptn)).read().strip()
  posresult = "CRC-{}: {} {}".format(len(ptn)-1, msg, crc_remainder(msg, ptn, '0'))
  return binresult == posresult

if __name__ == "__main__":
  if len(sys.argv) == 1:
    print("Usage:")
    print(" {} <data> <pattern>".format(sys.argv[0]))
    print(" {} [-chk] <data> <pattern>".format(sys.argv[0]))
    print(" {} [-tst] <bin_path> <test_count>".format(sys.argv[0]))
    sys.exit(0)

  if sys.argv[1] == "-c":
    print(crc_check(sys.argv[2], sys.argv[3], sys.argv[4]))
  elif sys.argv[1] == "-t":
    succeed_cnt = 0
    failed_cnt = 0
    binpath = sys.argv[2]
    count = int(sys.argv[3])
    for i in range(count):
      msg = bin(random.randint(0, 2**32-1))[2:]
      ptn = bin(random.randint(0, 2**16-1))[2:]
      result = test(binpath, msg, ptn)
      print("Data: {}\nPattern: {}\nTest result: {}".format(msg, ptn, "Succeed" if result else "Failed"))
      if result:
        succeed_cnt += 1
      else:
        failed_cnt += 1
    print("Passed: {}/{}".format(succeed_cnt, count))
  else:
    print("CRC-{}: {} {}".format(len(sys.argv[2])-1, sys.argv[1], crc_remainder(sys.argv[1], sys.argv[2], '0')))
