#include "mbed.h"
#include "LSM9DS1.h"
#include "uLCD_4DGL.h"
#include "Speaker.h"
#include "RPG.h"
#define PI 3.14159
// Earth's magnetic field varies by location. Add or subtract
// a declination to get a more accurate heading. Calculate
// your's here:
// http://www.ngdc.noaa.gov/geomag-web/#declination
#define DECLINATION -4.94 // Declination (degrees) in Atlanta,GA.

//Serial  pc(USBTX, USBRX);

uLCD_4DGL uLCD(p28,p27,p29); // serial tx, serial rx, reset pin;
Serial pc(USBTX, USBRX);
DigitalIn pbMID(p16);
InterruptIn pb_true(p17);
InterruptIn pb_false(p18);
DigitalOut myLED1(p20);
DigitalOut myLED2(p8);
DigitalOut myLED3(p7);
DigitalOut myLED4(p6);
DigitalOut myLED5(p25);
DigitalOut myLED6(p26);
DigitalOut myLED7(p30);
DigitalOut greenWire(p15);
DigitalOut redWire(p14);
DigitalIn yellowWire(p13);
DigitalIn orangeWire(p12);
InterruptIn pb3(p16); //LED Game
RPG rpg1(p24,p23,p22);
Timer T;
Speaker myspeaker(p21);

bool answer;
bool userAnswered = false;
int questionCount = 0;
int questionNum = rand() % 4 + 1;
int strikes = 0;
int dubs = 0;

int currentLED = 0;
int difficulty = 1;
float light_speed;
bool LED_run = false;

void pb3_hit_interrupt (void) {
    if(LED_run) {
        if(myLED4 == 1) {
            myspeaker.PlayNote(523.25,0.2,0.1);
            myspeaker.PlayNote(659.25,0.2,0.1);
            myspeaker.PlayNote(784,0.2,0.1);
            myspeaker.PlayNote(1046.5,0.2,0.1);
            dubs++;
            uLCD.cls();
            uLCD.printf("Dubs: %i,Strikes: %i\n", dubs, strikes); 
            uLCD.printf("Nice Job!");
            for(int i = 0; i < 6; i++) {
                myLED4 = !myLED4;
                wait(.5);
                }
        }else {
            switch(currentLED){
                case 1:
                    myspeaker.PlayNote(220,0.1,0.1);
                    myspeaker.PlayNote(207,0.1,0.1);
                    myspeaker.PlayNote(196,0.1,0.1);
                    myspeaker.PlayNote(185,0.1,0.1);
                    myspeaker.PlayNote(174,0.1,0.1);
                    myspeaker.PlayNote(164,0.1,0.1);
                    uLCD.cls();
                    uLCD.printf("You missed the \ncorrect LED!");
                    strikes++;
                    for(int i = 0; i <= 6; i++) {
                        myLED1 = !myLED1;
                        wait(.5);
                    }
                    break;
                case 2:
                    myspeaker.PlayNote(220,0.1,0.1);
                    myspeaker.PlayNote(207,0.1,0.1);
                    myspeaker.PlayNote(196,0.1,0.1);
                    myspeaker.PlayNote(185,0.1,0.1);
                    myspeaker.PlayNote(174,0.1,0.1);
                    myspeaker.PlayNote(164,0.1,0.1);
                    uLCD.cls();
                    uLCD.printf("You missed the \ncorrect LED!");
                    strikes++;
                    for(int i = 0; i <= 6; i++) {
                        myLED2 = !myLED2;
                        wait(.5);
                    }
                    break;
                case 3:
                    myspeaker.PlayNote(220,0.1,0.1);
                    myspeaker.PlayNote(207,0.1,0.1);
                    myspeaker.PlayNote(196,0.1,0.1);
                    myspeaker.PlayNote(185,0.1,0.1);
                    myspeaker.PlayNote(174,0.1,0.1);
                    myspeaker.PlayNote(164,0.1,0.1);
                    uLCD.cls();
                    uLCD.printf("You missed the \ncorrect LED!");
                    strikes++;
                    for(int i = 0; i <= 6; i++) {
                        myLED3 = !myLED3;
                        wait(.5);
                    }
                    break;
                case 5:
                    myspeaker.PlayNote(220,0.1,0.1);
                    myspeaker.PlayNote(207,0.1,0.1);
                    myspeaker.PlayNote(196,0.1,0.1);
                    myspeaker.PlayNote(185,0.1,0.1);
                    myspeaker.PlayNote(174,0.1,0.1);
                    myspeaker.PlayNote(164,0.1,0.1);
                    uLCD.cls();
                    strikes++;
                    uLCD.printf("You missed the \ncorrect LED!");
                    for(int i = 0; i <= 6; i++) {
                        myLED5 = !myLED5;
                        wait(.5);
                    }
                    break;
                case 6:
                    myspeaker.PlayNote(220,0.1,0.1);
                    myspeaker.PlayNote(207,0.1,0.1);
                    myspeaker.PlayNote(196,0.1,0.1);
                    myspeaker.PlayNote(185,0.1,0.1);
                    myspeaker.PlayNote(174,0.1,0.1);
                    myspeaker.PlayNote(164,0.1,0.1);
                    uLCD.cls();
                    strikes++;
                    uLCD.printf("You missed the \ncorrect LED!");
                    for(int i = 0; i <= 6; i++) {
                        myLED6 = !myLED5;
                        wait(.5);
                    }
                    break;
                case 7:
                    myspeaker.PlayNote(220,0.1,0.1);
                    myspeaker.PlayNote(207,0.1,0.1);
                    myspeaker.PlayNote(196,0.1,0.1);
                    myspeaker.PlayNote(185,0.1,0.1);
                    myspeaker.PlayNote(174,0.1,0.1);
                    myspeaker.PlayNote(164,0.1,0.1);
                    uLCD.cls();
                    strikes++;
                    uLCD.printf("You missed the \ncorrect LED!");
                    for(int i = 0; i <= 6; i++) {
                        myLED7 = !myLED7;
                        wait(.5);
                    }
                    break;
            }
        }    
    }
}   

