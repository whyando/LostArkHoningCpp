// main

#include <iostream>
#include "calc.h"

using namespace std;

int main() {
	StoneState s = { 10, 0, 0, 0, 0, 0, 0, 75 };
	CalcResult ret = maximise(s, [](int a, int b, int c) {
		return (float)(a);
	},
	{
		[](int a, int b, int c) { return (float)(a); },
		[](int a, int b, int c) { return (float)(b); },
		[](int a, int b, int c) { return (float)(c); },
	});

	cout << "A: " << ret.averageScoreA << " " << ret.averageEvalA[0] << " " << ret.averageEvalA[1] << " " << ret.averageEvalA[2] << endl;
	cout << "B: " << ret.averageScoreB << " " << ret.averageEvalB[0] << " " << ret.averageEvalB[1] << " " << ret.averageEvalB[2] << endl;
	cout << "C: " << ret.averageScoreC << " " << ret.averageEvalC[0] << " " << ret.averageEvalC[1] << " " << ret.averageEvalC[2] << endl;

	return 0;
}
