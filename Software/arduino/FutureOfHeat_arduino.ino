//#include <SoftwareSerial.h>

//**State Manipulation, On Board LEDs**
#define AVG_WINDOW 10
#define POWER_LOADS 300
//Variables

//Module 1
const int house1 = 27;     
const int house2 = 28;    //red
const int house3 = 29;

//Module 2
const int house4 = 30;     
const int house5 = 31;    //yellow
const int house6 = 32;    

//Module 3
const int house7 = 38;     
const int house8 = 39;    //green
const int house9 = 40;   

//Module 4
const int house10 = 41;     
const int house11 = 42;    //blue
const int house12 = 43;     


//R/B Demux A,B,C control input
const int heatingcontrolmod1 = 9;
const int heatingcontrolmod2 = 7;
const int heatingcontrolmod3 = 5;
const int heatingcontrolmod4 = 3;

//R/B Demux PWM input
const int pwm_mod1= 8;
const int pwm_mod2= 6;
const int pwm_mod3= 4;
const int pwm_mod4= 2;

const int demux_en = 13;  //Enable pin for demuxs

//const int maxcount = 50;
//bool flag_heating = false;
//int count = 0;

//Electric Vehicle loads
const int vechload1 = 14;
const int vechload2 = 15;
const int vechload3 = 16;
const int vechload4 = 17;
const int vechload5 = 18;
const int vechload6 = 19;
const int vechload7 = 20;
const int vechload8 = 21;
const int vechload9 = 23;
const int vechload10 = 24;
const int vechload11 = 25;
const int vechload12 = 26;

// User serial console input variables
const byte numChars = 32;                
char receivedChars[numChars];
char tempChars[numChars];       // temporary array for use by strtok() function

// variables to hold the parsed data
char messageFromPC[numChars] = {0};
int elechome = 0;
int elecvehic = 0;
int weather = 0;
int remainder;
int allonmodule;

boolean newData = false;


//Functions
float computeAvg(int *myArrg);
void collectPoints(int sampleInterval, int pinNumP, int pinNumN, int *myArrg);
void recvWithStartEndMarkers();
void showNewData();
void parseData();
void showParsedData();
void heatingtime(int weather);
void loadcontrol(int elechome, int elecvehic);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //arduinomega.begin(9600);
 
  pinMode(house1,OUTPUT);
  pinMode(house2,OUTPUT);
  pinMode(house3,OUTPUT);
  pinMode(house4,OUTPUT);
  pinMode(house5,OUTPUT);
  pinMode(house6,OUTPUT);
  pinMode(house7,OUTPUT);
  pinMode(house8,OUTPUT);
  pinMode(house9,OUTPUT);
  pinMode(house10,OUTPUT);
  pinMode(house11,OUTPUT);
  pinMode(house12,OUTPUT);

  pinMode(vechload1,OUTPUT);
  pinMode(vechload2,OUTPUT);
  pinMode(vechload3,OUTPUT);
  pinMode(vechload4,OUTPUT);
  pinMode(vechload5,OUTPUT);
  pinMode(vechload6,OUTPUT);
  pinMode(vechload7,OUTPUT);
  pinMode(vechload8,OUTPUT);
  pinMode(vechload9,OUTPUT);
  pinMode(vechload10,OUTPUT);
  pinMode(vechload11,OUTPUT);
  pinMode(vechload12,OUTPUT);
  
  
  pinMode(demux_en,OUTPUT);
  
  pinMode(heatingcontrolmod1,OUTPUT);
  pinMode(heatingcontrolmod2,OUTPUT);
  pinMode(heatingcontrolmod3,OUTPUT);
  pinMode(heatingcontrolmod4,OUTPUT);

  pinMode(pwm_mod1,OUTPUT);
  pinMode(pwm_mod2,OUTPUT);
  pinMode(pwm_mod3,OUTPUT);
  pinMode(pwm_mod4,OUTPUT);
  
}

void (*resetFunc)(void)=0;

