/*
 * File:   main.c
 * Author: Eslam Emara
 *
 * Created on April 15, 2024, 6:20 AM
 */


#include <xc.h>

#include "gpio.h"
#include "lcd.h"
#include "keypad.h"
#include "motor.h"
#include "button.h"
#include "led.h"
#include "buzzer.h"
#include "pir.h"

#include <string.h>             /*to use strcmp function*/

    
#define _XTAL_FREQ     4000000          /*Clock frequency*/
#define PASS_CODE   "1234"              /*Enter your pass code here*/

typedef enum{ACTIVATED,DEACTIVATED}Modes_t;         /*modes of operation*/

int sysButtonTimer = 0;     /*used to detect 3 seconds press on sys button*/
int activatedStateTimer = 0; /*used to count 5 seconds that shows activated on screen*/
int GateCloseTimer=20; /*used to count the 10 seconds to close the gate after detection*/
int emergencyTimer=0;   /*used to count 5 seconds to blink in emergency mode*/
int rstButtonTimer=0;
void __interrupt() Timer0_ISR(){        /*Timer 0 interrupt Fires every 1s*/
    if(TMR0IF){
        TMR0IF = 0;     /*reset the flag*/
        TMR0H = 0xF0;   /*set the starting values to overflow at 1s*/
        TMR0L = 0xBD;
        
        /*Increment the timers*/
        sysButtonTimer++;
        activatedStateTimer++;
        GateCloseTimer++;
        emergencyTimer++;
        rstButtonTimer++;
    }
}
/*Iinitalize the timer at 16bit timer with overflow interrupt fires every 1s*/
void Timer0_init(){
    T0CON = 0X87;/*16-bit timer with 256 prescalar*/
    TMR0H = 0xF0;
    TMR0L = 0xBD;
    TMR0IE = 1; /*enable interrupt*/
    GIE =1; /*enable global interrupts*/
}

