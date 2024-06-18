#include <raylib.h>
#include "../lib/functions.h"

#define MAX_INPUT_CHARS 8

int main()
{
  bool restart = false;

  InitWindow(500, 200, "colorByte");
  SetTargetFPS(60);

  char input[MAX_INPUT_CHARS + 1] = "\0";
  int numCount = 0;
  bool mouseOnText = false;
  bool mouseOnButton = false;
  bool buttonPressed = false;
  int framesCounter = 0;
  Rectangle textBox = {25, 110, 200, 60};
  Rectangle button = {275, 110, 200, 60};

  while(!WindowShouldClose())
  {
    if (CheckCollisionPointRec(GetMousePosition(), textBox)) mouseOnText = true;
    else mouseOnText = false;
    
    if (CheckCollisionPointRec(GetMousePosition(), button)) mouseOnButton = true;
    else mouseOnButton = false;

    if (mouseOnText)
    {
      SetMouseCursor(MOUSE_CURSOR_IBEAM);

      int key = GetCharPressed();

      while (key > 0)
      {
        if(((key == 48) || (key == 49)) && (numCount < MAX_INPUT_CHARS))
        {
          input[numCount] = (char)key;
          input[numCount+1] = '\0';
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
    DrawText("colorByte v1.1.1", 400, 180, 10, WHITE);

    DrawRectangleRec(textBox, LIGHTGRAY);

    if (mouseOnText) DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, RED);
    else DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, DARKGRAY);

    DrawText(input, (int)textBox.x + 5, (int)textBox.y + 8, 40, BLACK);

    if (mouseOnText)
    {
      if (numCount < MAX_INPUT_CHARS)
      {
        if (((framesCounter/20)%2) == 0) DrawText("_", (int)textBox.x + 8 + MeasureText(input, 40), (int)textBox.y + 12, 40, BLACK);
      }
    }

    DrawText("Welcome to colorByte!\n\nHover you mouse over the box and\n\ninput a colorByte.", 10, 10, 20, WHITE);

    DrawRectangleRec(button, LIGHTGRAY);

    if(numCount == 8)
    {
      DrawText("DISPLAY\n\n  COLOR", 300, 110, 30, BLACK);
    }

    if(numCount == 8 && mouseOnButton)
    {
      DrawRectangleRec(button, DARKGRAY);
      DrawText("DISPLAY\n\n  COLOR", 300, 110, 30, BLACK);
      if (mouseOnButton) DrawRectangleLines((int)button.x, (int)button.y, (int)button.width, (int)button.height, RED);
      else DrawRectangleLines((int)button.x, (int)button.y, (int)button.width, (int)button.height, DARKGRAY);
      if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
      {
        buttonPressed = true;
        break;
      }
    }

    EndDrawing();
  }

  CloseWindow();

  if(numCount == 8 && buttonPressed)
  {
    int rgba[4];

    for(int i = 0; i < 4; i++)
    {
      rgba[i] = byte_to_rgba(input)[i];
    }

    Color colorByteColor = {rgba[0], rgba[1], rgba[2], rgba[3]};

    InitWindow(500, 600, "colorByte");

    Texture2D background = LoadTexture("./src/background.png");

    while(!WindowShouldClose())
    {
      BeginDrawing();

      ClearBackground(LIGHTGRAY);
      DrawTexture(background, 0, 0, WHITE);
      DrawRectangleLines(0, 500, 500, 100, RED);
      DrawText("R TO RESTART\n\nESC TO QUIT", 25, 525, 30, BLACK);

      DrawRectangle(0, 0, 500, 500, colorByteColor);

      EndDrawing();

      if(IsKeyPressed(KEY_R))
      {
        restart = true;
        break;
      }
    }

    UnloadTexture(background);

    CloseWindow();
  }

  if(restart)
    restart_program();
}
