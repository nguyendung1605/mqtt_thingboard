#include <Arduino.h>

extern boolean check_node ;
extern float temperature ;

void data_node(){
    check_node = false ;
    temperature = random(20,30);
    check_node = true ;
}