void main(void) {
	uint8_t keypad_reading = 0;         /*holds the input from the keypad*/
    uint8_t inputCounter = 0;               /*holds the number of inputs enterd by the user*/
    uint8_t emergencyState = 0;             /*a flag to fire emergency state*/
    uint8_t buzzerSet = 0;                  /*a flag to fire buzzer*/
    uint8_t rstFirstPress = 0;                 /*flag to check if reset button is firstly pressed to set timer*/
    uint8_t sysFirstPress = 0;                 /*flag to check if reset button is firstly pressed to set timer*/

    char passCode[5] = {0};             /*char array to save the input from the user*/
    
    uint8_t passCodeReq = 0;            /*flag to check if its required to get input from user or not*/
    Modes_t mode = ACTIVATED;           /*startup mode*/
    
    ADCON1 = 0x07;                      /*setting PORTA as digital I/O*/
    Timer0_init();                      /*initializing Timer0*/
   
    /*Peripheral Initialization*/
    LCD_init();
    keypad_init(); 
    motor_init();
    button_init(RESET_BUTTON);
    button_init(SYSTEM_BUTTON);
    button_init(EMERGENCY_BUTTON);
    pir_init(PIR);
    buzzer_init(BUZZER);
    led_init(LED1);
    led_init(LED2);
    led_on(LED1);       /*System is working*/

    uint8_t last_reading = 0;           /*Saves last reading to avoid button multi inputs*/
    while(1){
        if(button_getState(SYSTEM_BUTTON)== HIGH){              /*if sys button is pressed*/
            if(sysFirstPress){
               sysButtonTimer = 0;                                 /*reset the button timer counter*/
               sysFirstPress = 0;                               /*not first time now*/
            }
            if(sysButtonTimer >=3){                         /*if 3 seconds has passed*/
                passCodeReq = 1;                            /*ask the user to enter pass*/
                passCode[0] = '\0';                         /*reset array of input*/
                inputCounter = 0;                           /*reset inpu counter*/
                LCD_clearScreen();                          /*clear the lcd*/
                sysFirstPress = 1;                          /*next time will be the first press to reset timer*/
            }/*if >3s*/
        }/*if(button_getState(SYSTEM_BUTTON)== HIGH)*/
        else{
            sysFirstPress = 1;                              /*not pressed? then next press will be first*/
        }
        
         if(button_getState(EMERGENCY_BUTTON)== HIGH){          /*If emergency button is pressed*/
             //LCD_clearScreen();                                 /*clear the screen*/
             emergencyState = 1;                                /*Set emergency flag to 1*/
             passCodeReq=0;                                     /*exit the pass code screen if its showing*/
         }
        
         if(button_getState(RESET_BUTTON)== HIGH){              /*if the reset button is pressed*/
             if(rstFirstPress){                                    /*check if its tje first time to enter here*/
                 rstButtonTimer =0;                             /*reset the reset timer (8s) to zero*/
                 rstFirstPress = 0;                                /*not first time now*/
             }
             if(rstButtonTimer>=8){                             /*if 8s has passed*/
                    passCodeReq = 1;                            /*ask user to enter pass*/
                    passCode[0] = '\0';                         /*reset variables and clear screen*/
                    inputCounter = 0;
                    LCD_clearScreen();
                    rstFirstPress =1;                              /*next time will be my first time*/
             }
            }
         else{
             rstFirstPress = 1;                                    /*the button is not pressed? then next press will be first*/
         }
         
        if(passCodeReq == 1){                                   /*if the user is asked to enter the pass code*/
            LCD_displayStringRowColumn(0,0,"Pass code: ");      /*Display that on the screen*/
            if(inputCounter<4){                                 /*if the user inputs 1/2/3/4 numbers*/
                keypad_reading=keypad_read();                   /*read that from the user*/
                if(keypad_reading == NO_KEY_PRESSED) last_reading = 0;      /*reset las_reading variable if the user not pressing*/
                 
                /*if user hit a button but not same as last button to take only 1 input*/
                /*to make it not take multiple times of same name so the user press 1 it shows 1 only 1 time not 111111*/
                if(keypad_reading != 255 && keypad_reading != NO_KEY_PRESSED && keypad_reading != last_reading){   
                    last_reading = keypad_reading;           /*save the input into this variable*/
                    LCD_goToRowColumn(1,inputCounter);      /*type the password on the second row*/
                    LCD_displayCharacter(keypad_reading);   /*display the inputs*/
                    passCode[inputCounter] = keypad_reading;/*save the input in the array*/
                    inputCounter++;                         /*update the counter*/
                }   /*if*/
            }/*if(inputCounter<4)*/
            else{       /*if the user entered the 4 inputs*/
                passCode[inputCounter] = '\0';              /*add termination to last element of array (4)*/
                if (strcmp(passCode,PASS_CODE)==0){         /*check if the input is equal the saved pass code*/
                    if(emergencyState){                     /*if we are in the emergency state then exit it*/
                        emergencyState =0;
                    }
                    else{ 
                        if (mode == ACTIVATED)                      /*else Toggle the modes */
                            mode = DEACTIVATED;
                        else{
                            mode = ACTIVATED;
                            activatedStateTimer = 0;                /*Show activated screen for 5s timer reset*/
                        }   /*else mode == activated*/
                    }
                }/*if passcode == PASS_CODE*/
                else{           /*error in pass*/
                    LCD_clearScreen();
                    LCD_displayStringRowColumn(0,0,"PASS ERR");         /*display PASS ERR for 1s*/
                    __delay_ms(1000);
                }
                /*resetting flags after inputs are all inputed*/
                passCodeReq=0;
                passCode[0] = '\0';
                inputCounter = 0;
                LCD_clearScreen();
            }/*else for input >4*/
        }/*if passCodeReq ==1*/
        
        /*Now we check which mode is active*/
        if(mode == ACTIVATED){          /*if we're in Activated mode*/
            if (emergencyState){        /*are we in emergency state??*/
                if(!passCodeReq)        /*Is pass code entry screen is on?*/
                     LCD_displayStringRowColumn(0,0,"99:GATE OPEN");    /*if not show emergency screen*/
                    if(emergencyTimer<=1)               /*turn on the buzzer for 2 seconds every 5 seconds*/
                        buzzer_on(BUZZER);
                    else
                        buzzer_off(BUZZER);
                if(emergencyTimer>=5){          /*reset the timer if > 5 so it repeats it self*/
                    DIO_TogglePin(LED2);        /*toggle the led every 5s*/
                    emergencyTimer=0;           /*reset the timer*/
                }
                motor_on();                     /*open the door*/
            }
            else
            {            /*if we are not in emergency state*/
                if(activatedStateTimer <=5 && !passCodeReq){  /*are we in the first 5s?? and are we not in code entry screen??*/
                    LCD_displayStringRowColumn(0,0,"Activated");        /*Activated screen showed*/
                }
                if(pir_getState(PIR)==HIGH){        /*checking if the pir sensor detects something*/
                    GateCloseTimer = 0;             /*reset the 10s timer*/
                    led_on(LED2);                   /*turn on led2*/
                    motor_on();                     /*open the door*/
                    if(activatedStateTimer>5 && !passCodeReq)       /*if 5 seconds has passed show GATE OPENED screen*/
                        LCD_displayStringRowColumn(0,0,"GATE OPENED");
                    buzzerSet = 1;                          /*set a flag to fire the buzzer once the door closes*/
                }
                else{
                    if(GateCloseTimer>=10){             /*if 10 seconds passed since the pir detects something*/
                        if(GateCloseTimer <12){         /*for 2 seconds*/
                            if(buzzerSet){              /*if we're asked to fire the buzzer*/
                                buzzer_on(BUZZER);      /*fire*/
                            }
                        }
                        else{                           /*after that*/
                            buzzer_off(BUZZER);         /*turn it off*/
                            buzzerSet = 0;              /*reset that flag so that it doesn't fire up again*/
                            GateCloseTimer = 20;        /*set the timer 20 until it resets when detection occurs so that it soesn't overflow*/
                        }
                        led_off(LED2);                  /*We're closing then turn the led off*/
                        motor_off();                    /*and close actually*/
                        if(activatedStateTimer>5 && !passCodeReq)       /*if we're not in the first 5s then show this msg*/
                            LCD_displayStringRowColumn(0,0,"GATE CLOSED");
                    }/*if(GateCloseTimer>=10)*/
                }/*if PIR is low*/

            }/*we're not in emergency*/
        }
        
        else if(mode == DEACTIVATED){       /*if the mode is deactivated*/
            if(emergencyState && !passCodeReq){         /*if we're in emergency and no pass is required*/
                LCD_displayStringRowColumn(0,0,"NO ER: DEACTIVE");      /*you have no emergency*/
            }
            else        /*we're not in emergency*/
            {
                if(!passCodeReq)    /*if no pass is req*/
                    LCD_displayStringRowColumn(0,0,"Deactivated");      /*show this*/
            }
            led_on(LED2);       /*turn on the poor led*/
            motor_off();        /*open the door for anyone to enter*/
        }   /*mode == DEACTIVATED*/
    }/*while(1) :)*/
  return;
}/*main*/
