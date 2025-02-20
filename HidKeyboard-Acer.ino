#ifndef USER_USB_RAM
#error "This example needs to be compiled with a USER USB setting"
#endif

#include "src/userUsbHidKeyboard/USBHIDKeyboard.h"

#define LED_BUILTIN 30

void setup() {
    USBInit();  // Initialize USB
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);  // Turn off the LED initially

    delay(5000);  // Initial delay to ensure USB is ready

    // Step 1: Push F12 twice a second for 26 seconds
    for (int i = 0; i < 26 * 2; i++) {
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

    // Step 2: Sleep for 11 seconds
    delay(11000);

     // Step 3: Down Arrow
    Keyboard_press(KEY_DOWN_ARROW);
    delay(10);  // Small delay to ensure it registers
    Keyboard_release(KEY_DOWN_ARROW);

    // Step 4: Sleep 250ms
    delay(250);

    // Step 5: Enter key
    Keyboard_press(KEY_RETURN);  // HID Code for Enter
    delay(50);
    Keyboard_release(KEY_RETURN);

    // Step 6: Sleep 33 seconds
    delay(33000);

    // Step 7: Type "Pa55word"
    Keyboard_write('P');
    Keyboard_write('a');
    Keyboard_write('S');
    Keyboard_write('S');
    Keyboard_write('W');
    Keyboard_write('D');
    delay(50);
    Keyboard_press(KEY_RETURN);  // HID Code for Enter
    delay(50);
    Keyboard_release(KEY_RETURN);

    // Step 8: Sleep 500ms
    delay(250);
    Keyboard_write('2');
    delay(250);

    // Step 9: Enter key
    Keyboard_press(KEY_RETURN);  // HID Code for Enter
    delay(50);
    Keyboard_release(KEY_RETURN);

    // Step 10: Sleep 17 minutes
    delay(17 * 60 * 1000);

    // Step 11: Type spacebar key
    Keyboard_press(0x2C);  // HID Code for Space
    delay(50);
    Keyboard_release(0x2C);

    // Step 12: Type "username"
    Keyboard_write('u');
    Keyboard_write('s');
    Keyboard_write('e');
    Keyboard_write('r');
    Keyboard_write('n');
    Keyboard_write('e');

    // Step 13: Sleep 250ms
    delay(250);

    // Step 14: Push Tab key
    Keyboard_press(KEY_TAB);  // HID Code for Tab
    delay(50);
    Keyboard_release(KEY_TAB);

    // Step 15: Type "Pa55Word"
    Keyboard_write('P');
    Keyboard_write('A');
    Keyboard_write('S');
    Keyboard_write('S');
    Keyboard_write('W');
    Keyboard_write('O');
    Keyboard_write('R');
    Keyboard_write('D');
    Keyboard_write('4');
    Keyboard_write('W');
    Keyboard_write('I');
    Keyboard_write('N');
    Keyboard_write('D');
    Keyboard_write('O');

    // Done executing
}

void loop() {
    // No loop behavior needed for this one-time automation
}