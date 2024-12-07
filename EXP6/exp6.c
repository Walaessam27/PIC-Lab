typedef enum
{
	/* Application's state machine's initial state. */
	APP_STATE_INIT=0, 
    APP_STATE_SERVICE_TASKS,
	/* TODO: Define states used by the application state machine. */

} APP_STATES;


typedef struct
{
    /* The application's current state */
    APP_STATES state;
    /* TODO: Define any additional data used by the application. */

} APP_DATA;

// -----------------------------------------------------------------

APP_DATA appData;
void APP_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
    appData.state = APP_STATE_INIT;
    /* TODO: Initialize your application's state machine and other
     * parameters.
     */
}
int i;

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
    // COL1
    LATB = 0xFB;
    for (i = 0; i < 1000000; i++);
    if (PORTBbits.RB7 == 0) {
        DRV_USART0_WriteByte('D');
        LATG = 0xD000;
    } else if (PORTBbits.RB8 == 0) {
        DRV_USART0_WriteByte('C');
        LATG = 0xC000;
    } else if (PORTBbits.RB9 == 0) {
        DRV_USART0_WriteByte('B');
        LATG = 0xB000;
    } else if (PORTBbits.RB10 == 0) {
        DRV_USART0_WriteByte('A');
        LATG = 0xA000;
    }

    // COL2
    LATB = 0xF7;
    for (i = 0; i < 1000000; i++);
    if (PORTBbits.RB7 == 0) {
        DRV_USART0_WriteByte('E');
        LATG = 0xE000;
    } else if (PORTBbits.RB8 == 0) {
        DRV_USART0_WriteByte('9');
        LATG = 0x9000;
    } else if (PORTBbits.RB9 == 0) {
        DRV_USART0_WriteByte('6');
        LATG = 0x6000;
    } else if (PORTBbits.RB10 == 0) {
        DRV_USART0_WriteByte('3');
        LATG = 0x3000;
    }

    // COL3
    LATB = 0xEF;
    for (i = 0; i < 1000000; i++);
    if (PORTBbits.RB7 == 0) {
        DRV_USART0_WriteByte('F');
        LATG = 0xF000;
    } else if (PORTBbits.RB8 == 0) {
        DRV_USART0_WriteByte('8');
        LATG = 0x8008;
    } else if (PORTBbits.RB9 == 0) {
        DRV_USART0_WriteByte('5');
        LATG = 0x5000;
    } else if (PORTBbits.RB10 == 0) {
        DRV_USART0_WriteByte('2');
        LATG = 0x2000;
    }

    // COL4
    LATB = 0xFFBF;
     for (i = 0; i < 1000000; i++);
    if (PORTBbits.RB7 == 0) {
        DRV_USART0_WriteByte('0');
        LATG = 0x0000;
    } else if (PORTBbits.RB8 == 0) {
        DRV_USART0_WriteByte('7');
        LATG = 0x7000;
    } else if (PORTBbits.RB9 == 0) {
        DRV_USART0_WriteByte('4');
        LATG = 0x4000;
    } else if (PORTBbits.RB10 == 0) {
        DRV_USART0_WriteByte('1');
        LATG = 0x1000;
    }

    for (i = 0; i < 1000000; i++);
    appData.state = APP_STATE_SERVICE_TASKS;
    break;
}
    }
}