void debug(){
  for(int i = 0; i < 5; i++){
    Serial.print("Flame ");
    Serial.print(Vlamed[i]);
    Serial.print(" ");
    Serial.println(Read_Vlame[i]);
  }
  Serial.print("Colour ");
  Serial.println(Read_Colour);
  // Hitam /Abu" > 300
  // Putih < 300
  Serial.print("UVtron :");
  Serial.println(Read_UVtron);
  // PING ==========
  Serial.print("Jarak Kiri = ");
  Serial.print(Jarak_Kiri);
  Serial.println(" cm");
  Serial.print("Jarak SKiri = ");
  Serial.print(Jarak_SKiri);
  Serial.println(" cm");
  Serial.print("Jarak Depan = ");
  Serial.print(Jarak_Depan);
  Serial.println(" cm");
  Serial.print("Jarak Kanan = ");
  Serial.print(Jarak_Kanan);
  Serial.println(" cm");
  Serial.print("Jarak SKanan = ");
  Serial.print(Jarak_SKanan);
  // Proxy =====
  Serial.print("Proxymity depan : ");
  Serial.println(Rproxydep);
}

