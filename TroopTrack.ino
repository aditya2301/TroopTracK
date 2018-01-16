//#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#include <Keypad.h>
//SoftwareSerial gps(P3_4,P3_3); // RX, TX
SoftwareSerial mySerial(P3_6,P3_5);
//LiquidCrystal lcd(7,6, 5, 4, 3, 2);
#define PIR P8_1
#define Heart_rate P2_6
#define temp A0
#define temp1 A1
int sense,rate=0,k,r=0;
float temp_value,temp_value1;
unsigned long time2,time1;
unsigned long time;
//String str="";
char str[70];
String gpsString="";

char *test="$GPGGA";

String latitude="12.9077";
String longitude="77.5613";
String p=latitude+","+longitude;
int t=0,i,z=0;
boolean gps_status=0;
const byte ROWS = 3; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'}
//  {'#','0','*'}
  };
//byte rowPins[ROWS] = {5, 4, 3, 2}; //connect to the row pinouts of the keypad
//byte colPins[COLS] = {8, 7, 6}; //connect to the column pinouts of the keypad

byte rowPins[ROWS] = { P4_3,P4_0,P3_7};
// Connect keypad COL0, COL1 and COL2 to these Arduino pins.
byte colPins[COLS] = { P7_4, P2_2, P8_2 };   



Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
    void setup()
{
  // put your setup code here, to run once:
// lcd.begin(16, 2);
     mySerial.begin(9600);
  Serial.begin(9600);
   //gps.begin(9600);
  //lcd.print("TroopTracK");
 //get_gps();
 delay(2000); pinMode(P2_1, INPUT_PULLUP);
 // gsm_init();
   //Serial.println("AT+CNMI=2,2,0,0,0");
 t=0;
 pinMode(PIR,INPUT);
 pinMode(Heart_rate,INPUT);
 attachInterrupt(P2_1, keypress,CHANGE ); // Interrupt is fired whenever button is pressed
}

void loop()
{
  // put your main code here, to run repeatedly:
  //lcd.clear();
    noInterrupts();
  sense=digitalRead(PIR);
  delay(1000);
  detect(sense);
 // lcd.clear();
  delay(1000);
  temp_value=analogRead(temp);
  temp_value=temp_value/9.31; //for mspf5529lp divide by 17.89
    tem(temp_value1);
  delay(1000);
  temp_value1=analogRead(temp1);
  temp_value1=temp_value1/9.31; //for mspf5529lp divide by 17.89
  tem(temp_value1);
  delay(1000);
  //lcd.clear();
  pulse();
  delay(1000);
  event();
  if(t)
  {
    //get_gps();
    t=0;
  }
  //lcd.clear();
  Serial.print("Lat:");
  Serial.println(latitude);
  //lcd.setCursor(0,1);
  Serial.print("Long:");
  Serial.println(longitude);
  delay(1000);
   Send2Pachube();
    Send2Pachube1();
     Send2Pachube2();
      Send2Pachube3();
   Send2Pachube4();
   Send2Pachube5();
  if (mySerial.available())
     Serial.write(mySerial.read());
       interrupts();
       r=0;
}   
  void keypress()
  {
   char key = keypad.getKey();
    
    if (key != NO_KEY)
    {
      Serial.println(key);
    if(key==49){
    Serial.println("hello");  //greencode
   // init_sms(); 
  //  send_data("hello");
   // tracking1();
     r=1;
    }
     if(key==50){
    Serial.println("hello2");
   // init_sms(); 
  //  send_data("hello2");
   // tracking1();
    }
     if(key==51){
    Serial.println("hello3");
   // init_sms(); 
   // send_data("hello3");
   // tracking1();
   r=3;
    }
     if(key==52){
    Serial.println("hello4");
   // init_sms(); 
   // send_data("hello4");
   // tracking1();
    }
     if(key==53){
    Serial.println("hello5");
   // init_sms(); 
   // send_data("hello5");
   // tracking1();
    }
     if(key==54){
    Serial.println("hello6");
   // init_sms(); 
   // send_data("hello6");
   // tracking1();
    }
     if(key==55){
    Serial.println("hello7");
  //  init_sms(); 
  //  send_data("hello7");
  //  tracking1();
  r=7;
    }
     if(key==56){
    Serial.println("hello8");
  //  init_sms(); 
  //  send_data("hello8");
  //  tracking1();
    }
     if(key==57){
    Serial.println("hello9");
   // init_sms(); 
  //  send_data("hello9");
 //   tracking1();
 r=9;
    }
  } 
  }     
