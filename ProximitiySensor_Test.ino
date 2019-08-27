
const int Sensor = 10; //Sensor input
int Value = 0;         //Actual value of the sensor
int old_Value = 0;     //Old value of the sensor
int State = 0;         // 1 = Object detected

void setup() {
  pinMode(Sensor, INPUT);
  Serial.begin(9600);
}

void loop() {
  Value = digitalRead(Sensor); // read the sensor input and stores it in val.

  //check if there was a state transition
  if ((Value == 1) && (old_Value == 0)) {
    Serial.println("Object Detected (1)");
  } else
  {
    Serial.println("Objct not detected (0)");
  }
  old_Value = Value;

  delay(1000);
}
