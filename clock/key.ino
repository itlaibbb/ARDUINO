
int rd_key()
{
  int key_code;
//
    key_code = PIND & 0b00111100;
    return (key_code);
}



