void suarabt(){
  if(suara == "nyalakan lampu tengah" 
  || suara == "nyalakan Lampu tengah" 
  || suara == "nyalakan lampu Tengah" 
  || suara == "nyalakan lampu Tengah" 
  || suara == "Nyalakan Lampu tengah"
  || suara == "Nyalakan Lampu Tengah"){
    digitalWrite(LampTeng, 1);
    Serial.println("Lampu Tengah ON");
  }

  if(suara == "nyalakan lampu depan" 
  || suara == "Nyalakan lampu depan" 
  || suara == "Nyalakan Lampu depan"
  || suara == "Nyalakan Lampu Depan"){
    digitalWrite(LampDep, 1);
    Serial.println("Lampu Depan ON");
  }

  if(suara == "nyalakan lampu samping" 
  || suara == "Nyalakan lampu samping" 
  || suara == "Nyalakan Lampu samping"
  || suara == "Nyalakan Lampu Samping"){
    digitalWrite(LampSamp, 1);
    Serial.println("Lampu Samping ON");
  }
  
  if(suara == "matikan lampu tengah"
  || suara == "Matikan lampu tengah"
  || suara == "matikan Lampu tengah" 
  || suara == "matikan lampu Tengah"  
  || suara == "Matikan Lampu tengah"
  || suara == "Matikan Lampu Tengah"){
    digitalWrite(LampTeng, 0);
    Serial.println("Lampu Tengah OFF");
  }
  
  if(suara == "matikan lampu depan"
  || suara == "Matikan lampu depan"
  || suara == "Matikan Lampu depan"
  || suara == "Matikan Lampu Depan"){
    digitalWrite(LampDep, 0);
    Serial.println("Lampu Depan OFF");
  }

  if(suara == "matikan lampu samping"
  || suara == "matikan lampu Samping"
  || suara == "matikan Lampu Samping"
  || suara == "Matikan lampu samping"
  || suara == "Matikan Lampu samping"
  || suara == "Matikan Lampu Samping"){
    digitalWrite(LampSamp, 0);
    Serial.println("Lampu Saping OFF");
  }

  if(suara == "buka garasi"
  || suara == "Buka garasi"
  || suara == "Buka Garasi"){
    Serial.println("Garasi Buka");
    for(int i = 110; i > 0; i-=10){
      garasi.write(i);
      delay(200);
    }
    suara = "";
  }

  if(suara == "tutup garasi"
  || suara == "Tutup garasi"
  || suara == "Tutup Garasi"){
    Serial.println("Garasi Tutup");
    for(int i = 0; i < 110; i+=10){
      garasi.write(i);
      delay(200);
    }
    suara = "";
  }
  if(suara == "matikan semua lampu"
  || suara == "Matikan semua lampu"
  || suara == "Matikan semua lampu"
  || suara == "Matikan semua lampu"){
    digitalWrite(LampSamp, 0);
    digitalWrite(LampTeng, 0);
    digitalWrite(LampDep, 0);
    Serial.println("Semua Lampu OFF");
  }
}
