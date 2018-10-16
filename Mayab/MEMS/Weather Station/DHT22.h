#ifndef DHT22
#define	DHT22

void start_signal();
void check_response();
char Read_Data();
unsigned short ReadByte();
void get_dht_values();
float dht_temperature();
float dht_humidity();

//void LCD_Port(char);
//void LCD_Cmd(char);
//void LCD_Clear();
//void LCD_SetCursor(char, char);
//void LCD_Init();
//void LCD_WriteChar(char);
//void LCD_WriteString(char *);
//void LCD_ShiftRight();
//void LCD_ShiftLeft();


#endif	/* DHT22 */