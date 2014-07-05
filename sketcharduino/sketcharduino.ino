/*
  Cafetera inteligente para el Reto Intel #CPMX5
  Julio 2014
  @sabasacustico
  theinventorhouse.org
*/
#define trigPin 2
#define echoPin 3

void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT_FAST);
  pinMode(echoPin, INPUT_FAST);
  pinMode(13, OUTPUT);
  digitalWrite(13,LOW);

  // Conectar a Galileo via telnet
  //system("telnetd -l /bin/sh"); 
 // Asgnar IP automatica DHCP
  system("ifconfig eth0 > /dev/ttyGS0");
  // Asgnar IP fija '192.168.1.78'
  //system("ifconfig eth0 192.168.1.78 netmask 255.255.255.0 up"); 
}

void loop() {
  
  char buffer[35];
  //Para poder ver la IP asignada en el monitor serial
  Serial.print(system("ifconfig eth0 > /dev/ttyGS0"));
  
  //Instrucciones para funcionamiento del sensor de distancia ultrasonico
  //PuseIn actualmente no esta funcionando en Intel Galileo Jul 2014
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
      
      digitalWrite(13, HIGH); //Led integrad en la tarjeta indica que esta trabajando
      
      temperatura=analogRead(0); //Lectura actual de la temperatura
      Serial.println(temperatura);
      String letras2=String(temperatura); //Convertimos a String
      String letras1="python /media/realroot/cafe.py ";
      String letras3=letras1+letras2; //Concatenamos string
      letras3.toCharArray(buffer,35); //Convertimos a arreglo de caracteres
      system(buffer); //Enviamos el arreglo de caracteres
    }
    
    delay(500);
    //Madamos la notificacion al smartphone
    system("node /media/realroot/notificacion.js");
    digitalWrite(13, LOW);
    Serial.println("Rico Cafe Listo");
  }
    
  
}

//Funcion que emula PulseIn
//Codigo encontrado en los foros de intel galileo
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
