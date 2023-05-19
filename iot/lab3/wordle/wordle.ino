const int count = 6;
String words[] = {
  "ruffs",
  "giant",
  "sulks",
  "loped",
  "oaken",
  "weedy",
  "pried",
  "berry",
  "wider",
  "eland",
  "lofts",
  "legit",
  "halts",
  "shaft",
  "treys",
  "tided",
  "grass",
  "spear",
  "befit",
  "vests",
  "licit",
  "mouse",
  "sarky",
  "lover",
  "bagel",
  "rapes",
  "rends",
  "daisy",
  "jerks",
  "doors",
  "revel",
  "amaze",
  "ninth",
  "khaki",
  "medic",
  "madam",
  "chaos",
  "squad",
  "smell",
  "shunt",
  "effed",
  "fades",
  "dealt",
  "viols",
  "educe",
  "chocs",
  "lisle",
  "idiot",
  "otter",
  "joyed",
  "umped",
  "doers",
  "tails",
  "tilde",
  "growl",
  "hoist",
  "lumps",
  "elver",
  "dower",
  "alter",
  "drops",
  "purge",
  "leafs",
  "durum"
};
String buffer = "";
String err_msg = " is not a valid world! Please try again";
String win_msg = " congratulations!";
String lost_msg = "Sorry, you lose! Answer:";
volatile bool receiveAll = false;
int no = 0, iter = 0;
String input = "";
String sel = "";
String result = "";
bool win = false, err = false;

String match(String input, String ans) {
  String res = "..... Wrong place: ";
  String rp = "";
  int i = 0, j = 0, right_cnt = 0;
  if(input.length() != 5) {
    return (input+err_msg);
  } else {
    for(i = 0; i < 5; ++i) {
      j = ans.indexOf(input[i]);
      if(j == -1) {
        continue;
      } else {
        if(input[i] == ans[i]) {
          ++right_cnt;
          res[i] = input[i];
        } else {
          rp += input[i];
        }
      }
    }
  }
  if(right_cnt == 5) {
    return input+win_msg;
  } else {
    return res + rp;
  }
}

void setup() {
  Serial.begin(115200);
  buffer.reserve(512);
  Serial.println("Select a word[1-64]");
}

void loop() {
  if(receiveAll) {
    if(no == 0) {
      no = buffer.toInt();
      if(no == 0) {
        Serial.println(err_msg);
      } else {
        sel = words[no];
      }
      Serial.println(sel);
      buffer = "";
      receiveAll = false;
    } else {
      Serial.println(buffer);
      result = match(buffer, sel);
      Serial.println(result);

      if(win_msg.equals(result)) {
        Serial.println("Select a word[1-64]");
        no = 0;
        iter = 0;
      } else if (err_msg.equals(result)) {
        goto _next;
      }

      if(++iter > count) {
        Serial.println(lost_msg+sel);
        Serial.println("Select a word[1-64]");
        iter = 0;
      }
_next:
      buffer = "";
      receiveAll = false;
    }
  }
}

void serialEvent() {
  char chr = 0;
  while(Serial.available()) {
    while((chr = (char)Serial.read()) != '\n') {
      buffer += chr;
    }
    receiveAll = true;
  }
}