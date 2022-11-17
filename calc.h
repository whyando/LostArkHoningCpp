#pragma once

#include <vector>

struct StoneState {
	int SZ;	// Size of stone
	int a;		// A successes so far
	int aN;		// A attempts so far
	int b;
	int bN;
	int c;
	int cN;
	int p;
};

struct CalcResult {
	// Expected value of score function from choosing option A
	float averageScoreA;
	float averageScoreB;
	float averageScoreC;
	// Expected value of eval function from choosing option A
	std::vector<float> averageEvalA;
	std::vector<float> averageEvalB;
	std::vector<float> averageEvalC;
};

typedef float (*ScoreFn)(int, int, int);

CalcResult maximise(const StoneState s, ScoreFn score, std::vector<ScoreFn> eval);
