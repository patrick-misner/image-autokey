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

// Credential Variables
#define IMG_PW "imagePWORD"
#define WIN_USR "USERNAME"
#define WIN_PW "PASSWORD"

// Global Delay Variables
int winPeBootDelay = 36; // Delay for WinPE to load in seconds
int shutDownDelay = 480; // Delay for Shutdown after login in seconds

// Model 1 parameters
const uint8_t model1BootKey = KEY_F12;
unsigned long model1BootDelay = 24; // Delay for one time boot menu load
int model1DownArrow = 1;
unsigned long model1LoginDelay = 960; // Delay from completed WinPE steps to Windows Logon screen in seconds

// Model 2 parameters
const uint8_t model2BootKey = KEY_F12;
unsigned long model2BootDelay = 16;
int model2DownArrow = 2;
unsigned long model2LoginDelay = 615;

// Model 3 parameters
const uint8_t model3BootKey = KEY_F9;
unsigned long model3BootDelay = 16;
int model3DownArrow = 1;
unsigned long model3LoginDelay = 515;

// Model 4 parameters
const uint8_t model4BootKey = KEY_F12;
unsigned long model4BootDelay = 16;
int model4DownArrow = 2;
unsigned long model4LoginDelay = 400;

// Model 5 parameters
const uint8_t model5BootKey = KEY_F9;
unsigned long model5BootDelay = 16;
int model5DownArrow = 1;
unsigned long model5LoginDelay = 960;

// Pointers to hold the selected model parameters
uint8_t bootKey;
unsigned long bootDelay;
int downArrow;
unsigned long loginDelay;
int selectedModel;


// WinPE Option 1 parameters
const char* option1Step1 = IMG_PW;
const char* option1Step2 = "2";
const char* option1Step3 = "";

// WinPE Option 2 parameters
const char* option2Step1 = "1";
const char* option2Step2 = IMG_PW;
const char* option2Step3 = "2";

// WinPE Option 3 parameters
const char* option3Step1 = "2";
const char* option3Step2 = IMG_PW;
const char* option3Step3 = "3";

// Pointers to hold the selected WinPE Option parameters
const char* optionStep1;
const char* optionStep2;
const char* optionStep3;
int selectedOpt;

// Function to type a string
void typeString(const char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        Keyboard_write(str[i]);
    }
    delay(500);
}

// Function to Key press and Delay
void typeKey(uint8_t key) {
    digitalWrite(LED_BUILTIN, LOW);
    Keyboard_press(key);
    delay(25);
    Keyboard_release(key);
    delay(150);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(325);
}

// Function to type a single character
void typeCharacter(char c) {
    digitalWrite(LED_BUILTIN, LOW);
    Keyboard_write(c);  // Writes the character as if typed on a keyboard
    delay(150);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(350);  // Short delay to simulate natural typing
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
        selectedModel = 1;
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
        selectedModel = 2;
    }
}

void checkModel3() {
    delay(50);
    digitalWrite(P15, LOW);
    delay(50);
    bool opt3IsShorted = digitalRead(P16) == LOW;
    digitalWrite(P15, HIGH);
    delay(50);
    if (opt3IsShorted) {
        bootKey = model3BootKey;
        bootDelay = model3BootDelay;
        downArrow = model3DownArrow;
        loginDelay = model3LoginDelay;
        selectedModel = 3;
    }
}

void checkModel4() {
    delay(50);
    digitalWrite(P17, LOW);
    delay(50);
    bool opt4IsShorted = digitalRead(P16) == LOW;
    digitalWrite(P17, HIGH);
    delay(50);
    if (opt4IsShorted) {
        bootKey = model4BootKey;
        bootDelay = model4BootDelay;
        downArrow = model4DownArrow;
        loginDelay = model4LoginDelay;
        selectedModel = 4;
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
        selectedModel = 5;
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
        selectedOpt = 1;
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
        selectedOpt = 2;
    }
}

