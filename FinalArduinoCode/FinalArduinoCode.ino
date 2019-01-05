
/*

              Mustafa Ayberk Kale 50359 mkale14
              Mert Akman          53908 makman15

*/

//Servo

#include<Servo.h> //getting servo library
/*

#define WifiName "CHANGE THIS"
#define WifiPassword "CHANGE THIS"


*/







//Detector//



float fivekurus_analogValue; //measure analog value
float twentyfivekurus_analogValue; //measure analog value
float fiftykurus_analogValue; //measure analog value
float onetl_analogValue; //measure analog value

int fivekurus_detectorPin=13;  //Analog value input 
int twentyfivekurus_detectorPin=12;  //Analog value input
int fiftykurus_detectorPin=11;  //Analog value input
int onetl_detectorPin3=10;  //Analog value input


int count5=0;
int count25=0;
int count50=0;
int count100=0;

int fivekurusDetectorAmount=0;
int twentyfivekurusDetectorAmount=0;
int fiftykurusDetectorAmount=0;
int onetlDetectorAmount=0;


int fivekurusDetectorMaxDeterminedAmount=3;
int twentyfivekurusDetectorMaxDeterminedAmount=3;
int fiftykurusDetectorMaxDeterminedAmount=2;
int onetlDetectorMaxDeterminedAmount=3;

int metalDetectorSwitch=0;
int metalDetectorPin=22;


//


// Money And Servos
int fivekurusAmount = 0;
int twentyfivekurusAmount = 0;
int fiftykurusAmount = 0;
int onetlAmount = 0;


int backUpfivekurusAmount = 0;
int backUptwentyfivekurusAmount = 0;
int backUpfiftykurusAmount = 0;
int backUponetlAmount = 0;

int fivekuruscountstop = 0;
int twentyfivekuruscountstop = 0;
int fiftykuruscountstop = 0;
int onetlcountstop=0;

float fivekurustankAnalog = 0;
float twentyfivekurustankAnalog = 0;
float fiftykurustankAnalog = 0;
float onetltankAnalog;

Servo fivekurusservo;// create servo object to control a servo 
Servo twentyfivekurusservo;// create servo object to control a servo 
Servo fiftykurusservo;// create servo object to control a servo 
Servo onetlservo;// create servo object to control a servo


Servo rejectservo;// create servo object to control a servo


Servo Pushservo;// create servo object to control a servo

int stuckButtonPin=11;


//Wifi Communication to Server



/**********************  WiFi SSID Name and Password **************************/

String Host_name = WifiName;//wifi name
String password = WifiPassword;//wifi password




String sendData(String command, const int timeOut, boolean debug); // send and receive data to/from Thingspeak

void connectToWiFi();//wifi connection maker

// WifiSender




int countTrueCommand;
int countTimeCommand; 
boolean found = false; 
int valSensor = 1;

int WifiIndicatorLightPin=8;

String CoinAmountData = "0,0,0,0";

// End of Wifi Sender

//Functions to Get data from server

String WSServoOne();


String WSUserDesiredValue();




//backups initial condition from server

String backupServoOne = "false";

String backupUserDesiredValue = "0";



//// 

bool BoolStringtoBoolean(String str);//string true/false to boolean true/false converter function
String BooltoStr(bool a);// true and false booleans to string converter









// Manual Buttons// come from server



bool ServoOne = false;


double UserDesiredValue = 0;

String ServerReply = "0";

double tankChoice=0;

int digit=0;

int backupDigit=0;

String previousServerReply = "0";

String previousCoinAmountDataSerial ="0";


const byte interruptPinUDV = 21;
const byte interruptPinCAS = 20;

bool UserDesiredValueInterruptswitch =false;

bool CoinAmountSendInterruptswitch =false;


int ServerReplySwitch=0;


int WiFiSenderErrorCheckSwitch=0;

int amountSenderSwitch=0;


// All functions pre-defined


void servoFunction();








