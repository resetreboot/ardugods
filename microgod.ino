// #include <LiquidCrystal.h>

/*
MicroGod

A god-themed Arduboy clicker game
*/

// Definitions

// Game state
#define TITLE     0
#define OPTIONS   1
#define PLAY      2
#define GAMEMENU  3
#define NOTIFY    4
#define SAVEMENU  5

// Game power up
#define PRAYERS           0
#define PROPHETS          1
#define PREDICAMENTS      2
#define SACRED_WRITINGS   3
#define PRIESTS           4
#define TEMPLES           5
#define MARTHYRS          6
#define SAINTS            7

#define NOTIFICATION_DURATION 60
#define DOUBLE_DURATION 300

#define SAVEGAME_LOCATION 333

#define ARROW_LEFT  0
#define ARROW_DOWN  1
#define ARROW_RIGHT 2

#include <Arduboy2.h>
#include <EEPROM.h>
#include "Font4x6.h"

// make an instance of arduboy used for many functions
Arduboy2 arduboy;
// Extra font for menus and such
Font4x6 font4x6 = Font4x6();

// Graphics
// Arrows
const unsigned char PROGMEM arrow_right[] = {
0xff,0xff,0x7e,0x7e,0x3c,0x3c,0x18,0x18
};

const unsigned char PROGMEM arrow_right_mask[] = {
0xff,0xff,0x7e,0x7e,0x3c,0x3c,0x18,0x18
};

const unsigned char PROGMEM arrow_left[] = {
0x18,0x18,0x3c,0x3c,0x7e,0x7e,0xff,0xff
};

const unsigned char PROGMEM arrow_left_mask[] = {
0x18,0x18,0x3c,0x3c,0x7e,0x7e,0xff,0xff
};

const unsigned char PROGMEM arrow_down[] = {
0x03,0x0f,0x3f,0xff,0xff,0x3f,0x0f,0x03
};

const unsigned char PROGMEM arrow_down_mask[] = {
0x03,0x0f,0x3f,0xff,0xff,0x3f,0x0f,0x03
};

const unsigned char PROGMEM arrow_up[] = {
0xc0,0xf0,0xfc,0xff,0xff,0xfc,0xf0,0xc0
};

const unsigned char PROGMEM arrow_up_mask[] = {
0xc0,0xf0,0xfc,0xff,0xff,0xfc,0xf0,0xc0
};

// Game elements
/* compressed
const PROGMEM uint8_t faith_image[] = {
0x0f,0x0f,0xb8,0x9d,0xca,0xf6,0xaa,0x5c,0xed,0x6a,0x77,0xb9,0x7b,0x97,0x77,0x78,
0xdb,0xef,0x52,0x29,0xf5,0xa9,0x2f,0x95,0xdc,0x8d,0x25
};
// bytes:27 ratio: 0.844

const PROGMEM uint8_t faith_mask[] = {
0x0f,0x0f,0xb8,0x9d,0x92,0xdb,0x6d,0x3a,0xbd,0xdd,0x2a,0xe9,0x1c,0xde,0xb6,0xce,
0x49,0xa5,0xd3,0x49,0xe5,0xdc,0x58,0x02
};*/

// faith sprite 16x16
const unsigned char PROGMEM faith_image[] = {
0x00,0x00,0x00,0xf0,0x08,0x64,0xf4,0xf2,0xf2,0xf4,0x64,0x08,0xf0,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x03,0x0c,0x11,0x67,0x67,0x11,0x0c,0x03,0x00,0x00,0x00,0x00
};

const unsigned char PROGMEM faith_mask[] = {
0x00,0x00,0x00,0xf0,0xf8,0xfc,0xfc,0xfe,0xfe,0xfc,0xfc,0xf8,0xf0,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x03,0x0f,0x1f,0x7f,0x7f,0x1f,0x0f,0x03,0x00,0x00,0x00,0x00
};

/*
 * compressed
// bytes:24 ratio: 0.750// faith_small.png  width: 8 height: 8
const PROGMEM uint8_t faith_small_image[] = {
0x07,0x07,0x5e,0xf6,0xd7,0x57,0xb9,0xce,0x75,0xdf,0xbd,0xdb,0x01
};
// bytes:13 ratio: 1.625

const PROGMEM uint8_t faith_small_mask[] = {
0x07,0x07,0x5e,0xf6,0xd7,0x57,0xb9,0xce,0x75,0xdf,0xbd,0xdb,0x01
};
// bytes:13 ratio: 1.625 */

