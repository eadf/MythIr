/*
 * A simple IR receiver for MythTV.
 * It is intended for Arduinos with Keyboard emulation (Leonardo, Due, Micro etc, etc)
 * But i guess it could easily be converted to use a PS/2 keyboard library as well.
 *
 * Dependencies: a clone of IRRemove by Ken Shirriff : https://github.com/eadf/Arduino-IRremote.git
 * 
 */

#include <IRremote.h>

// Comment out this line for serial debugging:
#define USE_KEYBOARD


#ifndef USE_KEYBOARD
  #define USE_SERIAL
#else 
  #undef USE_SERIAL
#endif


#ifndef USE_KEYBOARD
// these values are copied from arduino/USBAPI.h
// An ordinary UNO can't access these values even if USBAPI.h is included (at least if we don't mess with system #defines like USBCON)

#define KEY_LEFT_CTRL           0x80
#define KEY_LEFT_SHIFT          0x81
#define KEY_LEFT_ALT            0x82
#define KEY_LEFT_GUI            0x83
#define KEY_RIGHT_CTRL          0x84
#define KEY_RIGHT_SHIFT         0x85
#define KEY_RIGHT_ALT           0x86
#define KEY_RIGHT_GUI           0x87

#define KEY_UP_ARROW            0xDA
#define KEY_DOWN_ARROW          0xD9
#define KEY_LEFT_ARROW          0xD8
#define KEY_RIGHT_ARROW         0xD7
#define KEY_BACKSPACE           0xB2
#define KEY_TAB                 0xB3
#define KEY_RETURN              0xB0
#define KEY_ESC                 0xB1
#define KEY_INSERT              0xD1
#define KEY_DELETE              0xD4
#define KEY_PAGE_UP             0xD3
#define KEY_PAGE_DOWN           0xD6
#define KEY_HOME                0xD2
#define KEY_END                 0xD5
#define KEY_CAPS_LOCK           0xC1
#define KEY_F1                  0xC2
#define KEY_F2                  0xC3
#define KEY_F3                  0xC4
#define KEY_F4                  0xC5
#define KEY_F5                  0xC6
#define KEY_F6                  0xC7
#define KEY_F7                  0xC8
#define KEY_F8                  0xC9
#define KEY_F9                  0xCA
#define KEY_F10                 0xCB
#define KEY_F11                 0xCC
#define KEY_F12                 0xCD

#endif

static const int RECV_PIN = 2;
static const int POWER_PIN = 3;
static const int SLOW_REPEAT = 125;
static const int FAST_REPEAT = 25;

IRrecv irrecv(RECV_PIN);
decode_results results;

void virtualKeyBoard(char key){
#ifdef USE_KEYBOARD
   Keyboard.press(key); 
#endif
}

void virtualSerialPrint(String s){
#ifdef USE_SERIAL
   Serial.print(s);
#endif
}

void virtualSerialPrintln(String s){
#ifdef USE_SERIAL
   Serial.println(s);
#endif
}

