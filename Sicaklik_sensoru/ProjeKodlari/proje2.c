#include<16f877.h>
#device ADC=10

#use delay(clock=4000000)
#fuses XT,NOLVP,NODEBUG,NOPROTECT,NOBROWNOUT,NOWDT
#define use_portb_lcd TRUE
#include<lcd.c>
#use fast_io(a)
#use fast_io(c)
#use fast_io(d)
int adet=0,girilen[3]={0,0,0},imlec=11,i=0,toplam=0;
float hava;  
unsigned long int  bilgi;
unsigned int net[3]={0,0,0};
float voltaj;
void dereceAyarla();
void sira();
void sicaklik();

#int_timer0
void timer0_kesmesi()
{
   set_timer0(255);
   printf(lcd_putc,"\f3 tane 2-155\narasinda derece");
   delay_ms(1000);
   printf(lcd_putc,"\f%d.Giriniz:",adet+1);
   dereceAyarla();
}
#int_timer1
void timer1_Kesmesi()
{
   sicaklik();
}


void kontrol()
{
   if(i==1)
   {
       toplam=girilen[0];
   }
   else if(i==2)
   {
     toplam=girilen[0]*10+girilen[1];
   }
   else if(i==3)
   {
       toplam=girilen[0]*100+girilen[1]*10+girilen[2];
   }
   
   
   if(toplam>=2 && toplam<=150)
   {
      net[adet]=toplam;
      adet++;
      printf(lcd_putc,"\fKayit Basarili!!");
      delay_ms(1000);
      if(adet!=3){printf(lcd_putc,"\f%d.Derece:",adet+1);} if(adet==3){ printf(lcd_putc,"\fIslemler\n  Kaydedildi!!");delay_ms(1000);sira();lcd_putc("\f");}
   }
   
   if(toplam<2 || toplam>150)
   {

      printf(lcd_putc,"\fYanlis TUslama!!");
      delay_ms(1000);
      printf(lcd_putc,"\f%d.Derece:",adet+1);
   }
   
   girilen[0]=0; girilen[1]=0;   girilen[1]=0;
   toplam=0;
   i=0;
   imlec=11;
  
   
}

void dereceAyarla()
{
    adet=0;
    while(adet<3)
    {
       output_high(pin_d0);
       if(input(pin_d4)){delay_ms(20);if(i<3){girilen[i]=1;lcd_gotoxy(imlec,1);printf(lcd_putc,"%d",girilen[i]);i++;imlec++;while(input(pin_d4));}}
       if(input(pin_d5)){delay_ms(20);if(i<3){girilen[i]=2;lcd_gotoxy(imlec,1);printf(lcd_putc,"%d",girilen[i]);i++;imlec++;while(input(pin_d5));}}
       if(input(pin_d6)){delay_ms(20);if(i<3){girilen[i]=3;lcd_gotoxy(imlec,1);printf(lcd_putc,"%d",girilen[i]);i++;imlec++;while(input(pin_d6));}}
       output_low(pin_d0);
       
       output_high(pin_d1);
       if(input(pin_d4)){delay_ms(20);if(i<3){girilen[i]=4;lcd_gotoxy(imlec,1);printf(lcd_putc,"%d",girilen[i]);i++;imlec++;while(input(pin_d4));}}
       if(input(pin_d5)){delay_ms(20);if(i<3){girilen[i]=5;lcd_gotoxy(imlec,1);printf(lcd_putc,"%d",girilen[i]);i++;imlec++;while(input(pin_d5));}}
       if(input(pin_d6)){delay_ms(20);if(i<3){girilen[i]=6;lcd_gotoxy(imlec,1);printf(lcd_putc,"%d",girilen[i]);i++;imlec++;while(input(pin_d6));}}
       output_low(pin_d1);
       
       output_high(pin_d2);
       if(input(pin_d4)){delay_ms(20);if(i<3){girilen[i]=7;lcd_gotoxy(imlec,1);printf(lcd_putc,"%d",girilen[i]);i++;imlec++;while(input(pin_d4));}}
       if(input(pin_d5)){delay_ms(20);if(i<3){girilen[i]=8;lcd_gotoxy(imlec,1);printf(lcd_putc,"%d",girilen[i]);i++;imlec++;while(input(pin_d5));}}
       if(input(pin_d6)){delay_ms(20);if(i<3){girilen[i]=9;lcd_gotoxy(imlec,1);printf(lcd_putc,"%d",girilen[i]);i++;imlec++;while(input(pin_d6));}}
       output_low(pin_d2);
       
       
       output_high(pin_d3);
       if(input(pin_d5)){delay_ms(20);if(i<3){girilen[i]=0;lcd_gotoxy(imlec,1);printf(lcd_putc,"%d",girilen[i]);i++;imlec++;while(input(pin_d5));}}
       if(input(pin_d6)){delay_ms(20);while(input(pin_d6));kontrol();}
       output_low(pin_d3);
       
       
       
      
    }
}


void ilkAyar()
{
   setup_psp(PSP_DISABLED);
   setup_timer_1(T1_INTERNAL | T1_DIV_BY_8);
   setup_timer_2(T2_DISABLED,0,1);
   setup_adc(ADC_CLOCK_DIV_32);
   setup_adc_ports(AN0);
   lcd_init();
   setup_timer_0(RTCC_EXT_H_TO_L | RTCC_DIV_1);
   set_timer0(255);
   
    
   enable_interrupts(INT_TIMER1); 
   enable_interrupts(INT_TIMER0);
   enable_interrupts(GLOBAL);
   
   set_tris_a(0x13); output_a(0x00);
   set_tris_c(0x00); output_c(0x00);
   set_tris_d(0xF0); output_d(0x00);
   
   printf(lcd_putc,"\fDerece Ayarli\nLed Yanmasi");
      
}
void sicaklik()
{ 
    set_adc_channel(0); 
    delay_us(20);
    bilgi=read_adc();
    voltaj=bilgi*(0.0048828125)*1000;
    hava=(voltaj/10)+2;
    printf(lcd_putc,"\fSicaklik:%f ",hava);
    if(hava<net[0])output_c(0x01);
    if(hava>net[0] && hava<net[1])output_c(0x02);
    if(hava>=net[1] && hava<net[2])output_c(0x04);
    if(hava>=net[2] )output_c(0x08);
    
    delay_ms(100);
}

void sira()
{
   
   for(int t=0;t<3;t++)
   {
      for(int j=1;j<3-t;j++)
      { 
        if(net[j-1]>net[j])
        {
           int gecici=net[j];
           net[j]=net[j-1];
           net[j-1]=gecici;
           
        }
      }
   }
   
   
   
}

void main()
{
   ilkAyar();
   
   while(true)
   {
     if(input(pin_a1))
     {
        delay_ms(20);
        printf(lcd_putc,"\fDereceler:\n%u ,%u ,%u",net[0],net[1],net[2]);
        delay_ms(1000);
        lcd_putc("\f");
        
     }
     
   }
   
}
