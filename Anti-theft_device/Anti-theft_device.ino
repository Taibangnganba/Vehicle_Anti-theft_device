#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
#include <SoftwareSerial.h>
#include <DFRobot_SIM808.h>

#define RST_PIN 9
#define SS_PIN 10
#define RELAY_PIN 6
#define PIN_TX    2
#define PIN_RX    3
#define PHONE_NUMBER  "+91xxxxxxxxxx"

char lat[12];
char lon[12];
char *gpsLoc;
char phone[16];

SoftwareSerial mySerial(PIN_TX, PIN_RX);
DFRobot_SIM808 sim808(&mySerial); 

MFRC522 mfrc522(SS_PIN, RST_PIN);
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

byte authorizedUID[] = {0xB3, 0x8C, 0x8E, 0xA6};
bool isAuthenticated = false;
unsigned long lastAccessTime = 0;
const unsigned long accessTimeout = 5000;

void setup() {
  mySerial.begin(9600);
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH);
  Serial.println(F("Present card for access control"));
  
  if (!accel.begin()) {
    Serial.println("Ooops, no ADXL345 detected ... Check your wiring!");
    while (1);
  }
  accel.setRange(ADXL345_RANGE_16_G);
  Serial.println("ADXL345 ready!");

  while (!sim808.init()) {
    delay(1000);
    Serial.println("Sim808 init error");
  }
  Serial.println("Sim808 init success");
  Serial.println("Start to call ...");

  if (sim808.attachGPS())
    Serial.println("Open the GPS power success");
  else
    Serial.println("Open the GPS power failure");

  Serial.println("Init Success, please send SMS message to me!");
}

void loop() {
  bool access_granted = false;

  if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) {
    if (!isAuthenticated || millis() - lastAccessTime >= accessTimeout) {
      isAuthenticated = false;
      digitalWrite(RELAY_PIN, HIGH);
      Serial.println(F("Authorization revoked due to timeout"));
      access_granted = false;
      mfrc522.PICC_HaltA();
      mfrc522.PCD_StopCrypto1();
    }

    delay(50);
  } 
  else {
    if (compareUID(mfrc522.uid.uidByte, authorizedUID, mfrc522.uid.size)) {
      isAuthenticated = true;
      lastAccessTime = millis();
      Serial.println(F("Access Granted."));
      digitalWrite(RELAY_PIN, LOW);
      return;
    } 
    else {
      isAuthenticated = false;
      Serial.println(F("Access Denied! Present a proper CARD"));
      digitalWrite(RELAY_PIN, HIGH);
    }
  }

  if (!isAuthenticated) {
    Serial.println("Out of scope");

    float threshold = 11;
    if (isMotionDetected(threshold)) {
      Serial.println("Motion detected!");
        char* gpsLoc = getGPSLocation();
        if (gpsLoc != NULL) {
          sim808.sendSMS((char*)PHONE_NUMBER, gpsLoc);
          sim808.callUp((char*)PHONE_NUMBER);
          free(gpsLoc); // Free the dynamically allocated memory
        } else {
          Serial.println("Error: GPS location is NULL.");
        }
      }
    }

  checkSMS(); 
}

bool compareUID(byte* uid1, byte* uid2, byte size) {
  for (byte i = 0; i < size; i++) {
    if (uid1[i] != uid2[i]) {
      return false;
    }
  }
  return true;
}

bool isMotionDetected(float threshold) {
  sensors_event_t event;
  accel.getEvent(&event);

  float x = event.acceleration.x;
  float y = event.acceleration.y;
  float z = event.acceleration.z;

  float magnitude = sqrt(x * x + y * y + z * z);
  Serial.println(magnitude);

  return magnitude > threshold;
}
  
 void checkSMS() {
  int messageIndex = sim808.isSMSunread();

  if (messageIndex > 0) {
    char datetime[24];
    char sender[16];
    char message[200];

    // Read the SMS message
    if (sim808.readSMS(messageIndex, message, 200, sender, datetime)) {
      Serial.println("Msg received from: ");
      Serial.println(sender);
      Serial.println("Message content: ");
      Serial.println(message);
      String msgContent = String(message); 
      msgContent.toLowerCase();
      if (msgContent.indexOf("gps") != -1) { 
      char* gpsLoc = getGPSLocation();
      if (gpsLoc != NULL) {
          sim808.sendSMS(sender, gpsLoc);
          free(gpsLoc); // Free the dynamically allocated memory
        } else {
          Serial.println("Error: GPS location is NULL.");
        }
      }
    }
  }
}
char* getGPSLocation() {
  // Keep trying until GPS data is available
  while (!sim808.getGPS()) {}

  // Convert latitude and longitude to strings
  char lat[12];
  char lon[12];
  dtostrf(sim808.GPSdata.lat, 6, 7, lat);
  dtostrf(sim808.GPSdata.lon, 6, 7, lon);

  // Construct GPS location string
  char* gpsLoc = (char*)malloc(100);
  if (gpsLoc != NULL) {
    snprintf(gpsLoc, 100, "Latitude : %s\nLongitude : %s\nhttp://maps.google.com/maps?q=%s,%s\n", lat, lon, lat, lon);
  } else {
    Serial.println("Error: Failed to allocate memory for GPS location.");
  }

  return gpsLoc;
}
