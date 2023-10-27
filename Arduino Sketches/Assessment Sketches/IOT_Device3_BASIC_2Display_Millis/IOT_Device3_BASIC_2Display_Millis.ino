#define LED_GREEN    1
#define LED_ORANGE   2
#define LED_RED      3
#define BUZZER       0

#include <LedControl.h> // Library by Eberhard Fahle

//Matrix Dispaly 1, the 8 Dot Matrix on the Right
const int CLK_PIN1 = 20;        //CLK PIN on Matrix 1
const int CS_PIN1 = 19;         //CS PIN on MATRIX 1
const int DIN_PIN1 = 18;        //DIN PIN on MATRIX 1

//Matrix Display 2, the 8 Dot Matrix on the Left
const int CLK_PIN2 = 17;
const int CS_PIN2 = 16;
const int DIN_PIN2 = 15;

//Off Mode Image of a animated Off Mode Image
const uint64_t M0[] = {         
0x3c42a59999a5423c,
  0x3c4281999981423c,
  0x3c4281818181423c,
  0x3c4281999981423c,
  0x3c42a59999a5423c,
  0xbd42a59999a542bd
};
const int M0_Len = sizeof(M0)/8;

//Temperatuere and Tilt Mode
const uint64_t M1[] = {
  0x1010101007010710,
  0x1020408007010700,
  0xf000000007010710
};
const int M1_LEN = sizeof(M1)/8;

//Temperature Only Mode Image of a animiated Snowflake
const uint64_t M2[] = {
  0x00105438ee385410,
  0x000010386c381000,
  0x0000001028100000,
  0x000010386c381000
};
const int M2_LEN = sizeof(M2)/8;

const uint64_t M3[] = {
  0x0101010101010101,
  0x0102040810204080,
  0xff00000000000000
};
const int M3_LEN = sizeof(M3)/8;

const uint64_t DIGITS[] = { //Digits with a degree symbol 0=99. Array Position Matches Number
//Created in LED Matrix Editor
  0x7050505070800000, //0
  0x2020202020800000, //1
  0x7010704070800000, //2
  0x7040704070800000, //3
  0x4040705050800000, //4
  0x7040701070800000, //5
  0x7050701070800000, //6
  0x4040404070800000, //7
  0x7050705070800000, //8
  0x7040705070800000, //9
  0x7454545474800000, //10
  0x2424242424800000, //11
  0x7414744474800000, //12
  0x7444744474800000, //13
  0x4444745454800000, //14
  0x7444741474800000, //15
  0x7454741474800000, //16
  0x4444444474800000, //17
  0x7454745474800000, //18
  0x7444745474800000, //19
  0x7751575477800000, //20
  0x2721272427800000, //21
  0x7711774477800000, //22
  0x7741774477800000, //23
  0x4741775457800000, //24
  0x7741771477800000, //25
  0x7751771477800000, //26
  0x4741474477800000, //27
  0x7751775477800000, //28
  0x7741775477800000, //29
  0x7754575477800000, //30
  0x2724272427800000, //31
  0x7714774477800000, //32
  0x7744774477800000, //33
  0x4744775457800000, //34
  0x7744771477800000, //35
  0x7754771477800000, //36
  0x4744474477800000, //37
  0x7754775477800000, //38
  0x7744775477800000, //39
  0x7454575575800000, //40
  0x2424272525800000, //41
  0x7414774575800000, //42
  0x7444774575800000, //43
  0x4444775555800000, //44
  0x7444771575800000, //45
  0x7454771575800000, //46
  0x4444474575800000, //47
  0x7454775575800000, //48
  0x7444775575800000, //49
  0x7754575177800000, //50
  0x2724272127800000, //51
  0x7714774177800000, //52
  0x7744774177800000, //53
  0x4744775157800000, //54
  0x7744771177800000, //55
  0x7754771177800000, //56
  0x4744474177800000, //57
  0x7754775177800000, //58
  0x7744775177800000, //59
  0x7755575177800000, //60
  0x2725272127800000, //61
  0x7715774177800000, //62
  0x7745774177800000, //63
  0x4745775157800000, //64
  0x7745771177800000, //65
  0x7755771177800000, //66
  0x4745474177800000, //67
  0x7755775177800000, //68
  0x7745775177800000, //69
  0x7454545477800000, //70
  0x2424242427800000, //71
  0x7414744477800000, //72
  0x7444744477800000, //73
  0x4444745457800000, //74
  0x7444741477800000, //75
  0x7454741477800000, //76
  0x4444444477800000, //77
  0x7454745477800000, //78
  0x7444745477800000, //79
  0x7755575577800000, //80
  0x2725272527800000, //81
  0x7715774577800000, //82
  0x7745774577800000, //83
  0x4745775557800000, //84
  0x7745771577800000, //85
  0x7755771577800000, //86
  0x4745474577800000, //87
  0x7755775577800000, //88
  0x7745775577800000, //89
  0x7754575577800000, //90
  0x2724272527800000, //91
  0x7714774577800000, //92
  0x7744774577800000, //93
  0x4744775557800000, //94
  0x7744771577800000, //95
  0x7754771577800000, //96
  0x4744474577800000, //97
  0x7754775577800000, //98
  0x7744775577800000 //99
};
const int DIGITS_LEN = sizeof(DIGITS)/8;

