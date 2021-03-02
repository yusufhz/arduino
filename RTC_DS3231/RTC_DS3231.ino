/*====== Program Real Time Clock ======
  Get more : https://www.youtube.com/channel/UCfPiNFHD3s1-R-yc0BXMymQ
*/
#include <Wire.h> // library untuk penggunaan I2C
#include <DS3231.h> // library RTC DS3231

/* ==== Inisialisai ==== */
DS3231 clock;
RTCDateTime dt;

void setup() {
  Serial.begin(9600);
  Serial.println("Reading DS3231");
  
  for(int i = 0; i<=3;i+=1){
    Serial.println("Loading ....");
  }
  clock.begin();
  clock.setDateTime(__DATE__, __TIME__);

  // Manual (YYYY, MM, DD, HH, II, SS
   clock.setDateTime(2018, 3, 30, 18, 07, 00);
}

void loop() {
  dt = clock.getDateTime();

  Serial.print("Format Tanggal dan 24 Jam : ");
  Serial.println(clock.dateFormat("d-m-Y H:i:s", dt));

  Serial.print("Format dengan Nama Bulan  : ");
  Serial.println(clock.dateFormat("d F Y H:i:s",  dt));

  Serial.print("Format Tanggal dan 12 Jam : ");
  Serial.println(clock.dateFormat("jS M y, h:ia", dt));

  Serial.print("Hari ini, Tanggal         : ");
  Serial.println(clock.dateFormat("l, d F Y", dt));

  Serial.print("Jumlah Hari di Bulan ini  : ");
  Serial.print(clock.dateFormat("t", dt));
  Serial.print(" Hari. Hari ke ");
  Serial.print(clock.dateFormat("z", dt));
  Serial.println(" di tahun ini.");

  Serial.print("Unixtime                  : ");
  Serial.println(clock.dateFormat("U", dt));

  Serial.println();

  delay(1000);
}
