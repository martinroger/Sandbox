bool anyButton() {
  if(analogRead(A0)<1021) {
    return true;
  }
  else return false;
}

