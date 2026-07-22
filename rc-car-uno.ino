#include <SoftwareSerial.h>

SoftwareSerial bluetooth(2, 3); 

// --- BİRİNCİ SÜRÜCÜ PİNLERİ (İleri-Geri) ---
const int ENA = 9;  
const int IN1 = 10; 
const int IN3 = 6;  
const int ENB = 5;  
const int IN2 = 11; 
const int IN4 = 7;  

// --- İKİNCİ SÜRÜCÜ PİNLERİ (Sağ-Sol) ---
const int ENA2 = 12;
const int IN1_2 = 4; 
const int IN2_2 = 8; 

char veri; 
int hiz = 255; 

void setup() {
  // Birinci Sürücü Çıkış Tanımlamaları
  pinMode(ENA, OUTPUT); pinMode(IN1, OUTPUT); pinMode(IN3, OUTPUT);
  pinMode(ENB, OUTPUT); pinMode(IN2, OUTPUT); pinMode(IN4, OUTPUT);

  // İkinci Sürücü Çıkış Tanımlamaları
  pinMode(ENA2, OUTPUT); pinMode(IN1_2, OUTPUT); pinMode(IN2_2, OUTPUT);

  bluetooth.begin(9600);
  Serial.begin(9600);
  Serial.println("Çift Sürücü Hazır. Komut Bekleniyor...");
}

void loop() {
  if (bluetooth.available() > 0) {
    veri = bluetooth.read();
    Serial.print("Gelen Veri: "); Serial.println(veri);
    
    // --- İLERİ / GERİ KONTROLÜ ---
    if (veri == 'F') { 
      geri();  
    } 
    else if (veri == 'B') { 
      ileri();  
    } 
    // --- SAĞ / SOL KONTROLÜ ---
    else if (veri == 'L') { 
      sag(); 
    }
    else if (veri == 'R') { 
      sol(); 
    }
    // --- DURMA ---
    else if (veri == 'S') { 
      dur();
    }
  }
}

// --- HAREKET FONKSİYONLARI ---

void ileri() {
  analogWrite(ENA, hiz);
  digitalWrite(IN1, LOW);   digitalWrite(IN3, HIGH);
  analogWrite(ENB, hiz);
  digitalWrite(IN2, LOW);   digitalWrite(IN4, HIGH);
  Serial.println("Hareket: ILERI");
}

void geri() {
  analogWrite(ENA, hiz);
  digitalWrite(IN1, HIGH);  digitalWrite(IN3, LOW);
  analogWrite(ENB, hiz);
  digitalWrite(IN2, HIGH);  digitalWrite(IN4, LOW);
  Serial.println("Hareket: GERI");
}

void sol() {
  analogWrite(ENA2, hiz);
  digitalWrite(IN1_2, HIGH);
  digitalWrite(IN2_2, LOW);
  Serial.println("Hareket: SOLA KIR");
}

void sag() {
  analogWrite(ENA2, hiz);
  digitalWrite(IN1_2, LOW);
  digitalWrite(IN2_2, HIGH);
  Serial.println("Hareket: SAGA KIR");
}

void dur() {
  // Tüm motorları ve tüm sürücüleri durdurur
  digitalWrite(IN1, LOW);   digitalWrite(IN3, LOW);
  digitalWrite(IN2, LOW);   digitalWrite(IN4, LOW);
  digitalWrite(IN1_2, LOW); digitalWrite(IN2_2, LOW);
  analogWrite(ENA, 0); 
  analogWrite(ENB, 0); 
  analogWrite(ENA2, 0);
  Serial.println("Hareket: DUR");
}