void setup() {

  Serial.begin(57600);//serial monitor
  Serial1.begin(250000);//Esp 8266


 pinMode(WifiIndicatorLightPin, OUTPUT);

 
 digitalWrite(WifiIndicatorLightPin,HIGH);

   

 
  connectToWiFi();// connect to wifi

  digitalWrite(WifiIndicatorLightPin,LOW);


  pinMode(interruptPinUDV, INPUT_PULLUP);
  //attachInterrupt(digitalPinToInterrupt(interruptPinUDV), UserDesiredValueInterrupt, FALLING);//interrupt change falling low


  
  pinMode(interruptPinCAS, INPUT_PULLUP);
  //attachInterrupt(digitalPinToInterrupt(interruptPinCAS), CoinAmountSendInterrupt, FALLING);

   pinMode(metalDetectorPin, INPUT);        // sets the digital pin 22 as input metal detector ,check pin


    fivekurusservo.attach(7);// create servo object to control a servo 
    twentyfivekurusservo.attach(6);// create servo object to control a servo 
    fiftykurusservo.attach(5);// create servo object to control a servo 
    onetlservo.attach(4);// create servo object to control a servo
    
    rejectservo.attach(2);
    
    fivekurusservo.write( 179 ); // sets the servo position
    twentyfivekurusservo.write( 179 ); // sets the servo position
    fiftykurusservo.write( 179 ); // sets the servo position 
    
    onetlservo.write( 179 ); // sets the servo position
    
    rejectservo.write(179);//reject servo closed

    Pushservo.attach(10);// create servo object to control a servo

    Pushservo.write( 7 ); // sets the servo position
    
    
    

   pinMode(stuckButtonPin,INPUT_PULLUP);




 
  

}





/*
 * 
 * 
 *                                     ***********************************MAIN CODE*************************** 
 * 
 * 
 *
 */