//Defining the the Display Function
LedControl display1 = LedControl(DIN_PIN1, CLK_PIN1, CS_PIN1);
LedControl display2 = LedControl(DIN_PIN2, CLK_PIN2, CS_PIN2);

//Using Millis Instead of Delay to fix the device hanging
unsigned long previousMillis = 0;
const unsigned long interval = 500;
int currentFrame = 0;

void setup() {
      //Matrix 1 
    display1.clearDisplay(0);
    display1.shutdown(0, false);
    display1.setIntensity(0, 10);
    //Matrix 2
    display2.clearDisplay(0);
    display2.shutdown(0, false);
    display2.setIntensity(0, 10);
    
    pinMode(LED_GREEN, OUTPUT);
    pinMode(LED_ORANGE, OUTPUT);
    pinMode(LED_RED, OUTPUT);
    pinMode(BUZZER, OUTPUT);

    Serial.begin(9600);       // For debugging
    Serial1.begin(9600);      // Bluetooth serial
}



void loop() { //Waiting for Bluetooth Signal
    if (Serial1.available()) {
        String command = Serial1.readStringUntil('\n');
        //Serial.println("Received command: " + command);
        handleCommand(command);
    }
}

void displayImage(LedControl& display, uint64_t image, bool rotate = false) { // Function for rotating the Dot Matrix Display to display correctly
  for (int i = 0; i < 8; i++) {
    byte row = (image >> i * 8) & 0xFF;
    if (rotate) {
      for (int j = 0; j < 8; j++) {
        display.setLed(0, 7 - j, i, bitRead(row, j));
      }
    } else {
      for (int j = 0; j < 8; j++) {
        display.setLed(0, i, j, bitRead(row, j));
      }
    }
  }
}

bool commandContains(String command, String keyword) {
    return command.indexOf(keyword) != -1;
}

//This extracts the temperature value from the bluetooth data
int extractTemperature(String command) {
    int startIndex = command.indexOf("TEMP:");
    if (startIndex == -1) return -1;

    int endIndex = command.indexOf("°C", startIndex);
    if (endIndex == -1) return -1;

    String tempStr = command.substring(startIndex + 5, endIndex);
    int decimalIndex = tempStr.indexOf(".");
    if (decimalIndex != -1) {
        tempStr = tempStr.substring(0, decimalIndex); // Extract only the whole numbers
    }

    return tempStr.toInt();
}

//Temperature number is the same as the position in the Digit Array.
void displayTemperature(int temperature) {
    if (temperature >= 0 && temperature < DIGITS_LEN) {
        uint64_t image = DIGITS[temperature];
        displayImage(display1, image, true);
    } else {
        display1.clearDisplay(0);
    }
}

