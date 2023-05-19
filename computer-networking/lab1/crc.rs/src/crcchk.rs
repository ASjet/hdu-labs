use binutils::{bitlen, str2bin, bin2str};
fn main() -> Result<(), std::num::ParseIntError> {
    let argv: Vec<String> = std::env::args().collect();
    let argc = argv.len();

    if argc != 3 {
        println!("Usage: {} <file> <ptn>", argv[0]);
        return Ok(());
    }

    let ptn = str2bin(&argv[2]);
    let len = bitlen(ptn) - 1;
    let msg = str2bin(&argv[1]);
    let crc = mod2div(msg << len, ptn);
    let msg_bin = bin2str(msg, 0);
    let crc_bin = bin2str(crc, len);

    println!("CRC-{}: {} {}", len, msg_bin, crc_bin);
    return Ok(());
}

fn mod2div(a: u128, b: u128) -> u128 {
    let mut lena = bitlen(a);
    let lenb = bitlen(b);
    let mut dived = a;
    if lena < lenb {
        return a;
    }
    let mut diver = b << (lena - lenb);
    loop {
        dived ^= diver;
        lena = bitlen(dived);
        if lena < lenb {
            break;
        }
        diver = b << (lena - lenb);
    }
    return dived;
}

#[allow(dead_code)]
fn crc32(data: &String, ptn: u64) -> u64 {
    let len_ptn = bitlen(ptn as u128);
    let mut len_diven;
    let mut diven = 0u64;

    for c in data.as_bytes() {
        diven |= *c as u64;
        len_diven = bitlen(diven as u128);
        while len_diven >= len_ptn {
            diven ^= ptn << (len_diven - len_ptn);
            len_diven = bitlen(diven as u128);
        }
        diven <<= 8;
    }
    diven >>= 8;
    return diven;
}
