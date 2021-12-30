#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 32 

#define OLED_RESET     4 
#define SCREEN_ADDRESS 0x3C 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int p = 0;
bool loopflag = false;
bool comma_flag = false;
bool run_loop = false;
char loop_array[230];
int la_pos = 0;

int freq = 50;

int bf_array[230];

void setup() {
  Serial.begin(9600);

  for (int i = 0; i < 10; i++){
    pinMode(2+i,OUTPUT);
  }
  
  
  for(int x = 0; x<230; x++) {
    
    bf_array[x] = x;
    
  }
  
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }


  display.display();
  delay(200); //short pause after initialisation 

  display.clearDisplay();

  display.display();
  delay(200);

  for (int i = 0; i<8; i++) {
    digitalWrite((2+i),LOW);
  }
  display.setTextSize(1);
  display.setCursor(0, 0);

  textprint("empty");
  display.display(); 
for(int count=0;count<230; count++){ loop_array[count]='#';} //empties the whole array

}

void comma_check(char inputchar){

  int ascii_num = int(inputchar);
  bf_array[p] = ascii_num;
  comma_flag=false;

}

void decode(char read_stuff) {

  if (read_stuff == '>') {
      p++;
      Serial.print("PointerPosition:");
      Serial.println(p);
    }

  if (read_stuff == ',') {
      comma_flag = true;
    }   

    if (read_stuff == '<') {
      p--;
      Serial.print("PointerPosition:");
    }

    if (read_stuff == '-') {
      bf_array[p] = (int(bf_array[p])-1);
    }

    if (read_stuff == '+') {
      bf_array[p] = (int(bf_array[p])+1);
    } 
   
    if (read_stuff == '.') {
      char printablechar = bf_array[p];
      textprint(String(printablechar));
      Serial.print(String(bf_array[p]));
    } 

    if (read_stuff == '[') {
      if (bf_array[p]!= 0) {
      loopflag = true;          
      }
    }
    if (read_stuff == ']') {
      la_pos = 0;
      loopflag = false;
      run_loop = true;
    }
}

void freqindicator(void){
  digitalWrite(9,LOW);
  delay(1000/freq);
  digitalWrite(9,HIGH);
  delay(1000/freq);
}

void loop() {
  
  freqindicator();

  char incomingByte;
  if (Serial.available() > 0) {
    
    incomingByte = Serial.read();
    char charbyte = char(incomingByte);
    
    binaryled(charbyte);

  if(comma_flag == true){
    comma_check(charbyte);
  }

   if(loopflag != true) {
    if (run_loop != true) {    

      decode(charbyte);          
 
    }
    else {
  
        while (bf_array[p] != 0) {

          for(int i=0; (loop_array[i] != '#'); i++){

            char instruction = loop_array[i];
            Serial.print(loop_array[i]);
            binaryled(loop_array[i]);
            decode(instruction);       
            freqindicator();                 
          }
                
          
        
      }  run_loop = false;        
    }
    } 
    else {
      if (charbyte == ']'){
        loopflag = false;
        run_loop = true;
      }
      else {
      loop_array[la_pos]=charbyte;
      la_pos++; }
      }
  
    Serial.print("Incoming Binary:");
    Serial.println(incomingByte,BIN);
   
  }
  
}

void binaryled (char c) {
  for (int i = 0; i<8; i++) {
    digitalWrite((2+i),LOW);
    int x = bitRead(c,i);
    if(x!=0){
      digitalWrite(2+i,HIGH);
    }
  }
}

 void errorled(void) {
  
  while(1==1){
    for (int i = 0; i<8; i++) {
    digitalWrite((2+i),LOW);
    }
    delay(500);
    for (int i = 0; i<8; i++) {
    digitalWrite((2+i),HIGH);
    }
    delay(500);
  
}
 }

void textprint(String text) {
  display.clearDisplay();
  Serial.println(text);
  display.setTextSize(3); 
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(text);
  display.display();   
  delay(20);

}
