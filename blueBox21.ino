/*----------XXXXX----------*/
#include <time.h>
#include<stdlib.h>
#include <LedControl.h>
 
/*----------XXXXX----------*/
#define SCREEN_DIN_PIN  3
#define SCREEN_CS_PIN   5
#define SCREEN_CLK_PIN  2
 
#define JYS_X_PIN       27
#define JYS_Y_PIN       26
#define JYS_BTN_PIN     22
 
#define GROVE_LED_PIN   21
#define GROVE_BTN_PIN   20
 
#define BUZZER_PIN      28
 
#define DEVICE_WIDTH    8
#define DEVICE_HEIGHT   8   
 
#define SCREEN_HEIGHT   32
#define SCREEN_WIDTH    8
 
/*----------XXXXX----------*/
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define REST 0
 
// change this to make the song slower or faster
int tempo = 144; 
 
int melody[] = {
  NOTE_E5,  4,  NOTE_B4,  8,  NOTE_C5,  8,  NOTE_D5,  4,  NOTE_C5,  8,  NOTE_B4,  8,
  NOTE_A4,  4,  NOTE_A4,  8,  NOTE_C5,  8,  NOTE_E5,  4,  NOTE_D5,  8,  NOTE_C5,  8,
  NOTE_B4, -4,  NOTE_C5,  8,  NOTE_D5,  4,  NOTE_E5,  4,
  NOTE_C5,  4,  NOTE_A4,  4,  NOTE_A4,  8,  NOTE_A4,  4,  NOTE_B4,  8,  NOTE_C5,  8,
 
  NOTE_D5, -4,  NOTE_F5,  8,  NOTE_A5,  4,  NOTE_G5,  8,  NOTE_F5,  8,
  NOTE_E5, -4,  NOTE_C5,  8,  NOTE_E5,  4,  NOTE_D5,  8,  NOTE_C5,  8,
  NOTE_B4,  4,  NOTE_B4,  8,  NOTE_C5,  8,  NOTE_D5,  4,  NOTE_E5,  4,
  NOTE_C5,  4,  NOTE_A4,  4,  NOTE_A4,  4,  REST,     4,
 
  NOTE_E5,  4,  NOTE_B4,  8,  NOTE_C5,  8,  NOTE_D5,  4,  NOTE_C5,  8,  NOTE_B4,  8,
  NOTE_A4,  4,  NOTE_A4,  8,  NOTE_C5,  8,  NOTE_E5,  4,  NOTE_D5,  8,  NOTE_C5,  8,
  NOTE_B4, -4,  NOTE_C5,  8,  NOTE_D5,  4,  NOTE_E5,  4,
  NOTE_C5,  4,  NOTE_A4,  4,  NOTE_A4,  8,  NOTE_A4,  4,  NOTE_B4,  8,  NOTE_C5,  8,
 
  NOTE_D5, -4,  NOTE_F5,  8,  NOTE_A5,  4,  NOTE_G5,  8,  NOTE_F5,  8,
  NOTE_E5, -4,  NOTE_C5,  8,  NOTE_E5,  4,  NOTE_D5,  8,  NOTE_C5,  8,
  NOTE_B4,  4,  NOTE_B4,  8,  NOTE_C5,  8,  NOTE_D5,  4,  NOTE_E5,  4,
  NOTE_C5,  4,  NOTE_A4,  4,  NOTE_A4,  4,  REST,     4,
   
  NOTE_E5,  2,  NOTE_C5,  2,
  NOTE_D5,  2,  NOTE_B4,  2,
  NOTE_C5,  2,  NOTE_A4,  2,
  NOTE_GS4, 2,  NOTE_B4,  4,  REST,     8, 
  NOTE_E5,  2,  NOTE_C5,  2,
  NOTE_D5,  2,  NOTE_B4,  2,
  NOTE_C5,  4,  NOTE_E5,  4,  NOTE_A5,  2,
  NOTE_GS5, 2,
};
 
int notes = sizeof(melody) / sizeof(melody[0]) / 2; 
 
int wholenote = (60000 * 4) / tempo;
 
int divider = 0, noteDuration = 0;
 
bool start_game = false;
bool tocou_musiquinha = true;
 
/*----------XXXXX----------*/
typedef struct{
  byte x,y;
} Point;
 
typedef struct{
  Point points[4];
  short type;
} Block;
 
/*----------XXXXX----------*/
LedControl led_controller = LedControl(SCREEN_DIN_PIN, SCREEN_CLK_PIN, SCREEN_CS_PIN, 0);
 
bool bottom_chunk[SCREEN_WIDTH][SCREEN_HEIGHT] = {false};
Block live_block;
int loop_counter = 0;
 