void loop() {
  /*
    if (digitalRead(metalDetectorPin)==1){// Metal Detector
                            
                   // Serial.println("Metal Detected");

                    metalDetectorSwitch=1;
              
               }
       */ 
       fivekurus_analogValue = analogRead(fivekurus_detectorPin); //A13'den değeri ölç
 twentyfivekurus_analogValue = analogRead(twentyfivekurus_detectorPin); //A12'den değeri ölç
fiftykurus_analogValue = analogRead(fiftykurus_detectorPin); //A11'den değeri ölç
  onetl_analogValue = analogRead(onetl_detectorPin3); //A10'den değeri ölç



if(onetl_analogValue<700){

    

    count100=1;
  
 } else if(fiftykurus_analogValue<700){
    

     count50=1;
  
 }else if(twentyfivekurus_analogValue<700){
  

    count25=1;

 }else if(fivekurus_analogValue<700){


    count5=1;

 
 }


              
/*
              else if (count5==1 && digitalRead(metalDetectorPin)==0){// Metal Detector if no Metal Detected
              
                    //Serial.println("Non Metal Detected");

                    RejectServoActivator();
 
                
               }

               
              */
               

if(count5==1 && count25==0 && count100==0 && count50==0){

   digitalWrite(WifiIndicatorLightPin,HIGH);

   

 


  //
  Serial.println("girdi5kurusa");

   delay (200);

              if (digitalRead(metalDetectorPin)==1){// Metal Detector
                            
                   // Serial.println("Metal Detected");

                    metalDetectorSwitch=1;
                
               }
  

        if(metalDetectorSwitch==1){
          Serial.println("Metal Detected");
           Serial.println (" 5 Kurus Detected");
                    
                    if (fivekurusDetectorAmount>=fivekurusDetectorMaxDeterminedAmount){
                        
                              Serial.println("Maxiumum Amount Reached");
                        RejectServoActivator();
                        
                      }else{
                       
                        
                        fivekurusDetectorAmount++;
                        Serial.print("fivekurusDetectorAmount: ");Serial.println(fivekurusDetectorAmount);
                        
                      }
        
       metalDetectorSwitch=0; //metal detector rebooted
      
          
        }else{
          Serial.println("Non Metal Detected");
          RejectServoActivator();
          metalDetectorSwitch=0; //metal detector rebooted
          
        }
      
     


 
      
       count5=0;
       count25=0;
      count50=0;
      count100=0;
      
      delay (200);  




 // digitalWrite(WifiIndicatorLightPin,LOW);


           
 }else if(count5==1&&count25==1 && count100==0 && count50==0){

     digitalWrite(WifiIndicatorLightPin,HIGH);



   delay (200);

              if (digitalRead(metalDetectorPin)==1){// Metal Detector
                            
                   // Serial.println("Metal Detected");

                    metalDetectorSwitch=1;
                
               }
  

                      if(metalDetectorSwitch==1){
                      Serial.println("Metal Detected");
                  Serial.println (" 25 Kurus Detected");


                              if (twentyfivekurusDetectorAmount>=twentyfivekurusDetectorMaxDeterminedAmount){
                                    
                              Serial.println("Maxiumum Amount Reached");
                                    RejectServoActivator();
                                    
                                  }else{
                                    
                                    twentyfivekurusDetectorAmount++;

                                    Serial.print("twentyfivekurusDetectorAmount: ");Serial.println(twentyfivekurusDetectorAmount);
                                    
                                  }
                                  
 metalDetectorSwitch=0; //metal detector rebooted
                        
                 
                      
                    }else{
                      Serial.println("Non Metal Detected");
                      RejectServoActivator();
                      metalDetectorSwitch=0; //metal detector rebooted
                      
                    }


   
       
       count5=0;
       count25=0;
      count50=0;
      count100=0;
      
      delay (200);   



  //digitalWrite(WifiIndicatorLightPin,LOW);

      
 } else if(count5==1&&count25==1 && count100==0 && count50==1){
       digitalWrite(WifiIndicatorLightPin,HIGH);



   delay (200);

              if (digitalRead(metalDetectorPin)==1){// Metal Detector
                            
                   // Serial.println("Metal Detected");

                    metalDetectorSwitch=1;
                
               }
  

             
                   if(metalDetectorSwitch==1){
                    Serial.println("Metal Detected");
                    Serial.println (" 50 Kurus Detected");

          
                       if ( fiftykurusDetectorAmount>=fiftykurusDetectorMaxDeterminedAmount){
              
                              Serial.println("Maxiumum Amount Reached");
                              RejectServoActivator();
                              
                            }else{
                              
                               fiftykurusDetectorAmount++;
                               Serial.print("fiftykurusDetectorAmount: ");Serial.println(fiftykurusDetectorAmount);
                               
                            }
                            
          
                 metalDetectorSwitch=0; //metal detector rebooted
              
            }else{
              Serial.println("Non Metal Detected");
              RejectServoActivator();
              metalDetectorSwitch=0; //metal detector rebooted
              
            }
      

       
           count5=0;
           count25=0;
          count50=0;
          count100=0;
          
          delay (200);  



  //digitalWrite(WifiIndicatorLightPin,LOW);
  
 }


  else if(count5==1&&count25==1 && count100==1 && count50==1){

         digitalWrite(WifiIndicatorLightPin,HIGH);


     delay (200);

              if (digitalRead(metalDetectorPin)==1){// Metal Detector
                            
                   // Serial.println("Metal Detected");

                    metalDetectorSwitch=1;
                
               }
    
   
                      if(metalDetectorSwitch==1){
                  Serial.println("Metal Detected");
              Serial.println (" 1 TL Detected");

                              if ( onetlDetectorAmount>=onetlDetectorMaxDeterminedAmount){

                              Serial.println("Maxiumum Amount Reached");
                              RejectServoActivator();
                              
                            }else{
                              
                               onetlDetectorAmount++;

                               Serial.print("onetlDetectorAmount: ");Serial.println(onetlDetectorAmount);
                               
         
                            }

              
              metalDetectorSwitch=0; //metal detector rebooted
                  
                }else{
                  Serial.println("Non Metal Detected");
                  RejectServoActivator();
                  metalDetectorSwitch=0; //metal detector rebooted
                  
                }

      
             

   
      
       count5=0;
       count25=0;
      count50=0;
      count100=0;
      
       delay (200);  



 // digitalWrite(WifiIndicatorLightPin,LOW);

        
  
 }

              
 
   //   metalDetectorSwitch=0; //metal detector rebooted

        //


      //Stuck Button
    if(digitalRead(stuckButtonPin)==LOW){
    
      delay(200);
    
      Pushservo.write( 30 ); // sets the servo position
      delay(600);
    
       Pushservo.write( 7 ); // sets the servo position
    }

      //
       
           // Seperator//

onetltankAnalog=analogRead(A6);
fiftykurustankAnalog = analogRead(A7);
twentyfivekurustankAnalog = analogRead(A8);
fivekurustankAnalog = analogRead(A9);


  /*
  Serial.println (onetltankAnalog);
  Serial.print("1tlamount: ");
  Serial.println (onetlAmount);

  */



  

    if (fivekurustankAnalog<700 && fivekuruscountstop==0){
          // digitalWrite(WifiIndicatorLightPin,HIGH);


      fivekurusAmount++;
      fivekuruscountstop=1;
String CoinAmountDataSerial = "5 Kurus: "+ String(fivekurusAmount) + " Pcs, 25 Kurus: "+ String(twentyfivekurusAmount) + " Pcs, 50 Kurus: "+ String(fiftykurusAmount) + " Pcs, 1 TL: "+ String(onetlAmount) + " Pcs";
   //  if(previousCoinAmountDataSerial.equals(CoinAmountDataSerial)!=1){
        Serial.println(CoinAmountDataSerial);
      delay(1500);

  digitalWrite(WifiIndicatorLightPin,LOW);
    
  }
  fivekuruscountstop=0;

  
    if (twentyfivekurustankAnalog<30 && twentyfivekuruscountstop==0){

        //   digitalWrite(WifiIndicatorLightPin,HIGH);
      twentyfivekurusAmount++;
      twentyfivekuruscountstop=1;
String CoinAmountDataSerial = "5 Kurus: "+ String(fivekurusAmount) + " Pcs, 25 Kurus: "+ String(twentyfivekurusAmount) + " Pcs, 50 Kurus: "+ String(fiftykurusAmount) + " Pcs, 1 TL: "+ String(onetlAmount) + " Pcs";
   //  if(previousCoinAmountDataSerial.equals(CoinAmountDataSerial)!=1){
        Serial.println(CoinAmountDataSerial);
      delay(1500);



  digitalWrite(WifiIndicatorLightPin,LOW);
    
  }
twentyfivekuruscountstop=0;



  
    if (fiftykurustankAnalog<30 && fiftykuruscountstop==0){

          // digitalWrite(WifiIndicatorLightPin,HIGH);


      fiftykurusAmount++;
      fiftykuruscountstop=1;
String CoinAmountDataSerial = "5 Kurus: "+ String(fivekurusAmount) + " Pcs, 25 Kurus: "+ String(twentyfivekurusAmount) + " Pcs, 50 Kurus: "+ String(fiftykurusAmount) + " Pcs, 1 TL: "+ String(onetlAmount) + " Pcs";
   //  if(previousCoinAmountDataSerial.equals(CoinAmountDataSerial)!=1){
        Serial.println(CoinAmountDataSerial);
      delay(1500);



  digitalWrite(WifiIndicatorLightPin,LOW);
    
  }
  fiftykuruscountstop=0;

    if (onetltankAnalog<30 && onetlcountstop==0){
          // digitalWrite(WifiIndicatorLightPin,HIGH);


      onetlAmount++;
      onetlcountstop=1;
String CoinAmountDataSerial = "5 Kurus: "+ String(fivekurusAmount) + " Pcs, 25 Kurus: "+ String(twentyfivekurusAmount) + " Pcs, 50 Kurus: "+ String(fiftykurusAmount) + " Pcs, 1 TL: "+ String(onetlAmount) + " Pcs";
   //  if(previousCoinAmountDataSerial.equals(CoinAmountDataSerial)!=1){
        Serial.println(CoinAmountDataSerial);
      delay(1500);


  digitalWrite(WifiIndicatorLightPin,LOW);
    
  }
  onetlcountstop=0;

  
    
   //  }

      
      // previousCoinAmountDataSerial= CoinAmountDataSerial;
      
        
        if(digitalRead(interruptPinUDV)==LOW){///////////////////
               digitalWrite(WifiIndicatorLightPin,HIGH);


          delay(250);

         // Serial.print("UserDesiredValueInterruptswitch");Serial.println(UserDesiredValueInterruptswitch);
          
                  backUpfivekurusAmount = fivekurusAmount;
                  backUptwentyfivekurusAmount = twentyfivekurusAmount;
                  backUpfiftykurusAmount = fiftykurusAmount;
                  backUponetlAmount = onetlAmount;
                  
                      
                      Serial.println("Data Receiving Initialized");
                  
                       ServerReply = WSUserDesiredValue();

                       

                       if(ServerReply.equals("ERROR")==1){

                        Serial.println("Connection Error Reconnecting!!!");

                        refreshWiFi();
                        ServerReply = WSUserDesiredValue();
    
                            if(ServerReply.equals("ERROR")==1){

                                Serial.println("Wifi cannot be connected!!!");
    
                                Serial.println("Control Your Internet Connection!!!");
        
                                Serial.println("Waiting!!!");
        
                                delay(2000);
        
                                Serial.println("Trying to Reconnect!!!");
    
                                refreshWiFi();

                                  ServerReply = WSUserDesiredValue();
    
                                if(ServerReply.equals("ERROR")==1){
    
                                  
                                 Serial.println("Control Your Internet Connection!!!");
    
                                 Serial.println("Wifi cannot be connected!!!");
    
                                  Serial.println("Working without WiFi!!!");
    
                                  
                                }
    
                             
                              } 
    
                            
                           }

                       
                    Serial.print("ServerReply: ");Serial.println(ServerReply);
                  
                    ServerReplySwitch=1;
                  
                    tankChoice=(ServerReply.substring(0, 1)).toDouble();
                  
                   // Serial.println(tankChoice);
                  
                       if (tankChoice==1){
                        Serial.print("5 Kurus : ");
                       }else if (tankChoice==2){
                        Serial.print("25 Kurus : ");
                       }else if (tankChoice==3){
                        Serial.print("50 Kurus : ");
                       }else if (tankChoice==4){
                        Serial.print("1 TL : ");
                       }
                    UserDesiredValue=(ServerReply.substring(1, 1 + digit-1)).toDouble();
                  
                    Serial.print(UserDesiredValue); Serial.println("  pcs");
                  
                    
                  
                  fivekurusAmount = backUpfivekurusAmount;
                  twentyfivekurusAmount = backUptwentyfivekurusAmount;
                  fiftykurusAmount = backUpfiftykurusAmount;
                  onetlAmount = backUponetlAmount;
                  
                  //refreshWiFi();//////burada
                  
                  
                  //UserDesiredValueInterruptswitch=false;
         // Serial.print("UserDesiredValueInterruptswitch");Serial.println(UserDesiredValueInterruptswitch);


  digitalWrite(WifiIndicatorLightPin,LOW);
          
        }
      
      
          if(digitalRead(interruptPinCAS)==LOW ||amountSenderSwitch==1){
                 digitalWrite(WifiIndicatorLightPin,HIGH);


            delay(250);

              //  Serial.print("CoinAmountSendInterruptswitch");Serial.println(CoinAmountSendInterruptswitch);
      
                backUpfivekurusAmount = fivekurusAmount;
                backUptwentyfivekurusAmount = twentyfivekurusAmount;
                backUpfiftykurusAmount = fiftykurusAmount;
                backUponetlAmount = onetlAmount;
                
                    Serial.println("Coin Amount Sender to Server has been Initiliazed");
                    
                    WifiSender();

                   if(WiFiSenderErrorCheckSwitch==1){
                    
                     Serial.println("Server Connection Error");
                     Serial.println("Reconnecting");

                      refreshWiFi();//////

                     WifiSender();
                     
                   }
  
                      
                        refreshWiFi();//////
                      

               
                    Serial.println("The Coin amount is sent");
                    
                fivekurusAmount = backUpfivekurusAmount;
                twentyfivekurusAmount = backUptwentyfivekurusAmount;
                fiftykurusAmount = backUpfiftykurusAmount;
                onetlAmount = backUponetlAmount;
                
                CoinAmountSendInterruptswitch=false;

              // Serial.print("CoinAmountSendInterruptswitch");Serial.println(CoinAmountSendInterruptswitch);
               
amountSenderSwitch=0;
  digitalWrite(WifiIndicatorLightPin,LOW);
        }
      
   if (previousServerReply.equals(ServerReply) !=1 || ServerReplySwitch==1 ){
         digitalWrite(WifiIndicatorLightPin,HIGH);



  Serial.println("Coin WithDraw Function = Servo");

      if(tankChoice==1){

        
          for (int i=0; i<UserDesiredValue; i++){
    
                fivekurusservo.write( 20 ); // sets the servo position
                fivekurusAmount--;
                fivekurusDetectorAmount--;

                delay(400);
        
                fivekurusservo.write( 179 ); // sets the servo position
    
                delay(500);
            }
            
      }else if(tankChoice==2){

        for (int i=0; i<UserDesiredValue; i++){

            twentyfivekurusservo.write( 20 ); // sets the servo position
            twentyfivekurusAmount--;

           twentyfivekurusDetectorAmount--;

            delay(500);
    
            twentyfivekurusservo.write( 179 ); // sets the servo position

            delay(500);
        }
      
        
      }else if(tankChoice==3){

          for (int i=0; i<UserDesiredValue; i++){

            fiftykurusservo.write( 20 ); // sets the servo position
            fiftykurusAmount--;

             fiftykurusDetectorAmount--;

            
            delay(550);
    
            fiftykurusservo.write( 179 ); // sets the servo position

            delay(550);
        }
      
        
      }else if(tankChoice==4){

        for (int i=0; i<UserDesiredValue; i++){

            onetlservo.write( 20 ); // sets the servo position
            onetlAmount--;

            onetlDetectorAmount--;
            delay(550);
    
            onetlservo.write( 179 ); // sets the servo position

            delay(400);
        }
      
        
      }

  ServerReplySwitch=0;


amountSenderSwitch=1;
  //refreshWiFi();//////



  //digitalWrite(WifiIndicatorLightPin,LOW);

  
  }
      
        
      
      
      
      previousServerReply = ServerReply;//changedv1
      
      
      



}

