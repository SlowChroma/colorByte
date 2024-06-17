#include <raylib.h>
#include "../lib/functions.h"

#define MAX_INPUT_CHARS 8

//TODO: FIX FLASHING COLOR BUG

int main()
{
  InitWindow(500, 700, "colorByte");
  SetTargetFPS(60);
  
  Texture2D background = LoadTexture("./src/background.png");
  
  char input[MAX_INPUT_CHARS + 1] = "\0";
  int numCount = 0;
  bool mouseOnText = false;
  int framesCounter = 0;
  Rectangle textBox = {150, 110, 200, 60};
  
  while(!WindowShouldClose())
  {
    if (CheckCollisionPointRec(GetMousePosition(), textBox)) mouseOnText = true;
    else mouseOnText = false;
    
    if (mouseOnText)
    {
      SetMouseCursor(MOUSE_CURSOR_IBEAM);
      
      int key = GetCharPressed();

      while (key > 0)
      {
        if(((key == 48) || (key == 49)) && (numCount < MAX_INPUT_CHARS))
        {
          input[numCount] = (char)key;
          input[numCount+1] = '\0'; // Add null terminator at the end of the string.
          numCount++;
        }

        key = GetCharPressed();
      }

      if (IsKeyPressed(KEY_BACKSPACE))
      {
        numCount--;
        if (numCount < 0) numCount = 0;
        input[numCount] = '\0';
      }
    }
    else SetMouseCursor(MOUSE_CURSOR_DEFAULT);

    if (mouseOnText) framesCounter++;
    else framesCounter = 0;
    
    BeginDrawing();
    
    ClearBackground(BLACK);
    
    DrawTexture(background, 0, 200, WHITE);
    DrawText("Welcome to colorByte!\n\nHover you mouse over the box and\n\ninput a colorByte.", 10, 10, 20, WHITE);
    
    DrawRectangleRec(textBox, LIGHTGRAY);
    if (mouseOnText) DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, RED);
    else DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, DARKGRAY);

    DrawText(input, (int)textBox.x + 5, (int)textBox.y + 8, 40, MAROON);

    if (mouseOnText)
    {
      if (numCount < MAX_INPUT_CHARS)
      {
        if (((framesCounter/20)%2) == 0) DrawText("_", (int)textBox.x + 8 + MeasureText(input, 40), (int)textBox.y + 12, 40, MAROON);
      }
    }

    int rgba[4];
    
    if(numCount == 8){
      for(int i = 0; i < 4; i++)
      {
      rgba[i] = byte_to_rgba(input)[i];        
      }
    }
    
    Color colorByteColor = {rgba[0], rgba[1], rgba[2], rgba[3]};
    
    DrawRectangle(0, 200, 500, 500, colorByteColor);
    
    EndDrawing();
  }
  
  CloseWindow();
  
  return 0;
}
