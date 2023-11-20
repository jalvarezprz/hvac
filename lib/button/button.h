void buttonRead(bool & buttonDown) {
    #define STATUS_BUTTON 5 
    if (digitalRead(STATUS_BUTTON))
    { 
        // Detect the transition from low to high
        if (!buttonDown)
        {
            buttonDown = true;
        
            // Toggle the LED state
            // Control de los dispositivos locales - START
            ledOn = !ledOn;
            digitalWrite(STATUS_LED, ledOn);
            String msg = "LED";
            String msgLocRem = "LOCAL";
            screenWriteString(0, 10, msg, msgLocRem, ledOn);
            // Control de los dispositivos locales - END
            
            // Send a message to all devices
            commSendMsgAllDev(ledOn);
            
        
        }
        // Delay to avoid bouncing
        delay(500);
    }
    else
    {
        // Reset the button state
        buttonDown = false;
    }
}