const unsigned char PROGMEM faith_small_image[] = {
0x0c,0x32,0x4d,0xbd,0xbd,0x4d,0x32,0x0c
};


const unsigned char PROGMEM faith_small_mask[] = {
0x0c,0x32,0x4d,0xbd,0xbd,0x4d,0x32,0x0c
};

/*
 * compressed
// predicament.png  width: 8 height: 8
const PROGMEM uint8_t predicament_image[] = {
0x07,0x07,0x88,0xe4,0x55,0x55,0xa5,0x2a,0x55,0x55,0x55,0x95,0x2c,0x22
};
// bytes:14 ratio: 1.750

const PROGMEM uint8_t predicament_mask[] = {
0x07,0x07,0x88,0xe4,0x55,0x55,0xa5,0x2a,0x55,0x55,0x55,0x95,0x2c,0x22
};
// bytes:14 ratio: 1.750 */

const unsigned char PROGMEM predicament_image[] = {
0x00,0x3e,0x55,0x5d,0x57,0x55,0x5f,0x00
};

const unsigned char PROGMEM predicament_mask[] = {
0x00,0x3e,0x55,0x5d,0x57,0x55,0x5f,0x00
};

/*
 * compressed
// sacred.png  width: 8 height: 8
const PROGMEM uint8_t sacred_image[] = {
0x07,0x07,0x5a,0x55,0xe5,0x7c,0x6d,0xb7,0xcb,0x2c,0x11
};
// bytes:11 ratio: 1.375

const PROGMEM uint8_t sacred_mask[] = {
0x07,0x07,0x5a,0x55,0xe5,0x7c,0x6d,0xb7,0xcb,0x2c,0x11
};
// bytes:11 ratio: 1.375 */

const unsigned char PROGMEM sacred_image[] = {
0x46,0x85,0x7f,0xf9,0xf9,0xf9,0x7e,0x00
};

const unsigned char PROGMEM sacred_mask[] = {
0x46,0x85,0x7f,0xf9,0xf9,0xf9,0x7e,0x00
};

/*
 * compressed
// prophet.png  width: 8 height: 8
const PROGMEM uint8_t prophet_image[] = {
0x07,0x07,0x2b,0xe9,0xba,0xb7,0xb9,0x5e,0x75,0xb2,0x9f,0x08
};
// bytes:12 ratio: 1.500

const PROGMEM uint8_t prophet_mask[] = {
0x07,0x07,0x2b,0xe9,0xba,0xb7,0xb9,0x5e,0x75,0xb2,0x9f,0x08
};
// bytes:12 ratio: 1.500 */

const unsigned char PROGMEM prophet_image[] = {
0x05,0x6f,0xf3,0x7b,0x73,0xfb,0x66,0x00
};

const unsigned char PROGMEM prophet_mask[] = {
0x05,0x6f,0xf3,0x7b,0x73,0xfb,0x66,0x00
};

/*
  * compressed
// priest.png  width: 8 height: 8
const PROGMEM uint8_t priest_image[] = {
0x07,0x07,0x4e,0x67,0xaf,0x5d,0x3a,0x59,0xab,0x73,0x79
};
// bytes:11 ratio: 1.375

const PROGMEM uint8_t priest_mask[] = {
0x07,0x07,0x4e,0x67,0xaf,0x5d,0x3a,0x59,0xab,0x73,0x79
};
// bytes:11 ratio: 1.375 */

const unsigned char PROGMEM priest_image[] = {
0x04,0x04,0x96,0xf7,0xf7,0xe5,0x84,0x00
};

const unsigned char PROGMEM priest_mask[] = {
0x04,0x04,0x96,0xf7,0xf7,0xe5,0x84,0x00
};

/*
 * compressed
// temple.png  width: 8 height: 8
const PROGMEM uint8_t temple_image[] = {
0x07,0x07,0x57,0xb2,0xbb,0x2a,0xd9,0xea,0x76,0x55,0xb2,0x73,0x4a,0x01
};
// bytes:14 ratio: 1.750

const PROGMEM uint8_t temple_mask[] = {
0x07,0x07,0x57,0xb2,0xbb,0x2a,0xd9,0xea,0x76,0x55,0xb2,0x73,0x4a,0x01
};
// bytes:14 ratio: 1.750 */