void loop() {
  
  Serial.println("<Arduino is ready>");
  Serial.println("Enter in number of electric houses and weather severity from 1-5 separated by comma:");
  //delay(5000);
  recvWithStartEndMarkers();
  
    if (newData == true) {
        strcpy(tempChars, receivedChars);
            // this temporary copy is necessary to protect the original data
            //   because strtok() replaces the commas with \0
        parseData();
        showParsedData();
        newData = false;
    }
      
        switch (elechome)
        {
          case 0:
            digitalWrite(house1, LOW);
            digitalWrite(house2, LOW);
            digitalWrite(house3, LOW);
            digitalWrite(house4, LOW);
            digitalWrite(house5, LOW);
            digitalWrite(house6, LOW);
            digitalWrite(house7, LOW);
            digitalWrite(house8, LOW);
            digitalWrite(house9, LOW);
            digitalWrite(house10,LOW);
            digitalWrite(house11,LOW);
            digitalWrite(house12,LOW);
            break;
          case 1:
            digitalWrite(house1,HIGH);
            digitalWrite(house2, LOW);
            digitalWrite(house3, LOW);
            digitalWrite(house4, LOW);
            digitalWrite(house5, LOW);
            digitalWrite(house6, LOW);
            digitalWrite(house7, LOW);
            digitalWrite(house8, LOW);
            digitalWrite(house9, LOW);
            digitalWrite(house10,LOW);
            digitalWrite(house11,LOW);
            digitalWrite(house12,LOW);
            break;
          case 2:
            digitalWrite(house1,HIGH);
            digitalWrite(house2,HIGH);
            digitalWrite(house3, LOW);
            digitalWrite(house4, LOW);
            digitalWrite(house5, LOW);
            digitalWrite(house6, LOW);
            digitalWrite(house7, LOW);
            digitalWrite(house8, LOW);
            digitalWrite(house9, LOW);
            digitalWrite(house10,LOW);
            digitalWrite(house11,LOW);
            digitalWrite(house12,LOW);
            break;
          case 3:
            digitalWrite(house1,HIGH);
            digitalWrite(house2,HIGH);
            digitalWrite(house3,HIGH);
            digitalWrite(house4, LOW);
            digitalWrite(house5, LOW);
            digitalWrite(house6, LOW);
            digitalWrite(house7, LOW);
            digitalWrite(house8, LOW);
            digitalWrite(house9, LOW);
            digitalWrite(house10,LOW);
            digitalWrite(house11,LOW);
            digitalWrite(house12,LOW);
            break;
          case 4:
            digitalWrite(house1,HIGH);
            digitalWrite(house2,HIGH);
            digitalWrite(house3,HIGH);
            digitalWrite(house4,HIGH);
            digitalWrite(house5, LOW);
            digitalWrite(house6, LOW);
            digitalWrite(house7, LOW);
            digitalWrite(house8, LOW);
            digitalWrite(house9, LOW);
            digitalWrite(house10,LOW);
            digitalWrite(house11,LOW);
            digitalWrite(house12,LOW);
            break;
          case 5:
            digitalWrite(house1,HIGH);
            digitalWrite(house2,HIGH);
            digitalWrite(house3,HIGH);
            digitalWrite(house4,HIGH);
            digitalWrite(house5,HIGH);
            digitalWrite(house6, LOW);
            digitalWrite(house7, LOW);
            digitalWrite(house8, LOW);
            digitalWrite(house9, LOW);
            digitalWrite(house10,LOW);
            digitalWrite(house11,LOW);
            digitalWrite(house12,LOW);
            break;
          case 6:
            digitalWrite(house1,HIGH);
            digitalWrite(house2,HIGH);
            digitalWrite(house3,HIGH);
            digitalWrite(house4,HIGH);
            digitalWrite(house5,HIGH);
            digitalWrite(house6,HIGH);
            digitalWrite(house7, LOW);
            digitalWrite(house8, LOW);
            digitalWrite(house9, LOW);
            digitalWrite(house10,LOW);
            digitalWrite(house11,LOW);
            digitalWrite(house12,LOW);
            break;
          case 7:
            digitalWrite(house1,HIGH);
            digitalWrite(house2,HIGH);
            digitalWrite(house3,HIGH);
            digitalWrite(house4,HIGH);
            digitalWrite(house5,HIGH);
            digitalWrite(house6,HIGH);
            digitalWrite(house7, LOW);
            digitalWrite(house8, LOW);
            digitalWrite(house9, LOW);
            digitalWrite(house10,LOW);
            digitalWrite(house11,HIGH);
            digitalWrite(house12,LOW);
            break;
          case 8:
            digitalWrite(house1,HIGH);
            digitalWrite(house2,HIGH);
            digitalWrite(house3,HIGH);
            digitalWrite(house4,HIGH);
            digitalWrite(house5,HIGH);
            digitalWrite(house6,HIGH);
            digitalWrite(house7,HIGH);
            digitalWrite(house8, LOW);
            digitalWrite(house9, LOW);
            digitalWrite(house10,LOW);
            digitalWrite(house11,HIGH);
            digitalWrite(house12,LOW);
            break;
          case 9:
            digitalWrite(house1,HIGH);
            digitalWrite(house2,HIGH);
            digitalWrite(house3,HIGH);
            digitalWrite(house4,HIGH);
            digitalWrite(house5,HIGH);
            digitalWrite(house6,HIGH);
            digitalWrite(house7,HIGH);
            digitalWrite(house8,HIGH);
            digitalWrite(house9, LOW);
            digitalWrite(house10,LOW);
            digitalWrite(house11,HIGH);
            digitalWrite(house12,LOW);
            break;
          case 10:
            digitalWrite(house1,HIGH);
            digitalWrite(house2,HIGH);
            digitalWrite(house3,HIGH);
            digitalWrite(house4,HIGH);
            digitalWrite(house5,HIGH);
            digitalWrite(house6,HIGH);
            digitalWrite(house7,HIGH);
            digitalWrite(house8,HIGH);
            digitalWrite(house9,HIGH);
            digitalWrite(house10,LOW);
            digitalWrite(house11,HIGH);
            digitalWrite(house12,LOW);
            break;
          case 11:
            digitalWrite(house1,HIGH);
            digitalWrite(house2,HIGH);
            digitalWrite(house3,HIGH);
            digitalWrite(house4,HIGH);
            digitalWrite(house5,HIGH);
            digitalWrite(house6,HIGH);
            digitalWrite(house7,HIGH);
            digitalWrite(house8,HIGH);
            digitalWrite(house9,HIGH);
            digitalWrite(house10,HIGH);
            digitalWrite(house11,HIGH);
            digitalWrite(house12,LOW);
            break;
          case 12:
            digitalWrite(house1,HIGH);
            digitalWrite(house2,HIGH);
            digitalWrite(house3,HIGH);
            digitalWrite(house4,HIGH);
            digitalWrite(house5,HIGH);
            digitalWrite(house6,HIGH);
            digitalWrite(house7,HIGH);
            digitalWrite(house8,HIGH);
            digitalWrite(house9,HIGH);
            digitalWrite(house10,HIGH);
            digitalWrite(house11,HIGH);
            digitalWrite(house12,HIGH);
            break;

          default:
            digitalWrite(house1, LOW);
            digitalWrite(house2, LOW);
            digitalWrite(house3, LOW);
            digitalWrite(house4, LOW);
            digitalWrite(house5, LOW);
            digitalWrite(house6, LOW);
            digitalWrite(house7, LOW);
            digitalWrite(house8, LOW);
            digitalWrite(house9, LOW);
            digitalWrite(house10,LOW);
            digitalWrite(house11,LOW);
            digitalWrite(house12,LOW);
            break; 
            
        }
      loadcontrol(elechome,elecvehic);
      heatingtime(weather);
//      Serial.print("elechomes: ");
//      Serial.println(elechome);
}