void pb_true_hit_interrupt (void) {
    uLCD.cls();
    if(!userAnswered) {
        if(answer == true) {
            myspeaker.PlayNote(523.25,0.2,0.1);
            myspeaker.PlayNote(659.25,0.2,0.1);
            myspeaker.PlayNote(784,0.2,0.1);
            myspeaker.PlayNote(1046.5,0.2,0.1);
            uLCD.locate(0,1);
            uLCD.printf("Correct! \n\nThe next question will appear\nshortly");
            userAnswered = true;
            dubs += 1;
            wait(3);
            uLCD.cls();
        }else {
            myspeaker.PlayNote(220,0.1,0.1);
            myspeaker.PlayNote(207,0.1,0.1);
            myspeaker.PlayNote(196,0.1,0.1);
            myspeaker.PlayNote(185,0.1,0.1);
            myspeaker.PlayNote(174,0.1,0.1);
            myspeaker.PlayNote(164,0.1,0.1);
            uLCD.locate(0,1);
            uLCD.printf("That is incorrect. You now have an\nadditional strike\n\nThe next question will appear \nshortly");
            userAnswered = true;
            strikes += 1;
            wait(3);
            uLCD.cls();
        }
    }
    T.stop();
    T.reset();
} 
    
void pb_false_hit_interrupt (void) {
    uLCD.cls();
    if(!userAnswered) {
        if(answer == false) {
            myspeaker.PlayNote(523.25,0.2,0.1);
            myspeaker.PlayNote(659.25,0.2,0.1);
            myspeaker.PlayNote(784,0.2,0.1);
            myspeaker.PlayNote(1046.5,0.2,0.1);
            uLCD.locate(0,1);
            uLCD.printf("Correct! \n\nThe next question will appear\nshortly");
            userAnswered = true;
            dubs += 1;
            wait(3);
            uLCD.cls();
        }else {
            myspeaker.PlayNote(220,0.1,0.1);
            myspeaker.PlayNote(207,0.1,0.1);
            myspeaker.PlayNote(196,0.1,0.1);
            myspeaker.PlayNote(185,0.1,0.1);
            myspeaker.PlayNote(174,0.1,0.1);
            myspeaker.PlayNote(164,0.1,0.1);
            uLCD.locate(0,1);
            uLCD.printf("That is incorrect. You now have an additional strike\n\nThe next question will appear \nshortly");
            userAnswered = true;
            strikes += 1;
            wait(3);
            uLCD.cls();
        }
    }
    T.stop();
    T.reset();
}

