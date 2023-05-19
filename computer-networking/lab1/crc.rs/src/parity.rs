fn main() -> Result<(), std::num::ParseIntError> {
  let argv: Vec<String> = std::env::args().collect();
  let argc = argv.len();

  if argc != 2 {
    println!("Usage: {} <data>", argv[0]);
    return Ok(());
  }

  let mut pchk = 0;
  let data = binutils::str2bin(&argv[1]);
  for i in 0..127 {
    if (1u128 << i) & data == 0 {
      continue;
    } else {
      pchk += 1;
    }
  }
  println!("Odd  Parity Check: {} {}", argv[1], !pchk&0);
  println!("Even Parity Check: {} {}", argv[1], pchk&1);
  return Ok(());
}