void loadcontrol(int elechome,int elecvehic)
{
  //avoid sharing LED control signal with elechome control signal?
  //could halve the number of pins needed if it can work, test on arduino UNO first
  switch (elecvehic)  
  {
    case 0:
      digitalWrite(vechload1,LOW);
      digitalWrite(vechload2,LOW);
      digitalWrite(vechload3,LOW);
      digitalWrite(vechload4,LOW);
      digitalWrite(vechload5,LOW);
      digitalWrite(vechload6,LOW);
      digitalWrite(vechload7,LOW);
      digitalWrite(vechload8,LOW);
      digitalWrite(vechload9,LOW);
      digitalWrite(vechload10,LOW);
      digitalWrite(vechload11,LOW);
      digitalWrite(vechload12,LOW);
      break;
    case 1:
      digitalWrite(vechload1,HIGH);
      digitalWrite(vechload2,LOW);
      digitalWrite(vechload3,LOW);
      digitalWrite(vechload4,LOW);
      digitalWrite(vechload5,LOW);
      digitalWrite(vechload6,LOW);
      digitalWrite(vechload7,LOW);
      digitalWrite(vechload8,LOW);
      digitalWrite(vechload9,LOW);
      digitalWrite(vechload10,LOW);
      digitalWrite(vechload11,LOW);
      digitalWrite(vechload12,LOW);
      break;
    case 2:
      digitalWrite(vechload1,HIGH);
      digitalWrite(vechload2,HIGH);
      digitalWrite(vechload3,LOW);
      digitalWrite(vechload4,LOW);
      digitalWrite(vechload5,LOW);
      digitalWrite(vechload6,LOW);
      digitalWrite(vechload7,LOW);
      digitalWrite(vechload8,LOW);
      digitalWrite(vechload9,LOW);
      digitalWrite(vechload10,LOW);
      digitalWrite(vechload11,LOW);
      digitalWrite(vechload12,LOW);
      break;
    case 3:
      digitalWrite(vechload1,HIGH);
      digitalWrite(vechload2,HIGH);
      digitalWrite(vechload3,HIGH);
      digitalWrite(vechload4,LOW);
      digitalWrite(vechload5,LOW);
      digitalWrite(vechload6,LOW);
      digitalWrite(vechload7,LOW);
      digitalWrite(vechload8,LOW);
      digitalWrite(vechload9,LOW);
      digitalWrite(vechload10,LOW);
      digitalWrite(vechload11,LOW);
      digitalWrite(vechload12,LOW);
      break;
    case 4:
      digitalWrite(vechload1,HIGH);
      digitalWrite(vechload2,HIGH);
      digitalWrite(vechload3,HIGH);
      digitalWrite(vechload4,HIGH);
      digitalWrite(vechload5,LOW);
      digitalWrite(vechload6,LOW);
      digitalWrite(vechload7,LOW);
      digitalWrite(vechload8,LOW);
      digitalWrite(vechload9,LOW);
      digitalWrite(vechload10,LOW);
      digitalWrite(vechload11,LOW);
      digitalWrite(vechload12,LOW);
      break;
    case 5:
      digitalWrite(vechload1,HIGH);
      digitalWrite(vechload2,HIGH);
      digitalWrite(vechload3,HIGH);
      digitalWrite(vechload4,HIGH);
      digitalWrite(vechload5,HIGH);
      digitalWrite(vechload6,LOW);
      digitalWrite(vechload7,LOW);
      digitalWrite(vechload8,LOW);
      digitalWrite(vechload9,LOW);
      digitalWrite(vechload10,LOW);
      digitalWrite(vechload11,LOW);
      digitalWrite(vechload12,LOW);
      break;
    case 6:
      digitalWrite(vechload1,HIGH);
      digitalWrite(vechload2,HIGH);
      digitalWrite(vechload3,HIGH);
      digitalWrite(vechload4,HIGH);
      digitalWrite(vechload5,HIGH);
      digitalWrite(vechload6,HIGH);
      digitalWrite(vechload7,LOW);
      digitalWrite(vechload8,LOW);
      digitalWrite(vechload9,LOW);
      digitalWrite(vechload10,LOW);
      digitalWrite(vechload11,LOW);
      digitalWrite(vechload12,LOW);
      break;
    case 7:
      digitalWrite(vechload1,HIGH);
      digitalWrite(vechload2,HIGH);
      digitalWrite(vechload3,HIGH);
      digitalWrite(vechload4,HIGH);
      digitalWrite(vechload5,HIGH);
      digitalWrite(vechload6,HIGH);
      digitalWrite(vechload7,HIGH);
      digitalWrite(vechload8,LOW);
      digitalWrite(vechload9,LOW);
      digitalWrite(vechload10,LOW);
      digitalWrite(vechload11,LOW);
      digitalWrite(vechload12,LOW);
      break;
    case 8:
      digitalWrite(vechload1,HIGH);
      digitalWrite(vechload2,HIGH);
      digitalWrite(vechload3,HIGH);
      digitalWrite(vechload4,HIGH);
      digitalWrite(vechload5,HIGH);
      digitalWrite(vechload6,HIGH);
      digitalWrite(vechload7,HIGH);
      digitalWrite(vechload8,HIGH);
      digitalWrite(vechload9,LOW);
      digitalWrite(vechload10,LOW);
      digitalWrite(vechload11,LOW);
      digitalWrite(vechload12,LOW);
      break;
    case 9:
      digitalWrite(vechload1,HIGH);
      digitalWrite(vechload2,HIGH);
      digitalWrite(vechload3,HIGH);
      digitalWrite(vechload4,HIGH);
      digitalWrite(vechload5,HIGH);
      digitalWrite(vechload6,HIGH);
      digitalWrite(vechload7,HIGH);
      digitalWrite(vechload8,HIGH);
      digitalWrite(vechload9,HIGH);
      digitalWrite(vechload10,LOW);
      digitalWrite(vechload11,LOW);
      digitalWrite(vechload12,LOW);
      break;
    case 10:
      digitalWrite(vechload1,HIGH);
      digitalWrite(vechload2,HIGH);
      digitalWrite(vechload3,HIGH);
      digitalWrite(vechload4,HIGH);
      digitalWrite(vechload5,HIGH);
      digitalWrite(vechload6,HIGH);
      digitalWrite(vechload7,HIGH);
      digitalWrite(vechload8,HIGH);
      digitalWrite(vechload9,HIGH);
      digitalWrite(vechload10,HIGH);
      digitalWrite(vechload11,LOW);
      digitalWrite(vechload12,LOW);
      break;
    case 11:
      digitalWrite(vechload1,HIGH);
      digitalWrite(vechload2,HIGH);
      digitalWrite(vechload3,HIGH);
      digitalWrite(vechload4,HIGH);
      digitalWrite(vechload5,HIGH);
      digitalWrite(vechload6,HIGH);
      digitalWrite(vechload7,HIGH);
      digitalWrite(vechload8,HIGH);
      digitalWrite(vechload9,HIGH);
      digitalWrite(vechload10,HIGH);
      digitalWrite(vechload11,HIGH);
      digitalWrite(vechload12,LOW);
      break;
    default:
      digitalWrite(vechload1,HIGH);
      digitalWrite(vechload2,HIGH);
      digitalWrite(vechload3,HIGH);
      digitalWrite(vechload4,HIGH);
      digitalWrite(vechload5,HIGH);
      digitalWrite(vechload6,HIGH);
      digitalWrite(vechload7,HIGH);
      digitalWrite(vechload8,HIGH);
      digitalWrite(vechload9,HIGH);
      digitalWrite(vechload10,HIGH);
      digitalWrite(vechload11,HIGH);
      digitalWrite(vechload12,HIGH);
      break;
  }
}


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


//float computeAvg(int *myArrg)
////compute the average of the array of points
//{
//  int accumulator = 0;
//  float val;
//  for (int j = 0; j < AVG_WINDOW; j++) {
//  accumulator = accumulator + myArrg[j];
//  }
//  val = (float)accumulator / AVG_WINDOW;
//  return val;
//  }
//
//void collectPoints(int sampleInterval, int pinNumP, int pinNumN, int *myArrg)
//  { // collect N points from 2 analog ins and take the difference.
//    int i = 0;
//    while(i < AVG_WINDOW) {
//      if(pinNumN == 'G'){
//        myArrg[i] = analogRead(pinNumP);
//      }
//      else{
//        myArrg[i] = analogRead(pinNumP) - analogRead(pinNumN);
//      }
//      
//      //i = (i + 1) % AVG_WINDOW;
//      ++i;
//      delay(sampleInterval);
//      }
//  }


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

void showNewData() {
    if (newData == true) {
        Serial.print("This just in ... ");
        Serial.println(receivedChars);
        newData = false;
    }
}

//============

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

//============

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

    
