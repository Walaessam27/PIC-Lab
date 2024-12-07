typedef enum {
APP_STATE_INIT=0,
APP_STATE_SERVICE_TASKS,
APP_STATE_COUNTER,
} APP_STATES;


typedef struct {
APP_STATES state;
int counter;
} APP_DATA;




case APP_STATE_INIT:
{
bool appInitialized = true;
myCounter=0;
bool btn1 = PLIB_PORTS_PinGet(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_6 );
if (appInitialized) {
if(btn1) appData.state = APP_STATE_COUNTER;
}
break;
}
case APP_STATE_COUNTER:
{
PORTG= appData.counter <<12;
int i;
for (i=0; i<50000000; i++);
appData.counter++;
break;
}
default:
{
break;
}






case APP_STATE_SERVICE_TASKS:
{
bool btn1 = PLIB_PORTS_PinGet(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_6 );
bool btn2 = PLIB_PORTS_PinGet(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_7 );
if (btn1 && btn2) {
LATG = 0x8000;
} else if (btn2) {
LATG = 0x4000;
} else if (btn1) {
LATG = 0x2000;
} else {
LATG = 0x1000;
}
break;
}


