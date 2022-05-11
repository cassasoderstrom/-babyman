#ifndef __SCORE_H__
#define __SCORE_H__

void SaveToFile(int scoreArr[5]);
void ReadFromFile(int scoreArr[5]);
int sortScore (const void * a, const void * b);
void AddScore(int scoreArr[5], int score);

#endif