void checkOption3() {
    if (optionStep1 == NULL) {
        optionStep1 = option3Step1;
        optionStep2 = option3Step2;
        optionStep3 = option3Step3;
        selectedOpt = 3;
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
    checkOption2();
    checkOption3();
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

    // Step 0 - Blink the Model and Options

    // Blink for selected model
    for (int i = 0; i < selectedModel - 1; i++) {
    digitalWrite(LED_BUILTIN, LOW);
    delay(150);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(250);
    }

    delay(1500);

    // Blink for selected option
    for (int i = 0; i < selectedOpt; i++) {
    digitalWrite(LED_BUILTIN, LOW);
    delay(150);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(250);
    }

    delay(1500);

    // STEP 1
    // Type bootKey for Model's defined bootDelay to one-time boot menu
    for (int i = 0; i < bootDelay * 2; i++) {
        typeKey(bootKey);
    }

    // Enter Down Arrow as many times as model needs to select USB flash drive
    for (int i = 0; i < downArrow; i++) {
    typeKey(KEY_DOWN_ARROW);
    }

    typeKey(KEY_RETURN);


    // STEP 2 WIN PE
    //Wait for WinPE and Image Prompts to Load

    // Blink twice every 2 seconds to indicate step 2 is pending
    for (int i = 0; i < winPeBootDelay / 2; i++) {
    digitalWrite(LED_BUILTIN, LOW);
    delay(150);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(150);
    digitalWrite(LED_BUILTIN, LOW);
    delay(150);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1550);
    }

    // Enter WinPE Prompts
    typeString(optionStep1);
    typeKey(KEY_RETURN);
    typeString(optionStep2);
    typeKey(KEY_RETURN);
    typeString(optionStep3);
    typeKey(KEY_RETURN);

    //STEP 3 Login to Windows 
    //Blink 3 times every 2 seconds to indicate step 3 is pending
    for (int i = 0; i < loginDelay / 2; i++) {
    digitalWrite(LED_BUILTIN, LOW);
    delay(150);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(150);
    digitalWrite(LED_BUILTIN, LOW);
    delay(150);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(150);
    digitalWrite(LED_BUILTIN, LOW);
    delay(150);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1250);
    }

    typeKey(KEY_RETURN);
    typeString(WIN_USR);
    typeKey(KEY_TAB);
    typeString(WIN_PW);
    typeKey(KEY_RETURN);
    delay(35000);

    //Try again with two Returns (policy for disclaimer may have loaded already)
    typeKey(KEY_RETURN);
    typeKey(KEY_RETURN);
    typeString(WIN_USR);
    typeKey(KEY_TAB);
    typeString(WIN_PW);
    typeKey(KEY_RETURN);


    // Step 4 Shutdown PC

    // Blink 4 times every 2 seconds to indicate step 4 is pending
    for (int i = 0; i < shutDownDelay / 2; i++) {
    digitalWrite(LED_BUILTIN, LOW);
    delay(150);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(150);
    digitalWrite(LED_BUILTIN, LOW);
    delay(150);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(150);
    digitalWrite(LED_BUILTIN, LOW);
    delay(150);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(150);
    digitalWrite(LED_BUILTIN, LOW);
    delay(150);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(950);
    }

    Keyboard_press(KEY_LEFT_GUI);
    delay(250);
    Keyboard_press('x'); 
    delay(50);
    Keyboard_release('x'); 
    Keyboard_release(KEY_LEFT_GUI);
    delay(250);
    Keyboard_press('u'); 
    delay(50);
    Keyboard_release('u'); 
    delay(250);
    Keyboard_press('u'); 
    delay(50);
    Keyboard_release('u'); 

    // try to shut down PC again.
    delay(30000);
    Keyboard_press(KEY_LEFT_GUI);
    delay(250);
    Keyboard_press('x'); 
    delay(50);
    Keyboard_release('x'); 
    Keyboard_release(KEY_LEFT_GUI);
    delay(250);
    Keyboard_press('u'); 
    delay(50);
    Keyboard_release('u'); 
    delay(250);
    Keyboard_press('u'); 
    delay(50);
    Keyboard_release('u'); 

}

void loop() {
}
