const int ledMerah = 8;
const int buzz = 7;
const int button1 = 2;
const int button2 = 3;
const int button3 = 4;
int buttonState1, buttonState2, buttonState3;
int oldButton1, oldButton2, oldButton3 = 0;
int state1, state2, state3 = 0;
void setup() {
pinMode(ledMerah, OUTPUT);
pinMode(buzz, OUTPUT);
pinMode(button1, INPUT_PULLUP);

}
void loop() {
buttonState1 = digitalRead(button1);
if(!buttonState1 && !oldButton1){
if(state1 == 0){
digitalWrite(ledMerah, HIGH);
state1 = 1;

}else if(state1 == 1){
digitalWrite(ledMerah, LOW);
digitalWrite(buzz, HIGH);
state1 = 2;
}
else if(state1 == 2){
digitalWrite(buzz, LOW);
state1 =0;
}
delay(150);
oldButton1 = 1;
}else if(buttonState1 && oldButton1){
oldButton1 = 0;
}
}
