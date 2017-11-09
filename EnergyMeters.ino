/* SolOasis Energy Meter
*
*  @author Ya-Liang Chang
*  @version 1.0 2017-11-08
*
*/
int POWER_METER_MEASURE_PERIOD = 2;
int AVG_CICLE = 50;
int CURRENT_BIAS = 512;
double CURRENT_RATIO = 0.0375;
double VOLTAGE_RATIO = 4.056;
double currentSensorValue = 0;
double voltageSensorValue = 0;
double actualCurrent = 0;
double actualVoltage = 0;
double energy = 0;
void setup() {
  Serial.begin(9600);
  Serial.println("Current sensing program start");

}

void loop() {
  currentSensorValue = 0;
  voltageSensorValue = 0;
  actualCurrent = 0;
  actualVoltage = 0;
  // Calculate 100 ms average current and voltage, 
  // and approximate energy = sum of {(I * V) * 2ms} 
  for (int i=0; i<AVG_CICLE; i++){
    double currentInThisLoop = (analogRead(A4) - CURRENT_BIAS) * CURRENT_RATIO;
    double voltageInThisLoop = analogRead(A5) * VOLTAGE_RATIO / 1024 * 5;
    currentSensorValue += currentInThisLoop;
    voltageSensorValue += voltageInThisLoop;
    energy += currentInThisLoop * voltageInThisLoop * POWER_METER_MEASURE_PERIOD / 1000;
    delay(POWER_METER_MEASURE_PERIOD);
  }
  
  actualCurrent = currentSensorValue / AVG_CICLE;
  actualVoltage = voltageSensorValue / AVG_CICLE;
  //Compensate time taken my these calculations (about 1 millisecond)
  energy += actualVoltage * actualCurrent / 1000;
  Serial.print("V: ");
  Serial.print(actualVoltage);
  Serial.print(" / I: ");
  Serial.print(actualCurrent);
  Serial.print(" / P:");
  Serial.print(actualVoltage * actualCurrent);
  Serial.print(" / E:");
  Serial.println(energy);
}
