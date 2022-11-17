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
//inline constexpr int S(int x) {
//    return x * (x + 1) / 2;
//}
//
//pair<int, int> tri_rev(int t) {
//    int x = 0;
//    for (int n = 0;; n++) {
//        if (x + n >= t)
//            return make_pair(n, t - x);
//        x += (n + 1);
//    }
//}
//
//int eval_heuristic(const int a, const int aN, const int b, const int bN, const int c, const int cN, const int p) {
//    float scoreA, scoreB, scoreC;
//    if (p >= 65) { // A > B > C
//        scoreA = 2;
//        scoreB = 1;
//        scoreC = 0;
//    }
//    else if (p >= 55) { // B > A > C
//        scoreA = 1;
//        scoreB = 2;
//        scoreC = 0;
//    }
//    else {              // C > B > A
//        scoreA = 0;
//        scoreB = 1;
//        scoreC = 2;
//    }
//    if (aN == SZ) scoreA = -1;
//    if (bN == SZ) scoreB = -1;
//    if (cN == SZ) scoreC = -1;
//    if (scoreA > scoreB && scoreA > scoreC)
//        return 0;
//    if (scoreB > scoreC)
//        return 1;
//    return 2;
//}
//
//void sim_step(const int choice, int &a, int &aN, int &b, int &bN, int &c, int &cN, int &p) {
//    bool success = (rand() % 100) < p;
//    if (choice == 0) {
//        aN++; a += success;
//    } else if (choice == 1) {
//        bN++; b += success;
//    } else if (choice == 2) {
//        cN++; c += success;
//    }
//    if(success)
//        p = max(25, p - 10);
//    else
//        p = min(75, p + 10);
//}
//
//inline constexpr int key(const int a, const int aN, const int b, const int bN, const int c, const int cN, const int p) {
//    const int pI = (p - 25) / 10;     constexpr int pSZ = 6;
//    const int aI = S(aN) + a;         const int aSZ = S(SZ + 1);
//    const int bI = S(bN) + b;         const int bSZ = S(SZ + 1);
//    const int cI = S(cN) + c;         const int cSZ = S(SZ + 1);
//    return pI + pSZ * (aI + aSZ * (bI + bSZ * (cI + cSZ * (0))));
//}
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
//    srand(0);
//    // srand(time(NULL));
//
//    auto start = high_resolution_clock::now();
//
//    vector<double> strat1_expScore, strat1_expA, strat1_expB, strat1_expC;
//    int count = f(strat1_expScore, strat1_expA, strat1_expB, strat1_expC, [](int a, int b, int c) {
//        return ((a >= 7 && b >= 7 && c <= 4) ? 100.0 : 0.0);
//    });
//    cout << count << endl;
//
//    vector<double> strat2_expScore, strat2_expA, strat2_expB, strat2_expC;
//    f(strat2_expScore, strat2_expA, strat2_expB, strat2_expC, [](int a, int b, int c) {
//        return ((a >= 7 && b >= 7 && c <= 4) ? 100.0 : 0.0);
//    });
//
//    //vector<double> strat2_expScore, strat2_expA, strat2_expB, strat2_expC;
//    //f(strat2_expScore, strat2_expA, strat2_expB, strat2_expC, [](int a, int b, int c) {
//    //    return ((a >= 8) ? 100.0 : 0.0);
//    //});
//
//    for (int i = 0; i <= key(SZ, SZ, SZ, SZ, SZ, SZ, 75); i++) {
//        auto [a, aN, b, bN, c, cN, p] = key_rev(i);
//        if (!reachable(a + b + c, aN + bN + cN, p)) continue;
//
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
//
//
//
//    auto start1 = high_resolution_clock::now();
//
//    // Sim the heuristic method
//    int64_t sumA = 0, sumB=0, sumC=0;
//    int64_t num_disagree = 0;
//    int64_t num_tick_disagree = 0;
//    int64_t total_tick = 0;
//    int64_t num_774 = 0;
//    const int T = 10000000;
//    for (int t = 0; t < 10000000; t++) {
//        int a = 0, b = 0, c = 0;
//        int aN = 0, bN = 0, cN = 0;
//        int p = 75;
//
//        bool disagree = false;
//        while (!(aN == SZ && bN == SZ && cN == SZ)) {
//            auto choice = eval_heuristic(a, aN, b, bN, c, cN, p);
//            const int k = key(a, aN, b, bN, c, cN, p);
//            bool tick_disagree = false;
//            if (choice == 0 && (strat1_expA[k] < strat1_expB[k] || strat1_expA[k] < strat1_expC[k]))
//                tick_disagree = true;
//            if (choice == 1 && (strat1_expB[k] < strat1_expA[k] || strat1_expB[k] < strat1_expC[k]))
//                tick_disagree = true;
//            if (choice == 2 && (strat1_expC[k] < strat1_expA[k] || strat1_expC[k] < strat1_expB[k]))
//                tick_disagree = true;
//            num_tick_disagree += tick_disagree;
//            total_tick += 1;
//            if (tick_disagree) disagree = true;
//            sim_step(choice, a, aN, b, bN, c, cN, p);
//        }
//        // cout << a << "/" << b << "/" << c << endl;
//        sumA += a; sumB += b; sumC += c;
//        num_disagree += disagree;
//        if (a >= 7 && b >= 7 && c <= 4)
//            num_774++;
//    }
//    cout << ((double)sumA/T) << "/" << ((double)sumB / T) << "/" << ((double)sumC / T) << endl;
//    cout << (double)num_disagree/T*100 << "%" << endl;
//    cout << (double)num_tick_disagree / total_tick * 100 << "%" << endl;
//    cout << (double)num_774 / T * 100 << "%" << endl;
//    auto stop1 = high_resolution_clock::now();
//    auto duration1 = duration_cast<milliseconds>(stop1 - start1);
//    cout << duration1.count() << "ms" << endl;
//}
