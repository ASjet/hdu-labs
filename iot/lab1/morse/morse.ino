// most launchpads have a red LED
#define LED RED_LED
//see pins_energia.h for more LED definitions
//#define LED GREEN_LED

#define DOT '0'
#define DASH '1'
#define SPLIT '.'
#define SPACE ' '

const char * morse_map(char chr) {
  switch (chr) {
    case 'A': return "01";
    case 'B': return "1000";
    case 'C': return "1010";
    case 'D': return "100";
    case 'E': return "0";
    case 'F': return "0010";
    case 'G': return "110";
    case 'H': return "0000";
    case 'I': return "00";
    case 'J': return "0111";
    case 'K': return "101";
    case 'L': return "0100";
    case 'M': return "11";
    case 'N': return "10";
    case 'O': return "111";
    case 'P': return "0110";
    case 'Q': return "1101";
    case 'R': return "010";
    case 'S': return "000";
    case 'T': return "1";
    case 'U': return "001";
    case 'V': return "0001";
    case 'W': return "011";
    case 'X': return "1001";
    case 'Y': return "1011";
    case 'Z': return "1100";
    case '0': return "11111";
    case '1': return "01111";
    case '2': return "00111";
    case '3': return "00011";
    case '4': return "00001";
    case '5': return "00000";
    case '6': return "10000";
    case '7': return "11000";
    case '8': return "11100";
    case '9': return "11110";
  }
}

void blink(char _flag, int _delay) {
  switch (_flag) {
    case DOT:
      digitalWrite(LED, HIGH);
      break;
    case DASH:
      digitalWrite(LED, HIGH);
      delay(_delay*2);
      break;
    case SPLIT:
      digitalWrite(LED, LOW);
      delay(_delay*2);
      break;
    case SPACE:
      digitalWrite(LED, LOW);
      delay(_delay*6);
      break;
  }
  digitalWrite(LED, LOW);
  delay(_delay);
}

void blinkbin(const char * _str, int _length, int _delay) {
  char * end = (char*)_str + _length;
  char * morse;
  for(char * i = (char*)_str; i != end; ++i) {
    if(*i == SPACE) {
      blink(*i, _delay);
    } else {
      morse = (char*)morse_map(*i);
      for(int j = 0; j < strlen(morse); ++j) {
        blink(morse[j], _delay);
      }
      blink(SPLIT, _delay);
    }
  }
}

// the setup routine runs once when you press reset:
void setup() {
  // initialize the digital pin as an output.
  pinMode(LED, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  // H    E L    L    O   W   O   R   L    D
  // .... . ._.. ._.. ___ .__ ___ ._. ._.. _..
  const char data[] = "HELLO WORLD";
  blinkbin(data, 11, 200);
}