/*----------XXXXX----------*/
void init_led_controller(){
  for(int index = 0; index < led_controller.getDeviceCount(); index++){
  //The MAX72XX is in power-saving mode on startup/
    led_controller.shutdown(index, false);
    /* Set the brightness to a medium values */
    led_controller.setIntensity(index, 0);
    /* and clear the display */
    led_controller.clearDisplay(index);
  }
}
 
/*----------XXXXX----------*/
void init_button_led(){
  pinMode(GROVE_BTN_PIN, INPUT_PULLUP);
  pinMode(GROVE_LED_PIN, OUTPUT);
 
  for (int i = 0; i < 5; i++){
    digitalWrite(GROVE_LED_PIN, LOW);
    delay(500);
    digitalWrite(GROVE_LED_PIN, HIGH);
    delay(500);
  }
}
 
/*----------XXXXX----------*/
void init_joy_stick(){
  pinMode(JYS_BTN_PIN, INPUT_PULLUP);
}
 
/*----------XXXXX----------*/
void show_screen_for_map(bool pixels[SCREEN_WIDTH][SCREEN_HEIGHT]){
  short deviceNumber = 0;
  for(int y = 0; y < SCREEN_HEIGHT; y++){
    deviceNumber = y/DEVICE_HEIGHT;
    for(int x = 0; x < DEVICE_WIDTH ; x++){
      led_controller.setLed(deviceNumber, DEVICE_WIDTH - x - 1, DEVICE_HEIGHT - y - 1 + deviceNumber * DEVICE_HEIGHT,pixels[x][y]);
    } 
  }
}
 
/*----------XXXXX----------*/
void show_game_map(){
  bool map[SCREEN_WIDTH][SCREEN_HEIGHT];
  for(int x = 0; x <SCREEN_WIDTH; x++)
    for(int y = 0; y < SCREEN_HEIGHT; y++)
    map[x][y] = bottom_chunk[x][y];
        for(int i = 0; i < 4 ; i++){
            map[live_block.points[i].x][live_block.points[i].y] = true; 
        }
        show_screen_for_map(map);
}
 
/*----------XXXXX----------*/
void show_load_screen() {
  //byte G[] = {B11110000, B10010000, B10010000, B11111110, B00010010, B00010010, B00011110, B00000000};
  //byte A[] = {B01010010, B01010010, B01010010, B01111110, B01000000, B01111110, B01000000, B01000000};
  //byte M[] = {B01110010, B01010100, B01011000, B01111110, B01000000, B01111110, B01000000, B01000000};
  //byte E[] = {B01011110, B01010010, B01010010, B01110010, B00000000, B01111110, B00000000, B00000000};

  byte G[] = {B00000000, B00001100, B01100010, B00000010, B00000010, B01100010, B00001100, B00000000};
  byte A[] = {B00000000, B01111110, B00000000, B01001000, B01001000, B01001000, B01111110, B00000000};
  byte M[] = {B00000000, B01111110, B00000000, B00000010, B00000010, B00000010, B01111110, B00000000};
  byte E[] = {B00000000, B01001010, B01111110, B00000000, B01111000, B01001000, B01111110, B00000000};
         
  //Clearing Displays
  for(int i = 0; i < led_controller.getDeviceCount(); i++)
    led_controller.clearDisplay(i);
 
  for(int i = 0; i < 8; i++){
    led_controller.setRow(3, i, G[i]);
  }
 
  for(int i = 0; i < 8; i++){
    led_controller.setRow(2, i, A[i]);   
  }
 
  for(int i = 0; i < 8; i++){
    led_controller.setRow(1, i, M[i]);
  }
 
  for(int i = 0; i < 8; i++){
    led_controller.setRow(0,i,E[i]);
  }
 
  delay(5000);
}
 
/*----------XXXXX----------*/
//Live Block Interactions
bool live_block_reached_bottom_chunck(){
  for(int i = 0; i < 4; i++)
    if( live_block.points[i].y == 0 || bottom_chunk[live_block.points[i].x][live_block.points[i].y - 1] == true )
      return true;
  return false;
}
 
/*----------XXXXX----------*/
void register_live_block_to_bottom_chunck(){
  for(int i = 0; i < 4; i++)
    bottom_chunk[live_block.points[i].x][live_block.points[i].y] = true;
  }
 
/*----------XXXXX----------*/
//Live Block Movements
void move_live_block_left() {
  for(int i = 0; i < 4 ; i++){
    if( live_block.points[i].x == 0 || bottom_chunk[live_block.points[i].x-1][live_block.points[i].y] )
  return;  
  }
   
  for(int i = 0; i < 4; i++) 
    live_block.points[i].x--;
}
 
/*----------XXXXX----------*/
void move_live_block_right(){
  for(int i = 0 ; i < 4; i++){
    if(live_block.points[i].x == SCREEN_WIDTH - 1 || bottom_chunk[live_block.points[i].x+1][live_block.points[i].y])
  return;  
  }
   
  for(int i = 0 ; i < 4; i++) 
    live_block.points[i].x++;
  }
 
