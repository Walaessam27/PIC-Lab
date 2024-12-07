typedef enum
{
	/* Application's state machine's initial state. */
	APP_STATE_INIT=0, 
    APP_STATE_SERVICE_TASKS,
    TX0_STATE,
    TX2_STATE,
    RX0_STATE,
    RX2_STATE,
	/* TODO: Define states used by the application state machine. */

} APP_STATES;


typedef struct
{
    /* The application's current state */
    APP_STATES state;
    char byte1;
    char byte2;
    char*buffer;
    char*buffer2;
    /* TODO: Define any additional data used by the application. */

} APP_DATA;

// --------------------------------------------------------------------------------------

APP_DATA appData;
void APP_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
    appData.state = APP_STATE_INIT;
    /* TODO: Initialize your application's state machine and other
     * parameters.
     */
}
int i, k, j, x;

/******************************************************************************
  Function:
    void APP_Tasks ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Tasks ( void )
{

    /* Check the application's current state. */
    switch ( appData.state )
    {
        /* Application's initial state. */
        case APP_STATE_INIT:
        {
            bool appInitialized = true;
            if (appInitialized){
                appData.state = APP_STATE_SERVICE_TASKS;
            }
            break;
        }
        case APP_STATE_SERVICE_TASKS:
        {
            if(!DRV_USART0_ReceiverBufferIsEmpty())
                appData.state=RX0_STATE;
            if(!DRV_USART1_ReceiverBufferIsEmpty())
                appData.state=RX2_STATE;
            break;
        }
        case RX0_STATE:
        {
            appData.byte1=DRV_USART0_ReadByte();
            if(appData.byte1=='\n' || appData.byte1=='\r' ){
                appData.buffer[i]='\0';
                i=0;
                appData.state= TX0_STATE;
            }
            else {
                appData.buffer[i++]=appData.byte1;
                appData.state=APP_STATE_SERVICE_TASKS;
            }
            break;
        }
        case TX0_STATE:
        {
            for(j=0;appData.buffer[j]!='\0';j++)
                DRV_USART1_WriteByte(appData.buffer[j]);
            //LEDs
            if(strcmp(appData.buffer,"led1")==0){
                LATG=0x1000;
                DRV_USART0_WriteByte('\n');
            }
            else if(strcmp(appData.buffer,"led2")==0){
                LATG=0x2000;
                DRV_USART0_WriteByte('\n');
            }
            else if(strcmp(appData.buffer,"led3")==0){ 
                LATG=0x4000;
                DRV_USART0_WriteByte('\n');
            }
            else if(strcmp(appData.buffer,"led4")==0){ 
                LATG=0x8000;
                DRV_USART0_WriteByte('\n');
            }
            else if(strcmp(appData.buffer,"led0")==0){ 
                LATG=0x0000;
                DRV_USART0_WriteByte('\n');
            }
            appData.state=APP_STATE_SERVICE_TASKS;
            break;
        }
        case RX2_STATE:
        {
            appData.byte2=DRV_USART1_ReadByte();
            if(appData.byte2=='\n' || appData.byte2=='\r' ){
                appData.buffer2[k]='\0';
                k=0;
                appData.state= TX2_STATE;
            }else {
                appData.buffer2[k++]=appData.byte2;
                appData.state=APP_STATE_SERVICE_TASKS;
            }
            break;
        }
        case TX2_STATE:
        {
            for(x=0;appData.buffer2[x]!='\0';x++)
                DRV_USART0_WriteByte(appData.buffer2[x]);
            //LEDs
            if(strcmp(appData.buffer2,"led1")==0){
                LATG=0x1000;
                DRV_USART1_WriteByte('\n');
            }
            else if(strcmp(appData.buffer2,"led2")==0){
                LATG=0x2000;
                DRV_USART1_WriteByte('\n');
            }
            else if(strcmp(appData.buffer2,"led3")==0){ 
                LATG=0x4000;
                DRV_USART1_WriteByte('\n');
            }
            else if(strcmp(appData.buffer2,"led4")==0){ 
                LATG=0x8000;
                DRV_USART1_WriteByte('\n');
            }
            else if(strcmp(appData.buffer2,"led0")==0){ 
                LATG=0x0000;
                DRV_USART1_WriteByte('\n');
            }
            appData.state=APP_STATE_SERVICE_TASKS;
            break;
        }
        default:
        {
            break;
        }
    }
}