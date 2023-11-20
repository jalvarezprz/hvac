void screenSetup(){
    u8g2.begin();
    u8g2.enableUTF8Print();		// enable UTF8 support for the Arduino print() function
    u8g2.setFont(u8g2_font_6x10_tf);  
    u8g2.setFontDirection(0);
}

void screenWriteString(uint8_t x, uint8_t y, String & msg, String & msgLocRem, uint8_t ledOn) {
    u8g2.clearBuffer();
    u8g2.setCursor(x, y);
    u8g2.print(WiFi.macAddress());
    u8g2.setCursor(x, y + 10);
    if (ledOn == true){ 
        u8g2.print(msg + " " + "ON" + " " + msgLocRem);
    } else {
        u8g2.print(msg + " " + "OFF" + " " + msgLocRem);
    }
    u8g2.sendBuffer();
}