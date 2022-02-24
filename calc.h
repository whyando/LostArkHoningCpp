#pragma once

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
	// Expected value of eval function from choosing option A
	float averageEvalA;
	float averageScoreB;
	float averageEvalB;
	float averageScoreC;
	float averageEvalC;
};

CalcResult maximise(StoneState s, double (*score)(int, int, int), double (*eval)(int, int, int));
