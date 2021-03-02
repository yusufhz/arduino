String dataIn = "";
String dataInLast = "*";
String dt[20];
String L1, L2, L3;
bool parsing;

void setup() {
  Serial.begin(115200);
  Serial3.begin(115200);
}

void loop() {
  ceknode();
}

void parsingData() {
  int j = 0;
  dt[j] = "";
  for(int i= 1 ; i < dataInLast.length() ; i++) {    
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
  
  Serial.print("data 1 = ");  Serial.println(L1);
  Serial.print("data 2 = ");  Serial.println(L2);
  Serial.print("data 3 = ");  Serial.println(L3);
}

void ceknode() {
  if (Serial3.available() > 0) {
    char inChar = (char)Serial3.read();
    dataIn += inChar;
    delay(20);
    Serial.print("dataIn     : ");Serial.println(dataIn);
    Serial.print("dataInLast : ");Serial.println(dataInLast);
    
    if (inChar == '\n' && dataInLast != dataIn) {
        parsing = true;
    }
  }
  if (parsing) {
    dataInLast = dataIn;
    parsingData();
    parsing = false;
    dataIn="";
  }
}