/*
 * 
 * 
 *  END OF MAIN LOOP
 * 
 * 
 */






void RejectServoActivator(){
  
rejectservo.write(169);//reject servo opened

Serial.println("Reject Servo is Opened");

delay(3000);

rejectservo.write(176);//reject servo closed

Serial.println("Reject Servo is Closed");


  
}

/*Wifi Communication*********************************************************************************************************************************************Wifi******************************************************








 **************************************************/

void UserDesiredValueInterrupt(){

  UserDesiredValueInterruptswitch =true;


   
   //UserDesiredValue = WSUserDesiredValue().toDouble();
   //Serial.print("UserDesiredValue: ");Serial.println(UserDesiredValue);

   //Serial.println("USDV ENTERED");

   
}


void CoinAmountSendInterrupt(){

  CoinAmountSendInterruptswitch=true;


 // WifiSender();
  
}







String WSUserDesiredValue()  //UserDesiredValue
{

 // sendCommand("AT+CIPMUX=1",5 ,"OK");
  //sendData("AT+CIPMUX=0", 1000, 1);
  char inv = '"';
  String add = "AT+CIPSTART";
  add += "=";
  add += inv;
  add += "TCP";   // type of connection
  add += inv;
  add += ",";
  add += inv;
  add += "api.thingspeak.com";  // host server
  add += inv;
  add += ",";
  add += "80";   // port
  add += "\r\n";
  sendData(add, 2000, 1);

  String rest = "AT+CIPSEND=90";
  rest += "\r\n";   // carriage return and new line
  sendData(rest, 1000, 1);


  String hostt = "GET /apps/thinghttp/send_request?api_key=CHANGE THIS";
  hostt += "\r\n";
  hostt += "Host:api.thingspeak.com";
  hostt += "\r\n\r\n\r\n\r\n\r\n";
  String Temp = sendData(hostt, 2000, 1);

sendData("AT+CIPCLOSE=0", 3000, 1);
 // sendCommand("AT+CIPCLOSE=0",5,"OK");

//  Serial.println(Temp)

/*
  if (Temp.indexOf("1:") > 0) {//SEARCH TEMPERATURE

    Temp = Temp.substring(Temp.indexOf("1:") + 2, Temp.indexOf("1:") + 2 + 1);
    backupUserDesiredValue = Temp;
  } else  if (Temp.indexOf("2:") > 0) {

    Temp = Temp.substring(Temp.indexOf("2:") + 2, Temp.indexOf("2:") + 2 + 2);
    backupUserDesiredValue = Temp;

  } else  if (Temp.indexOf("3:") > 0) {

    Temp = Temp.substring(Temp.indexOf("3:") + 2, Temp.indexOf("3:") + 2 + 3);
    backupUserDesiredValue = Temp;

  } else {

    Temp = backupUserDesiredValue;
  refreshWiFi();
    WSUserDesiredValue();
  }

*/

    if (Temp.indexOf("+IPD,") > 0) {

    int startindex=Temp.indexOf("+IPD,");
    digit=(Temp.substring(startindex+5, startindex+6)).toDouble();
    backupDigit = digit;
    int valueindex=startindex+7;

    
    /*
    Serial.println(Temp);
    Serial.println(Temp.indexOf("+IPD,"));
    Serial.println("***");
    Serial.println((Temp.substring(Temp.indexOf("+IPD,")+5, Temp.indexOf("+IPD,")+6)).toDouble());

    */
    
    Temp = Temp.substring(valueindex, valueindex + digit);
    
    backupUserDesiredValue = Temp;

    

  } else {

   
    Serial.println("Error Occurred");
   Temp = "ERROR" ;

    
  }

  return (Temp);



}


