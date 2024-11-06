#ifndef SCREEN_H
#define SCREEN_H

void screenInit(int drawBorders);
void screenClear();
void screenSetCharAt(int x, int y, char c);
void screenGotoxy(int x, int y);
void screenUpdate();
void screenHideCursor();
void screenShowCursor();

#endif /* SCREEN_H */
