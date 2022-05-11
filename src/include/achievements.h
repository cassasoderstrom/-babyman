#ifndef __ACHIEVEMENTS_H__
#define __ACHIEVEMENTS_H__

/**
 * @brief Loads achievement checker
 * 
 */
void LoadAchievements(int achArr[]);

/**
 * @brief Saves achievement progress
 * 
 */
void SaveProgress(int progArr[]);

/**
 * @brief Loads achievement progress
 * 
 */
void LoadProgress(int progArr[]);

/**
 * @brief Checks for completed achievements
 * 
 * @param achArr achievements array
 * @param progArr progress array
 * @param seconds seconds for time-achievements
 * @param score score for score-achievements
 */
void CheckAchievements(int achArr[], int progArr[], int seconds, int score);

/**
 * @brief 
 * 
 */
void SaveAchievements(int achArr[]);

#endif