const unsigned char PROGMEM temple_image[] = {
0xe3,0xdb,0xea,0x1b,0x1b,0xea,0xdb,0xe3
};

const unsigned char PROGMEM temple_mask[] = {
0xe3,0xdb,0xea,0x1b,0x1b,0xea,0xdb,0xe3
};

/*
 * compressed
// saint.png  width: 8 height: 8
const PROGMEM uint8_t saint_image[] = {
0x07,0x07,0x9d,0xad,0xd5,0x15,0x51,0xfa,0xab,0xaf,0x77,0x0e
};
// bytes:12 ratio: 1.500

const PROGMEM uint8_t saint_mask[] = {
0x07,0x07,0x9d,0xad,0xd5,0x15,0x51,0xfa,0xab,0xaf,0x77,0x0e
};
// bytes:12 ratio: 1.500 */
const unsigned char PROGMEM saint_image[] = {
0x0f,0x34,0xd6,0x7f,0x7f,0xd6,0x34,0x0f
};

const unsigned char PROGMEM saint_mask[] = {
0x0f,0x34,0xd6,0x7f,0x7f,0xd6,0x34,0x0f
};

/*
 * compressed
// marthyr.png  width: 8 height: 8
const PROGMEM uint8_t marthyr_image[] = {
0x07,0x07,0x98,0xee,0xa5,0x52,0xbd,0x2a,0xe5,0xa4,0xa2,0x02
};
// bytes:12 ratio: 1.500

const PROGMEM uint8_t marthyr_mask[] = {
0x07,0x07,0x98,0xee,0xa5,0x52,0xbd,0x2a,0xe5,0xa4,0xa2,0x02
};
// bytes:12 ratio: 1.500 */

const unsigned char PROGMEM marthyr_image[] = {
0x00,0x6c,0x3e,0x6e,0x2e,0x1e,0x1c,0x00
};


const unsigned char PROGMEM marthyr_mask[] = {
0x00,0x6c,0x3e,0x6e,0x2e,0x1e,0x1c,0x00
};

// Game state
int gamestate = TITLE;
int prev_state = TITLE;
int pointer = 0;
int page = 0;
int scroll = 0;
bool scrolling = false;
bool theres_items = false;
int notif_counter = 0;
int frame_counter = 0;
long faith = 0L;
long resources[8] = {1L, 0L, 0L, 0L, 0L, 0L, 0L, 0L};
long prices[8] = {10L, 100L, 1000L, 10000L, 100000L, 1000000L, 10000000L, 100000000L};
const char* names[8] = {"Prayers", "Prophets", "Predicaments", "Sacred Writings", "Priests", "Temples", "Marthyrs", "Saints"};
char* notification;
bool random_arrows = false;
bool double_rate = false;
int  double_rate_countdown = 0;
bool deity_fight = false;

// For saving and loading from EEPROM
typedef struct {
  long faith;

  long resources[8];
  long prices[8];
} SaveGame;

// Classes
class FaithSprite {
  private:
    int x;
    int y;
    int velocity;
    int steps;

  public:
    FaithSprite() {
      this->x = 0;
      this->y = -20;
      this->velocity = 1;
      this->steps = 0;
    }

    void start(int x, int y) {
      this->x = x;
      this->y = y;
      this->velocity = 1;
      this->steps = 0;
    }

    void animate() {
      if (this->y > -16) {
        this->y = this->y - this->velocity;
        this->steps++;
        if (this->steps > 5) {
          this->steps = 0;
          this->velocity++;
        }
        arduboy.drawBitmap(this->x, this->y, faith_mask, 16, 16, BLACK);
        arduboy.drawBitmap(this->x, this->y, faith_image, 16, 16, WHITE);
      }
    }

    bool is_running() {
      return this->y > -16;
    }
};

class RandomArrow {
  private:
    int x;
    int y;
    int frame_counter;
    int arrow_direction;
    bool dir = false;

  public:
    RandomArrow() {
      this->x = 0;
      this->y = 0;
      this->frame_counter = 0;
    }
    
    void start(int x, int y, int arrow_direction) {
      this->frame_counter = 120;
      this->x = x;
      this->y = y;
      this->dir = false;
      this->arrow_direction = arrow_direction;
    }

