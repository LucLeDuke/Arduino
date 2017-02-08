#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN     9
#define SS_PIN      10

MFRC522 mfrc522(SS_PIN, RST_PIN);

String read_rfid;

String ok_rfid_1="";
String ok_rfid_2="";
int lock = 7;

void setup() {
    Serial.begin(9600);
    while (!Serial);
    SPI.begin();
    mfrc522.PCD_Init();
    pinMode(lock, OUTPUT);

}

void dump_byte_array(byte *buffer, byte bufferSize) {
    read_rfid="";
    for (byte i = 0; i < bufferSize; i++) {
      read_rfid=read_rfid + String(buffer[i], HEX);    
    }
}
void open_lock() {     // servo will be here
  digitalWrite(lock, HIGH);
  delay(2000);
  digitalWrite(lock, LOW);
}


void loop() {
  if ( ! mfrc522.PICC_IsNewCardPresent())
      return;

  if ( ! mfrc522.PICC_ReadCardSerial())
      return;

  dump_byte_array(mfrc522.uid.uidByte, mfrc522.uid.size);
  Serial.println(read_rfid);
  if (read_rfid==ok_rfid_1) {
    Serial.println(ok_rfid_1);
    open_lock();
  }
  if (read_rfid==ok_rfid_2) {
    open_lock();
  }
      

}
