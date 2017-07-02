// Fill the dots one after the other with a color
void colorWipe() {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, color);
    strip.show();
   
  }
}

void rainbow() {
 
  if(cycleCounter<256) 
  {
    for(innrecycleCounter=0; innrecycleCounter<strip.numPixels(); innrecycleCounter++) {
      strip.setPixelColor(innrecycleCounter, Wheel((innrecycleCounter+cycleCounter) & 255));
    }
    strip.show();
    delay(intervalNeoPixel);
    cycleCounter++;
  }
  else
  {
    cycleCounter=0;
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle() {

  if(cycleCounter<256*5) { // 5 cycles of all colors on wheel
    for(innrecycleCounter=0; innrecycleCounter< strip.numPixels(); innrecycleCounter++) {
      strip.setPixelColor(innrecycleCounter, Wheel(((innrecycleCounter * 256 / strip.numPixels()) + cycleCounter) & 255));
    }
    strip.show();
    delay(intervalNeoPixel);
    cycleCounter++;
  }
  else
  {
    cycleCounter=0;
  }
}

//Theatre-style crawling lights.
void theaterChase() {
  if (theaterChaseBool) {
   if (cycleCounter < 3) {
      for (innrecycleCounter=0; innrecycleCounter < strip.numPixels(); innrecycleCounter=innrecycleCounter+3) {
        strip.setPixelColor(innrecycleCounter+cycleCounter, color);    //turn every third pixel on
      }
      strip.show();

      delay(intervalNeoPixel);

      for (innrecycleCounter=0; innrecycleCounter < strip.numPixels(); innrecycleCounter=innrecycleCounter+3) {
        strip.setPixelColor(innrecycleCounter+cycleCounter, 0);        //turn every third pixel off
      }
      cycleCounter++;
    }
    else
    {
      cycleCounter=0;
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow() {
  if (cycleCounter< 256) {     // cycle all 256 colors in the wheel
    if (innrecycleCounter < 3) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+innrecycleCounter, Wheel( (i+cycleCounter) % 255));    //turn every third pixel on
      }
      strip.show();

      delay(intervalNeoPixel);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+innrecycleCounter, 0);        //turn every third pixel off
      }
      innrecycleCounter++;
    }
    else
    {
      innrecycleCounter = 0;
    }
    cycleCounter++;
  }
  else
  {
    cycleCounter = 0;
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

void startShow() {

  String data = server.arg("plain");
   yield();
  StaticJsonBuffer<200> jBuffer;
  JsonObject& jObject = jBuffer.parseObject(data);
  
  int value = jObject["value"];
  yield();

  cloasAllNeoPixel();
  
  switch(value){
    case 0: //off
           cloasAllNeoPixel();
            break;
            
    case 1: //Red
           cloasAllNeoPixel();
           oneColorBool = true;
           color = strip.Color(255, 0, 0);
            break;
            
    case 2: //Green
           oneColorBool = true;
           color = strip.Color(0, 255, 0);
            break;
            
    case 3: //Blue
           oneColorBool = true;
           color = strip.Color(0, 0, 255);
            break;
            
    case 4:  // White
           theaterChaseBool = true;
           color = strip.Color(127, 127, 127);
           intervalNeoPixel = 50;
           cycleCounter = 0;
           innrecycleCounter =0;
            break;
            
    case 5: // Red
           theaterChaseBool = true;
           color = strip.Color(127, 0, 0);
           intervalNeoPixel = 50;
           cycleCounter = 0;
           innrecycleCounter =0;
            break;
            
    case 6: // Blue
           theaterChaseBool = true;
           color = strip.Color(0, 0, 127);
           intervalNeoPixel = 50;
           cycleCounter = 0;
           innrecycleCounter =0;
            break;
            
    case 7: 
           rainbowBool = true;
           cycleCounter = 0;
           innrecycleCounter =0;
           intervalNeoPixel = 20;
            break;
            
    case 8: 
           rainbowCycleBool = true;
           cycleCounter = 0;
           innrecycleCounter =0;
           intervalNeoPixel = 20;
            break;
    case 9: 
           theaterChaseRainbowBool = true;
           cycleCounter = 0;
           innrecycleCounter =0;
           intervalNeoPixel = 40;
            break;
  }
}


void cloasAllNeoPixel()
{
  theaterChaseBool = false;
  oneColorBool = false;
  rainbowBool = false;
  rainbowCycleBool = false;
  theaterChaseRainbowBool = false;

  color = strip.Color(0, 0, 0);
  colorWipe();
}

