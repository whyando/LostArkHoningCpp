//#include <iostream>
//#include <vector>
//#include <algorithm>
//#include <cassert>
//#include <chrono>
//
//using namespace std::chrono;
//using namespace std;
//
//const int SZ = 10;
//
//
//tuple<int, int, int, int, int, int, int> key_rev(const int k0) {
//    int k = k0;
//    const int pSZ = 6;
//    constexpr int aSZ = S(SZ + 1);
//    constexpr int bSZ = S(SZ + 1);
//    constexpr int cSZ = S(SZ + 1);
//
//    int pI = k % pSZ; k /= pSZ;
//    int aI = k % aSZ; k /= aSZ;
//    int bI = k % bSZ; k /= bSZ;
//    int cI = k % cSZ; k /= cSZ;
//
//    int p = pI*10 + 25;
//    auto [aN, a] = tri_rev(aI);
//    auto [bN, b] = tri_rev(bI);
//    auto [cN, c] = tri_rev(cI);
//
//    if (key(a, aN, b, bN, c, cN, p) != k0) {
//        throw std::exception("!");
//    }
//    return tuple<int, int, int, int, int, int, int>(a, aN, b, bN, c, cN, p);
//}
//
//int f(vector<double> &X, vector<double>& expA, vector<double>& expB, vector<double>& expC, double (*score)(int, int, int)) {
//    X = vector<double>(key(SZ, SZ, SZ, SZ, SZ, SZ, 75) + 1, -DBL_MAX);
//    expA = vector<double>(key(SZ, SZ, SZ, SZ, SZ, SZ, 75) + 1, -DBL_MAX);
//    expB = vector<double>(key(SZ, SZ, SZ, SZ, SZ, SZ, 75) + 1, -DBL_MAX);
//    expC = vector<double>(key(SZ, SZ, SZ, SZ, SZ, SZ, 75) + 1, -DBL_MAX);
//
//    int count = 0;
//    // double expA, expB, expC;
//    int a, b, c, aN, bN, cN, S, p;
//
//    S = 3 * SZ;
//    for (aN = 0; aN <= SZ; aN++) {
//        for (bN = 0; bN <= SZ && aN + bN <= S; bN++) {
//            cN = S - aN - bN;
//            if (cN > SZ) continue;
//
//            for (a = 0; a <= aN; a++) {
//                for (b = 0; b <= bN; b++) {
//                    for (c = 0; c <= cN; c++) {
//                        for (p = 25; p <= 75; p += 10)
//                            X[key(a, aN, b, bN, c, cN, p)] = score(a,b,c);
//                    }
//                }
//            }
//        }
//    }
//
//    for (S = SZ * 3 - 1; S >= 0; S--) {
//        for (aN = 0; aN <= SZ; aN++) {
//            for (bN = 0; bN <= SZ && aN + bN <= S; bN++) {
//                cN = S - aN - bN;
//                if (cN > SZ) continue;
//
//                for (a = 0; a <= aN; a++) {
//                    for (b = 0; b <= bN; b++) {
//                        for (c = 0; c <= cN; c++) {
//                            for (p = 25; p <= 75; p += 10) {
//                                const int k = key(a, aN, b, bN, c, cN, p);
//                                expA[k] = aN == SZ ? -DBL_MAX
//                                    : p / 100.0 * X[key(a + 1, aN + 1, b, bN, c, cN, max(25, p - 10))] + (100 - p) / 100.0 * X[key(a, aN + 1, b, bN, c, cN, min(75, p + 10))];
//                                expB[k] = bN == SZ ? -DBL_MAX
//                                    : p / 100.0 * X[key(a, aN, b + 1, bN + 1, c, cN, max(25, p - 10))] + (100 - p) / 100.0 * X[key(a, aN, b, bN + 1, c, cN, min(75, p + 10))];
//                                expC[k] = cN == SZ ? -DBL_MAX
//                                    : p / 100.0 * X[key(a, aN, b, bN, c + 1, cN + 1, max(25, p - 10))] + (100 - p) / 100.0 * X[key(a, aN, b, bN, c, cN + 1, min(75, p + 10))];
//                                X[k] = max(expA[k], max(expB[k], expC[k]));
//                                count++;
//                            }
//                        }
//                    }
//                }
//            }
//        }
//    }
//    return key(SZ, SZ, SZ, SZ, SZ, SZ, 75) + 1;
//}
//
//// prob starts at 75
//bool reachable(int X, int N, int prob) {
//    int dp = 5 - ((prob - 25) / 10);
//    // just need to 'fail enough'
//    return N - X >= dp;
//}
//
//int main()
//{
//    auto start = high_resolution_clock::now();
//
//    vector<double> strat1_expScore, strat1_expA, strat1_expB, strat1_expC;
//    int count = f(strat1_expScore, strat1_expA, strat1_expB, strat1_expC, [](int a, int b, int c) {
//        return (double)(a);
//    });
//    cout << count << endl;
//
//    vector<double> strat2_expScore, strat2_expA, strat2_expB, strat2_expC;
//    f(strat2_expScore, strat2_expA, strat2_expB, strat2_expC, [](int a, int b, int c) {
//        return ((a >= 8) ? 100.0 : 0.0);
//    });
//
//    for (int i = 0; i <= key(SZ, SZ, SZ, SZ, SZ, SZ, 75); i++) {
//        auto [a, aN, b, bN, c, cN, p] = key_rev(i);
//        if (!reachable(a + b + c, aN + bN + cN, p)) continue;
//        bool strat1_hatesA = (strat1_expA[i] < strat1_expB[i] || strat1_expA[i] < strat1_expC[i]);
//        bool strat1_hatesB = (strat1_expB[i] < strat1_expA[i] || strat1_expB[i] < strat1_expC[i]);
//        bool strat1_hatesC = (strat1_expC[i] < strat1_expA[i] || strat1_expC[i] < strat1_expB[i]);
//        bool strat2_hatesA = (strat2_expA[i] < strat2_expB[i] || strat2_expA[i] < strat2_expC[i]);
//        bool strat2_hatesB = (strat2_expB[i] < strat2_expA[i] || strat2_expB[i] < strat2_expC[i]);
//        bool strat2_hatesC = (strat2_expC[i] < strat2_expA[i] || strat2_expC[i] < strat2_expB[i]);
//
//        // if all options are 'hated', we have contradicting outcomes
//        if (((strat1_hatesA|| strat2_hatesA) + (strat1_hatesB || strat2_hatesB) + (strat1_hatesC || strat2_hatesC)) == 3) {
//            cout << "contradict:" << a << "/" << aN << " " << b << "/" << bN << " " << c << "/" << cN << "\t" << p << "%" << endl;
//            cout << "strat1:" << strat1_expA[i] << " (" << strat1_expA[i] - strat1_expScore[i] << ") "
//                << strat1_expB[i] << " (" << strat1_expB[i] - strat1_expScore[i] << ") "
//                << strat1_expC[i] << " (" << strat1_expC[i] - strat1_expScore[i] << ") " << endl;
//            cout << "strat2:" << strat2_expA[i] << " (" << strat2_expA[i] - strat2_expScore[i] << ") "
//                << strat2_expB[i] << " (" << strat2_expB[i] - strat2_expScore[i] << ") "
//                << strat2_expC[i] << " (" << strat2_expC[i] - strat2_expScore[i] << ") " << endl;
//        }
//    }
//
//    auto stop = high_resolution_clock::now();
//    auto duration = duration_cast<milliseconds>(stop - start);
//    cout << duration.count() << "ms" << endl;
//}