/*----------XXXXX----------*/
void move_live_block_down(){
  if(!live_block_reached_bottom_chunck())
    for(int i = 0; i < 4; i++) 
      live_block.points[i].y--;
  }
 
/*----------XXXXX----------*/
void rotatelive_block(){
  //Linear Shape
  if(live_block.type == 0){
     
    //Vertical
    if(live_block.points[0].x == live_block.points[1].x){
      int newY = live_block.points[2].y;
      int newX = live_block.points[2].x;
 
      for(int i = 0 ; i < 4; i++)
        live_block.points[i].y = newY;
        live_block.points[3].x = newX - 1;
        live_block.points[1].x = newX +1;
        live_block.points[0].x = newX +2; 
      return;
    }
     
    //Horizontal
    if(live_block.points[0].y == live_block.points[1].y){
      int newX = live_block.points[1].x;
      int newY = live_block.points[1].y;
 
      for(int i = 0 ; i < 4; i++)
        live_block.points[i].x = newX;
        live_block.points[0].y = newY + 1;
        live_block.points[2].y = newY -1 ;
        live_block.points[3].y = newY - 2;   
      return;
    } 
  }
             
  //T & L Shapes
  if(live_block.type ==2 || live_block.type == 3 || live_block.type == 4){
    for( int i = 0 ; i < 4 ; i++ ){
      int prev_x = live_block.points[i].x;
      int prev_y = live_block.points[i].y;
      live_block.points[i].x = prev_y - live_block.points[1].y +live_block.points[1].x;
      live_block.points[i].y = -prev_x + live_block.points[1].x + live_block.points[1].y;
    }
  return;
  }
 
  if(live_block.type == 5){
    int newX = live_block.points[2].x;
    int newY = live_block.points[2].y;
             
    if(live_block.points[1].y == live_block.points[3].y){
      live_block.points[3].x = live_block.points[3].x + 2;
      live_block.points[1].y = live_block.points[1].y - 2;
    }
    else{
      live_block.points[3].x = live_block.points[3].x - 2;
      live_block.points[1].y = live_block.points[1].y + 2;
    }
  }
}
 
/*----------XXXXX----------*/
//Game Logic
void clear_bottom_chunck(){
  for(int i = 0; i < SCREEN_WIDTH; i++)
    for(int j = 0; j < SCREEN_HEIGHT; j++)
      bottom_chunk[i][j] = false;
}
 
/*----------XXXXX----------*/
void check_button(){
  while (start_game == false){
    show_load_screen();
     
    for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2){
 
      Serial.print("estado botão: ");
      Serial.println(digitalRead(GROVE_BTN_PIN));
      Serial.print("Iniciou jogo? ");
      Serial.println(start_game);
      if (digitalRead(GROVE_BTN_PIN) == LOW){
        Serial.print("Entrou no if");
        delay(1000);
        start_game = true;
      }   
      if (start_game == true){
        //Clearing Displays
        for(int i = 0; i < led_controller.getDeviceCount(); i++)
        led_controller.clearDisplay(i);
        start_new_game();
      }
      else if (!tocou_musiquinha){
        divider = melody[thisNote + 1];
        if (divider > 0){
          // regular note, just proceed
          noteDuration = (wholenote) / divider;
        } 
        else if (divider < 0) {
          // dotted notes are represented with negative durations!!
          noteDuration = (wholenote) / abs(divider);
          noteDuration *= 1.5; // increases the duration in half for dotted notes
        }
          
        // we only play the note for 90% of the duration, leaving 10% as a pause
        tone(BUZZER_PIN, melody[thisNote], noteDuration*0.9);
        // Wait for the specief duration before playing the next note.
        delay(noteDuration);
        // stop the waveform generation before the next note.
        noTone(BUZZER_PIN); 
      }
    }
    tocou_musiquinha = true;
  }   
}
 
/*----------XXXXX----------*/
void start_new_game(){
  clear_bottom_chunck();
  generate_new_live_block();
  loop_counter = 0;
}
 
