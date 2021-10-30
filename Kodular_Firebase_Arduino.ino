/* masukkan library yang dibutuhkan */
#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>

/* buat object firebaseData dari class FirebaseData */
FirebaseData firebaseData;

void setup()
{
  /* atur pin D0 sebagai OUTPUT */
  pinMode(D0, OUTPUT);
  
  /* mulai komunikasi serial dengan baudrate 115200 */
  Serial.begin(115200);

  /* mulai koneksi WIFI begin(SSID,PASSWORD) */
  WiFi.begin(SSID, PASSWORD);

  /* tunggu hingga wifi terkoneksi */
  Serial.print("Menghubungkan ke Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Terkoneksi dengan IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  /* mulai koneksi dengan firebase begin(database URL ,database Secret */
  Firebase.begin(DATABASE_URL, DATABASE_SECRET);

  /* jika WIFI terputus , hubungkan kembali */
  Firebase.reconnectWiFi(true);
 
}

void loop()
{
  /* coba Ambil data dari FIREBASE di PATH "/belajar_kodular/kondisi_lampu" */
  if(Firebase.getString(firebaseData, "/belajar_kodular/kondisi_lampu") == true)
  {
    /* jika berhasil tampung dan tampilkan data tersebut  */
    String data_lampu = firebaseData.stringData();
    
    Serial.print("Ambil data string berhasil , = ");
    Serial.println(data_lampu);

    if(data_lampu == String("1"))
    {
      digitalWrite(D0, HIGH);
    }
    if(data_lampu == String("0"))
    {
      digitalWrite(D0, LOW);
    }
    delay(2000);
  }else{
    /* jika gagal tampilkan pesan error nya  */
    Serial.print("Ambil data String eroor, ");
    Serial.println(firebaseData.errorReason());
  }
}
