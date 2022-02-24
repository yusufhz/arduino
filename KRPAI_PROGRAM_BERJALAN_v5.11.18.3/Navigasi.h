void Navigasi_Darat(){
//  if(Rproxydep != 1){
//    mundur();
//    mundur();
//    mundur();
//    belok_kanan();
//    belok_kanan();
//    belok_kanan();
//    belok_kanan();
//    belok_kanan();
//    belok_kanan();
//  }
  if(Jarak_Depan > 14 ){//|| Rproxydep != 0){
    if(Jarak_SKanan < 14){
      belok_kiri();
    }
    else if(Jarak_SKiri < 14){
      belok_kanan();
    }
    else if(Jarak_Kanan > 20){// 30
      belok_kanan();
    }
    else if(Jarak_Kanan < 10 ){
      belok_kiri();
      maju();
    }
//    else if(Jarak_Kiri > 20 && Jarak_Kanan > 20){
//      belok_kanan();
//      belok_kanan();
//      belok_kanan();
//      maju();
//      maju();
//      maju();
//    }
    else{
      maju();
    }
  }
  //else if (Jarak_Depan < 14 || Rproxydep != 1 ){
  else{ 
    if(Jarak_SKiri < 14 || Jarak_Kiri < 14){
        belok_kanan();
//      do{
//        belok_kanan();
//        sensor_pingdep();
//        if(Jarak_Depan > 22){
//          break;
//        }
//      }
//      while(Jarak_Depan > 20);
    }
    else if(Jarak_SKanan < 14 || Jarak_Kanan < 14) {
        belok_kiri();
//      do{
//        belok_kiri();
//        sensor_pingdep();
//        if(Jarak_Depan > 22){
//          break;
//        }
//      }
//    while(Jarak_Depan > 20);
    }else{
      belok_kiri();
    }
  }
}

void Navigasi_Api(){
  if(Read_Vlame[2] > Read_Vlame[1] && Read_Vlame[2] > Read_Vlame[3]){
    if(Read_Vlame[2] <= 70){
      digitalWrite(Relay_Ex, HIGH);
      delay(100);
      madamkan();
      digitalWrite(Relay_Ex, HIGH);
      delay(100);
      madamkan();
      Gerak_Jalan = false;
    }else{
      digitalWrite(Relay_Ex, LOW);
      Gerak_Jalan = true;
    }
    Navigasi_Darat();
  }
  else if(Read_Vlame[1] > Read_Vlame[2]){
    belok_kanan();
  }
  else {
    belok_kiri();
  }
}