/*----------XXXXX----------*/
void generate_new_live_block(){
  live_block.type = rand() % 6 ;
  if(live_block.type== 0){
    live_block.points[0].x = 4;
    live_block.points[1].x = 4;
    live_block.points[2].x = 4;
    live_block.points[3].x = 4;
    live_block.points[0].y = SCREEN_HEIGHT - 1;
    live_block.points[1].y = SCREEN_HEIGHT - 2;
    live_block.points[2].y = SCREEN_HEIGHT - 3;
    live_block.points[3].y = SCREEN_HEIGHT - 4;
  }
  else if(live_block.type == 1){
    live_block.points[0].x = 3;
    live_block.points[1].x = 3;
    live_block.points[2].x = 4;
    live_block.points[3].x = 4;
    live_block.points[0].y = SCREEN_HEIGHT - 1;
    live_block.points[1].y = SCREEN_HEIGHT - 2;
    live_block.points[2].y = SCREEN_HEIGHT - 1;
    live_block.points[3].y = SCREEN_HEIGHT - 2;
  }
  else if(live_block.type== 2){
    live_block.points[0].x = 3;
    live_block.points[1].x = 4;
    live_block.points[2].x = 5;
    live_block.points[3].x = 3;
    live_block.points[0].y = SCREEN_HEIGHT - 1;
    live_block.points[1].y = SCREEN_HEIGHT - 2;
    live_block.points[2].y = SCREEN_HEIGHT - 2;
    live_block.points[3].y = SCREEN_HEIGHT - 2;
  }
         
  else if(live_block.type == 3){
    live_block.points[0].x = 4;
    live_block.points[1].x = 4;
    live_block.points[2].x = 5;
    live_block.points[3].x = 3;
    live_block.points[0].y = SCREEN_HEIGHT - 1;
    live_block.points[1].y = SCREEN_HEIGHT - 2;
    live_block.points[2].y = SCREEN_HEIGHT - 2;
    live_block.points[3].y = SCREEN_HEIGHT - 2;
  }
   
  else if(live_block.type == 4){
    live_block.points[0].x = 5;
    live_block.points[1].x = 4;
    live_block.points[2].x = 5;
    live_block.points[3].x = 3;
    live_block.points[0].y = SCREEN_HEIGHT - 1;
    live_block.points[1].y = SCREEN_HEIGHT - 2;
    live_block.points[2].y = SCREEN_HEIGHT - 2;
    live_block.points[3].y = SCREEN_HEIGHT - 2;
  }
         
  else if(live_block.type == 5){
    live_block.points[0].x = 5;
    live_block.points[1].x = 4;
    live_block.points[2].x = 4;
    live_block.points[3].x = 3;
    live_block.points[0].y = SCREEN_HEIGHT - 2;
    live_block.points[1].y = SCREEN_HEIGHT - 1;
    live_block.points[2].y = SCREEN_HEIGHT - 2;
    live_block.points[3].y = SCREEN_HEIGHT - 1;
  }
}
 
/*----------XXXXX----------*/
void remove_full_bottom_rows(){ 
  short counter = 0;
  short full_count = 0;
  short y = 0;
  for(; y < SCREEN_HEIGHT; y++){
    short x = 0;
    for(; x < SCREEN_WIDTH; x++)
      if( !bottom_chunk[x][y] )
        break;
    if( x != SCREEN_WIDTH && full_count > 0 ){
      break;
    }
    if(x == SCREEN_WIDTH){
      full_count++;
      for(short x = 0; x < SCREEN_WIDTH; x++)
        bottom_chunk[x][y] = false;
      }
  }
  if(full_count){
   for(y -= full_count; y < SCREEN_HEIGHT - full_count; y++)
     for(short x = 0; x < SCREEN_WIDTH; x++)
       bottom_chunk[x][y] = bottom_chunk[x][y+full_count];
   for(; y < SCREEN_HEIGHT; y++)
     for(short x = 0; x < SCREEN_WIDTH; x++ )
       bottom_chunk[x][y] = false;        
  }       
}
 
/*----------XXXXX----------*/  
//Action Handlings
void getAction(){
  int y = analogRead(JYS_X_PIN);
  int x = analogRead(JYS_Y_PIN);
         
  //Left
  if(x > 540 && y < 612 && y > 412){
    move_live_block_left();
    return;
  }
 
  //Right
  if(x < 500 && y < 612 && y > 412){
    move_live_block_right();
    return;
  }
   
  //Down
  if(y > 650){
    move_live_block_down();
    return;
  }
   
  //Up -> Rotate
  if(digitalRead(JYS_BTN_PIN) == LOW){
     delay(100);
     rotatelive_block();
  }  
}
 
/*----------XXXXX----------*/ 
//Main
void setup(){
  Serial.begin(9600);
  init_button_led();
  init_joy_stick();
  init_led_controller();
  check_button();  
}
 
/*----------XXXXX----------*/     
void loop(){ 
  loop_counter++;
  if(loop_counter % 3 == 0){
    move_live_block_down();
  }
  if(loop_counter == 1100){
    //clear_bottom_chunck();
    loop_counter = 0;            
  }
  getAction();
  show_game_map();
  if(live_block_reached_bottom_chunck()){
    register_live_block_to_bottom_chunck();
    remove_full_bottom_rows();
    show_game_map();
    generate_new_live_block();
    show_game_map();
    if(live_block_reached_bottom_chunck()){
      delay(1000);      
      clear_bottom_chunck();
      start_game = false;
      check_button();
    }
  }
}
