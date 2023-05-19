// Max 128bit
pub fn str2bin(string: &String) -> u128 {
    let mut ret: u128 = 0;
    for c in string.chars() {
        ret = match c {
            '1' => (ret << 1) + 1,
            '0' => ret << 1,
            ' ' => continue,
            _ => panic!("Parsing error in\n{}\n", string)
        };
    }
    return ret;
}

pub fn bin2str(num: u128, width: i32) -> String {
    let mut s = String::new();
    let mut i = 1u128 << 127;
    for _j in 0..128-width {
        if i & num != 0 {
            break;
        } else {
            i >>= 1;
        }
    }
    while i > 0 {
        s += if num & i != 0 {
            "1"
        } else {
            "0"
        };
        i >>= 1;
    }
    return s;
}

pub fn bitlen(num: u128) -> i32 {
  let mut len = 0i32;
  let maxlen = 127;
  for i in 0..maxlen {
    if (num & (1u128 << i)) != 0 {
      len = i;
    }
  }
  return len + 1;
}