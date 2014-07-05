#include <SD.h> // The SD library is used to read a temporary file,
                // where the py script stores an unread email count.
                
#define trigPin 2
#define echoPin 3

void setup() {
  //initSDCard();  // Initializes the SD class
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT_FAST);
  pinMode(echoPin, INPUT_FAST);
  pinMode(13, OUTPUT);
  digitalWrite(13,LOW);

  // Connect to Galileo over telnet
  //system("telnetd -l /bin/sh"); 
  // Assign the IP address '192.168.1.78' to it
  //system("ifconfig eth0 down");
  //delay(1000);
  //system("ifconfig eth0 up");
  system("ifconfig eth0 > /dev/ttyGS0");
 
  //system("ifconfig eth0 192.168.1.78 netmask 255.255.255.0 up"); 
}

void loop() {
  
  char buffer[35];
  //Serial.print(system("ifconfig eth0 > /dev/ttyGS0"));
  long duration, distance;
  
  digitalWrite(trigPin, LOW); // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
  // delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn2(echoPin, HIGH);
  distance = (duration/29/2);
  if (distance >= 200 || distance <= 0){
    Serial.println("Alguien quiere un cafe?");
    
  }
  else {
    //Serial.print(distance);
    Serial.println("Buen dia");
    int temperatura=analogRead(0);
    
    while(temperatura <900){
      
      digitalWrite(13, HIGH);
      temperatura=analogRead(0);
      Serial.println(temperatura);
      String letras2=String(temperatura);
      String letras1="python /media/realroot/cafe.py ";
      String letras3=letras1+letras2;
      letras3.toCharArray(buffer,35);
      system(buffer);
    }
    delay(500);
    system("node /media/realroot/notificacion.js");
    digitalWrite(13, LOW);
    Serial.println("Rico Cafe Listo");
  }
    
  
}

unsigned long pulseIn2(uint8_t pin, uint8_t state) {
    unsigned long pulseWidth = 0;
    unsigned long loopCount = 0;
    unsigned long loopMax = 5000000;
    // While the pin is *not* in the target state we make sure the timeout hasn't been reached.
    while ((digitalRead(pin)) != state) {
        if (loopCount++ == loopMax) {
            return 0;
        }
    }
    // When the pin *is* in the target state we bump the counter while still keeping track of the timeout.
    while ((digitalRead(pin)) == state) {
        if (loopCount++ == loopMax) {
            return 0;
        }
        pulseWidth++;
    }
    // Return the pulse time in microsecond!
    return pulseWidth * 50; // Calculated the pulseWidth //this is the value to be tweaked
}
