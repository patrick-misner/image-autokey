#ifndef USER_USB_RAM
#error "This example needs to be compiled with a USER USB setting"
#endif

#include "src/userUsbHidKeyboard/USBHIDKeyboard.h"

#define LED_BUILTIN 30
#define P32 32  // Define P32 pin
#define P14 14  // Define P14 pin
#define P15 15  // Define P15 pin
#define P16 16  // Define P16 pin
#define P17 17  // Define P17 pin
#define P31 31  // Define P31 pin
#define P30 30  // Define P30 pin
#define P11 11  // Define P11 pin
#define P33 33  // Define P33 pin
#define P34 34  // Define P34 pin

// Variables
const char *imgPw = "imagePWORD";
const char *winUser = "USERNAME";
const char *winPw = "PASSWORD";

// Function to type a string
void typeString(const char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        Keyboard_write(str[i]);
    }
}

// Function to Key press and Delay
void pressKey(uint8_t key) {
    Keyboard_press(key);
    delay(25);  // Short delay to simulate a real key press
    Keyboard_release(key);
    delay(475)
}

// Check if P32 and P14 are shorted
bool checkIfOpt1Shorted() {
    digitalWrite(P32, LOW);
    delay(50);
    bool opt1IsShorted = digitalRead(P14) == LOW;
    digitalWrite(P32, HIGH);
    delay(50);
    return opt1IsShorted; 
}

// Check if P14 and P15 are shorted P14 reads high on boot
bool checkIfOpt2Shorted() {
    digitalWrite(P15, LOW);
    delay(50);
    bool opt2IsShorted = digitalRead(P14) == LOW;
    digitalWrite(P15, HIGH);
    delay(50);
    return opt2IsShorted;
}

// Check if P15 and P16 are shorted P16 reads LOW on boot
bool checkIfOpt3Shorted() {
    delay(50);
    digitalWrite(P17, LOW);
    delay(50);
    bool opt3IsShorted = digitalRead(P16);
    digitalWrite(P15, LOW);
    digitalWrite(P17, HIGH);
    delay(50);
    return opt3IsShorted;
}

bool checkIfOpt4Shorted() {
    delay(50);
    bool opt4IsShorted = digitalRead(P16);
    digitalWrite(P17, LOW);
    delay(50);
    return opt4IsShorted;
}




void setup() {
    USBInit();
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);
    pinMode(P32, OUTPUT);
    pinMode(P14, INPUT);
    pinMode(P15, OUTPUT);
    pinMode(P16, INPUT);   
    pinMode(P17, OUTPUT);
    pinMode(P31, INPUT);
    pinMode(P32, OUTPUT);
    delay(5000);  // Initial delay to ensure USB is ready

    // Check if P32 and P14 are shorted
    bool opt1IsShorted = checkIfOpt1Shorted();

    // Check if P14 and P15 are shorted
    bool opt2IsShorted = checkIfOpt2Shorted();

    // Check if P15 and P16 are shorted
    bool opt3IsShorted = checkIfOpt3Shorted();

    // Check if P16 and P17 are shorted
    bool opt4IsShorted = checkIfOpt4Shorted();

    if (opt1IsShorted) {
      typeString("OPTION 1");
    }

    if (opt2IsShorted) {
      typeString("OPTION 2");
    }

    if (opt3IsShorted) {
      typeString("OPTION 3");
    }

    if (opt4IsShorted) {
      typeString("OPTION 4");
    }
    
    Keyboard_press(KEY_RETURN);  // HID Code for Enter
    delay(25);
    Keyboard_release(KEY_RETURN);
    typeString(winPw);
}  // <-- Closing brace for setup()

void loop() {
    // Example usage

    // Add any other code you need in the loop
}
