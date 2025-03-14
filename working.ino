#ifndef USER_USB_RAM
#error "This example needs to be compiled with a USER USB setting"
#endif

#include "src/userUsbHidKeyboard/USBHIDKeyboard.h"

#define LED_BUILTIN 30
#define P32 32  // Define P32 pin
#define P14 14  // Define P14 pin
#define P15 15  // Define P14 pin

//Option 1 is Student Lenovo 500ws (gen 3 and 4)
bool checkIfOpt1Shorted() {
    digitalWrite(P32, LOW);  // Drive P32 high
    delay(10);  // Small delay to stabilize the signal
    bool opt1IsShorted = digitalRead(P14) == LOW;  // Read P14
    digitalWrite(P32, HIGH);  // Drive P32 low again
    return opt1IsShorted;  // Return true if P14 reads high (shorted), false otherwise
}

//Option 2 is Staff Laptop (Lenovo Yoga L13)
bool checkIfOpt2Shorted() {
    digitalWrite(P15, LOW);  // Drive P32 high
    delay(10);  // Small delay to stabilize the signal
    bool opt2IsShorted = digitalRead(P14) == LOW;  // Read P14
    digitalWrite(P15, HIGH);  // Drive P32 low again
    return opt2IsShorted;  // Return true if P14 reads high (shorted), false otherwise
}