    void animate() {
      if (this->frame_counter > 0) {
        this->frame_counter--;
        if (this->frame_counter % 5 == 0) {
          this->dir = !this->dir;
        }

        if (this->frame_counter % 2 == 0) {
          if (this->dir) {
            this->x++;
          } else {
            this->x--;
          }
        }

        switch (this->arrow_direction) {
          case ARROW_LEFT:
            arduboy.drawBitmap(this->x, this->y, arrow_left_mask, 8, 8, BLACK);
            arduboy.drawBitmap(this->x, this->y, arrow_left, 8, 8, WHITE);
            break;
          case ARROW_RIGHT:
            arduboy.drawBitmap(this->x, this->y, arrow_right_mask, 8, 8, BLACK);
            arduboy.drawBitmap(this->x, this->y, arrow_right, 8, 8, WHITE);
            break;
          case ARROW_DOWN:
            arduboy.drawBitmap(this->x, this->y, arrow_down_mask, 8, 8, BLACK);
            arduboy.drawBitmap(this->x, this->y, arrow_down, 8, 8, WHITE);
            break;
        }
      }
    }

    int running() {
      // Returns the arrow direction if it's running, else, returns -1
      if (this->frame_counter > 0) {
        return this->arrow_direction;
      }
      return -1;
    }

    void stop() {
      this->frame_counter = 0;
    }
};

FaithSprite faith_effects_manual[8];
FaithSprite faith_effects_auto[8];
RandomArrow random_arrow = RandomArrow();

// This function runs once in your game.
// use it for anything that needs to be set only once in your game.
void setup() {
  // initiate arduboy instance
  arduboy.begin();

  // here we set the framerate to 15, we do not need to run at
  // default 60 and it saves us battery life
  arduboy.setFrameRate(30);
  
  resetgame();    // Set initial state
}

void resetgame() {
  gamestate = TITLE;
  faith = 0L;
  pointer = 0;
  resources[0] = 1L;
  frame_counter = 0;
  scroll = 0;
  long p = 100L;
  for (int c = 1; c < 8; c++) {
    resources[c] = 0L;
    prices[c] = p;
    p = p * 10L;
  }
  
  arduboy.initRandomSeed();
}

void savegame() {
  SaveGame game;
  game.faith = faith;
  for (int c = 0; c < 8; c++) {
    game.resources[c] = resources[c];
    game.prices[c] = prices[c];
  }
  uint16_t address = EEPROM_STORAGE_SPACE_START + SAVEGAME_LOCATION;

  // Add a header so we know that the EEPROM contains a saved city
  EEPROM.update(address++, 'M'); 
  EEPROM.update(address++, 'C'); 
  EEPROM.update(address++, 'G'); 
  EEPROM.update(address++, 'D'); 

  uint8_t* ptr = (uint8_t*) &game;
  for(size_t n = 0; n < sizeof(SaveGame); n++)
  {
    EEPROM.update(address++, *ptr);
    ptr++;
  }
}

bool loadgame() {
  SaveGame game;
  
  uint16_t address = EEPROM_STORAGE_SPACE_START + SAVEGAME_LOCATION;

  if(EEPROM.read(address++) != 'M') return false;
  if(EEPROM.read(address++) != 'C') return false;
  if(EEPROM.read(address++) != 'G') return false;
  if(EEPROM.read(address++) != 'D') return false;

  uint8_t* ptr = (uint8_t*) &game;
  for(size_t n = 0; n < sizeof(SaveGame); n++)
  {
    *ptr = EEPROM.read(address++);
    ptr++;
  }

  faith = game.faith;

  for (int c = 0; c < 8; c++) {
    resources[c] = game.resources[c];
    prices[c] = game.prices[c];
  }

  return true;
}


// our main game loop, this runs once every cycle/frame.
// this is where our game logic goes.
void loop() {
  // pause render until it's time for the next frame
  if (!(arduboy.nextFrame())) {
    return;
  }

  // first we clear our screen to black
  arduboy.clear();

  // Game state loop
  switch (gamestate) {
    case TITLE:
      title();
      break;
      
    case PLAY:
      game_play();
      break;
      
    case GAMEMENU:
      game_menu();
      break;
      
    case NOTIFY:
      notify();
      break;

     case SAVEMENU:
      save_menu();
      break;
  }

  if (((gamestate != TITLE) && (gamestate != OPTIONS)) &&
     (gamestate != SAVEMENU)){
    game_tick();
  }

  // then we finaly we tell the arduboy to display what we just wrote to the display
  arduboy.display();
}

