void parsingData() {
  int j = 0;
  dt[j] = "";
  for( i= 1 ; i < dataInLast.length() ; i++) {    
    if (dataInLast[i] == ',') {
      j++;
      dt[j] = "";
    }
    if(dataInLast[i] == '*' || dataInLast[i] == '#'){
      break;
    } 
    else {
      if(dataInLast[i] == ','){
        i++;
      }
      dt[j] = dt[j] + dataInLast[i];
    }
  }
  L1 = dt[0];
  L2 = dt[1];
  L3 = dt[2];
  
}
