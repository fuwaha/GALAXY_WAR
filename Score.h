#pragma once

// スコアと生存時間を持つクラス
// シーンを切り替えるとInGameSceneは作り直されて中身が消えるので、static で持ってどのシーンからも読めるようにする
class Score
{
public:
	static void Reset();				// スコアと生存時間を0に戻す(InGameInitで呼ぶ)
	static void AddScore(int amount);	// スコアを足す(敵を倒したときなど)
	static void AddSurviveFrame();		// 生存時間を1フレーム進める(ゲーム中に毎フレーム呼ぶ)

	static int GetScore();				// 今のスコア(撃破点だけ。生存時間ボーナスは入っていない)
	static int GetSurviveFrame();		// 生き残ったフレーム数
	static int GetSurviveSeconds();		// 生き残った秒数(端数は切り捨て)
	static int GetTimeBonus();			// 生存時間ボーナス(秒数×TIME_BONUS_PER_SECOND)
	static int GetTotalScore();			// 最終スコア(スコア+生存時間ボーナス)

	static void SaveHighScoreFile();    //ハイスコアをファイルに保存(ファイルがなければ生成)
	static void LoadHighScoreFile();    //ハイスコアを保存しているファイルを読み込む、ゲーム起動時に一回だけ実行
	static void UpdateHighScore();      //ハイスコアを更新、ファイルも一緒に更新する、新記録なら更新
	static int GetHighScore();          //現在のハイスコアを返す
	static bool IsNewRecord();          //m_isNewRecordを返す

	static const int TIME_BONUS_PER_SECOND = 10;	// 1秒生き残るごとのボーナス点

private:
	static inline int m_score = 0;			// スコアの合計
	static inline int m_highScore = 0;      //ハイスコア
	static inline int m_surviveFrame = 0;	// 生き残ったフレーム数、秒数に変換したあとスコアに加算する

	static inline bool m_isNewRecord = false;

	static constexpr const char* FILE_NAME = "HighScore.txt"; //ハイスコアを保存しておくファイル
};