void title() {
  // Write the title
  arduboy.setTextSize(2);
  arduboy.setCursor(2, 2);
  arduboy.print("Micro God");
  
  // Draw the menu
  font4x6.setCursor(70, 24);
  font4x6.print(F("New game"));
  font4x6.setCursor(70, 34);
  font4x6.print(F("Load game"));
  
  pointer = pointer % 2;
  
  if (pointer < 0) {
    pointer = 2;
  }
  
  switch (pointer) {
    case 0:
      arduboy.drawBitmap(61, 24, arrow_right, 8, 8);
      break;
    case 1:
      arduboy.drawBitmap(61, 34, arrow_right, 8, 8);
      break;
  }
  
  arduboy.pollButtons();
  
  if (arduboy.justPressed(UP_BUTTON)) {
    pointer--;
  }
  
  if (arduboy.justPressed(DOWN_BUTTON)) {
    pointer++;
  }
  
  if (arduboy.justPressed(A_BUTTON) || arduboy.justPressed(B_BUTTON)) {
    switch (pointer) {
      case 0:
        resetgame();
        gamestate = PLAY;
        break;
      case 1:
        load_game();
        break;
    }
  }
}

void load_game() {
  if (!loadgame()) {
    notification = "Could not load";
    prev_state = TITLE;
    gamestate = NOTIFY;
  } else {
    notification = "Loaded game";
    prev_state = PLAY;
    gamestate = NOTIFY;
  }
}

void save_menu() {
  // Write the title
  arduboy.setTextSize(2);
  arduboy.setCursor(2, 2);
  arduboy.print("Micro God");
  
  // Draw the menu
  font4x6.setCursor(70, 24);
  font4x6.print(F("Save game"));
  font4x6.setCursor(70, 34);
  font4x6.print(F("Fight god"));
  font4x6.setCursor(70, 44);
  font4x6.print(F("End game"));
  font4x6.setCursor(70, 54);
  font4x6.print(F("Exit menu"));
  
  pointer = pointer % 4;
  
  if (pointer < 0) {
    pointer = 3;
  }
  
  switch (pointer) {
    case 0:
      arduboy.drawBitmap(61, 24, arrow_right, 8, 8);
      break;
    case 1:
      arduboy.drawBitmap(61, 34, arrow_right, 8, 8);
      break;
    case 2:
      arduboy.drawBitmap(61, 44, arrow_right, 8, 8);
      break;
    case 3:
      arduboy.drawBitmap(61, 54, arrow_right, 8, 8);
      break;
  }
  
  arduboy.pollButtons();
  
  if (arduboy.justPressed(UP_BUTTON)) {
    pointer--;
  }
  
  if (arduboy.justPressed(DOWN_BUTTON)) {
    pointer++;
  }
  
  if (arduboy.justPressed(A_BUTTON) || arduboy.justPressed(B_BUTTON)) {
    switch (pointer) {
      case 0:
        savegame();
        notification = "Game saved";
        prev_state = PLAY;
        gamestate = NOTIFY;
        break;
      case 1:
        // TODO: Fight against other gods
        break;
      case 2:
        resetgame();
        break;
      case 3:
        gamestate = PLAY;
        break;
    }
  }
}

void game_play() {
  random_arrow.animate();
  animate_faith();
  animate_items();
  
  arduboy.setTextSize(1);
  arduboy.setCursor(2, 2);
  if (double_rate) {
    arduboy.print(F("Faith(x3): "));
  } else {
    arduboy.print(F("Faith: "));  
  }
  
  arduboy.print(faith);

  // Save menu indication
  font4x6.setCursor(12,55);
  font4x6.print(F("menu"));
  arduboy.drawBitmap(2,56, arrow_up_mask, 8, 8, BLACK);
  arduboy.drawBitmap(2,56, arrow_up, 8, 8, WHITE);

  // Buy menu indication
  font4x6.setCursor(102, 55);
  font4x6.print(F("B buy"));
  
  arduboy.pollButtons();
  if (arduboy.justPressed(A_BUTTON)) {
    long prayers = resources[PRAYERS];
    if (double_rate) {
      prayers = prayers * 3;
    }
    faith = faith + prayers;
    int effect = prayers / 8;
    if (effect == 0) {
      effect = 1;
    }

    if (effect > 8) {
      effect = 8;
    }
    add_faith_manual(effect);
  }
  
  if (arduboy.justPressed(B_BUTTON)) {
    gamestate = GAMEMENU;
  }

  if (arduboy.justPressed(UP_BUTTON)) {
    pointer = 0;
    gamestate = SAVEMENU;
  }

  if (arduboy.justPressed(LEFT_BUTTON) && random_arrow.running() == ARROW_LEFT) {
    double_rate = true;
    double_rate_countdown = DOUBLE_DURATION;
    random_arrow.stop();
  }

  if (arduboy.justPressed(RIGHT_BUTTON) && random_arrow.running() == ARROW_RIGHT) {
    double_rate = true;
    double_rate_countdown = DOUBLE_DURATION;
    random_arrow.stop();
  }

  if (arduboy.justPressed(DOWN_BUTTON) && random_arrow.running() == ARROW_DOWN) {
    double_rate = true;
    double_rate_countdown = DOUBLE_DURATION;
    random_arrow.stop();
  }
}

