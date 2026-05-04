#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include <addons/TokenHelper.h>
#include <addons/RTDBHelper.h>
#include <NewPing.h>
#include <ESP32Servo.h>

// ------------------------- CONFIGURATION -------------------------
const int TOTAL_SLOTS = 3;
#define SLOT_THRESHOLD 15
#define GATE_THRESHOLD 15
#define MAX_DISTANCE 200

// --- Pin Assignments ---
#define TRIG_PIN_1 4
#define ECHO_PIN_1 5
#define TRIG_PIN_2 6
#define ECHO_PIN_2 7
#define TRIG_PIN_3 8
#define ECHO_PIN_3 9
#define TRIG_GATE_PIN 18
#define ECHO_GATE_PIN 17
#define SERVO_PIN 13

// --- Wi-Fi & Firebase Credentials ---
#define WIFI_SSID ""
#define WIFI_PASSWORD ""
#define API_KEY "A"
#define DATABASE_URL "g-iot-86d8f-def"
#define USER_EMAIL "fozle"
#define USER_PASSWORD "12"

// ------------------------- OBJECTS -------------------------
NewPing sonar1(TRIG_PIN_1, ECHO_PIN_1, MAX_DISTANCE);
NewPing sonar2(TRIG_PIN_2, ECHO_PIN_2, MAX_DISTANCE);
NewPing sonar3(TRIG_PIN_3, ECHO_PIN_3, MAX_DISTANCE);
NewPing gateSonar(TRIG_GATE_PIN, ECHO_GATE_PIN, MAX_DISTANCE);
Servo gateServo;

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

bool slotStatus[TOTAL_SLOTS] = {false, false, false};
int availableSlots = TOTAL_SLOTS;
bool gateOpen = false;
unsigned long sendDataPrevMillis = 0;
bool firebaseReady = false;

// ------------------------- SETUP -------------------------
void setup() {
  Serial.begin(115200);
  delay(100);

  gateServo.attach(SERVO_PIN);
  gateServo.write(0);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.println("✅ Connected to Wi-Fi!");

  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
  firebaseReady = true;

  Serial.println("✅ Firebase Connected Successfully");
  Serial.println("🚗 Smart Parking System Started");
}

// ------------------------- LOOP -------------------------
void loop() {
  updateSlotStatus();
  controlGate();
  sendToFirebase();
  delay(500);
}

// ------------------------- FUNCTIONS -------------------------
void updateSlotStatus() {
  int dist1 = sonar1.ping_cm();
  int dist2 = sonar2.ping_cm();
  int dist3 = sonar3.ping_cm();

  slotStatus[0] = (dist1 > 0 && dist1 < SLOT_THRESHOLD);
  slotStatus[1] = (dist2 > 0 && dist2 < SLOT_THRESHOLD);
  slotStatus[2] = (dist3 > 0 && dist3 < SLOT_THRESHOLD);

  int occupiedCount = 0;
  for (int i = 0; i < TOTAL_SLOTS; i++) {
    if (slotStatus[i]) occupiedCount++;
  }
  availableSlots = TOTAL_SLOTS - occupiedCount;

  Serial.print("Available slots: ");
  Serial.println(availableSlots);
}

void controlGate() {
  int gateDistance = gateSonar.ping_cm();
  Serial.print("Gate distance: ");
  Serial.println(gateDistance);

  bool carAtGate = (gateDistance > 0 && gateDistance < GATE_THRESHOLD);

  if (carAtGate && availableSlots > 0) {
    gateServo.write(90);
    if (!gateOpen) {
      Serial.println("Gate: OPEN");
      gateOpen = true;
    }
  } else {
    gateServo.write(0);
    if (gateOpen) {
      Serial.println("Gate: CLOSED");
      gateOpen = false;
    }
  }
}

void sendToFirebase() {
  if (Firebase.ready() && firebaseReady && (millis() - sendDataPrevMillis > 2000 || sendDataPrevMil-lis == 0)) {
    sendDataPrevMillis = millis();

    if (!Firebase.RTDB.setInt(&fbdo, "Parking/AvailableSlots", availableSlots))
      Serial.println("Error updating AvailableSlots: " + fbdo.errorReason());

    if (!Firebase.RTDB.setBool(&fbdo, "Parking/Slot1", slotStatus[0]))
      Serial.println("Error updating Slot1: " + fbdo.errorReason());
    if (!Firebase.RTDB.setBool(&fbdo, "Parking/Slot2", slotStatus[1]))
      Serial.println("Error updating Slot2: " + fbdo.errorReason());
    if (!Firebase.RTDB.setBool(&fbdo, "Parking/Slot3", slotStatus[2]))
      Serial.println("Error updating Slot3: " + fbdo.errorReason());

    if (!Firebase.RTDB.setString(&fbdo, "Parking/GateStatus", gateOpen ? "OPEN" : "CLOSED"))
      Serial.println("Error updating GateStatus: " + fbdo.errorReason());

    Serial.println("✅ Data updated in Firebase");
  }
}.
