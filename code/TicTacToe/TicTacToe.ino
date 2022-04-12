#include <FastLED.h>

#define NUM_LEDS 9
#define DATA_PIN 6
#define CHIPSET NEOPIXEL
#define BUTTON1 A0
#define BUTTON2 A1
#define BUTTON3 A2
#define BUTTON4 A3
#define BUTTON5 A4
#define BUTTON6 A5
#define BUTTON7 10
#define BUTTON8 9
#define BUTTON9 8
#define BUTTON_RESET 7
#define LED1 -1
#define LED2 -1
#define LED3 -1
#define LED4 -1
#define LED5 -1
#define LED6 -1
#define LED7 -1
#define LED8 -1
#define LED9 -1
#define RED CRGB::Red
#define BLUE CRGB::Blue
#define BLACK CRGB(0x000000)
#define BRIGHTNESS 50

bool newGame = true;
unsigned int userInput = -1;
bool player1sTurn = false;
CRGB leds[NUM_LEDS];
int buttons[] = {BUTTON1, BUTTON2, BUTTON3,
                 BUTTON4, BUTTON5, BUTTON6,
                 BUTTON7, BUTTON8, BUTTON9,
                 BUTTON_RESET};
int buttonStates[] = {0,0,0,
                      0,0,0,
                      0,0,0,0};
int theLEDs[] = {LED1, LED2, LED3,
                 LED4, LED5, LED6,
                 LED7, LED8, LED9};
int numButtons = 10;
int numLEDs = 9;
int winningLEDs[] = {-1,-1,-1};

void setup() {
  // put your setup code here, to run once:
  pinMode(BUTTON1, INPUT_PULLUP);
  pinMode(BUTTON2, INPUT_PULLUP);
  pinMode(BUTTON3, INPUT_PULLUP);
  pinMode(BUTTON4, INPUT_PULLUP);
  pinMode(BUTTON5, INPUT_PULLUP);
  pinMode(BUTTON6, INPUT_PULLUP);
  pinMode(BUTTON7, INPUT_PULLUP);
  pinMode(BUTTON8, INPUT_PULLUP);
  pinMode(BUTTON9, INPUT_PULLUP);
  pinMode(BUTTON_RESET, INPUT_PULLUP);
  Serial.begin(9600);
  FastLED.addLeds<CHIPSET, DATA_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  startUp();
}

void startUp() {
  for(int i = 0; i < NUM_LEDS; i++) {
    if(i != 0) {
      leds[i-1] = BLACK;
    }
    leds[i] = CRGB::Purple;
    FastLED.show();
    delay(100);
  }
  leds[NUM_LEDS - 1] = BLACK;
  FastLED.show();
}

void loop() {
  // put your main code here, to run repeatedly:
  if(newGame) {
    playGame();
  }
}

void playGame() {
  int roundResult = -1;
  int stateOfGame = 0;
  int numRounds = 0;
  bool reachedLastRound = false;
  while(!stateOfGame) {
    if(!reachedLastRound) {
      roundResult = playRound();
    }
    
    if(roundResult == -2) {
      newGame = true;
      break;
    }
    stateOfGame = checkStateOfGame(roundResult, reachedLastRound);
    reachedLastRound = ((numRounds>=8)?true:false);
    numRounds++;
  }
  switch(stateOfGame) {
    case 0:
      finishGame(false);
      break;
    case 1:
      finishGame(true);
      break;
    case 2:
      tieGame();
  }
}

int checkStateOfGame(int playerMove, bool thereIsTie) {
  // Check tie first
  if(thereIsTie) {
    return 2;
  }
  // If playerMove in {1,3,5,7,9} (odd), check diagonal
  // Always check column/row
  int playerNum = buttonStates[playerMove];
  if((playerMove)%2==0) { // checking for evens because playerMove is index
    return (checkDiagonalWin(playerMove,playerNum) || checkRow(playerMove,playerNum) || checkColumn(playerMove,playerNum));
  }
  
  return (checkRow(playerMove,playerNum) || checkColumn(playerMove,playerNum));
}

bool checkDiagonalWin(int playerMove,int playerNum) {
  if(playerMove == 1 || playerMove == 9) {
    return checkRDiag(playerMove, playerNum);
  }
  else if(playerMove == 3 || playerMove == 7) {
    return checkLDiag(playerMove, playerNum);
  }
  else {
    return (checkRDiag(playerMove, playerNum) || checkLDiag(playerMove, playerNum));
  }
}

bool checkRDiag(int playerMove, int playerNum) {
  int ledOne = buttonStates[0];
  winningLEDs[0] = 0;
  winningLEDs[1] = 4;
  winningLEDs[2] = 8;
  return ((ledOne==playerNum)&&(ledOne==buttonStates[4])&&(ledOne==buttonStates[8]));
}

bool checkLDiag(int playerMove, int playerNum) {
  int ledThree = buttonStates[2];
  winningLEDs[0] = 2;
  winningLEDs[1] = 4;
  winningLEDs[2] = 6;
  return ((ledThree==playerNum)&&(ledThree==buttonStates[4])&&(ledThree==buttonStates[6]));
}