///////




String WSServoOne()  //ServoOne
{

 // sendCommand("AT+CIPMUX=1",5,"OK");
  //delay(2000);
  char inv = '"';
  String add = "AT+CIPSTART";
  add += "=";
  add += inv;
  add += "TCP";   // type of connection
  add += inv;
  add += ",";
  add += inv;
  add += "api.thingspeak.com";  // host server
  add += inv;
  add += ",";
  add += "80";   // port
  add += "\r\n";
  sendData(add, 3000, 1);

  String rest = "AT+CIPSEND=90";
  rest += "\r\n";   // carriage return and new line
  sendData(rest, 1000, 1);


  String hostt = "GET /apps/thinghttp/send_request?api_key=CHANGE THIS";
  hostt += "\r\n";
  hostt += "Host:api.thingspeak.com";
  hostt += "\r\n\r\n\r\n\r\n\r\n";
  String Temp = sendData(hostt, 2000, 1);delay(1500);

  sendCommand("AT+CIPCLOSE=0",5,"OK");


  if (Temp.indexOf("false") > 0) {

    Temp = "false";
    backupServoOne = Temp;
  } else  if (Temp.indexOf("true") > 0) {

    Temp = "true";
    backupServoOne = Temp;

  } else {

    Temp = backupServoOne;
  }


  return (Temp);



}