void add_faith_manual(int num) {
  int c = 0;
  while ((c < 8) && (num > 0)) {
    FaithSprite f = faith_effects_manual[c];
    if (!f.is_running()) {
      f.start(random(0, 116), random(30, 48));
      faith_effects_manual[c] = f;
      num--;
    }
    c++;
  }
}

void add_faith_auto(int num) {
  int c = 0;
  while ((c < 8) && (num > 0)) {
    FaithSprite f = faith_effects_auto[c];
    if (!f.is_running()) {
      f.start(random(0, 116), random(30, 48));
      num--;
      faith_effects_auto[c] = f;
    }
    num--;
    c++;
  }
}

void animate_faith() {
  int c;
  for (c = 0; c < 8; c++) {
    faith_effects_manual[c].animate();
  }
  for (c = 0; c < 8; c++) {
    faith_effects_auto[c].animate();
  }
}

void animate_items() {
  if (!theres_items) {
    // Check to see if we have items to show
    int sum = 0;
    for (int c=1; c < 8; c++) {
      sum = sum + resources[c];
    }

    theres_items = sum > 0;
  } else {
    if (!scrolling) {
      scroll = 127;
      scrolling = true;
    }
    bool drawn = false;
    int column = 0;
    int line = 0;
    for (int c=1; c < 8; c++) {
      int amount = resources[c];
      if (amount == 0) {
        continue;
      }
      int x = scroll;
      int currentx = x + (column * 8);
      if (currentx >= 128) {
        // Avoid drawing off screen
        continue;
      }
      for (int i=0; i < amount; i++) {
        draw_item(c, x + (column * 8), 46 - (line * 9));
        line++;
        if (line >= 3) {
          line = 0;
          column++;
        }
      }
      if (line != 0) {
        column++;
      }
      line = 0;
      if (x + (column * 8) <= -8) {
        drawn = false;
      } else {
        drawn = true;
      }
    }

    if (!drawn) {
      scrolling = false;    // Reset the scroll
    }
    scroll--;
  }
}

void draw_item(int item, int x, int y) {
  switch(item) {
    case PRAYERS:
      arduboy.drawBitmap(x, y, faith_small_mask, 8, 8, BLACK);
      arduboy.drawBitmap(x, y, faith_small_image, 8, 8, WHITE);
      break;
    case SACRED_WRITINGS:
      arduboy.drawBitmap(x, y, sacred_mask, 8, 8, BLACK);
      arduboy.drawBitmap(x, y, sacred_image, 8, 8, WHITE);
      break;
    case PREDICAMENTS:
      arduboy.drawBitmap(x, y, predicament_mask, 8, 8, BLACK);
      arduboy.drawBitmap(x, y, predicament_image, 8, 8, WHITE);
      break;
    case PRIESTS:
      arduboy.drawBitmap(x, y, priest_mask, 8, 8, BLACK);
      arduboy.drawBitmap(x, y, priest_image, 8, 8, WHITE);
      break;
    case PROPHETS:
      arduboy.drawBitmap(x, y, prophet_mask, 8, 8, BLACK);
      arduboy.drawBitmap(x, y, prophet_image, 8, 8, WHITE);
      break;
    case SAINTS:
      arduboy.drawBitmap(x, y, saint_mask, 8, 8, BLACK);
      arduboy.drawBitmap(x, y, saint_image, 8, 8, WHITE);
      break;
    case TEMPLES:
      arduboy.drawBitmap(x, y, temple_mask, 8, 8, BLACK);
      arduboy.drawBitmap(x, y, temple_image, 8, 8, WHITE);
      break;
    case MARTHYRS:
      arduboy.drawBitmap(x, y, marthyr_mask, 8, 8, BLACK);
      arduboy.drawBitmap(x, y, marthyr_image, 8, 8, WHITE);
      break;
  }
}