void setup() {
    USBInit();  // Initialize USB
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);  // Turn off the LED initially

    pinMode(P32, OUTPUT);  // Set P32 as output
    pinMode(P14, INPUT);   // Set P14 as input
    pinMode(P15, OUTPUT);  // Set P32 as output

    delay(5000);  // Initial delay to ensure USB is ready

    // Check if P32 and P14 are shorted
    bool opt1IsShorted = checkIfOpt1Shorted();

    // Check if P14 and P15 are shorted
    bool opt2IsShorted = checkIfOpt2Shorted();

    // Step 1: Push F12 twice a second for 26 seconds
    for (int i = 0; i < 24 * 2; i++) {
        // Turn LED on for 150ms
        digitalWrite(LED_BUILTIN, LOW);
        delay(150);
        digitalWrite(LED_BUILTIN, HIGH);

        // Press F12
        Keyboard_press(KEY_F12);
        delay(10);  // Small delay to ensure it registers
        Keyboard_release(KEY_F12);

        // Complete the rest of the 2000ms cycle
        delay(500 - 150); // Adjust timing so total period is 500ms per iteration
    }

    // Step 2: Boot off USB
    delay(5000);

    digitalWrite(LED_BUILTIN, LOW);
    Keyboard_press(KEY_DOWN_ARROW);
    delay(10);  // Small delay to ensure it registers
    delay(150);
    digitalWrite(LED_BUILTIN, HIGH);
    Keyboard_release(KEY_DOWN_ARROW);

    if (opt1IsShorted) {
      digitalWrite(LED_BUILTIN, LOW);
      Keyboard_press(KEY_DOWN_ARROW);
      delay(10);  // Small delay to ensure it registers
      delay(150);
      digitalWrite(LED_BUILTIN, HIGH);
      Keyboard_release(KEY_DOWN_ARROW);
    }

    if (opt2IsShorted) {
      digitalWrite(LED_BUILTIN, LOW);
      Keyboard_press(KEY_DOWN_ARROW);
      delay(10);  // Small delay to ensure it registers
      delay(150);
      digitalWrite(LED_BUILTIN, HIGH);
      Keyboard_release(KEY_DOWN_ARROW);
      delay(150);
      Keyboard_press(KEY_DOWN_ARROW);
      delay(10);  // Small delay to ensure it registers
      delay(150);
      digitalWrite(LED_BUILTIN, HIGH);
      Keyboard_release(KEY_DOWN_ARROW);
    }

    delay(250);

    digitalWrite(LED_BUILTIN, LOW);
    Keyboard_press(KEY_RETURN);  // HID Code for Enter
    delay(10);
    delay(150);
    Keyboard_release(KEY_RETURN);
    digitalWrite(LED_BUILTIN, HIGH);

    // Step 3: WinPE Options Select

    delay(36000);
    if (opt2IsShorted) {
      delay(250);
      Keyboard_write('2');
      delay(250);
      Keyboard_press(KEY_RETURN); 
      delay(50);
      Keyboard_release(KEY_RETURN);
    }
    Keyboard_write('F');
    Keyboard_write('a');
    Keyboard_write('l');
    Keyboard_write('l');
    Keyboard_write('2');
    Keyboard_write('4');
    delay(50);
    Keyboard_press(KEY_RETURN);
    delay(50);
    Keyboard_release(KEY_RETURN);
    if (opt2IsShorted) {
      delay(250);
      Keyboard_write('3');
      delay(250);
    } else {
      delay(250);
      Keyboard_write('2');
      delay(250);
    }

    Keyboard_press(KEY_RETURN);
    delay(50);
    Keyboard_release(KEY_RETURN);

    // Step 4: Log in to Win 11 with credentials so policies can start loading

    if (opt1IsShorted) {
      delay(615000);
    }
    if (opt2IsShorted) {
      delay(360000);
    }
    if ((!opt1IsShorted) && (!opt2IsShorted))
    {
          delay(960000);
    }
    Keyboard_press(KEY_RETURN);
    delay(50);
    Keyboard_release(KEY_RETURN);
    delay(750);

    Keyboard_write('i');
    Keyboard_write('n');
    Keyboard_write('t');
    Keyboard_write('u');
    Keyboard_write('n');
    Keyboard_write('e');

    delay(250);

    Keyboard_press(KEY_TAB);
    delay(50);
    Keyboard_release(KEY_TAB);

    Keyboard_write('T');
    Keyboard_write('i');
    Keyboard_write('m');
    Keyboard_write('e');
    Keyboard_write('4');
    Keyboard_write('F');
    Keyboard_write('a');
    Keyboard_write('l');
    Keyboard_write('l');
    Keyboard_write('2');
    Keyboard_write('0');
    Keyboard_write('2');
    Keyboard_write('4');
    Keyboard_write('!');
    delay(500);

    Keyboard_press(KEY_RETURN);
    delay(50);
    Keyboard_release(KEY_RETURN);

    // Step 5: Log in to win 11 again with two return keys, in case there is a disclaimer before login prompt or the policy loaded quicker than normal
    delay(39000);
    Keyboard_press(KEY_RETURN);
    delay(50);
    Keyboard_release(KEY_RETURN);
    delay(750);
    Keyboard_press(KEY_RETURN);
    delay(50);
    Keyboard_release(KEY_RETURN);
    delay(750);

    Keyboard_write('i');
    Keyboard_write('n');
    Keyboard_write('t');
    Keyboard_write('u');
    Keyboard_write('n');
    Keyboard_write('e');

    delay(250);

    Keyboard_press(KEY_TAB);  // HID Code for Tab
    delay(50);
    Keyboard_release(KEY_TAB);
    delay(500);
    Keyboard_write('T');
    Keyboard_write('i');
    Keyboard_write('m');
    Keyboard_write('e');
    Keyboard_write('4');
    Keyboard_write('F');
    Keyboard_write('a');
    Keyboard_write('l');
    Keyboard_write('l');
    Keyboard_write('2');
    Keyboard_write('0');
    Keyboard_write('2');
    Keyboard_write('4');
    Keyboard_write('!');
    delay(500);

    Keyboard_press(KEY_RETURN);
    delay(50);
    Keyboard_release(KEY_RETURN);

    // Step 6: Shutdown the PC
    delay(480000);
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

    // Step 7: try to shut down PC again.
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
    // No loop behavior needed for this one-time automation
}
