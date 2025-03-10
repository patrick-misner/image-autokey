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
#define IMG_PW "imagePWORD"
#define WIN_USR = "USERNAME";
#define WIN_PW = "PASSWORD";

// Model 1 parameters
const char* model1BootKey = "KEY_F12";
unsigned long model1BootDelay = 5000;
int model1DownArrow = 1;
unsigned long model1LoginDelay = 50000;

// Model 2 parameters
const char* model2BootKey = "KEY_F12";
unsigned long model2BootDelay = 5000;
int model2DownArrow = 2;
unsigned long model2LoginDelay = 50000;

// Model 3 parameters
const char* model3BootKey = "KEY_F9";
unsigned long model3BootDelay = 5000;
int model3DownArrow = 2;
unsigned long model3LoginDelay = 50000;

// Model 4 parameters
const char* model4BootKey = "KEY_F9";
unsigned long model4BootDelay = 5000;
int model4DownArrow = 2;
unsigned long model4LoginDelay = 50000;

// Model 5 parameters
const char* model5BootKey = "KEY_F9";
unsigned long model5BootDelay = 5000;
int model5DownArrow = 2;
unsigned long model5LoginDelay = 50000;

// Pointers to hold the selected model parameters
const char* bootKey;
unsigned long bootDelay;
int downArrow;
unsigned long loginDelay;


// WinPE Option 1 parameters
const char* option1Step1 = IMG_PW;
const char* option1Step2 = "2";
const char* option1Step3 = "";

// WinPE Option 2 parameters
const char* option2Step1 = "2";
const char* option2Step2 = IMG_PW;
const char* option2Step3 = "2";

// WinPE Option 2 parameters
const char* option3Step1 = "2";
const char* option3Step2 = IMG_PW;
const char* option3Step3 = "2";

// Pointers to hold the selected WinPE Option parameters
const char* optionStep1;
const char* optionStep2;
const char* optionStep3;


// Function to type a string
void typeString(const char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        Keyboard_write(str[i]);
    }
    delay(500);
}

// Function to Key press and Delay
void typeKey(uint8_t key) {
    Keyboard_press(key);
    delay(25);
    Keyboard_release(key);
    delay(475);
}

// Function to type a single character (Maybe not needed?)
void typeCharacter(char c) {
    Keyboard_write(c);  // Writes the character as if typed on a keyboard
    delay(500);  // Short delay to simulate natural typing
}

void checkModel1() {
    digitalWrite(P32, LOW);
    delay(50);
    bool opt1IsShorted = digitalRead(P14) == LOW;
    digitalWrite(P32, HIGH);
    delay(50);
    if (opt1IsShorted) {
        bootKey = model1BootKey;
        bootDelay = model1BootDelay;
        downArrow = model1DownArrow;
        loginDelay = model1LoginDelay;
    }
}

void checkModel2() {
    digitalWrite(P15, LOW);
    delay(50);
    bool opt2IsShorted = digitalRead(P14) == LOW;
    digitalWrite(P15, HIGH);
    delay(50);
    if (opt2IsShorted) {
        bootKey = model2BootKey;
        bootDelay = model2BootDelay;
        downArrow = model2DownArrow;
        loginDelay = model2LoginDelay;
    }
}

void checkModel3() {
    delay(50);
    digitalWrite(P17, LOW);
    delay(50);
    bool opt3IsShorted = digitalRead(P16);
    digitalWrite(P15, LOW);
    digitalWrite(P17, HIGH);
    delay(50);
    if (opt3IsShorted) {
        bootKey = model3BootKey;
        bootDelay = model3BootDelay;
        downArrow = model3DownArrow;
        loginDelay = model3LoginDelay;
    }
}

void checkModel4() {
    delay(50);
    bool opt4IsShorted = digitalRead(P16);
    digitalWrite(P17, LOW);
    delay(50);
    if (opt4IsShorted) {
        bootKey = model4BootKey;
        bootDelay = model4BootDelay;
        downArrow = model4DownArrow;
        loginDelay = model4LoginDelay;
    }
}

void checkModel5() {
    digitalWrite(P30, LOW);
    delay(50);
    bool opt5IsShorted = digitalRead(P31) == LOW;
    digitalWrite(P30, HIGH);
    delay(50);
    if (opt5IsShorted) {
        bootKey = model5BootKey;
        bootDelay = model5BootDelay;
        downArrow = model5DownArrow;
        loginDelay = model5LoginDelay;
    }
}

void checkOption1() {
    digitalWrite(P34, LOW);
    delay(50);
    bool opt6IsShorted = digitalRead(P33) == LOW;
    digitalWrite(P34, HIGH);
    delay(50);
    if (opt6IsShorted) {
        optionStep1 = option1Step1;
        optionStep2 = option1Step2;
        optionStep3 = option1Step3;
    }
}

void checkOption2() {
    digitalWrite(P11, LOW);
    delay(50);
    bool opt7IsShorted = digitalRead(P33) == LOW;
    digitalWrite(P11, HIGH);
    delay(50);
    if (opt7IsShorted) {
        optionStep1 = option2Step1;
        optionStep2 = option2Step2;
        optionStep3 = option2Step3;
    }
}




void setup() {
    USBInit();
    checkModel1();
    checkModel2();
    checkModel3();
    checkModel4();
    checkModel5();
    checkOption1();
    checkTopion2();
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);
    pinMode(P32, OUTPUT);
    pinMode(P14, INPUT);
    pinMode(P15, OUTPUT);
    pinMode(P16, INPUT);   
    pinMode(P17, OUTPUT);
    pinMode(P30, OUTPUT);
    pinMode(P31, INPUT);
    pinMode(P11, OUTPUT);
    pinMode(P33, INPUT);
    pinMode(P34, OUTPUT);
    delay(5000);  // Initial delay to ensure USB is ready


    typeString(optionStep1);
    typeString(optionStep2);
    typeString(optionStep3);
    typeString("I want this to work");
    typeKey(KEY_RETURN);
    typeString("I want this and work reliably");
    typeKey(KEY_RETURN);

}  // <-- Closing brace for setup()

void loop() {
    // Example usage

    // Add any other code you need in the loop
}
