const int LIGHT_CNT = 3;
const int duration[] = { 2000, 500, 2000 };
const char *desc[3] = { "red", "yellow", "green" };
const char *light_stat[2] = { "亮", "灭" };

const byte push = PUSH2;
const int green = 2;
int l = 0;

void lighton(int light) {
  Serial.println(desc[light]);
  // Serial.println(light_stat[0]);
}
void lightoff(int light) {
  // Serial.print(desc[light]);
  // Serial.println(light_stat[1]);
  ;
}
void update() {
  lighton(l);
	if(l == 2) {
		delay(duration[l] - 1000);
		for(int i = 0; i < 5; ++i) {
			lightoff(l);
			delay(100);
			lighton(l);
			delay(100);
		}
	} else {
		delay(duration[l]);
	}
  lightoff(l);
}

void pass() {
  l = green;
  for(int i = 0; i < LIGHT_CNT; ++i) {
    lightoff(i);
  }
  update();
}

void setup() {
  Serial.begin(115200);
  pinMode(push, INPUT_PULLUP);
  attachInterrupt(push, pass, RISING);
  l = 0;
}

void loop() {
  update();
  l = (++l) % LIGHT_CNT;
}
