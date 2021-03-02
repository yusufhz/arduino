void dataserial(){
  switch(datame){
    case 'a':
      digitalWrite(LampTeng, 1);
      Serial.println("Lampu Tengah ON");
      break;
    case 'b':
      digitalWrite(LampTeng, 0);
      Serial.println("Lampu Tengah OFF");
      break;
    case 'c':
      digitalWrite(LampSamp, 1);
      Serial.println("Lampu Samping ON");
      break;
    case 'd':
      digitalWrite(LampSamp, 0);
      Serial.println("Lampu Samping ON");
      break;
    case 'e':
      digitalWrite(LampDep, 1);
      Serial.println("Lampu Depan ON");
      break;
    case 'f':
      digitalWrite(LampDep, 0);
      Serial.println("Lampu Depan ON");
      break;
    case 'g':
      Serial.println("Garasi Buka");
      for(int i = 110; i > 0; i-=10){
        garasi.write(i);
        delay(200);
      }
      datame ="";
      break;
    case 'h':
      Serial.println("Garasi Tutup");
      for(int i = 0; i < 110; i+=10){
        garasi.write(i);
        delay(200);
      }
      datame ="";
      break;
    default:
      break;
  }//end switch
}//end
