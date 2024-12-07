typedef enum
{
APP_STATE_INIT=0,
APP_STATE_SERVICE_TASKS,
APP_STATE_RECEIVE,
APP_STATE_ECHO,
RX_State,
TX_State,
} APP_STATES;

typedef struct
{
APP_STATES state;
char input;
char * rx_byte
} APP_DATA;

case APP_STATE_INIT: {
bool appInitialized = true;
if (appInitialized) appData.state = APP_STATE_RECEIVE;
break;
}
case APP_STATE_RECEIVE:{
if (!DRV_USART0_ReceiverBufferIsEmpty()){
appData.inputt = DRV_USART0_ReadByte();
appData.state = APP_STATE_ECHO;
}
break;
}

case APP_STATE_ECHO:
{
DRV_USART0_WriteByte((appData.inputt +1));
appData.state = APP_STATE_RECEIVE;
break;
}
The next part we write two states one for receive and another for sending:
case APP_STATE_SERVICE_TASKS:
{
if (!DRV_USART0_ReceiverBufferIsEmpty()) appData.state=RX_State;
break;
}
case RX_State:
{
appData.rx_byte=DRV_USART0_ReadByte();
if (appData.rx_byte=='\n'|| appData.rx_byte=='\r'){
appData.buffer[i++] = '\0';
if(strcmp(appData.buffer,"led1") ==0){
LATG = 0x1000;
DRV_USART0_WriteByte('\n');
}
else if(strcmp(appData.buffer,"led2")==0){
LATG = 0x2000;
DRV_USART0_WriteByte('\n');
}
else if(strcmp(appData.buffer,"led3")==0){
LATG = 0x4000;
DRV_USART0_WriteByte('\n');
}
else if (strcmp(appData.buffer,"leds are off")==0){
LATG = 0X0000;
}
else if(strcmp(appData.buffer,"led4")==0){
LATG = 0x8000;
DRV_USART0_WriteByte('\n');
}
i=0;
appData.state = APP_STATE_SERVICE_TASKS;
}
appData.buffer[i++] = appData.rx_byte;
appData.state=TX_State;
break;
}
case TX_State:
{
DRV_USART0_WriteByte(appData.rx_byte);
appData.state = APP_STATE_SERVICE_TASKS;
}