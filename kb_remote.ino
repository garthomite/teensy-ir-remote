#include <IRremote.h>

const int RECV_PIN = 12;
const int skipRepeat = 3;
int repeatCount = 0;
int lastBtn = 0;

IRrecv irrecv(RECV_PIN);

decode_results results;

void sendKey(int key) //Send a single key
{
  Keyboard.set_key1(key);
  Keyboard.send_now();    
  Keyboard.set_key1(0);
  Keyboard.send_now();  
}

void sendForButton(int btn) //Map the button and send the command on the keyboard
{
  if (btn == 0xFFFFFFFF){   
    repeatCount+=1;
    if (repeatCount > skipRepeat){
        btn = lastBtn;
    } else {
      return;
    }
  } else {
    repeatCount = 0;
    lastBtn = btn;
  }
  Serial.print("Got key: ");
  Serial.println(btn, HEX);
  
  switch (btn) {
    case 0x2C2E80FF: //UP
      sendKey(KEY_UP);
      break;
    case 0x5A1A483D:
      sendKey(KEY_DOWN); //DOWN
      break;
    case 0x9578646A:
      sendKey(KEY_LEFT); //LEFT
      break;
    case 0xDC18602C:
      sendKey(KEY_RIGHT); //RIGHT
      break;
    case 0xCB3CC07F:
      sendKey(KEY_ENTER); //OK
      break;
    case 0x2935B9A7:
      sendKey(KEY_BACKSPACE); //EXIT
      break;
    case 0xFEF03E2C:
      Keyboard.print("r");  //REV
      break;
    case 0x313599EC:
      Keyboard.print("p"); //PLAN
      break;
    case 0x66E97044:
      Keyboard.print("f");  //FWD
      break;        
    case 0xD6599F48:
      Keyboard.print("x");  //STOP
      break;
    case 0xD922D768:
      Keyboard.print(" ");  //PAUSE
      break;
    case 0x603F1D32:
      sendKey(KEY_PAGE_UP);  //PAGE UP
      break;
    case 0x9715433C:
      sendKey(KEY_PAGE_DOWN); //PAGE DOWN
      break;
    case 0x19EB3488: //SETTINGS
      Keyboard.print("c"); //
      break;
    case 0x4666CC0D: //INFO
      Keyboard.print("i");
      break;
    case 0xE9C74319: //GUIDE
      Keyboard.print("m");
      break;
  }
}

void setup()
{
  Serial.begin(9600);
  Serial.println("Starting");
  irrecv.enableIRIn(); // Start the receiver
  irrecv.blink13(true);
}

void loop() {
  if (irrecv.decode(&results)) {
    sendForButton(results.value);
    irrecv.resume(); // Receive the next value
  }
}


