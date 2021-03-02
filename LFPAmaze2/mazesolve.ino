void turn (char dir) {
  switch(dir)
  {    
   case 'R':
     do {
      readsensor();
      right();
      Serial.print("Kanan");
    } while (error != 0);
   break;
   
   case 'L':
    do {
      readsensor();
      left();
      Serial.print("Kiri");
    } while (error != 0);
   break;
   
   case 'S':
      calculate_pid();
   break;

   case 'B':
    do {
      readsensor();
      left();
    } while (error != 0);
   break;
   
   case 'H':
    do {
      readsensor();
      left();
    } while (error != 0);
   break;
   
   case 'F':
      forward();
   break;
  }
}

void Maze(){
  while(!status1){
  readsensor();
  switch (mode){
       case Left:
       path[pathLength] = 'L'; 
       pathLength ++;
       turn('L');
       break;

       case Right:
      // forward();
       //delay(100);
         if(mode != Line){
            path[pathLength] = 'R'; 
            pathLength ++;
            turn('R');
         }
         else if (mode == Line){
            path[pathLength] = 'S'; 
            pathLength ++;
            turn('S');
            }
        break;   

       case Cross:
      // path[pathLength] = 'F'; 
      //pathLength ++;
       turn('F');
       break;

//       case Noline:
//       path[pathLength] = 'B'; 
//       pathLength ++;
//       turn('B');
//       break;

       case Fire:
       path[pathLength] = 'F'; 
       pathLength ++;
       padam = true;
       status1 = 1;
       turn('F');
       break;

       case Hall:
       path[pathLength] = 'B'; 
       pathLength ++;
       turn('B');
       break;

       case Line:
       calculate_pid();
       break;
  }
 }
}

void nullify(char a[]) {
  for (int i=0; i<pathSize; i++) {
    a[i] = NULL;
  }
}

void simpleMaze() {
  boolean changed = true;
  tempLength = pathLength;
  optimizedPathLength = pathLength;
  int i = 0;
  int j = 0;
  
  //copies the path array
  for (i=0; i<pathLength; i++) {
    a1[i] = path[i];
  }
  
  while (changed == true) {
    changed = false;
    for (i=0, j=0; i<tempLength; i++, j++) {
      if (a1[i+1] != 'B') {
        a2[j] = a1[i];
      } else if (a1[i+1] == 'B') {
        
        if (a1[i] == 'L' && a1[i+2] == 'R') {
          a2[j] = 'B';
        } else if (a1[i] == 'L' && a1[i+2] == 'S') {
          a2[j] = 'R';
        } else if (a1[i] == 'R' && a1[i+2] == 'L') {
          a2[j] = 'B';
        } else if (a1[i] == 'S' && a1[i+2] == 'L') {
          a2[j] = 'R';
        } else if (a1[i] == 'S' && a1[i+2] == 'S') {
          a2[j] = 'B';
        } else if (a1[i] == 'L' && a1[i+2] == 'L') {
          a2[j] = 'S';
        }
        
        i+=2;
        optimizedPathLength -= 2;
      } //end if
      
    } //end for
    nullify(a1);
    tempLength = optimizedPathLength;
    
    for (i=0, j=0; i<tempLength; i++, j++) {
      if (a2[i+1] != 'B') {
        a1[j] = a2[i];
      } else if (a2[i+1] == 'B') {
        
        if (a2[i] == 'L' && a2[i+2] == 'R') {
          a1[j] = 'B';
        } else if (a2[i] == 'L' && a2[i+2] == 'S') {
          a1[j] = 'R';
        } else if (a2[i] == 'R' && a2[i+2] == 'L') {
          a1[j] = 'B';
        } else if (a2[i] == 'S' && a2[i+2] == 'L') {
          a1[j] = 'R';
        } else if (a2[i] == 'S' && a2[i+2] == 'S') {
          a1[j] = 'B';
        } else if (a2[i] == 'L' && a2[i+2] == 'L') {
          a1[j] = 'S';
        }
        
        i+=2;
        optimizedPathLength -= 2;
        changed = true;
      } //end if
      
    } //end for
    nullify(a2);
    tempLength = optimizedPathLength;
  } //end while
  
  for (i=0; i<optimizedPathLength; i++) {
    optimizedPath[i] = a1[i];
    Serial.print(optimizedPath[i]);
    Serial.print('\t');
  }

  Serial.print('\n');
  
  for (i=0, j=0; i<optimizedPathLength; i++, j++) {
    if (optimizedPath[i] == 'L' ) {a3[j] = 'R';}
    else if (optimizedPath[i] == 'R' ) {a3[j] = 'L';}
    else if (optimizedPath[i] == 'S' ) {a3[j] = optimizedPath[i];}
    else if (optimizedPath[i] == 'B' ) {a3[j] = optimizedPath[i];}
  }

  for (j=0; j<optimizedPathLength; j++) {
    Serial.print(a3[j]);
    Serial.print('\t');
  }
  
  Serial.print('\n');
  
  for (i=0; i<optimizedPathLength; i++) {
    a4[i] = a3[i];
  }

  int temp;
  if(optimizedPathLength%2==0){
    for(i=0; i<optimizedPathLength/2; i++){
      temp=a4[optimizedPathLength-1-i];
      a4[optimizedPathLength-1-i]=a4[i];
      a4[i]=temp;
    }
    for (i=0; i<optimizedPathLength; i++) {
    Serial.print(a4[i]);
    Serial.print('\t');
  }
  }
  else if(optimizedPathLength%2==1){
    for(i=0; i<(optimizedPathLength-1)/2; i++){
      temp=a4[optimizedPathLength-1-i];
      a4[optimizedPathLength-1-i]=a4[i];
      a4[i]=temp;
    }
    for (i=0; i<optimizedPathLength; i++) {
    Serial.print(a4[i]);
    Serial.print('\t');
  }
  }
//  Serial.println(a4[1]);
 //Serial.println(optimizedPathLength);  
}