String sendData(String command, const int timeOut, boolean debug)// THE FUNCTION THAT RECEIVES AND SENDS THE DATA
{
  String response = "";//our response

  Serial1.print(command); // send the read character to the Serial1

  long int timeMilli = millis();//wait

  while ( (timeMilli + timeOut) > millis())
  {
    while (Serial1.available())
    {

      // The esp has data so display its output to the serial window
      char c = Serial1.read(); // read the next character.
      response += c;
    }
  }

  if (debug)
  {

    Serial.println(response);// the received data

  }

  return response;//return received data

}


void connectToWiFi() {

   // digitalWrite(WifiIndicatorLightPin,HIGH);

  Serial.println("Please Wait!");



  


  sendData("AT+RST\r\n", 2000, 1);
  sendData("AT+CWQAP\r\n", 5000, 1); // Disconnect WiFi if connected.
  char inv = '"';
  sendData("AT+CWMODE=1\r\n", 1000, 1); // configure as  station mode.
  delay(3000);

  sendData("AT+CWQAP\r\n", 4000, 1); // again quit the connection if any.
  String conn = "AT+CWJAP";
  conn += "=";
  conn += inv;
  conn += Host_name;  // Host name
  conn += inv;
  conn += ",";
  conn += inv;
  conn += password; // Password
  conn += inv;
  conn += "\r\n\r\n";
  sendData(conn, 7000, 1); // Join the connection.( AT+CWJAP = "Host_name","password" )

  Serial.println("You can continue!");
 
 // digitalWrite(WifiIndicatorLightPin, LOW);

}

