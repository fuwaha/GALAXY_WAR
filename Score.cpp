#include "Score.h"
#include "GameSettings.h"
#include <fstream>

void Score::Reset()
{
	m_score = 0;
	m_isNewRecord = false;
	m_surviveFrame = 0;
}

void Score::AddScore(int amount)
{
	m_score += amount;
}

void Score::AddSurviveFrame()
{
	m_surviveFrame++;
}

int Score::GetScore()
{
	return m_score;
}

int Score::GetSurviveFrame()
{
	return m_surviveFrame;
}

int Score::GetSurviveSeconds()
{
	return m_surviveFrame / GameSettings::FPS;
}

int Score::GetTimeBonus()
{
	return GetSurviveSeconds() * TIME_BONUS_PER_SECOND;
}

int Score::GetTotalScore()
{
	return m_score + GetTimeBonus();
}

void Score::SaveHighScoreFile()
{
	std::ofstream file(FILE_NAME);
	if (file) file << m_highScore;
}

void Score::LoadHighScoreFile()
{
	std::ifstream file(FILE_NAME);
	if (!(file >> m_highScore))
		m_highScore = 0;
}

void Score::UpdateHighScore() 
{
	if (GetTotalScore() > m_highScore)
	{
		m_highScore = GetTotalScore();
		m_isNewRecord = true;
		SaveHighScoreFile();
	}
}

int Score::GetHighScore() 
{
	return m_highScore;
}

bool Score::IsNewRecord()
{
	return m_isNewRecord;
}