void tem(float a)
  {
    //lcd.setCursor(0,0);  
    Serial.print("Temperature= ");
    //lcd.setCursor(0,1);
    Serial.print(a);
    Serial.print("degrees");
    Serial.println();
    delay(100);
    if(a>=60||a<=-10)     // change contraints as required
     {
      e();
      delay(3000);
     }
  }
  void pulse()
 {
   k=0;
   rate=0;
   while(k<5)
    {
     if(digitalRead(Heart_rate))
     {
      if(k==0)
      time1=millis();
      k++;
      while(digitalRead(Heart_rate));
     }
    }
   time2=millis();
   rate=time2-time1;
   rate=rate/5;
   rate=60000/rate;
   //lcd.clear();
   //lcd.setCursor(0,0);   
   Serial.print("Heart rate= ");
   delay(100); 
   //lcd.setCursor(0,1);   
   Serial.print(rate);
   Serial.println();   
   delay(100); 
   k=0;
 }
 void detect(int sense)
  {
   // lcd.clear();
   // lcd.setCursor(0,0);
    if(sense==1)
     {
       Serial.println("Intrusion Alert!");
       delay(5000);
       e();
     }
     else
     {
       Serial.println("Everything Secure");
       delay(500);
     }  
  }
  void e()
  {
   //lcd.clear();
   //lcd.setCursor(0,0);
   Serial.println("Emergency");
   delay(500);
//   init_sms();
  // tracking1();
  }