void refreshWiFi() {
  //digitalWrite(WifiIndicatorLightPin,HIGH);
                      
  Serial.println("Please Wait Connecting...!");
                      
                    
                      
                        
                        

  sendData("AT+RST\r\n", 2000, 0);

 
  sendData("AT+CWQAP\r\n", 5000, 0); // Disconnect WiFi if connected.
  char inv = '"';
  sendData("AT+CWMODE=1\r\n", 1000, 0); // configure as  station mode.
  delay(3000);
 
  sendData("AT+CWQAP\r\n", 4000, 0); // again quit the connection if any.
 
  String conn = "AT+CWJAP";
  conn += "=";
  conn += inv;
  conn += Host_name;  // Host name
  conn += inv;
  conn += ",";
  conn += inv;
  conn += password; // Password
  conn += inv;
  conn += "\r\n\r\n";
  sendData(conn, 7000, 0); // Join the connection.( AT+CWJAP = "Host_name","password" )

  
    Serial.println("You can continue !");
                       
   // digitalWrite(WifiIndicatorLightPin, LOW);


}



/*End of Wifi Communication*********************************************************************************************************************************************Wifi******************************************************








 **************************************************/




 /*
  * 
  * 
  * 
  * 
  * ********************MAIN FUNCTIONS************
  * 
  */














bool BoolStringtoBoolean(String str) {// boolean to string converter

  if (str == "true") {

    return true;
  } else if (str == "false") {

    return false;
  }


}

String BooltoStr(bool a) {// string to boolean converter

  if (a) {

    return "true";
  } else if (!a) {

    return "false";
  }

}



