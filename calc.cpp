#include "calc.h"
#include <vector>

using namespace std;

// Sum of 1 <= x <= N
inline constexpr int S(int x) {
    return x * (x + 1) / 2;
}

//pair<int, int> tri_rev(int t) {
//    int x = 0;
//    for (int n = 0;; n++) {
//        if (x + n >= t)
//            return make_pair(n, t - x);
//        x += (n + 1);
//    }
//}

inline constexpr int key(const int SZ, const int a, const int aN, const int b, const int bN, const int c, const int cN, const int p) {
    const int pI = (p - 25) / 10;     constexpr int pSZ = 6;
    const int aI = S(aN) + a;         const int aSZ = S(SZ + 1);
    const int bI = S(bN) + b;         const int bSZ = S(SZ + 1);
    const int cI = S(cN) + c;         const int cSZ = S(SZ + 1);
    return pI + pSZ * (aI + aSZ * (bI + bSZ * (cI + cSZ * (0))));
}
inline constexpr int key(const StoneState stone) {
    return key(stone.SZ, stone.a, stone.aN, stone.b, stone.bN, stone.c, stone.cN, stone.p);
}


CalcResult maximise(const StoneState stone, ScoreFn score, vector<ScoreFn> eval) {
    int num_states = S(stone.SZ + 1) * S(stone.SZ + 1) * S(stone.SZ + 1) * 6;
    int num_eval_fns = eval.size();
    vector<float> X(num_states, -FLT_MAX);
    vector<vector<float>> Y(num_eval_fns, vector<float>(num_states, -FLT_MAX));

    // Assign a score to all terminal states (states with aN == bN == cN == stone.sZ )
    int count = 0;
    for (int a = 0; a <= stone.SZ; a++) {
        for (int b = 0; b <= stone.SZ; b++) {
            for (int c = 0; c <= stone.SZ; c++) {
                for (int p = 25; p <= 75; p += 10) {
                    X[key(stone.SZ, a, stone.SZ, b, stone.SZ, c, stone.SZ, p)] = score(a, b, c);
                    for(int k=0;k< num_eval_fns;k++)
                        Y[k][key(stone.SZ, a, stone.SZ, b, stone.SZ, c, stone.SZ, p)] = eval[k](a, b, c);
                }
            }
        }
    }

    const int target_k = key(stone);

    // prep ret object
    CalcResult ret;
    ret.averageEvalA = vector<float>(num_eval_fns);
    ret.averageEvalB = vector<float>(num_eval_fns);
    ret.averageEvalC = vector<float>(num_eval_fns);


    // Iterate the rest of the states
    for (int S = stone.SZ * 3 - 1; S >= 0; S--) {
        for (int aN = 0; aN <= stone.SZ; aN++) {
            for (int bN = 0; bN <= stone.SZ && aN + bN <= S; bN++) {
                int cN = S - aN - bN;
                if (cN > stone.SZ) continue;

                for (int a = 0; a <= aN; a++) {
                    for (int b = 0; b <= bN; b++) {
                        for (int c = 0; c <= cN; c++) {
                            for (int p = 25; p <= 75; p += 10) {

                                const int k = key(stone.SZ, a, aN, b, bN, c, cN, p);
                                float expA = aN == stone.SZ ? -FLT_MAX
                                    : p / 100.0 * X[key(stone.SZ, a + 1, aN + 1, b, bN, c, cN, max(25, p - 10))] + (100 - p) / 100.0 * X[key(stone.SZ, a, aN + 1, b, bN, c, cN, min(75, p + 10))];
                                float expB = bN == stone.SZ ? -FLT_MAX
                                    : p / 100.0 * X[key(stone.SZ, a, aN, b + 1, bN + 1, c, cN, max(25, p - 10))] + (100 - p) / 100.0 * X[key(stone.SZ, a, aN, b, bN + 1, c, cN, min(75, p + 10))];
                                float expC = cN == stone.SZ ? -FLT_MAX
                                    : p / 100.0 * X[key(stone.SZ, a, aN, b, bN, c + 1, cN + 1, max(25, p - 10))] + (100 - p) / 100.0 * X[key(stone.SZ, a, aN, b, bN, c, cN + 1, min(75, p + 10))];
                                float maxScore = max(expA, max(expB, expC));
                                X[k] = maxScore;

                                for (int eval_fn = 0; eval_fn < num_eval_fns; eval_fn++) {
                                    float expEvalA = aN == stone.SZ ? -FLT_MAX
                                        : p / 100.0 * Y[eval_fn][key(stone.SZ, a + 1, aN + 1, b, bN, c, cN, max(25, p - 10))] + (100 - p) / 100.0 * Y[eval_fn][key(stone.SZ, a, aN + 1, b, bN, c, cN, min(75, p + 10))];
                                    float expEvalB = bN == stone.SZ ? -FLT_MAX
                                        : p / 100.0 * Y[eval_fn][key(stone.SZ, a, aN, b + 1, bN + 1, c, cN, max(25, p - 10))] + (100 - p) / 100.0 * Y[eval_fn][key(stone.SZ, a, aN, b, bN + 1, c, cN, min(75, p + 10))];
                                    float expEvalC = cN == stone.SZ ? -FLT_MAX
                                        : p / 100.0 * Y[eval_fn][key(stone.SZ, a, aN, b, bN, c + 1, cN + 1, max(25, p - 10))] + (100 - p) / 100.0 * Y[eval_fn][key(stone.SZ, a, aN, b, bN, c, cN + 1, min(75, p + 10))];
                                    Y[eval_fn][k] = ((expA == maxScore) ? expEvalA : 0)
                                        + ((expB == maxScore) ? expEvalB : 0)
                                        + ((expC == maxScore) ? expEvalC : 0);
                                    Y[eval_fn][k] /= (expA == maxScore) + (expB == maxScore) + (expC == maxScore);

                                    if (k == target_k) {
                                        ret.averageEvalA[eval_fn] = expEvalA;
                                        ret.averageEvalB[eval_fn] = expEvalB;
                                        ret.averageEvalC[eval_fn] = expEvalC;
                                    }
                                }

                                count++;
                                if (k == target_k) {
                                    ret.averageScoreA = expA;
                                    ret.averageScoreB = expB;
                                    ret.averageScoreC = expC;
                                    return ret;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