/*  void gpsEvent()
{
  gpsString="";
  while(1)
  {
   while (gps.available()>0)            //checking serial data from GPS
   {
    char inChar = (char)gps.read();
     gpsString+= inChar;                    //store data from GPS into gpsString
     i++;
     if (i < 7)                      
     {
      if(gpsString[i-1] != test[i-1])         //checking for $GPGGA sentence
      {
        i=0;
        gpsString="";
      }
     }
    if(inChar=='\r')
    {
     if(i>65)
     {
       gps_status=1;
       break;
        }
     else
     {
       i=0;
     }
    }
  }
   if(gps_status)
    break;
  }
}
void get_gps()
{
   gps_status=0;
   int x=0;
   while(gps_status==0)
   {
    gpsEvent();
    int str_lenth=i;
    latitude="";
    longitude="";
    int comma=0;
    while(x<str_lenth)
    {
      if(gpsString[x]==',')
      comma++;
      if(comma==2)        //extract latitude from string
      latitude+=gpsString[x+1];     
      else if(comma==4)        //extract longitude from string
      longitude+=gpsString[x+1];
      x++;
    }
    int l1=latitude.length();
    latitude[l1-1]=' ';
    l1=longitude.length();
    longitude[l1-1]=' ';
      i=0;x=0;
    str_lenth=0;
    delay(2000);
   }
} */
void event()
{
  delay(4000);
  t=1;
}
/*void gsm_init()
{
  boolean at_flag=1;
  while(at_flag)
  {
    mySerial.println("AT");
    while(mySerial.available()>0)
    {
      if(mySerial.find("OK"))
      at_flag=0;
    }
    
    delay(1000);
  }
  boolean echo_flag=1;
  while(echo_flag)
  {
    mySerial.println("ATE0");
    while(mySerial.available()>0)
    {
      if(mySerial.find("OK"))
      echo_flag=0;
    }
    delay(1000);
  }
  boolean net_flag=1;
  while(net_flag)
  {
    mySerial.println("AT+CPIN?");
    while(mySerial.available()>0)
    {
      if(mySerial.find("+CPIN: READY"))
      net_flag=0;
    }
    delay(1000);
  }
  delay(1000);
  //lcd.clear();
}*/
 /*void tracking()
{
    init_sms();
    send_data("Troop Tracking Alert:");
    send_data("Your Troop Current Location is:");
    Serial.print("Latitude:");
    send_data(latitude);
    Serial.print("Longitude:");
    send_data(longitude);                                                       //sensors value for  gsm
    send_sms();
    delay(2000);
}
void init_sms()
{
  mySerial.println("AT+CMGF=1");
  delay(400);
  mySerial.println("AT+CMGS=\"+917676687057\"");   // use your 10 digit cell no. here
  delay(400);
}

void send_data(String message)
{
  mySerial.println(message);
  delay(200);
}

void send_sms()
{
  mySerial.write(26);
}*/
void Send2Pachube()
{
  mySerial.println("AT");
  delay(1000);

  mySerial.println("AT+CPIN?");
  delay(1000);

  mySerial.println("AT+CREG?");
  delay(1000);

  mySerial.println("AT+CGATT?");
  delay(1000);

  mySerial.println("AT+CIPSHUT");
  delay(1000);

  mySerial.println("AT+CIPSTATUS");
  delay(2000);

  mySerial.println("AT+CIPMUX=0");
  delay(2000);
 
  ShowSerialData();
 
  mySerial.println("AT+CSTT=\"aircelgprs\"");//start task and setting the APN,
  delay(1000);
 
  ShowSerialData();
 
  mySerial.println("AT+CIICR");//bring up wireless connection
  delay(3000);
 
  ShowSerialData();
 
  mySerial.println("AT+CIFSR");//get local IP adress
  delay(2000);
 
  ShowSerialData();
 
  mySerial.println("AT+CIPSPRT=0");
  delay(3000);
 
  ShowSerialData();
  
  mySerial.println("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",\"80\"");//start up the connection
  delay(2000);
 
  ShowSerialData();
 
  mySerial.println("AT+CIPSEND");//begin send data to remote server
  delay(4000);
  ShowSerialData();
  
    String str="GET https://api.thingspeak.com/update?api_key=KCTXD8Y5U0OAQHXC&field1=" + String(temp_value);
  mySerial.println(str);//begin send data to remote server
  delay(4000);
  ShowSerialData();

  mySerial.println((char)26);//sending
  delay(5000);//waitting for reply, important! the time is base on the condition of internet 
  mySerial.println();
 
  ShowSerialData();
  Serial.println(temp_value);

  mySerial.println("AT+CIPSHUT");//close the connection
  delay(100);
  ShowSerialData();
} 
void Send2Pachube1()
{
  mySerial.println("AT");
  delay(1000);

  mySerial.println("AT+CPIN?");
  delay(1000);

  mySerial.println("AT+CREG?");
  delay(1000);

  mySerial.println("AT+CGATT?");
  delay(1000);

  mySerial.println("AT+CIPSHUT");
  delay(1000);

  mySerial.println("AT+CIPSTATUS");
  delay(2000);

  mySerial.println("AT+CIPMUX=0");
  delay(2000);
 
  ShowSerialData();
 
  mySerial.println("AT+CSTT=\"aircelgprs\"");//start task and setting the APN,
  delay(1000);
 
  ShowSerialData();
 
  mySerial.println("AT+CIICR");//bring up wireless connection
  delay(3000);
 
  ShowSerialData();
 
  mySerial.println("AT+CIFSR");//get local IP adress
  delay(2000);
 
  ShowSerialData();
 
  mySerial.println("AT+CIPSPRT=0");
  delay(3000);
 
  ShowSerialData();
  
  mySerial.println("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",\"80\"");//start up the connection
  delay(6000);
 
  ShowSerialData();
 
  mySerial.println("AT+CIPSEND");//begin send data to remote server
  delay(4000);
  ShowSerialData();
  
    String str="GET https://api.thingspeak.com/update?api_key=KCTXD8Y5U0OAQHXC&field2=" + String(rate);
  mySerial.println(str);//begin send data to remote server
  delay(4000);
  ShowSerialData();

  mySerial.println((char)26);//sending
  delay(5000);//waitting for reply, important! the time is base on the condition of internet 
  mySerial.println();
 
  ShowSerialData();
  Serial.println(rate);
 
  mySerial.println("AT+CIPSHUT");//close the connection
  delay(100);
  ShowSerialData();
} 
void Send2Pachube2()
{
  mySerial.println("AT");
  delay(1000);

  mySerial.println("AT+CPIN?");
  delay(1000);

  mySerial.println("AT+CREG?");
  delay(1000);

  mySerial.println("AT+CGATT?");
  delay(1000);

  mySerial.println("AT+CIPSHUT");
  delay(1000);

  mySerial.println("AT+CIPSTATUS");
  delay(2000);

  mySerial.println("AT+CIPMUX=0");
  delay(2000);
 
  ShowSerialData();
 
  mySerial.println("AT+CSTT=\"aircelgprs\"");//start task and setting the APN,
  delay(1000);
 
  ShowSerialData();
 
  mySerial.println("AT+CIICR");//bring up wireless connection
  delay(3000);
 
  ShowSerialData();
 
  mySerial.println("AT+CIFSR");//get local IP adress
  delay(2000);
 
  ShowSerialData();
 
  mySerial.println("AT+CIPSPRT=0");
  delay(3000);
 
  ShowSerialData();
  
  mySerial.println("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",\"80\"");//start up the connection
  delay(6000);
 
  ShowSerialData();
 
  mySerial.println("AT+CIPSEND");//begin send data to remote server
  delay(4000);
  ShowSerialData();
  
    String str="GET https://api.thingspeak.com/update?api_key=KCTXD8Y5U0OAQHXC&field3=" + String(sense);
  mySerial.println(str);//begin send data to remote server
  delay(4000);
  ShowSerialData();

  mySerial.println((char)26);//sending
  delay(5000);//waitting for reply, important! the time is base on the condition of internet 
  mySerial.println();
 
  ShowSerialData();
  Serial.println(sense);
 
  mySerial.println("AT+CIPSHUT");//close the connection
  delay(100);
  ShowSerialData();
} 
void Send2Pachube3()
{
  mySerial.println("AT");
  delay(1000);

  mySerial.println("AT+CPIN?");
  delay(1000);

  mySerial.println("AT+CREG?");
  delay(1000);

  mySerial.println("AT+CGATT?");
  delay(1000);

  mySerial.println("AT+CIPSHUT");
  delay(1000);

  mySerial.println("AT+CIPSTATUS");
  delay(2000);

  mySerial.println("AT+CIPMUX=0");
  delay(2000);
 
  ShowSerialData();
 
  mySerial.println("AT+CSTT=\"aircelgprs\"");//start task and setting the APN,
  delay(1000);
 
  ShowSerialData();
 
  mySerial.println("AT+CIICR");//bring up wireless connection
  delay(3000);
 
  ShowSerialData();
 
  mySerial.println("AT+CIFSR");//get local IP adress
  delay(2000);
 
  ShowSerialData();
 
  mySerial.println("AT+CIPSPRT=0");
  delay(3000);
 
  ShowSerialData();
  
  mySerial.println("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",\"80\"");//start up the connection
  delay(6000);
 
  ShowSerialData();
 
  mySerial.println("AT+CIPSEND");//begin send data to remote server
  delay(4000);
  ShowSerialData();
  
    String str="GET https://api.thingspeak.com/update?api_key=KCTXD8Y5U0OAQHXC&field4=" + String(p);
  mySerial.println(str);//begin send data to remote server
  delay(4000);
  ShowSerialData();

  mySerial.println((char)26);//sending
  delay(5000);//waitting for reply, important! the time is base on the condition of internet 
  mySerial.println();
 
  ShowSerialData();
  Serial.println(p);
 
  mySerial.println("AT+CIPSHUT");//close the connection
  delay(100);
  ShowSerialData();
} 
void Send2Pachube4()
{
  mySerial.println("AT");
  delay(1000);

  mySerial.println("AT+CPIN?");
  delay(1000);

  mySerial.println("AT+CREG?");
  delay(1000);

  mySerial.println("AT+CGATT?");
  delay(1000);

  mySerial.println("AT+CIPSHUT");
  delay(1000);

  mySerial.println("AT+CIPSTATUS");
  delay(2000);

  mySerial.println("AT+CIPMUX=0");
  delay(2000);
 
  ShowSerialData();
 
  mySerial.println("AT+CSTT=\"aircelgprs\"");//start task and setting the APN,
  delay(1000);
 
  ShowSerialData();
 
  mySerial.println("AT+CIICR");//bring up wireless connection
  delay(3000);
 
  ShowSerialData();
 
  mySerial.println("AT+CIFSR");//get local IP adress
  delay(2000);
 
  ShowSerialData();
 
  mySerial.println("AT+CIPSPRT=0");
  delay(3000);
 
  ShowSerialData();
  
  mySerial.println("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",\"80\"");//start up the connection
  delay(6000);
 
  ShowSerialData();
 
  mySerial.println("AT+CIPSEND");//begin send data to remote server
  delay(4000);
  ShowSerialData();
  
    String str="GET https://api.thingspeak.com/update?api_key=KCTXD8Y5U0OAQHXC&field5=" + String(r);
  mySerial.println(str);//begin send data to remote server
  delay(4000);
  ShowSerialData();

  mySerial.println((char)26);//sending
  delay(5000);//waitting for reply, important! the time is base on the condition of internet 
  mySerial.println();
 
  ShowSerialData();
  Serial.println(r);
 
  mySerial.println("AT+CIPSHUT");//close the connection
  delay(100);
  ShowSerialData();
}
void Send2Pachube5()
{
  mySerial.println("AT");
  delay(1000);

  mySerial.println("AT+CPIN?");
  delay(1000);

  mySerial.println("AT+CREG?");
  delay(1000);

  mySerial.println("AT+CGATT?");
  delay(1000);

  mySerial.println("AT+CIPSHUT");
  delay(1000);

  mySerial.println("AT+CIPSTATUS");
  delay(2000);

  mySerial.println("AT+CIPMUX=0");
  delay(2000);
 
  ShowSerialData();
 
  mySerial.println("AT+CSTT=\"aircelgprs\"");//start task and setting the APN,
  delay(1000);
 
  ShowSerialData();
 
  mySerial.println("AT+CIICR");//bring up wireless connection
  delay(3000);
 
  ShowSerialData();
 
  mySerial.println("AT+CIFSR");//get local IP adress
  delay(2000);
 
  ShowSerialData();
 
  mySerial.println("AT+CIPSPRT=0");
  delay(3000);
 
  ShowSerialData();
  
  mySerial.println("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",\"80\"");//start up the connection
  delay(6000);
 
  ShowSerialData();
 
  mySerial.println("AT+CIPSEND");//begin send data to remote server
  delay(4000);
  ShowSerialData();
  
    String str="GET https://api.thingspeak.com/update?api_key=KCTXD8Y5U0OAQHXC&field6=" + String(temp_value1);
  mySerial.println(str);//begin send data to remote server
  delay(4000);
  ShowSerialData();

  mySerial.println((char)26);//sending
  delay(5000);//waitting for reply, important! the time is base on the condition of internet 
  mySerial.println();
 
  ShowSerialData();
  Serial.println(temp_value1);
 
 
  mySerial.println("AT+CIPSHUT");//close the connection
  delay(100);
  ShowSerialData();
}
void ShowSerialData()
{
  while(mySerial.available()!=0)
    Serial.write(mySerial.read());
}
/*void tracking1()
{
    send_data("Troop Tracking Alert:");
    send_data("Your Troop Current Location is:");
    Serial.print("Latitude:");
    send_data(latitude);
    Serial.print("Longitude:");
    send_data(longitude);                                                       //sensors value for  gsm
    send_sms();
    delay(2000);
}*/
