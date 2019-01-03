/* 
                     HOMEAUTOTMATION Using........... 
 Fingerprint 				..
 GSM
 Bluetooth
 interrupt
 LCD Interfacing
 Relay
*/
#include"LPC2148.H"

delay()
{
int i;
for(i=0;i<3500;i++);
}
delay1()			 
{
int z,q;
for(z=200;z>0;z--)
{for(q=200;q>0;q--);}}

 int main()
 {
 VPBDIV= 0x02;
 PINSEL0=0x05;
 U0LCR= 0x83;
 U0DLL= 0xC3;
 U0LCR= 0x03;
 fingerprint();
  
 }

 //fingerprint
fingerprint()
{
collect();
}

send(int data)
{
while( (U0LSR & 0x20)==0);
U0THR = data;
}

receive()
{
while( (U0LSR & 0x01)==0);
return(U0RBR);
}

empty()	  // to empty
{
char empty[12]={0xEF,0x01,0xFF,0xFF,0xFF,0xFF,0x01,0x00,0x03,0x0D,0x00,0x11};
char acknowledge[12];
int i,j;
for(i=0;i<12;i++)
{
send(empty[i]);
}
for(j=0;j<12;j++)
{
acknowledge[j]=receive();
}
if(acknowledge[9]==0x00)
{
sendstring("storage full");
}
else
{
sendstring("emptied");
}}

collect()
{
char collect[12]={0xEF,0x01,0xFF,0xFF,0xFF,0xFF,0x01,0x00,0x03,0x01,0x00,0x05};
char acknowledge[12];
int i,j;
for(i=0;i<12;i++)
{
send(collect[i]);
}
for(j=0;j<12;j++)
{
acknowledge[j]=receive();
}
if(acknowledge[9]==0)
{
character();
sendstring("data collected");
}
else
{
sendstring("retry");
//empty();
}}

character()
{
char character[13]={0xEF,0x01,0xFF,0xFF,0xFF,0xFF,0x01,0x00,0x04,0x02,0x01,0x00,0x08};
char acknowledge[13];
int i,j;
for(i=0;i<13;i++)
{
send(character[i]);
}
for(j=0;j<12;j++)
{
acknowledge[j]=receive();
}
if(acknowledge[10]==0)
{
sendstring("data acknowleged");
store();
}
else
{
sendstring("retry");
}}

store()
{
char store[15]={0xEF,0x01,0xFF,0xFF,0xFF,0xFF,0x01,0x00,0x06,0x06,0x01,0x00,0x01,0x00,0x0F};
char acknowledge[12];
int i,j;
for(i=0;i<14;i++)
{
send(store[i]);
}
for(j=0;j<11;j++)
{
acknowledge[j]=receive();
}
if(acknowledge[9]==0)
{
sendstring("yes");
}
else
{
sendstring("no");
}}


//lcd interfacing

show()
{
IO0DIR|=0X00003C00;
IO1DIR|=0X01C00000;
delay();
command(0x28);
delay1();
command(0x01);
delay1();
command(0x06);
delay1();
command(0x0E);
delay1();
command(0x80);
delay1();
data('t');
delay1();
}
 command(int a)
{
 int b=a;
 int c=a;

IO1CLR|=(1<<23);
IO1CLR|=(1<<24);
IO1SET|=(1<<22);
delay();
IO0CLR|=(0x3c00);
delay();
IO0SET|=(b<<6);
IO1CLR|=(1<<22);
delay1();
IO0CLR=(0x3c00);
delay();
IO1SET=(1<<22);
delay();
IO0SET=(c<<10);
IO1CLR=(1<<22);
delay1();
}
data(char z)
{
 char b=z;
 char c=z;

IO1CLR|=(1<<23);
IO1SET|=(1<<24);
IO1SET|=(1<<22);
delay();
IO0CLR|=(0x3c00);
delay();
IO0SET|=(b<<6);
IO1CLR|=(1<<22);
delay1();
IO0CLR=(0x3c00);
delay();
IO1SET=(1<<22);
delay();
IO0SET=(c<<10);
IO1CLR=(1<<22);
delay1();
}
	 
sendstring(char ch[])
{
int i=0;
while(ch[i]!='\0')	
{
data(ch[i]);
i++;
}}

//GSM

		