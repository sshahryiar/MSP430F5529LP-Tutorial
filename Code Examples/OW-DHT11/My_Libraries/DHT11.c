#include "DHT11.h"


unsigned char values[0x05];


void DHT11_init(void)
{
   DHT11_DIR_IN();
   delay_ms(1000);
}


unsigned char get_byte(void)
{
   unsigned char s = 0;
   unsigned char value = 0;

   DHT11_DIR_IN();

   for(s = 0; s < 8; s++) 
   {
      value <<= 1;
      while(DHT11_pin_IN() == LOW);
      delay_us(30);

      if(DHT11_pin_IN() == HIGH)
      {
          value |= 1;
      }
      
      while(DHT11_pin_IN() == HIGH);
   }
   return value;
}


unsigned char get_data(void)
{
   short chk = 0;
   unsigned char s = 0;
   unsigned char check_sum = 0;

   DHT11_DIR_OUT();

   DHT11_pin_HIGH();
   DHT11_pin_LOW();
   delay_ms(18);
   DHT11_pin_HIGH();
   delay_us(26);
   
   DHT11_DIR_IN();

   chk = DHT11_pin_IN();
   
   if(chk)
   {
      return 1;
   }
   delay_us(80);
   
   chk = DHT11_pin_IN();

   if(!chk)
   {
      return 2;
   }
   delay_us(80);

   for(s = 0; s <= 4; s += 1)
   {
       values[s] = get_byte();
   }

   DHT11_DIR_OUT();
  
   DHT11_pin_HIGH(); 
   
   DHT11_DIR_IN();

   for(s = 0; s < 4; s += 1)
   {
       check_sum += values[s];
   }
   
   if(check_sum != values[4])
   {
      return 3;
   }
   else
   {
      return 0;
   }
}
