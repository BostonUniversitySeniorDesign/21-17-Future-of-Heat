# SOFTWARE REPORT

This documents the web application and Arduino codes used in the Future Of Heat Project.

## Web Application

The web application is the user interface resonsible for the interaction between the user and the diorama.

### Front-End Development
The web application is a single-page wesite that consists of four sections:

* Home
* User Inputs
* Output graphs
* Trend charts

The [Chartist.js](https://gionkunz.github.io/chartist-js/) charting library built with SVG was used for the front-end chart generation because it provides responsive functions that enhance the user's experience.

Also, [W3Schools](https://www.w3schools.com/html/) is a web deveolper information website that is referenced on this app. The site provides a reference maunal covering many aspects of the web application HTML, CSS, JavaScript programming.

#### Plugins
Some features for the charts aren't included in the main chartist.js file but we used plugins that were avaiable to add features like:

* [Axis labels](https://github.com/alexstanbury/chartist-plugin-axistitle)
    - This plugin allows the creation and placement of axis titles. The plugin will throw an error if it is applied to a chart that contains no axes, such as a Pie chart.

* [Tooltips at data points](https://github.com/tmmdata/chartist-plugin-tooltip)
    - This plugin provides quick and easy tooltips for your chartist charts.

* [Coloring above/below a threshold](https://github.com/gionkunz/chartist-plugin-threshold)
    - This Chartist plugin can be used to divide your Line or Bar chart with a threshold. Everything above and below the threshold will be tagged with a special class, in order for your to apply different styling where appropriate.

#### Dependencies
The dependencies between the different files is shown in the flowchart below:


### Back-End Development

We used [Google's Firbase](https://firebase.google.com) to handle hosting and realtime database. The web applications stores the electric homes, electric vehicle and weather range
using the [Firebase Realtime Database](https://firebase.google.com/products/realtime-database). The Firebase database is structured as a JSON tree with four main parents:

*   electric_homes
*   electric_vehicles
*   homes
*   weather

Functions in index.js calculate the number of electric homes and electric vehicles using users percentage selection and the weather range using the outside temperature selection.

### Setup and Configure Firebase
1.  Create an account at https://firebase.google.com/

2.  After setting up your new project, it will display all the initialization code you need to get started, for example :

        
        <script> // Your web app's Firebase configuration
           // For Firebase JS SDK v7.20.0 and later, measurementId is optional
           var firebaseConfig = {
               apiKey: "AIzaSyCtjVPCkMEUtS4fd6zuc91DjEeeXi2ncL0",
               authDomain: "test-future-of-heat.firebaseapp.com"
               databaseURL: "https://test-future-of-heat-default-rtdb.firebaseio.com",
               projectId: "test-future-of-heat",
               storageBucket: "test-future-of-heat.appspot.com",
               messagingSenderId: "1019447598625",
               appId: "1:1019447598625:web:c3299f5ea4e0d20dd34d60",
               measurementId: "G-9ZXX8F0T40"
           };

           // Initialize Firebase
           firebase.initializeApp(firebaseConfig);
           firebase.analytics();
        </script>


3.  Enable Firestore under console => Database
4.  Set database permissions to enable read/write access for all users

        {
          "rules": {
            ".read": true,
            ".write": true,
          },
        }

The /database.rules.json is a copy of the Firebase Realtime Database rules.

The web application uses plain javascript to wirte and read data from our dev-database.
Below is a snippet of the write and read code that are implemented in the index.js file when the 'Click to Start' and 'Enter' buttons are clicked:

When 'Click to Start' button is pressed all values in the database are reset to zero.

    const database = firebase.database();
    const rootRef = database.ref();
    startBtn.addEventListener('click', (e) => {
        e.preventDefault();
        rootRef.child("electric_homes").set(0);
        rootRef.child("electric_vehicles").set(0);
        rootRef.child("weather").set(0);
        
    
        for(i = 0; i < 12 ; i++) {
            var num = i + 1;
            var n = num.toString();
             var starCountRef = firebase.database().ref('homes/Load-' + n);
              starCountRef.set(0);
          }

    });

When 'Enter' button is pressed all values in the database are updated according to the users selection.

    enterBtn.addEventListener('click', (e) => {
        e.preventDefault();
        rootRef.child("electric_homes").set(homeValue(home.value));
        rootRef.child("electric_vehicles").set(vehiclesValue(vehicles.value));
        rootRef.child("weather").set(weatherValue(weather.value));
        rootRef.child("active").set(1);

    });

Essentially, the .ref() method gets you to the root of the database, and calling .child() creates a child key.

More information on how to initialize and work with Firebase for a web application can be found in [Firebase Documentation](https://firebase.google.com/docs/web/setup)

## Arduino Mega and ESP8266 Feather Huzzah:

The Arduino Mega 2560 that was used for this project can be programmed using the Arduino IDE, which can be downloaded for free at [https://www.arduino.cc/en/guide/windows](https://www.arduino.cc/en/guide/windows).

Additionally the ESP8266 Feather Huzzah that was used as the wifi module was also programmed using the Arduino IDE. Note that for uploading code a USB A to USB B cable is needed for the Arduino while a USB A to USB micro cable is needed for the ESP8266. The source code for the Arduino is at FutureOfHeat\_arduino, while the source code for the ESP8226 is at FutureOfHeat\_ESP8266. The Arduino version used for coding both the Arduino Mega and the ESP8266 was Arduino 1.8.13.

### Arduino Mega

The Arduino code consists of a main setup function and a  main loop function. All of the digital control pins are instantiated in the beginning prior to the setup function. The setup function then sets all of these listed control pins as output signals correspondingly. Regarding the dependencies of the functions only the loop function calls on other functions. This loop function calls the following functions:

recvWithStartEndMarkers();

parseData();

showParsedData();

loadcontrol(int elecvehic);

heatingtime(int weather);

The dependency of between these functions can be seen as follows: (ArduinoFunctions)

The overview of each function is as follows:

**recvWithStartEndMarkers();**
        
    void recvWithStartEndMarkers() {
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rc;

    while (Serial.available() > 0 && newData == false) {
        rc = Serial.read();

        if (recvInProgress == true) {
            if (rc != endMarker) {
                receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= numChars) {
                    ndx = numChars - 1;
                }
            }
            else {
                receivedChars[ndx] = '\0'; // terminate the string
                recvInProgress = false;
                ndx = 0;
                newData = true;
            }
        }

        else if (rc == startMarker) {
            recvInProgress = true;
        }
      }
    }

This function saves any of the serially received characters within these brackets, \< \>, to the character string receivedChars[numChars], where in this case numChars is 32. The \< and \> denotes start and end markers for when the input values begin and end. For this project specifically the serial information received is in the form \<#electric homes, weather severity, # electric vehicles\>. More specifically this character string is formatted, created, and transmitted by the ESP8266 wifi module to the Arudino for reading. Note that this function buffers serial inputs up to 32 characters in length, as a group of serial information is 7 characters long, including the commas and the brackets, a maximum of 4 inputs grouping can be buffered. This is more than sufficient as it is expected that a designated person will be moderating the diorama exhibit.

**parseData();**

    void parseData() {

      // split the data into its parts
    char * strtokIndx; // this is used by strtok() as an index
    
    strtokIndx = strtok(tempChars, ","); // this continues where the previous call left off
    elechome = atoi(strtokIndx);     // convert this part to an integer

    strtokIndx = strtok(NULL, ",");
    weather = atoi(strtokIndx);     // convert this part to an integer

    strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
    elecvehic = atoi(strtokIndx);     // convert this part to an integer

    }

This function takes the copied serial data in receivedChars and parses it using the commas between the #electric homes, weather severity, # electric vehicles. It converts these characters to integers and writes them to their respective variables of elechome, weather, and elecvehic respectively.

 **showParsedData();**
 
    void showParsedData() {
        Serial.print("User Inputs ");
        Serial.println(messageFromPC);
        Serial.print("Number of Electric Homes ");
        Serial.println(elechome);
        Serial.print("Weather Severity in Degrees (5 is coldest) ");
        Serial.println(weather);
        Serial.print("Number of Electric Vehicles ");
        Serial.println(elecvehic);
    }

This function is used strictly for troubleshooting as it prints out the parsed data into the serial console. This function prints out the message received from the serial communication along with all of the values parseData() parsed through.

**loadcontrol(int elecvehic);**

This function is in charge of controlling the electric vehicle loads. The elecvehic input parsed from the serially transmitted characters is used in a switch statement to determine which digital control signals should be turned to HIGH. This HIGH (5V) signal will turn on corresponding photodiode relays which will connect the resistor used to model electric vehicles to the load circuit.

**heatingtime(int weather);**

    void heatingtime (int weather)
    {
        int wait=0;
        int brightness;
        switch (weather) 
        {
        
        case 1:
          wait =8;
          brightness =80;
          break;
        
          
        case 2:
          wait=20;
          brightness = 125;
          break;
        
        case 3:
          wait=30;
          brightness = 155;
          break;
          
        case 4:
          wait=50;
          brightness = 180;
          break;
        
        case 5:
          wait= 75;
          brightness = 200;
          break;
          
       default:
          wait=8;
          brightness = 80;
          break;

     }
     
      digitalWrite(heatingcontrolmod1,HIGH);
      digitalWrite(heatingcontrolmod2,HIGH);
      digitalWrite(heatingcontrolmod3,HIGH);
      digitalWrite(heatingcontrolmod4,HIGH);
      for(int i=brightness; i>0; i--)
      {
        analogWrite(pwm_mod1, i);             
        analogWrite(pwm_mod2, i);
        analogWrite(pwm_mod3, i);
        analogWrite(pwm_mod4, i);
        
        delay(wait+200-i);    
      }
      for(int j=3; j<brightness; j++)
      {
        digitalWrite(heatingcontrolmod1,LOW);
        digitalWrite(heatingcontrolmod2,LOW);
        digitalWrite(heatingcontrolmod3,LOW);
        digitalWrite(heatingcontrolmod4,LOW);
        analogWrite(pwm_mod1, j);
        analogWrite(pwm_mod2, j);
        analogWrite(pwm_mod3, j);
        analogWrite(pwm_mod4, j);
        delay(wait+200-j);
      }
    }

This function is in charge of controlling the Red and Blue dual LEDs (R/B LEDs) that are mounted within each of the diorama&#39;s houses. The weather input parsed from the serially transmitted characters is used in logic control to determine how long the LED transitions from blue to red as well as how intense the red and blue will be. Essentially this function controls the PWM for the signals powering the R/B LEDs in order to simulate houses heating up.

### ESP8266 Feather Huzzah:

The ESP8266 code also consists of a main setup function and a main loop function. In this code module no custom functions were called however a few libraries were used in order to implement specific functions. The ESP8266WiFi.h library was used as it allows for wifi connection through the use of its WiFi functions. Additionally FirebaseESP8266.h; was also used in order to utilize read functions, allowing the ESP8266 to read data from Google&#39;s Firebase Realtime Database. This library was downloaded as open source software from [ESP8266WiFi.h](https://github.com/esp8266/Arduino/blob/master/libraries/ESP8266WiFi/src/ESP8266WiFi.h). Lastly string library was called as it will be needed to read data from the web app and string concatenate the brackets, commas, and user inputs for #electric homes, weather severity, # electric vehicles prior to serial transmission to the Arduino.

Key things to note the string constants defined for the specific Firebase host and authentication as FIREBASE\_HOST and FIREBASE\_AUTH should correspond directly to the web app&#39;s database. Additionally the string constants defined for WIFI\_SSID and WIFI\_PASSWORD should correspond to the SSID and password to the wifi network that the ESP8226 will be connected to. One thing to note about the ESP8266&#39;s WIfi connectivity is that it is only supported on 802.1 2.4 GHz networks, additionally trying to connect the ESP8226 directly to a campus network is rather difficult due to red tape. The easier alternative is to connect to a mobile hotspot set to 2.4 GHz. Lastly a firebase base data object (fdbo) was initialized for \<FirebaseEsp8266\>.

The main setup function initializes the ESP8266&#39;s wifi connection, note the importance of setting the baud rate of the ESP8266 to match that of the Arduino Mega. In this case 9600 was selected. Should the baud rates mismatch, the serial communication will be garbled. The local IP address is then printed as a check for the module&#39;s network connection.

The main loop function calls back to the fbdo and references data from the database&#39;s JSON tree structure via it&#39;s branch names. Note that an &quot;/active&quot; data bit was used to only have the ESP8266 read when a user is changing the inputs. Once all the user inputs for #electric homes, weather severity, # electric vehicles are read a string is concatenated in the form of  \<#electric homes, weather severity, # electric vehicles\>; for serial transmission to the Arduino Mega.
