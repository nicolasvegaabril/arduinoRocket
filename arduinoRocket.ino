/* Librerias necesarias */
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
#include <Servo.h>

int servoPin = 9;
Servo Servo1;

/* Asigna id al sensor*/
Adafruit_ADXL345_Unified accel =
Adafruit_ADXL345_Unified(12345);
void displaySensorDetails(void){
  sensor_t sensor;
  accel.getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.print ("Sensor: ");
  Serial.println(sensor.name);
  Serial.print ("Id: ");
  Serial.println(sensor.sensor_id);
  Serial.print ("Valor maximo: ");
  Serial.print(sensor.max_value); Serial.println(" G");
  Serial.print ("Valor minimo: ");
  Serial.print(sensor.min_value); Serial.println(" G");
  Serial.print ("Resolucion: ");
  Serial.print(sensor.resolution); Serial.println(" G");
  Serial.println("------------------------------------");
  Serial.println("");
  delay(500);
}
void displayDataRate(void){
  Serial.print ("Data Rate: ");
  switch(accel.getDataRate()){
  case ADXL345_DATARATE_3200_HZ:
  Serial.print ("3200 ");
  break;
  case ADXL345_DATARATE_1600_HZ:
  Serial.print ("1600 ");
  break;
  case ADXL345_DATARATE_800_HZ:
  Serial.print ("800 ");
  break;
  case ADXL345_DATARATE_400_HZ:
  Serial.print ("400 ");
  break;
  case ADXL345_DATARATE_200_HZ:
  Serial.print ("200 ");
  break;
  case ADXL345_DATARATE_100_HZ:
  Serial.print ("100 ");
  break;
  case ADXL345_DATARATE_50_HZ:
  Serial.print ("50 ");
  break;
  case ADXL345_DATARATE_25_HZ:
  Serial.print ("25 ");
  break;
  case ADXL345_DATARATE_12_5_HZ:
  Serial.print ("12.5 ");
  break;
  case ADXL345_DATARATE_6_25HZ:
  Serial.print ("6.25 ");
  break;
  case ADXL345_DATARATE_3_13_HZ:
  Serial.print ("3.13 ");
  break;
  case ADXL345_DATARATE_1_56_HZ:
  Serial.print ("1.56 ");
  break;
  case ADXL345_DATARATE_0_78_HZ:
  Serial.print ("0.78 ");
  break;
  case ADXL345_DATARATE_0_39_HZ:
  Serial.print ("0.39 ");
  break;
  case ADXL345_DATARATE_0_20_HZ:
  Serial.print ("0.20 ");
  break;
  case ADXL345_DATARATE_0_10_HZ:
  Serial.print ("0.10 ");
  break;
  default:
  Serial.print ("???? ");
  break;
  }
  Serial.println(" Hz");
}
void displayRange(void){
  Serial.print ("Range: +/- ");
  switch(accel.getRange()){
  case ADXL345_RANGE_16_G:
  Serial.print ("16 ");
  break;
  case ADXL345_RANGE_8_G:
  Serial.print ("8 ");
  break;
  case ADXL345_RANGE_4_G:
  Serial.print ("4 ");
  break;
  case ADXL345_RANGE_2_G:
  Serial.print ("2 ");
  break;
  default:
  Serial.print ("?? ");
  break;
  }
  Serial.println(" g");
}
void setup(void){
  Servo1.attach(servoPin);
  Serial.begin(9600);
  Serial.println("Accelerometer Test");
  Serial.println("");
  Servo1.write(0);
  /* Inicializa el sensor */
  if(!accel.begin()){
  /* Si no se detecta el sensor */
  Serial.println("Sensor no detectado");
  while(1);
  }
  accel.setRange(ADXL345_RANGE_16_G);
  /* Muestra informacion basica del sensor */
  displaySensorDetails();
  /* Muestra informacion adicional */
  displayDataRate();
  displayRange();
  Serial.println("");
}
void loop(void) {
  /* Nuevo event del sensor*/
  sensors_event_t event;
  accel.getEvent(&event);
  /* Muestra los resultados, se divide entre 9.8 para
  dar el valor en G */
  Serial.print("X: "); Serial.print(event.acceleration.x
  /9.8); Serial.print(" ");
  Serial.print("Y: "); Serial.print(event.acceleration.y
  /9.8); Serial.print(" ");
  Serial.print("Z: "); Serial.print(event.acceleration.z
  /9.8); Serial.print(" ");
  Serial.println("G");
  /*Abre el paracaidas si el cohete esta de costado*/
  if (event.acceleration.x /9.8 < 0.3){
  Servo1.write(90);
  }
  delay(400);
}
