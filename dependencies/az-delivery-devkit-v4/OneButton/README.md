Arduino OneButton Library
===

This Arduino library is improving the usage of a singe button for input.
It allows using a digital input pin with a single pushbutton attached and detecting some of the typical button press events like single clicks, double clicks, multple clicks and long-time pressing.
This enables you to reuse the same button for multiple functions and lowers the hardware investments.

This is also a sample for implementing simple finite-state machines by using the simple pattern above. 

You can find more details on this library at
http://www.mathertel.de/Arduino/OneButtonLibrary.aspx

**Modified by ShaggyDog18@gmail.com**

**Major Modification**:
- added new functions:
  - `multiClickFunc()` for multiple 3+ clicks (for 3 clicks and more)
  - `getNumberClicks()` to return number of multiple clicks;
  - `attachPressStart()` to mainatin compatibility with the new release v1.5 of the parent library: fires immediately as the button is pressed down. 
  
## Change Log:

**21.01.2021**
- added `isIdle()` function to maintain compatibility with original library developments
- renamed `tripleClick()` to `multiClick()` to maintain compatibility
- made some more optimization to decrease size

**12.02.2020**
- modified state machine (still same number of states), maintained full compatibility with the initial library; 
- introduced a new functions: `multiClickFunc()` for multiple 3+ clicks; `getNumberClicks()` to return number of clicks; 
- optimized - changed some types of variables (f.e.: `bool _buttonPressed`, `uint8_t _state`) to compact the code; 
- optimized - by using `switch()` instead of multiple `if()`-s; 
- introdiced `#define PARAM_FUNC` - if commented in `oneButton.h`, the call functions with parameters will not be used to save space; 
- modified `SimpleOneButton` example to test more functions incl. new `multiClickFunc()` and `getNumberClicks()` functions.

**23.06.2020**
- sync up with the original library, release v1.5, by adding the new function `attachPressStart()`.
- extensed `SimpleOneButton` example that includes new function and allows to test almost all library functions.

**If you like new functions and use the modified library, please, consider making a small "cup of coffee" donation using [PayPal](https://paypal.me/shaggyDog18/3USD)**

## Getting Started

Clone this repository into `Arduino/Libraries` or use the built-in Arduino IDE Library manager to install
a copy of this library. You can find more detail about installing libraries 
[here, on Arduino's website](https://www.arduino.cc/en/guide/libraries).

```CPP
#include <Arduino.h>
#include <OneButton.h>
```

Each physical button requires its own `OneButton` instance. You can initialize them like this:


### Initialize a Button to GND

```CPP
#define BUTTON_PIN 4

/**
 * Initialize a new OneButton instance for a button
 * connected to digital pin 4 and GND, which is active low
 * and uses the internal pull-up resistor.
 */

OneButton btn = OneButton(
  BUTTON_PIN, // Input pin for the button
  LOW,       // Button is active LOW
  true       // Enable internal pull-up resistor
);
```

The same by using active low as a default settings:
```CPP
OneButton btn = OneButton( BUTTON_PIN ); // Input pin for the button
```

### Initialize a Button to VCC

```CPP
#define BUTTON_PIN 4

/**
 * Initialize a new OneButton instance for a button
 * connected to digital pin 4, which is active high.
 * As this does not use any internal resistor
 * an external resistor (4.7k) may be required to create a LOW signal when the button is not pressed.
 */

OneButton btn = OneButton(
  BUTTON_PIN, // Input pin for the button
  HIGH,       // Button is active high
  false       // Disable internal pull-up resistor
);
```


### Attach State Events

Once you have your button initialized, you can handle events by attaching them to the button
instance. Events can either be static functions or lambdas (without captured variables).

```CPP
// Handler function for a single click:
static void handleClick() {
  Serial.println("Clicked!");
}

// Single Click event attachment
btn.attachClick(handleClick);

// Double Click event attachment with lambda
btn.attachDoubleClick([]() {
  Serial.println("Double Click!");
};

// Triple Click event attachment
btn.attachMultiClick([]() {
  Serial.println("Multi Click!");
};
```

### Don't forget to `tick()`!

In order for `OneButton` to work correctly, you must call `tick()` on __each button instance__
within your main `loop()`. If you're not getting any button events, this is probably why.
You may also call `tick()` from PinChangeInterupt routine to make buttons more reponsive. Please, refer to `InterruptOneButton` example. 

```CPP
void loop() {
  btn.tick();

  // Do other things...
}
```


## State Events

Here's a full list of events handled by this library:

| Attach Function         | Description                                                |
| ----------------------- | ---------------------------------------------------------- |
| `attachClick`           | Fires as soon as a single click is detected.               |
| `attachDoubleClick`     | Fires as soon as a double click is detected.               |
| `attachMultiClick`      | **NEW** Fires as soon as multiple 3+ click are detected.      |
| `attachPressStart`      | **NEW** Fires as soon as the button is pressed down.          |
| `attachLongPressStart`  | Fires as soon as the button is held down for 1 second.     |
| `attachDuringLongPress` | Fires periodically as long as the button is held down.     |
| `attachLongPressStop`   | Fires when the button is released after a long hold.       |

### Event Timing

Valid events occur when `tick()` is called after a specified number of milliseconds. You can use
the following functions to change the timing.

**Note:** Attaching a double click will increase the delay for detecting a single click. If a double
click event is not attached, the library will assume a valid single click after one click duration,
otherwise it must wait for the double click timeout to pass.

| Function                | Default (ms) | Description                                                   |
| ----------------------- | ------------ | ------------------------------------------------------------- |
| `setDebounceTicks(int)` | `50`         | Period of time in which to ignore additional level changes.   |
| `setClickTicks(int)`    | `400`        | Timeout used to distinguish single clicks from double clicks. |
| `setPressTicks(int)`    | `800`        | Duration to hold a button to trigger a long press.            |


### Additional Functions

`OneButton` also provides a couple additional functions to use for querying button status:

| Function                   | Description                                                                        |
| -------------------------- | ---------------------------------------------------------------------------------- |
| `bool isLongPressed()`     | Detect whether or not the button is currently inside a long press.                 |
| `bool isIdle()`            | **NEW** Returns `true` if no button press is under processing  |
| `int getPressedTicks()`    | Get the current number of milliseconds that the button has been held down for. |
| `uint8_t getNumberClicks()`| **NEW** Get number of detected clicks. Return single or multiple number of clicks.     |

### `tick()` and `reset()`

You can specify a logic level when calling `tick(bool)`, which will skip reading the pin and use
that level instead. If you wish to reset the internal state of your buttons, call `reset()`.


## Troubleshooting

If your buttons aren't acting they way they should, check these items:

1. Check your wiring and pin numbers.
2. Did you call `tick()` on each button instance in your loop?
3. Did you alter your clock timers in any way without adjusting ticks?
   
**If you like new functions and use the modified library, please, consider making a small "cup of coffee" donation using [PayPal](https://paypal.me/shaggyDog18/3USD)**