bool handleHauppauge(int codeValue) {
  bool handled = false;
  int delayValue = FAST_REPEAT;
  switch ( codeValue ) {
    case 0x89247451:
    case 0xC62ACE9F:
      virtualSerialPrintln("Hauppauge Down");
      virtualKeyBoard(KEY_DOWN_ARROW);
      handled = true;
      break;
    case 0x8C247908:
    case 0xC52ACD0A:
      virtualSerialPrintln("Hauppauge Up");
      virtualKeyBoard(KEY_UP_ARROW);
      handled = true;
      break;  
    case 0x4A163A7E:
    case 0xAFF26B20:
      virtualSerialPrintln("Hauppauge Right");
      virtualKeyBoard(KEY_RIGHT_ARROW);
      handled = true;
      break;
    case 0x2D125EBE:
    case 0x885F6860:
      virtualSerialPrintln("Hauppauge FWD");
      virtualKeyBoard(KEY_RIGHT_ARROW);
      handled = true;
      break;
    case 0x4B163C13:
    case 0xACF26669:
      virtualSerialPrintln("Hauppauge Left");
      virtualKeyBoard(KEY_LEFT_ARROW);
      handled = true;
      break;
    case 0x8FFB894E:
    case 0xF3ADCC0C:
      virtualSerialPrintln("Hauppauge BWD");
      virtualKeyBoard(KEY_LEFT_ARROW);
      handled = true;
      break;
    case 0xBB6899B:
    case 0xD5CF0661:
      virtualSerialPrintln("Hauppauge Ok");
      virtualKeyBoard(' ');
      handled = true;
      delayValue = SLOW_REPEAT;
      break; 
    case 0x87E174B5:
    case 0x9AEDB5FB:
      virtualSerialPrintln("Hauppauge Green");
      virtualKeyBoard(KEY_F11);
      handled = true;
      break;    
    case 0xB2CDF6E4:
    case 0x2140D662:
      virtualSerialPrintln("Hauppauge Red");
      virtualKeyBoard(KEY_F10);
      handled = true;
      break; 
    case 0x6DC3EC99:
    case 0x5EB7B1A3:
      virtualSerialPrintln("Hauppauge Blue");
      virtualKeyBoard(KEY_F10);
      handled = true;
      break;
    case 0xB21542AA:
    case 0xADE36EE8:
      virtualSerialPrintln("Hauppauge Yellow");
      virtualKeyBoard(KEY_F10);
      handled = true;
      break;
    case 0xF0A82194:
    case 0x609BB826:
      virtualSerialPrintln("Hauppauge Mute");
      virtualKeyBoard(KEY_F9);
      handled = true;
      delayValue = SLOW_REPEAT;
      break;
    case 0x77E1FAC1:
      virtualSerialPrintln("Hauppauge Pause");
      virtualKeyBoard('p');
      handled = true;
      delayValue = SLOW_REPEAT;
      break; 
    case 0xA9C698DA:
    case 0x86057268:
    case 0xF772111B:
      virtualSerialPrintln("Hauppauge Back/Exit");
      virtualKeyBoard(KEY_ESC);
      handled = true;
      delayValue = SLOW_REPEAT;
      break; 
    case 0x895F69F3:
    case 0x2E126051:
      virtualSerialPrintln("Hauppauge Play");
      virtualKeyBoard('p');
      handled = true;
      delayValue = SLOW_REPEAT;
      break; 
    case 0xAE61E2CB:
    case 0x5314D925:
      virtualSerialPrintln("Hauppauge Stop");
      virtualKeyBoard('p');
      handled = true;
      delayValue = SLOW_REPEAT;
      break;
    case 0xDFE32936:
    case 0xDBA319C:
      virtualSerialPrintln("Hauppauge Pause");
      virtualKeyBoard('p');
      handled = true;
      delayValue = SLOW_REPEAT;
      break;
    case 0x5C1C240B:
    case 0xF63FF365:
      virtualSerialPrintln("Hauppauge FFWD");
      virtualKeyBoard(KEY_PAGE_DOWN);
      delayValue = SLOW_REPEAT;
      handled = true;
      break;
    case 0xAB68808:
    case 0xD4CF04CE:
      virtualSerialPrintln("Hauppauge FBWD");
      virtualKeyBoard(KEY_PAGE_UP);
      delayValue = SLOW_REPEAT;
      handled = true;
      break;
    case 0x71BFFC81:
    case 0x84D9E853:
      virtualSerialPrintln("Hauppauge Menu");
      virtualKeyBoard('m');
      handled = true;
      delayValue = SLOW_REPEAT;
      break;
    case 0x85D9E9E6:
    case 0x6EBFF7C8:
      virtualSerialPrintln("Hauppauge Blank");
      virtualKeyBoard('d');
      handled = true;
      delayValue = SLOW_REPEAT;
      break;
    case 0xC5E2063C:
    case 0xF158F416:
      virtualSerialPrintln("Hauppauge Full");
      virtualKeyBoard(KEY_RIGHT_ALT);
      virtualKeyBoard(KEY_F11);
      handled = true;
      delayValue = SLOW_REPEAT;
      break;

   case 0x7741AE45:
   case 0xDCA391EB:
      virtualSerialPrintln("Hauppauge 1");
      virtualKeyBoard('1');
      handled = true;
      delayValue = SLOW_REPEAT;
      break;
   case 0x6C3566C:
   case 0x6E3C936E:
      virtualSerialPrintln("Hauppauge 2");
      virtualKeyBoard('1');
      handled = true;
      delayValue = SLOW_REPEAT;
      break;
   case 0x42D5986:
   case 0x69F469B4:
      virtualSerialPrintln("Hauppauge 3");
      virtualKeyBoard('1');
      handled = true;
      delayValue = SLOW_REPEAT;
      break;
   case 0xBA16A8A2:
   case 0x8920CF74:
      virtualSerialPrintln("Hauppauge 4");
      virtualKeyBoard('1');
      handled = true;
      delayValue = SLOW_REPEAT;
      break;
   case 0xBB16AA35:
   case 0x8A20D107:
      virtualSerialPrintln("Hauppauge 5");
      virtualKeyBoard('1');
      handled = true;
      delayValue = SLOW_REPEAT;
      break;
   case 0xFB283EAD:
   case 0x94142E3B:
      virtualSerialPrintln("Hauppauge 6");
      virtualKeyBoard('1');
      handled = true;
      delayValue = SLOW_REPEAT;
      break;
   case 0x7BDA68A:
   case 0x83BCA2F0:
      virtualSerialPrintln("Hauppauge 7");
      virtualKeyBoard('1');
      handled = true;
      delayValue = SLOW_REPEAT;
      break;
   case 0x74E7452C:
   case 0xE35A24AA:
      virtualSerialPrintln("Hauppauge 8");
      virtualKeyBoard('1');
      handled = true;
      delayValue = SLOW_REPEAT;
      break;
   case 0xE45A263F:
   case 0x71E74075:
      virtualSerialPrintln("Hauppauge 9");
      virtualKeyBoard('1');
      handled = true;
      delayValue = SLOW_REPEAT;
      break;
   case 0xDBA39056:
   case 0x7A41B2FC:
      virtualSerialPrintln("Hauppauge 0");
      virtualKeyBoard('1');
      handled = true;
      delayValue = SLOW_REPEAT;
      break;
      
      
   // No keyboard mappings for these   
   case 0xA2C9559A:
   case 0x5A552E28:
      virtualSerialPrintln("Hauppauge Rec");
      handled = true;
      delayValue = SLOW_REPEAT;
      break;
  case 0x6DFCBA0A:
  case 0x6DC95AF8:
      virtualSerialPrintln("Hauppauge Go");
      handled = true;
      delayValue = SLOW_REPEAT;
      break;
  case 0xC8E20AF5:
  case 0xF058F283:
      virtualSerialPrintln("Hauppauge Power");
      handled = true;
      delayValue = SLOW_REPEAT;
      break;
  }
  if (handled) {
    delay(delayValue);
#ifdef USE_KEYBOARD
    Keyboard.releaseAll();
#endif
  }
  return handled;
}


void setup()
{
#ifdef USE_SERIAL  
  Serial.begin(9600);
  delay(500);
  Serial.println("Running in serial mode - no key presses will be generated.");
#endif
#ifdef USE_KEYBOARD
  Keyboard.begin();
#endif
  irrecv.enableIRIn(); // Start the receiver
  pinMode(POWER_PIN, OUTPUT);
  digitalWrite(POWER_PIN, true);
}

void loop() {
  if (irrecv.decodeOnlyHash(&results)) {
    if (!handleHauppauge(results.value)) {
#ifdef USE_SERIAL
      // for easy copy & paste back into code 
      Serial.print("    case 0x");
      Serial.print(results.value, HEX);
      Serial.println(":");
#endif
    }
    irrecv.resume(); // Receive the next value
  }
  delay(FAST_REPEAT);
}
