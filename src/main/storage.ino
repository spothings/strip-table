#define EEPROM_SIZE 8

void EEPROMSetup(){
  EEPROM.begin(EEPROM_SIZE);
}

void StorageWrite(int _address, int _value){
  EEPROM.put(_address, _value);
  EEPROM.commit();
}

int StorageRead(int _address){
  int value;
  EEPROM.get(_address, value);
  EEPROM.commit();

  return value;
}