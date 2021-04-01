//TUGAS BESAR SISTEM DIGITAL DAN MIKROPROSESOR

// Air Humidifier ----------------------------------------------------------------------------

// 18318010 | Salma Majidah 
// 18318011 | M. Izzrul Izzrufi 

//  Kebutuhan Awal ---------------------------------------------------------------------------
#include <DHT.h>

//  Pemetaan PIN -----------------------------------------------------------------------------
//    Digital
// D2   | 2   - Relay ke Mist Maker
// D3   | 3   - Relay ke Kipas

//    Analog 
// A0   - DHT 11 (sensor suhu dan kelembapan)   
// A1   - Potensiometer  

//  Persiapan Lokal --------------------------------------------------------------------------
//  DHT
#define DHTPIN A0     //PIN yang digunakan DHT
#define DHTTYPE DHT11   // jenis DHT : DHT 11
DHT dht(DHTPIN, DHTTYPE);

//  Mist maker
int mist = 2;

//  Kipas
int kipas = 3;

// Potensiometer
#define potPIN A1

//  Kalibrasi
int cal = 7;

//  Fungsi Setup -----------------------------------------------------------------------------
void setup() {
  //  Serial begin dan Greeting
  Serial.begin(9600); //baud komunikasi serial
  Serial.println(" Air Humidifier Diaktifkan! "); 

  //  Pengaturan pin kipas dan mist maker sebagai output
  pinMode(kipas, OUTPUT);
  pinMode(mist, OUTPUT);
  
  //  Pembacaan modul sensor dht11
  dht.begin(); 
}

//  Fungsi Loop ------------------------------------------------------------------------------

void loop() {
  //  Menunggu kesiapan sensor
  delay (2000); 

  //  Membaca potensiometer ...
  //  ...(nilai potensiometer diatur agar memiliki range 40-80)
  int pot = 40 + (analogRead(potPIN) / 25);
  
  //  Membaca Kelembapan 
  float kelembapan = dht.readHumidity()+ cal ;
  
  //  Mengecek pembacaan apabila gagal
  if (isnan(kelembapan) ) 
  {
    Serial.println("Pembacaan data dari module sensor gagal!");
    return;
  }
  
  //  Menampilkan nilai kelembapan, target kelembapan, dan kondisi air humidifier
  Serial.print("Kelembapan: " + String(kelembapan) + " %\t");
  Serial.print("Target Kelembapan: " + String(pot) + " %\t");
  Serial.print("Air Humidifier : ");
  
  //  Jika kelembapan kurang dari nilai treshold
  //  Pengulangan pembacaan kondisi alat
  while (kelembapan <= pot)
  {
    // Air humidifier menyala selama 5 detik
    Serial.println(" ON ");
    digitalWrite(mist, LOW);
    digitalWrite(kipas, LOW);
    delay(5000);
    
    //  Pembacaan ulang variabel dan penampilan ulang pada serial monitor
    kelembapan = dht.readHumidity() + cal;
    pot = 40 + (analogRead(potPIN) / 25);
    Serial.print("Kelembapan: " + String(kelembapan) + " %\t");
    Serial.print("Target Kelembapan: " + String(pot) + " %\t");
    Serial.print("Air Humidifier : ");
  }

  //  Mematikan air humidifier apabila kondisi tidak terpenuhi
  Serial.println(" OFF ");
  digitalWrite(mist, HIGH);
  digitalWrite(kipas, HIGH);
}
