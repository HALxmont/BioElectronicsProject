#include "stm32f1xx.h"
#include "stm32f1xx_hal.h"
#include "UI.h"
#include "defs.h"
#include "HardwareInit.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>



char UI_Buffer[UI_Buff_Size];

UI_SetParams_t UI; 
HATypeDefAlarms  HA_Alarms;
extern UART_HandleTypeDef huart3;
extern UART_HandleTypeDef huart1;

uint8_t UTC_Day;
uint8_t UTC_Mon;
uint8_t UTC_Year;
uint8_t UTC_Hour;
uint8_t UTC_Min;
uint8_t UTC_Sec;

uint8_t v1 = 11;
uint8_t v2 = 5;


//#####################################################################################
//##### UI RX PROCESSS 																  #
//#####################################################################################

void UI_SetParams()
{

const char delim[2] = ",";
char *token = NULL;
uint8_t tokenIndex = 0;
char t1[20];

int8_t tagetRxBuff[UIBuffLength];

//####################
//##### ?INFO CASE ###
//####################

memset(tagetRxBuff, 0, UIBuffLength); 
Delimiter(tagetRxBuff, UI_Buffer, "?INFO");

	if(  (UI.rxIndex>0))
	{
    	if(!strncmp(tagetRxBuff, "?INFO", 4)){  //DATA REQUEST

		UI_SendINFO(); //send info 
		UI.rxIndex=0;		//reset index
		
		} // endif "?LVV"	
	memset(tagetRxBuff, 0, UIBuffLength);  
   	}  //endif



//####################
//##### !RTC CASE ####
//####################
//!RTC_uart,13,07,2022,22,43,39,*
//dd,MM,yyyy,HH,mm,ss
memset(tagetRxBuff, 0, UIBuffLength); 
Delimiter(tagetRxBuff, UI_Buffer, "!RTC_uart");

	if(  (UI.rxIndex>0))
	{
    	if(!strncmp(tagetRxBuff, "!RTC_uart", 9)){
        	/* get the first token */
        	token = strtok(tagetRxBuff, delim);      
    		/* walk through other tokens */
    		while( token != NULL ) {

				token = strtok(NULL, delim);
        		tokenIndex++;

        		switch(tokenIndex){

            		case 1: 	
							t1[0] = token[0];
                    		t1[1] = token[1];
							t1[2] = '\0';
							UTC_Day = atoi(t1);
					break;

	            	case 2: 
							t1[0] = token[0];
							t1[1] = token[1];
							t1[2] = '\0';
							UTC_Mon = atoi(t1);
            		break;	
	    
					case 3: 
							t1[0] = token[2];
                    		t1[1] = token[3];
                    		t1[2] = '\0';
                    		UTC_Year = atoi(t1);
					break;

					case 4: 
							t1[0] = token[0];
                    		t1[1] = token[1];
                    		t1[2] = '\0';
                    		UTC_Hour = atoi(t1);
					case 5: 
							t1[0] = token[0];
                    		t1[1] = token[1];
                    		t1[2] = '\0';
                    		UTC_Min = atoi(t1);
					case 6: 
							t1[0] = token[0];
                    		t1[1] = token[1];
                    		t1[2] = '\0';
                    		UTC_Sec = atoi(t1);
					break;
   	     		} //endcase
			} //endwhile
		UI.rxIndex=0;		//reset index
		} // endif "!RTI"	
	memset(tagetRxBuff, 0, UIBuffLength);  

   	}  //endif


}//end function UI



void UI_SendINFO(void){
myprintf("UI INFO: %d/%d/%d %d:%d:%d, %d, %d \r\n", UTC_Day, UTC_Mon, UTC_Year, UTC_Hour, UTC_Min, UTC_Sec, v1, v2);

}