//GLOBAL GAME VARIABLES
int TOTALGAMES = 5;
int bannedGame = 0;
int bannedGame2 = 0;
int gameSelect = 0;
int randGame = rand()%(TOTALGAMES) + 1;
bool gameOver = false;
bool gameWon = false;


//GLOBAL INDIVIDUAL GAME VARIABLES
int CIRCLERADIUS = 10;
int targetCircleX = 64;
int targetCircleY = 64;
int playerCircleX = rand()%(100) + 10;
int playerCircleY = rand()%(100) + 10;
int timeToMove = 0;

int main() {
    srand(time(0));
    uLCD.baudrate(3000000);
    pbMID.mode(PullUp);
    pb_true.mode(PullUp);
    pb_false.mode(PullUp);
    pb3.mode(PullUp);
    //trivia program loaded
    pb3.rise(&pb3_hit_interrupt);
    LED_run = true;
    pb_true.fall(&pb_true_hit_interrupt);
    pb_false.fall(&pb_false_hit_interrupt);
    
    uLCD.text_width(2); //2X size text
    uLCD.text_height(2);
    uLCD.cls();
    uLCD.printf("\n4180 FINAL PROJECT"); //Default Green on black text
    uLCD.printf("BOMB DEFUSAL GAME");
    uLCD.text_width(1); //1X size text
    uLCD.text_height(1);
    uLCD.printf("\nBy: George Kullen"); //Default Green on black text
    uLCD.printf("\nand Ray Murphy");
    uLCD.printf("\n\nPress Right \nButton to Begin...");
    
    myspeaker.PlayNote(349,0.3,0.1);
    myspeaker.PlayNote(349,0.1,0.1);
    myspeaker.PlayNote(349,0.1,0.1);
    myspeaker.PlayNote(349,0.1,0.1);
    myspeaker.PlayNote(392,0.3,0.1);
    myspeaker.PlayNote(392,0.3,0.1);
    myspeaker.PlayNote(440,0.4,0.1);
            
    while(pbMID > 0.5) {
        wait(0.2);   
    }
    uLCD.cls();
    uLCD.text_width(1); //2X size text
    uLCD.text_height(1);
    uLCD.printf("Complete 6 tasks \nto win! Fail two\nand you're out!");
    
    LSM9DS1 IMU(p9, p10, 0xD6, 0x3C);
    IMU.begin();
    
    wait(4);
    uLCD.cls();
    //Core GameLoop
    while(!gameOver) { //Verify Game is run (game over does not imply W or L)
        randGame = rand()%(TOTALGAMES) + 1;
        while(randGame == bannedGame || randGame == bannedGame2) {
            randGame = rand()%(TOTALGAMES) + 1;
        }
        if (dubs == 2 || dubs == 4){
            difficulty++;
        }
        switch(randGame) {
          case 1: // GAME 1: TRIVIA
            uLCD.cls();
            uLCD.printf("Dubs: %i,Strikes: %i\n", dubs, strikes); 
            wait(0.5);
            bannedGame = bannedGame2;
            bannedGame2 = 1;
            questionCount = 0;
            uLCD.text_width(2);
            uLCD.text_height(2);
            uLCD.printf("Trivia!\n");
            
            myspeaker.PlayNote(493,0.3,0.1);
            myspeaker.PlayNote(392,0.3,0.1);
            myspeaker.PlayNote(293,0.3,0.1);
            myspeaker.PlayNote(784,0.3,0.1);
            
            //uLCD.locate(0,1);
            uLCD.text_width(1);
            uLCD.text_height(1);
            uLCD.printf("\n\n\nLeft pb = True\n");
            uLCD.printf("-----------------\n");
            uLCD.printf("Right pb = False\n");
            wait(5);
            T.stop();
            T.reset();
            uLCD.cls();
            int timeToAnswer;
            
            if(difficulty == 1) {
                timeToAnswer = 15;
                }
            else if(difficulty == 2) {
                timeToAnswer = 12;
            }else if(difficulty == 3) {
                timeToAnswer = 10;
            }else {
                uLCD.printf("Difficulty level not present");
            }    
            while(1) {
                questionCount++;
                if (strikes >= 2) {
                    break;    
                }
                if(questionCount > 2 ) {
                    uLCD.cls();
                    uLCD.printf("You have completed\nTrivia!");
                    
                    myspeaker.PlayNote(493,0.3,0.1);
                    myspeaker.PlayNote(392,0.3,0.1);
                    myspeaker.PlayNote(293,0.3,0.1);
                    myspeaker.PlayNote(784,0.3,0.1);
                    
                    questionCount = 0;
                    T.stop();
                    T.reset();
                    wait(3);
                    break;
                    }
                switch(questionNum) {
                    case 1:
                        uLCD.locate(0,1);
                        uLCD.printf("Printed circuit \nboards first \nbegan being \ndeveloped in the \nearly 1900s (T/F?)\n");
                        userAnswered = false;
                        answer = true;
                        break;
                    case 2:
                        uLCD.locate(0,1);
                        uLCD.printf("The world's \nlargest wind \nturbine (222-meterdiamter rotor) \nis located in \nGermany (T/F?)\n");
                        userAnswered = false;
                        answer = false;
                        break;
                    case 3:
                        uLCD.locate(0,1);
                        uLCD.printf("A Petabyte is equivalent to 1024 Terabytes (T/F?)\n");
                        userAnswered = false;
                        answer = true;
                        break;
                    case 4:
                        uLCD.locate(0,1);
                        uLCD.printf("The first camera had an exposure time of a whopping 8 hours (T/F?)\n");
                        userAnswered = false;
                        answer = true;
                        break;
                    case 5:
                        uLCD.locate(0,1);
                        uLCD.printf("The lightning we see is charge flowing from the cloud to ground (T/F?)\n");
                        userAnswered = false;
                        answer = false;
                        break;
                    }
                questionNum++;
                if(questionNum == 6) {
                    questionNum = 1;
                    }
                
                T.start();
                for(int i = 0; i <= timeToAnswer; i++) {
                    wait(1);
                    if (userAnswered) {
                        break;
                    }
                    if(T.read() >= timeToAnswer) {
                        uLCD.printf("You did not answer the question in time");
                        strikes += 1;
                        wait(2);
                        T.stop();
                        T.reset();
                        uLCD.cls();
                        break;
                    }
                    
                }
            
            }
            wait(1);
            uLCD.cls();
            break;
          case 2: // GAME 2: BUTTON PRESS
            uLCD.cls();
            uLCD.printf("Dubs: %i,Strikes: %i\n", dubs, strikes); 
            uLCD.printf("Press the right button\nwhen the center\ngreen LED glows!");
            wait(1);
            uLCD.printf("\n3");
            wait(1);
            uLCD.printf("\n2");
            wait(1);
            uLCD.printf("\n1");
            wait(1);
            uLCD.printf("\nGO!");
            wait(0.5);
            bannedGame = bannedGame2;
            bannedGame2 = 2;
            wait(3);
            
            int currentStrikes = strikes;
            int currentDubs = dubs;
            switch(difficulty) {
                case 1:
                    light_speed = 0.3;
                    break;
                case 2:
                    light_speed = 0.2;
                    break;
                case 3:
                    light_speed = 0.1;
                    break;
            }
            
            while(1) {
                if (dubs > currentDubs || strikes > currentStrikes + 1 || strikes >= 2) {
                    myLED1 = 0;
                    myLED2 = 0; 
                    myLED3 = 0;
                    myLED4 = 0;
                    myLED5 = 0;
                    myLED6 = 0;
                    myLED7 = 0;
                    break;
                }
                for(currentLED = 1; currentLED <= 7; currentLED++) {
                    //Reset all LEDs 
                    myLED1 = 0;
                    myLED2 = 0; 
                    myLED3 = 0;
                    myLED4 = 0;
                    myLED5 = 0;
                    myLED6 = 0;
                    myLED7 = 0;
                    
                    //Light LEDs in sequence
                    switch(currentLED){
                        case 1:
                            myLED1 = 1;
                            break;
                        case 2:
                            myLED2 = 1;
                            break;
                        case 3:
                            myLED3 = 1;
                            break;
                        case 4:
                            myLED4 = 1;
                            break;
                        case 5:
                            myLED5 = 1;
                            break;
                        case 6:
                            myLED6 = 1;
                            break;
                        case 7:
                            myLED7 = 1;
                            break;
                            
                    }
                    wait(light_speed);
                }    
            }
            
            break;
          case 3: // GAME 3: BALL GAME
            if(difficulty == 1) {
                timeToMove = 10;
                }
            else if(difficulty == 2) {
                timeToMove = 7;
            }else if(difficulty == 3) {
                timeToMove = 5;
            }else {
                uLCD.printf("Difficulty level not present");
            } 
            uLCD.printf("Dubs: %i,Strikes: %i\n", dubs, strikes); 
            wait(0.5);
            uLCD.printf("\nTilt the white circle into the red circle in %i seconds", timeToMove);
            
            myspeaker.PlayNote(698,0.3,0.1);
            myspeaker.PlayNote(740,0.3,0.1);
            myspeaker.PlayNote(784,0.3,0.1);
            myspeaker.PlayNote(830.6,0.3,0.1);
            myspeaker.PlayNote(880,0.3,0.1);
            myspeaker.PlayNote(932.3,0.3,0.1);
            
            wait(1);
            uLCD.printf("\n3");
            wait(1);
            uLCD.printf("\n2");
            wait(1);
            uLCD.printf("\n1");
            wait(1);
            uLCD.printf("\nGO!");
            wait(0.5);
            // code block   
            bannedGame = bannedGame2;
            bannedGame2 = 3;
            playerCircleX = rand()%(100) + 10;
            playerCircleY = rand()%(100) + 10;
            uLCD.circle(targetCircleX, targetCircleY, CIRCLERADIUS, BLACK);
            T.stop();
            T.reset();
            T.start();
            while(1) {
                if (targetCircleX + 4 > playerCircleX && targetCircleX - 4 < playerCircleX
                    && targetCircleY + 4 > playerCircleY && targetCircleY - 4 < playerCircleY) {
                    dubs += 1;
                    uLCD.cls();
                    uLCD.printf("You have completed\nball game!");
                    
                    myspeaker.PlayNote(784,0.3,0.1);
                    myspeaker.PlayNote(987.8,0.3,0.1);
                    myspeaker.PlayNote(987.8,0.2,0.1);
                    myspeaker.PlayNote(1046.5,0.3,0.1);
                    
                    wait(3);
                    break;
                }
                if(T.read() >= timeToMove) {
                    uLCD.printf("You did not move the ball in time!");
                    myspeaker.PlayNote(220,0.1,0.1);
                    myspeaker.PlayNote(207,0.1,0.1);
                    myspeaker.PlayNote(196,0.1,0.1);
                    myspeaker.PlayNote(185,0.1,0.1);
                    myspeaker.PlayNote(174,0.1,0.1);
                    myspeaker.PlayNote(164,0.1,0.1);
                    strikes += 1;
                    
                    wait(3);
                    T.stop();
                    T.reset();
                    uLCD.cls();
                    break;
                }
                IMU.readAccel();
                IMU.readGyro();
                if (IMU.calcAccel(IMU.ax) > 0.2) {
                    playerCircleX -= 2;
                } else if (IMU.calcAccel(IMU.ax) < -0.2) {
                    playerCircleX += 2;
                }
                if (IMU.calcAccel(IMU.ay) > 0.2) {
                    playerCircleY -= 2;
                } else if (IMU.calcAccel(IMU.ay) < -0.2) {
                    playerCircleY += 2;
                }
                uLCD.cls();
                uLCD.circle(targetCircleX, targetCircleY, CIRCLERADIUS, RED);
                uLCD.circle(playerCircleX, playerCircleY, CIRCLERADIUS - 2, WHITE);
                wait(0.05);
            }
            wait(3);
            break;
          case 4: // GAME 4: WIRE GAME
            if(difficulty == 1) {
                timeToMove = 10;
                }
            else if(difficulty == 2) {
                timeToMove = 7;
            }else if(difficulty == 3) {
                timeToMove = 5;
            }else {
                uLCD.printf("Difficulty level not present");
            } 
            uLCD.printf("Dubs: %i,Strikes: %i\n", dubs, strikes); 
            wait(0.5);
            uLCD.printf("\nConnect specified wires in %i seconds", timeToMove);
            wait(1);
            uLCD.printf("\n3");
            wait(1);
            uLCD.printf("\n2");
            wait(1);
            uLCD.printf("\n1");
            wait(1);
            uLCD.printf("\nGO!");
            wait(0.5);
            // code block   
            bannedGame = bannedGame2;
            bannedGame2 = 4;
            T.stop();
            T.reset();
            T.start();
            uLCD.cls();
            switch (rand()%4 + 1) {
                case 1:
                    uLCD.printf("Touch the red\nwire to the yellow wire");
                    myspeaker.PlayNote(987.8,0.3,0.1);
                    myspeaker.PlayNote(932.3,0.3,0.1);
                    myspeaker.PlayNote(880,0.3,0.1);
                    myspeaker.PlayNote(784,0.3,0.1);
                    myspeaker.PlayNote(659.3,0.3,0.1);
                    redWire = 1;
                    greenWire = 0;
                    while(redWire != yellowWire) {
                        wait(0.05);
                        if(T.read() >= timeToMove) {
                        uLCD.printf("You did not connect the wire in time!");
                        strikes += 1;
                        wait(3);
                        T.stop();
                        T.reset();
                        uLCD.cls();
                        break;
                        }
                    }
                    if(redWire == yellowWire) {
                        dubs += 1;
                        uLCD.cls();
                        uLCD.printf("You have completed\nwire game!");
                        myspeaker.PlayNote(1318,0.3,0.1);
                        myspeaker.PlayNote(1661,0.3,0.1);
                        myspeaker.PlayNote(1975.5,0.3,0.1);
                        wait(3);
                        break;
                    }
                    break;
                case 2:
                    redWire = 1;
                    greenWire = 0;
                    uLCD.printf("Touch the red\nwire to the orange wire");
                    myspeaker.PlayNote(987.8,0.3,0.1);
                    myspeaker.PlayNote(932.3,0.3,0.1);
                    myspeaker.PlayNote(880,0.3,0.1);
                    myspeaker.PlayNote(784,0.3,0.1);
                    myspeaker.PlayNote(659.3,0.3,0.1);
                    while(redWire != orangeWire) {
                        wait(0.05);
                        if(T.read() >= timeToMove) {
                        uLCD.printf("You did not connect the wire in time!");
                        strikes += 1;
                        wait(3);
                        T.stop();
                        T.reset();
                        uLCD.cls();
                        break;
                        }
                    }
                    if(redWire == orangeWire) {
                        dubs += 1;
                        uLCD.cls();
                        uLCD.printf("You have completed\nwire game!");
                        myspeaker.PlayNote(1318,0.3,0.1);
                        myspeaker.PlayNote(1661,0.3,0.1);
                        myspeaker.PlayNote(1975.5,0.3,0.1);
                        wait(3);
                        break;
                    }
                    break;
                case 3:
                    redWire = 0;
                    greenWire = 1;
                    uLCD.printf("Touch the green\nwire to the orange wire");
                    myspeaker.PlayNote(987.8,0.3,0.1);
                    myspeaker.PlayNote(932.3,0.3,0.1);
                    myspeaker.PlayNote(880,0.3,0.1);
                    myspeaker.PlayNote(784,0.3,0.1);
                    myspeaker.PlayNote(659.3,0.3,0.1);
                    while(greenWire != orangeWire) {
                        wait(0.05);
                        if(T.read() >= timeToMove) {
                        uLCD.printf("You did not connect the wire in time!");
                        strikes += 1;
                        
                        wait(3);
                        T.stop();
                        T.reset();
                        uLCD.cls();
                        break;
                        }
                    }
                    if(greenWire == orangeWire) {
                        dubs += 1;
                        uLCD.cls();
                        uLCD.printf("You have completed\nwire game!");
                        myspeaker.PlayNote(1318,0.3,0.1);
                        myspeaker.PlayNote(1661,0.3,0.1);
                        myspeaker.PlayNote(1975.5,0.3,0.1);
                        wait(3);
                        uLCD.cls();
                        break;
                    }
                    break;
                case 4:
                    redWire = 0;
                    greenWire = 1;
                    uLCD.printf("Touch the green\nwire to the yellow wire");
                    myspeaker.PlayNote(987.8,0.3,0.1);
                    myspeaker.PlayNote(932.3,0.3,0.1);
                    myspeaker.PlayNote(880,0.3,0.1);
                    myspeaker.PlayNote(784,0.3,0.1);
                    myspeaker.PlayNote(659.3,0.3,0.1);
                    while(greenWire != yellowWire) {
                        wait(0.05);
                        if(T.read() >= timeToMove) {
                        uLCD.printf("You did not connect the wire in time!");
                        strikes += 1;
                        
                        wait(3);
                        T.stop();
                        T.reset();
                        uLCD.cls();
                        break;
                        }
                    }
                    if(greenWire == yellowWire) {
                        dubs += 1;
                        uLCD.cls();
                        uLCD.printf("You have completed\nwire game!");
                        myspeaker.PlayNote(1318,0.3,0.1);
                        myspeaker.PlayNote(1661,0.3,0.1);
                        myspeaker.PlayNote(1975.5,0.3,0.1);
                        wait(3);
                        break;
                    }
                    wait(3);
                    break;
                }      
            case 5: // GAME 5: RPG GAME
                int playerCircleRadius, targetCircleRadius;
                int targetChange, playerChange;
                
                if(difficulty == 1) {
                    timeToMove = 10;
                    }
                else if(difficulty == 2) {
                    timeToMove = 7;
                }else if(difficulty == 3) {
                    timeToMove = 5;
                }else {
                    uLCD.printf("Difficulty level not present");
                } 
                //uLCD.printf("Dubs: %i,Strikes: %i\n", dubs, strikes); 
                wait(0.5);
                uLCD.printf("\nUSE the RPG to match the circles in %i seconds", timeToMove);
                wait(1);
                uLCD.printf("\n3");
                wait(1);
                uLCD.printf("\n2");
                wait(1);
                uLCD.printf("\n1");
                wait(1);
                uLCD.printf("\nGO!");
                wait(0.5);
                // code block   
                bannedGame = bannedGame2;
                bannedGame2 = 5;
                playerCircleRadius = rand()%(50) + 30;
                targetCircleRadius = rand()%(15) + 5;
                targetChange = 0;
                playerChange = 0;
                T.stop();
                T.reset();
                T.start();
                while(1) {
                    if (targetCircleRadius + 8 > playerCircleRadius && targetCircleRadius - 8 < playerCircleRadius) {
                        dubs += 1;
                        uLCD.cls();
                        uLCD.printf("You have completed\ncircle game!");
                        myspeaker.PlayNote(523.25,0.2,0.1);
                        myspeaker.PlayNote(659.25,0.2,0.1);
                        myspeaker.PlayNote(784,0.2,0.1);
                        myspeaker.PlayNote(1046.5,0.2,0.1);
                        wait(3);
                        break;
                    }
                    if(T.read() >= timeToMove) {
                        strikes += 1;
                        uLCD.printf("You did not match the circles in time!");
                        myspeaker.PlayNote(220,0.1,0.1);
                        myspeaker.PlayNote(207,0.1,0.1);
                        myspeaker.PlayNote(196,0.1,0.1);
                        myspeaker.PlayNote(185,0.1,0.1);
                        myspeaker.PlayNote(174,0.1,0.1);
                        myspeaker.PlayNote(164,0.1,0.1);
                        
                        wait(3);
                        T.stop();
                        T.reset();
                        uLCD.cls();
                        break;
                    }
                    playerChange = 3 * rpg1.dir();
                    targetCircleRadius += targetChange;
                    playerCircleRadius += playerChange;
                    uLCD.cls();
                    uLCD.circle(64, 64, targetCircleRadius, WHITE);
                    uLCD.circle(64, 64, playerCircleRadius, RED);
                    wait(.02);
                }
                wait(3);
                break; // end case
        }
        if(dubs >= 6) {
            gameOver = true;
            gameWon = true;   
        } else if (strikes >= 2) {
            gameOver = true;   
        }
    }
    if (gameWon) { //Win Screen
        uLCD.cls();
        uLCD.printf("Dubs: %i,Strikes: %i", dubs, strikes); 
        uLCD.printf("\nYOU DEFUSED THE\nBOMB");
        myspeaker.PlayNote(523,0.2,0.1);
        myspeaker.PlayNote(659,0.2,0.1);
        myspeaker.PlayNote(784,0.2,0.1);
        myspeaker.PlayNote(1046,0.2,0.1);
        myspeaker.PlayNote(1318,0.2,0.1);
        myspeaker.PlayNote(1567,0.2,0.1);
        myspeaker.PlayNote(2093,0.2,0.1);
        myspeaker.PlayNote(523,0.2,0.1);
        myspeaker.PlayNote(659,0.2,0.1);
        myspeaker.PlayNote(784,0.2,0.1);
        myspeaker.PlayNote(1046,0.2,0.1);
        myspeaker.PlayNote(1318,0.2,0.1);
        myspeaker.PlayNote(1567,0.2,0.1);
        myspeaker.PlayNote(2093,0.2,0.1);
        
        for(int i = 1; i <= 20; i++) {
            if(i%2 == 1) {
                myLED1 = 1;
                myLED2 = 0;    
                myLED3 = 1;
                myLED4 = 0;
                myLED5 = 1;
                myLED6 = 0;
                myLED7 = 1;
            }else {
                myLED1 = 0;
                myLED2 = 1;  
                myLED3 = 0;
                myLED4 = 1;
                myLED5 = 0;
                myLED6 = 1;
                myLED7 = 0;
            } 
            wait(0.5);
        }
    } else { //Lose Screen
        uLCD.cls();
        uLCD.printf("Dubs: %i,Strikes: %i", dubs, strikes); 
        uLCD.printf("\nTHE BOMB BLEW UP!");
        myspeaker.PlayNote(1760,0.1,0.1);
        myspeaker.PlayNote(1567,0.1,0.1);
        myspeaker.PlayNote(1396,0.1,0.1);
        myspeaker.PlayNote(1318,0.1,0.1);
        myspeaker.PlayNote(1174,0.1,0.1);
        myspeaker.PlayNote(1046,0.1,0.1);
        myspeaker.PlayNote(987,0.1,0.1);
        myspeaker.PlayNote(880,0.1,0.1);
        myspeaker.PlayNote(783,0.1,0.1);
        myspeaker.PlayNote(698,0.1,0.1);
        myspeaker.PlayNote(659,0.1,0.1);
        myspeaker.PlayNote(587,0.1,0.1);
        myspeaker.PlayNote(523,0.1,0.1);
        myspeaker.PlayNote(493,0.1,0.1);
        myspeaker.PlayNote(440,0.1,0.1);
        myspeaker.PlayNote(392,0.1,0.1);
        myspeaker.PlayNote(349,0.1,0.1);
        myspeaker.PlayNote(329,0.1,0.1);
        myspeaker.PlayNote(110,0.3,0.1);
        
        for(int i = 1; i <= 20; i++) {
            if(i%2 == 1) {
                myLED1 = 0;
                myLED2 = 1;   
                myLED3 = 0;
                myLED4 = 0;
                myLED5 = 0;
                myLED6 = 1;
                myLED7 = 0;
            }else {
                myLED1 = 0;
                myLED2 = 0; 
                myLED3 = 0;
                myLED4 = 0;
                myLED5 = 0;
                myLED6 = 0;
                myLED7 = 0;
            } 
            wait(1);
        }
    }
    wait(10);
    myLED1 = 0;
    myLED2 = 0; 
    myLED3 = 0;
    myLED4 = 0;
    myLED5 = 0;
    myLED6 = 0;
    myLED7 = 0;
    uLCD.cls();
}