void print2digits(int number) {
  if (number >= 0 && number < 10)
    Serial.write('0');
  Serial.print(number);
}


// Wifi Receiver
/*
void WifiSender(){

String API = "CHANGE THIS";   // CHANGE ME
String HOST = "api.thingspeak.com";
String PORT = "80";
String field = "field1";
  
 CoinAmountData = getCoinAmountData();
 String getData = "GET /update?api_key="+ API +"&"+ field +"="+String(valSensor);
 sendCommand("AT+CIPMUX=1",5,"OK");
 sendCommand("AT+CIPSTART=0,\"TCP\",\""+ HOST +"\","+ PORT,15,"OK");
 sendCommand("AT+CIPSEND=0," +String(getData.length()+4),4,">");
 Serial1.println(getData);delay(1500);countTrueCommand++;
 sendCommand("AT+CIPCLOSE=0",5,"OK");
 
}
*/

void WifiSender(){

String API = "CHANGE THIS";   // CHANGE ME
String HOST = "api.thingspeak.com";
String PORT = "80";
String field1 = "field1";
String field2 = "field2";
String field3 = "field3";
String field4 = "field4";
  
 //CoinAmountData = getCoinAmountData();
/*
 fivekurusAmount = random(10);
twentyfivekurusAmount = random(10);
fiftykurusAmount = random(10);
onetlAmount = random(10);

*/

  CoinAmountData = String(fivekurusAmount) +","+String(twentyfivekurusAmount)+","+ String(fiftykurusAmount)+","+String(onetlAmount);

  String CoinAmountDataSerial = "5 Kurus: "+ String(fivekurusAmount) + " Pcs, 25 Kurus: "+ String(twentyfivekurusAmount) + " Pcs, 50 Kurus: "+ String(fiftykurusAmount) + " Pcs, 1 TL: "+ String(onetlAmount) + " Pcs";
 
 Serial.println(CoinAmountDataSerial);

  
 String getData = "GET /update?api_key="+ API +"&"+ field1 +"="+String(fivekurusAmount)+"&"+ field2 +"="+String(twentyfivekurusAmount)+"&"+ field3 +"="+String(fiftykurusAmount)+"&"+ field4 +"="+String(onetlAmount);
 
 
 sendCommand("AT+CIPMUX=1",5,"OK");
 sendCommand("AT+CIPSTART=0,\"TCP\",\""+ HOST +"\","+ PORT,15,"OK");
 sendCommand("AT+CIPSEND=0," +String(getData.length()+4),4,">");
 Serial1.println(getData);delay(1500);countTrueCommand++;

 

 
 sendCommand("AT+CIPCLOSE=0",5,"OK");
 
}

/*
int getSensorData(){
  int rand=random(10); // Replace with
  Serial.print("Random Number:   ");
  Serial.println(rand);
  return rand; 
}*/


String getCoinAmountData(){
/*
fivekurusAmount = random(10);
twentyfivekurusAmount = random(10);
fiftykurusAmount = random(10);
onetlAmount = random(10);

*/

  CoinAmountData = String(fivekurusAmount) +","+String(twentyfivekurusAmount)+","+ String(fiftykurusAmount)+","+String(onetlAmount);
  String CoinAmountDataSerial = "5 Kurus: "+ String(fivekurusAmount) + " Pcs, 25 Kurus: "+ String(twentyfivekurusAmount) + " Pcs, 50 Kurus: "+ String(fiftykurusAmount) + " Pcs, 1 TL: "+ String(onetlAmount) + " Pcs";
 
 Serial.println(CoinAmountDataSerial);
  
  return CoinAmountData; 
}


void sendCommand(String command, int maxTime, char readReplay[]) {
 Serial.print(countTrueCommand);
 Serial.print(". at command => ");
 Serial.print(command);
 Serial.print(" ");
  while(countTimeCommand < (maxTime*1))
  {
    Serial1.println(command);//at+cipsend
    if(Serial1.find(readReplay))//ok
    {
      found = true;
      break;
    }
  
    countTimeCommand++;
  }
  
  if(found == true)
  {
    Serial.println("OYI");
    WiFiSenderErrorCheckSwitch==0;
    countTrueCommand++;
    countTimeCommand = 0;
  }
  
  if(found == false)
  {
    Serial.println("Fail");
    WiFiSenderErrorCheckSwitch=1;
    countTrueCommand = 0;
    countTimeCommand = 0;
  }
  
  found = false;
 }

//End of Wifi Receiver

