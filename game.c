#include "game.h"

#include <stdio.h>
#include <stdlib.h>

#include "gba.h"
#include "images/starz.h"
#include "images/brickwallsad.h"
#include "images/brick.h"



typedef enum {
  START,
  PLAY,
  WIN,
} GBAState;

int main(void) {
  

  // Manipulate REG_DISPCNT here to set Mode 3 //
  REG_DISPCNT = MODE3 | BG2_ENABLE;
  // Save current and previous state of button input
  u32 previousButtons = BUTTONS;
  u32 currentButtons = BUTTONS;

  // Load initial game state

  GBAState state = START;

  SELECT:

  cs.ball.row = 80;
  cs.ball.col = 120;
  cs.ball.rd = 1;
  cs.ball.cd = 1;
  cs.ball.color = RED;
  cs.ball.size = 5;

  cs.blocker.row = 155;
  cs.blocker.col = 120;
  cs.blocker.rd = 1;
  cs.blocker.cd = 3;
  cs.blocker.color = BLUE;
  cs.blocker.height = 3;
  cs.blocker.length = 25;


  for (int i = 0; i < NUM_BRICKS; i++) {
    cs.brick[i].height = 7;
    cs.brick[i].length = 10;
    cs.brick[i].color = YELLOW;
  }

  cs.brick[0].row = 30;
  cs.brick[0].col = 30;
  cs.brick[1].row = 30;
  cs.brick[1].col = 60;
  cs.brick[2].row = 30;
  cs.brick[2].col = 90;
  cs.brick[3].row = 30;
  cs.brick[3].col = 120;
  cs.brick[4].row = 30;
  cs.brick[4].col = 150;
  cs.brick[5].row = 30;
  cs.brick[5].col = 180;
  cs.brick[6].row = 30;
  cs.brick[6].col = 210;

  cs.brick[7].row = 60;
  cs.brick[7].col = 15;
  cs.brick[8].row = 60;
  cs.brick[8].col = 45;
  cs.brick[9].row = 60;
  cs.brick[9].col = 75;
  cs.brick[10].row = 60;
  cs.brick[10].col = 105;
  cs.brick[11].row = 60;
  cs.brick[11].col = 135;
  cs.brick[12].row = 60;
  cs.brick[12].col = 165;
  cs.brick[13].row = 60;
  cs.brick[13].col = 195;
  cs.brick[14].row = 60;
  cs.brick[14].col = 225;
  
  int totalBricks = NUM_BRICKS;
  int r = 0;
  int c = 0;
  fillScreenDMA(BLACK);

  while (1) {
    currentButtons = BUTTONS;  // Load the current state of the buttons


    switch (state) {
      case START:

        while((KEY_DOWN(BUTTON_START, BUTTONS)) || (KEY_DOWN(BUTTON_START, BUTTONS)));
        drawFullScreenImageDMA(brick);
        drawString(30, 40, "Welcome to GBA Brick Breaker!", GREEN);
        drawString(50, 55, "Press Start to Begin", GREEN);
        drawString(70, 5, "Use left and right arrows to move the", GREEN);
        drawString(90, 5, "                blocker", GREEN);
        
        
        while(!(KEY_DOWN(BUTTON_START, BUTTONS)) || !(KEY_DOWN(BUTTON_START, BUTTONS)));
        if(KEY_DOWN(BUTTON_SELECT, BUTTONS)) {
          state = START;
          goto SELECT;
        }
        state = PLAY;
        goto SELECT;
        break;
      case PLAY:
        r = 0;
        c = 0;
        ps = cs;

        if(KEY_DOWN(BUTTON_RIGHT, BUTTONS)) {
          cs.blocker.col += cs.blocker.cd;
          if(cs.blocker.col > 239-cs.blocker.length+1) {
            cs.blocker.col = 239-cs.blocker.length+1;
          }
        }
        if(KEY_DOWN(BUTTON_LEFT, BUTTONS)) {
          cs.blocker.col -= cs.blocker.cd;
          if(cs.blocker.col < 0) {
            cs.blocker.col = 0;
          }
        }

        //Graphics for Ball
        cs.ball.row += cs.ball.rd;
        cs.ball.col += cs.ball.cd;
        if(cs.ball.col < 0) {
          cs.ball.col = 0;
          cs.ball.cd = -cs.ball.cd;
        }
        if(cs.ball.col > 239-cs.ball.size+1) {
          cs.ball.col = 239-cs.ball.size+1;
          cs.ball.cd = -cs.ball.cd;
        }
        if(cs.ball.row < 0) {
          cs.ball.row = 0;
          cs.ball.rd = -cs.ball.rd;
        }
        if(cs.ball.row > 159-cs.ball.size+1) {
          cs.ball.row = 80;
          cs.ball.col = 120;
        }

    

        //if ball hits blocker
        if (getPixel(cs.ball.row + 2, cs.ball.col, BLUE) == 1) {
          cs.ball.rd = -cs.ball.rd;
        }

        //if ball hits brick
        if (getPixel(cs.ball.row, cs.ball.col, YELLOW) == 1) {
          cs.ball.rd = -cs.ball.rd;
          totalBricks--;
          r = cs.ball.row;
          c = cs.ball.col;
        } else if (getPixel(cs.ball.row, cs.ball.col, YELLOW) == 1) {
          cs.ball.cd = -cs.ball.cd;
          totalBricks--;
          c = cs.ball.col;
          r = cs.ball.row;
        }
      
        if ((r <= 37 && r >= 30) && (c >= 30 && c <= 40)) {
          cs.brick[0].color = BLACK;
        } else if ((r <= 37 && r >= 30) && (c >= 60 && c <= 70)) {
          cs.brick[1].color = BLACK;
        } else if ((r <= 37 && r >= 30) && (c >= 90 && c <= 100)) {
          cs.brick[2].color = BLACK;
        } else if ((r <= 37 && r >= 30) && (c >= 120 && c <= 130)) {
          cs.brick[3].color = BLACK;
        } else if ((r <= 37 && r >= 30) && (c >= 150 && c <= 160)) {
          cs.brick[4].color = BLACK;
        } else if ((r <= 37 && r >= 30) && (c >= 180 && c <= 190)) {
          cs.brick[5].color = BLACK;
        } else if ((r <= 37 && r >= 30) && (c >= 210 && c <= 220)) {
          cs.brick[6].color = BLACK;
        } else if ((r <= 67 && r >= 60) && (c >= 15 && c <= 25)) {
          cs.brick[7].color = BLACK;
        } else if ((r <= 67 && r >= 60) && (c >= 45 && c <= 55)) {
        cs.brick[8].color = BLACK;
        } else if ((r <= 67 && r >= 60) && (c >= 75 && c <= 85)) {
          cs.brick[9].color = BLACK;
        } else if ((r <= 67 && r >= 60) && (c >= 105 && c <= 115)) {
          cs.brick[10].color = BLACK;
        } else if ((r <= 67 && r >= 60) && (c >= 135 && c <= 145)) {
          cs.brick[11].color = BLACK;
        } else if ((r <= 67 && r >= 60) && (c >= 165 && c <= 175)) {
          cs.brick[12].color = BLACK;
        } else if ((r <= 67 && r >= 60) && (c >= 195 && c <= 205)) {
          cs.brick[13].color = BLACK;
        } else if ((r <= 67 && r >= 60) && (c >= 225 && c <= 235)) {
          cs.brick[14].color = BLACK;
        }
    
    
        if(KEY_DOWN(BUTTON_SELECT, BUTTONS)) {
          while (KEY_DOWN(BUTTON_SELECT, BUTTONS));
          state = START;
          goto SELECT;
        }
        waitForVBlank();

        do {
          drawImageDMA(80, 80, 80, 80, starz);
        } while (0);
        

        //draw ball
        drawRectDMA(ps.ball.row, ps.ball.col, ps.ball.size, ps.ball.size, BLACK);
        drawRectDMA(cs.ball.row, cs.ball.col, cs.ball.size, cs.ball.size, cs.ball.color);


        //draw blocker
        drawRectDMA(ps.blocker.row, ps.blocker.col, ps.blocker.height, ps.blocker.length, BLACK);
        drawRectDMA(cs.blocker.row, cs.blocker.col, cs.blocker.height, cs.blocker.length, cs.blocker.color);



        //draw bricks
        for (int i = 0; i < NUM_BRICKS; i++) {
          drawRectDMA(ps.brick[i].row, ps.brick[i].col, ps.brick[i].height, ps.brick[i].length, BLACK);
          drawRectDMA(cs.brick[i].row, cs.brick[i].col, cs.brick[i].height, cs.brick[i].length, cs.brick[i].color);
        }

        char left[50];

        
        drawString(15, 75, "Bricks Left:", WHITE);
        sprintf(left, "%d", (totalBricks + 1)); 
        drawString(15, 150, left, BLACK);
        sprintf(left, "%d", totalBricks);
        drawString(15, 150, left, WHITE);

        if(totalBricks <= 0) {
          state = WIN;
        }
        break;
      case WIN:
        drawFullScreenImageDMA(brickwallsad);
        drawString(15, 65, "Congrats! You Win!", GREEN);
        drawString(65, 12, "Press Start or Select to play again.", GREEN);
        while(!(KEY_DOWN(BUTTON_START, BUTTONS)) || !(KEY_DOWN(BUTTON_SELECT, BUTTONS)));
        if((KEY_DOWN(BUTTON_START, BUTTONS)) || (KEY_DOWN(BUTTON_SELECT, BUTTONS))) {
          state = START;
          goto SELECT;
        }
        break;
    }

    previousButtons = currentButtons;  // Store the current state of the buttons
  }


  return 0;
}
