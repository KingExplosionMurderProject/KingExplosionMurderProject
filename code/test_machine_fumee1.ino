//Paramètres de départ
const int relais_ventilo = 2 ;
const int relais_resistance = 7 ;

void setup() {
  Serial.begin(9600);
  Serial.println("Initialisation du système");
  pinMode(relais_ventilo, OUTPUT);
  pinMode(relais_resistance, OUTPUT);
}

void loop() {
  Serial.println("_____Test_____");
  Serial.println("Allumons la résistance chauffante pendant 120 secondes");
  digitalWrite(relais_resistance,HIGH);
  digitalWrite(relais_ventilo,LOW);
  delay(120000);
  Serial.println("Allumons la ventilation");
  digitalWrite(relais_ventilo,HIGH);
  delay(5000);
  digitalWrite(relais_resistance,LOW);
  digitalWrite(relais_ventilo,LOW);
  Serial.println("Fin du test");
  delay(10000);
}
