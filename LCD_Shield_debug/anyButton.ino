bool anyButton() {
  if(analogRead(A0)<1000) {
    return true;
  }
  else return false;
}