bool checkRow(int playerMove, int playerNum) {
  int row = playerMove / 3;
  for(int i = (row*3);i<(row*3+3);i++) {
    if(buttonStates[i] != playerNum) {
      return false;
    }
  }
  winningLEDs[0] = row*3;
  winningLEDs[1] = row*3+1;
  winningLEDs[2] = row*3+2;
  return true;
}

bool checkColumn(int playerMove, int playerNum) {
  int col = playerMove % 3;
  for(int i = col; i<9; i+=3) {
    if(buttonStates[i]!=playerNum) {
      return false;
    }
  }
  winningLEDs[0] = col;
  winningLEDs[1] = col+3;
  winningLEDs[2] = col+6;
  return true;
}

void tieGame() {
  CRGB theLEDColors[9];
  for(int i = 0; i<9; i++) {
    theLEDColors[i] = leds[i];
    setLED(i,BLACK);
  }
  FastLED.show();
  for(int j = 0; j<5; j++) {
    delay(100);
    for(int i = 0; i<9; i++) {
      setLED(i,theLEDColors[i]);
    }
    FastLED.show();
    delay(200);
    for(int i = 0; i<9; i++) {
      setLED(i,BLACK);
    }
    FastLED.show();
  }
  for(int i = 0; i<9; i++) {
    setLED(i,theLEDColors[i]);
  }
  FastLED.show();
  finishGame(false);
}

void finishGame(bool gameHasWinner) {
  Serial.println("finishGame called");
  if(gameHasWinner) {
    flashWinnerLights();
  }
  startUp();
  turnOffLEDs(); 
  for(int i = 0; i < 10; i++) {
    buttonStates[i] = 0;
  }
}

void flashWinnerLights() {
  // Try to write a better algorithm for this,
  // I'm brain dead rn
  int winnerNum = player1sTurn ? 2 : 1;
  CRGB winnerColor = player1sTurn ? BLUE : RED;
  //int winnerLEDs[] = {-1,-1,-1,-1,-1};
  // If there is a winner, there should be a max
  // possible # of moves by the winner of 5
  int numWinningLEDs = 0;
  /*for(int i = 0; i < numButtons; i++) {
    if(buttonStates[i]==winnerNum) {
      winnerLEDs[numWinningLEDs]=i;
      numWinningLEDs++;
    }
  }*/
  numWinningLEDs = 3;
  for(int i = 0; i < 3; i++) {
    Serial.print(winningLEDs[i]);
    Serial.print(" ");
  }
  Serial.println();
  for(int i = 0; i < 5; i++) {
    for(int j = 0; j < numWinningLEDs; j++) {
      setLED(winningLEDs[j], winnerColor);
    }
    FastLED.show();
    delay(200);
    for(int j = 0; j < numWinningLEDs; j++) {
      setLED(winningLEDs[j], BLACK);
    }
    FastLED.show();
    delay(100);
  }
}

void turnOffLEDs() {
  for(int i = 0; i < numLEDs; i++) {
    if(leds[i] == BLACK) {
      continue;
    }
    leds[i] = BLACK;
    FastLED.show();
    delay(100); // To give the turning off more of an animated feel
  }
}

int playRound() {
  userInput = waitForUserInput();
  if(buttons[userInput] == BUTTON_RESET) {
    Serial.println("Button reset pressed");
    return -2;
  }
  lightUpLED(player1sTurn, userInput);
  flipUserTurn();
  return userInput;
}


void flipUserTurn() {
  player1sTurn = !player1sTurn;
}

int waitForUserInput() {
  int theUserInput = getUserInput();
  int counter = 0;
  String a = "Waiting for input ";
  while(theUserInput == -1) {
    //a = a.substring(0,a.indexOf(' ',15));
    //a.concat(counter);
    a = a + counter++;
    for(int i = 0; i < 10; i++) {
      Serial.print(buttonStates[i]);
      Serial.print(" ");
    }
    Serial.println();
    theUserInput = getUserInput();
    //counter += 1;
    delay(10);
  }
  Serial.println("Out of input");
  return theUserInput;
}

int getUserInput() {
  for(int i = 0; i < numButtons; i++) {
    if(digitalRead(buttons[i]) == LOW) {
      if(buttonStates[i] == 1 || buttonStates[i] == 2) {
        Serial.print("Already pressed:");
        Serial.println(i);
        return -1;
      }
      Serial.print("User input: ");
      Serial.println(i);
      return i;
    }
  }
  return -1;
}

void lightUpLED(bool itsPlayer1sTurn, int userInput) {
  if(itsPlayer1sTurn) {
    buttonStates[userInput] = 1;
    setLED(userInput,RED);
  }
  else {
    buttonStates[userInput] = 2;
    setLED(userInput,BLUE);
  }
  FastLED.show();
}

void setLED(int userInput, CRGB color) {
  leds[userInput] = color;
}