void game_menu() {
  int x = 20;
  int y = 10;

  pointer = pointer % 8;
  if (pointer < 0) {
    pointer = 7;
  }

  if (pointer < 5) {
    page = 1;
  } else {
    page = 2;
  }

  font4x6.setCursor(2, 2);
  font4x6.print(F("Price: "));
  font4x6.print(prices[pointer]);

  if (page == 1) {
    for (int c = 0; c < 5; c++) {
      font4x6.setCursor(x, y + (c * 10));
      font4x6.print(names[c]);
      font4x6.print(F(": "));
      font4x6.print(resources[c]);
      draw_item(c, x - 9, y + (c * 10));
    }
    font4x6.setCursor(100, 56);
    font4x6.print(F("More..."));
  } else {
    for (int c = 5; c < 8; c++) {
      font4x6.setCursor(x, y + ((c - 5) * 10));
      font4x6.print(names[c]);
      font4x6.print(F(": "));
      font4x6.print(resources[c]);
      draw_item(c, x - 9, y + ((c - 5) * 10));
    }
  }

  if (pointer < 5) {
    arduboy.drawBitmap(2, y + (10 * pointer), arrow_right, 8, 8);
  } else {
    arduboy.drawBitmap(2, y + (10 * (pointer - 5)), arrow_right, 8, 8);
  }
  
  arduboy.pollButtons();

  if (arduboy.justPressed(UP_BUTTON)) {
    pointer--;
  }

  if (arduboy.justPressed(DOWN_BUTTON)) {
    pointer++;
  }

  if (arduboy.justPressed(A_BUTTON)) {
    if (faith >= prices[pointer]) {
      faith -= prices[pointer];
      resources[pointer] = resources[pointer] + 1;
      prices[pointer] = prices[pointer] + (prices[pointer] / 2);
      notification = "Acquired!";
      prev_state = PLAY;
      gamestate = NOTIFY;
    } else {
      notification = "Not Enough Faith!";
      prev_state = GAMEMENU;
      gamestate = NOTIFY;
    }
  }
  
  if (arduboy.justPressed(B_BUTTON)) {
    gamestate = PLAY;
  }
}

void notify() {
  // Write the notification
  arduboy.setTextSize(1);
  arduboy.setCursor(2, 2);
  arduboy.print(notification);

  notif_counter++;

  if (notif_counter >= NOTIFICATION_DURATION) {
    gamestate = prev_state;
    notif_counter = 0;
  }

  arduboy.pollButtons();

  if ((arduboy.justPressed(A_BUTTON)) || (arduboy.justPressed(B_BUTTON))) {
    gamestate = prev_state;
    notif_counter = 0;
  }
}

void game_tick() {
  frame_counter++;

  if (frame_counter > 6) {
    // Game tick elapsed, parse the resources and add accordingly
    // except the prayers, those are only for clicks
    int delta = 0;
    for (int c = 1; c < 8; c++) {
      int res = resources[c];
      delta += res * (c * c);
    }

    if (double_rate) {
      delta = delta * 3;
      double_rate_countdown--;

      if (double_rate_countdown <= 0) {
        double_rate = false;
      }
    }
    // Add the amount generated by auto resources
    faith += delta;

    // Calculate the amount of faith effect to create
    if (delta > 0) {
      random_arrows = delta >= 80;    // Random arrows appear at this level
      delta = (delta / 80) + 1;
      if (delta > 8) {
        delta = 8;
      }
      add_faith_auto(delta);
    }
    frame_counter = 0;

    if (random_arrow.running() < 0 && !double_rate) {
      if (random_arrows && random(0, 100) > 98) {
        int dir;
        switch (random(0,3)) {
          case 0:
            dir = ARROW_LEFT;
            break;
          case 1:
            dir = ARROW_RIGHT;
            break;
          case 2:
            dir = ARROW_DOWN;
            break;
        }
        random_arrow.start(random(0, 120), random(12, 76), dir);
      }
    }
  }
}
