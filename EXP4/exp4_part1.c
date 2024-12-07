app.h

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
    /* TODO: Define any additional data used by the application. */

} APP_DATA;

// -----------------------------------------------------------------------
app.c

void APP_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
    appData.state = APP_STATE_INIT;
    /* TODO: Initialize your application's state machine and other
     * parameters.
     */
}
APP_DATA appData;
bool appInitialized = true;

/******************************************************************************
  Function:
    void APP_Tasks ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Tasks ( void )
{

    /* Check the application's current state. */
    switch ( appData.state ) {
        /* Application's initial state. */
        case APP_STATE_INIT:
        {
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
            appData.state=TX0_STATE;
            break;
        }
        case TX0_STATE:
        {
            DRV_USART1_WriteByte(appData.byte1);
            appData.state=APP_STATE_SERVICE_TASKS;
            break;
        }
        case RX2_STATE:
        {
            appData.byte2=DRV_USART1_ReadByte();
            appData.state=TX2_STATE;
            break;
        }
        case TX2_STATE:
        {
            DRV_USART0_WriteByte(appData.byte2);
            appData.state=APP_STATE_SERVICE_TASKS;
            break;
        }
        default:
        {
            break;
        }
    }
}