//This handles the messages from the bluetooth device. Using the same code from IOT Device 1.
void handleCommand(String command) {
    //Matrix Display
    int temperature = extractTemperature(command);
    if (temperature != -1) {
        Serial.println("Received command: " + command);
        displayTemperature(temperature);
    } else {
        display1.clearDisplay(0);
    }
    //Matrix Display 2
    if (commandContains(command, "[OFF]")) {
        displayM0Image(); // function to display M0 image on display2
    } else if (commandContains(command, "[M1]")) {
        displayM1Image(); // function to display M1 image on display2
    } else if (commandContains(command, "[M2]")) {
        displayM2Image(); // function to display M2 image on display2
    } else if (commandContains(command, "[M3]")) {
        displayM3Image(); // function to display M3 image on display2
    }

    // Temperature status
    bool isOK = commandContains(command, "[OK]");
    bool isCaution = commandContains(command, "[!]");
    bool isWarning = commandContains(command, "[!!!]");
    
    // Position status
    bool isStable = commandContains(command, "[Stable]");
    bool isTilted = commandContains(command, "[Tilted]");
    bool isTipped = commandContains(command, "[Tipped]");

    if (isOK || isCaution || isWarning) { // If temperature is present
        if (isStable || isTilted || isTipped) { // If both temperature and position are present
            // Combined logic
            if (isOK && isStable) {
                lightGreen();
            } else if (isOK && isTilted) {
                lightOrange();
            } else if (isOK && isTipped) {
                lightRed();
            } else if (isCaution && isStable) {
                lightOrange();
            } else if (isCaution && isTilted) {
                lightOrange();
            } else if (isCaution && isTipped) {
                lightRed();
            } else if (isWarning && isStable) {
                lightRed();
            } else if (isWarning && isTilted) {
                lightRed();
            } else if (isWarning && isTipped) {
                lightRed();
            }
        } else { // Only temperature is present
            if (isOK) {
                lightGreen();
            } else if (isCaution) {
                lightOrange();
            } else if (isWarning) {
                lightRed();
            }
        }
    } else if (isStable || isTilted || isTipped) { // Only position is present
        if (isStable) {
            lightGreen();
        } else if (isTilted) {
            lightOrange();
        } else if (isTipped) {
            lightRed();
        }
    } else {
        // Handle default logic if none of the conditions match
        digitalWrite(LED_GREEN, LOW);
        digitalWrite(LED_ORANGE, LOW);
        digitalWrite(LED_RED, LOW);
    }
}


//Functions for the LED Lights
void lightGreen() {
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_ORANGE, LOW);
  
}

void lightOrange() {
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_ORANGE, HIGH);
    tone(BUZZER, 500, 250);  // Caution tone
    
}

void lightRed() {
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_ORANGE, LOW);
    digitalWrite(LED_RED, HIGH);
    tone(BUZZER, 2000, 250); // Warning tone
}

/*Using Millis to display the Animation. Using delay causes the program to wait for the animation.
Using delay caused the program to wait for the animation to finish before any other functions could be used.*/
void displayM0Image() {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;
        displayImage(display2, M0[currentFrame], true); // Display the current frame
        currentFrame++; // Advance to the next frame

        if (currentFrame >= M0_Len) { // Check if at the end of animation frames
            currentFrame = 0; // Restart the animation
        }
    }
}

void displayM1Image() {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;
        displayImage(display2, M1[currentFrame], true); // Display the current frame
        currentFrame++; // Advance to the next frame

        if (currentFrame >= M1_LEN) { // Check if at the end of animation frames
            currentFrame = 0; // Restart the animation
        }
    }
}

void displayM2Image() {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;
        displayImage(display2, M2[currentFrame], true); // Display the current frame
        currentFrame++; // Advance to the next frame

        if (currentFrame >= M2_LEN) { // Check if at the end of animation frames
            currentFrame = 0; // Restart the animation
        }
    }
}

void displayM3Image() {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;
        displayImage(display2, M3[currentFrame], true); // Display the current frame
        currentFrame++; // Advance to the next frame

        if (currentFrame >= M3_LEN) { // Check if at the end of animation frames
            currentFrame = 0; // Restart the animation
        }
    }
}

void displayImage(LedControl& lc, uint64_t img) {
    for (int i = 0; i < 8; i++) {
        byte row = (img >> (i * 8)) & 0xFF;
        lc.setRow(0, 7 - i, row);
    }
}