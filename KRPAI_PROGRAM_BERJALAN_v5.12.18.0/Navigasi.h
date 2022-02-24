void Navigasi_Darat(){
  if(Rproxydep == 0){
    mundur();
    mundur();
    mundur();
    belok_kanan();
    belok_kanan();
    belok_kanan();
    belok_kanan();
    belok_kanan();
    belok_kanan();
  }
  else if(Jarak_Depan > 14){
    if(Jarak_SKanan < 14){
      belok_kiri();
    }
    else if(Jarak_SKiri < 14){
      belok_kanan();
    }
    else if(Jarak_Kanan > 20 || Rproxykan == 0){// 30
      belok_kanan();
    }
    else if(Jarak_Kanan < 10 ){
      belok_kiri();
      maju();
    }
    else if(Jarak_Kiri > 50 && Jarak_Kanan > 50 ){
      maju();
      maju();
    }
    else{
      maju();
    }
  }
  //else if (Jarak_Depan < 14 || Rproxydep != 1 ){
  else{ 
    if(Jarak_SKiri < 14 || Jarak_Kiri < 14){
        belok_kanan();
    }
    else if(Jarak_SKanan < 14 || Jarak_Kanan < 14) {
        belok_kiri();
    }else{
      belok_kiri();
    }
  }
}

void Navigasi_Api(){
  if(Read_Vlame[2] > Read_Vlame[1] && Read_Vlame[2] > Read_Vlame[3]){
    maju();
  }
}
