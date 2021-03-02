boolean Testing;
boolean Tes_Sensor;
boolean Tes_Suara;

void pin_testing(){
  pinMode (A0, INPUT_PULLUP);
  pinMode (A1, INPUT_PULLUP);
}

void Test(){
  if(digitalRead(A0) == 1){
    Tes_Sensor = true;
    Serial.println("Mode Testing Sensor Aktif");
  }else{
    Tes_Sensor = false;
  }
  if(digitalRead(A1) == 1){
    Tes_Suara = true;
    Serial.println("Mode Testing Suara Aktif");
  }else{
    Tes_Suara = false;
  }
  if(Tes_Suara == true || Tes_Sensor == true){
    Testing = true;
  }else{
    Testing = false;
  }
}

