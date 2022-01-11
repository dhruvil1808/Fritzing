const int heater = 2, fan = 3;
int Ro = 50, B =  3950, Rseries = 10;
float To = 298.15;
int optimum = 25, variation = 2;
void setup() {
  pinMode(heater, OUTPUT);
  pinMode(fan, OUTPUT);
}

void loop() {
  float Vi = analogRead(A0) * (5.0 / 1023.0);
  float R = (Vi * Rseries) / (5 - Vi);
  float T =  1 / ((1 / To) + ((log(R / Ro)) / B));
  float Tc = T - 273.15;
  //For optimum temperature 25 and variation 2.
  //Heater control
  if (Tc <= (optimum - variation)) {
    //Below or equal 23 : heater ON
    digitalWrite(heater, HIGH);
  } else if (Tc >= optimum) {
    //Above or equal to 25 : heater OFF
    digitalWrite(heater, LOW);
  }
  //Fan control
  if (Tc >= (optimum + variation)) {
    //Above or equal to 27 : fan ON
    digitalWrite(fan, HIGH);
  } else if (Tc <= optimum) {
    //Below or equal to 25 : fan OFF
    digitalWrite(fan, LOW);
  }
  delay(1000);
}