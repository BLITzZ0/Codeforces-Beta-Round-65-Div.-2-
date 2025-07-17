#include <bits/stdc++.h>
using namespace std;

unordered_map<string, int> symbolToNumber = {
    {"H",1},{"He",2},{"Li",3},{"Be",4},{"B",5},{"C",6},{"N",7},{"O",8},{"F",9},{"Ne",10},
    {"Na",11},{"Mg",12},{"Al",13},{"Si",14},{"P",15},{"S",16},{"Cl",17},{"Ar",18},{"K",19},{"Ca",20},
    {"Sc",21},{"Ti",22},{"V",23},{"Cr",24},{"Mn",25},{"Fe",26},{"Co",27},{"Ni",28},{"Cu",29},{"Zn",30},
    {"Ga",31},{"Ge",32},{"As",33},{"Se",34},{"Br",35},{"Kr",36},{"Rb",37},{"Sr",38},{"Y",39},{"Zr",40},
    {"Nb",41},{"Mo",42},{"Tc",43},{"Ru",44},{"Rh",45},{"Pd",46},{"Ag",47},{"Cd",48},{"In",49},{"Sn",50},
    {"Sb",51},{"Te",52},{"I",53},{"Xe",54},{"Cs",55},{"Ba",56},{"La",57},{"Ce",58},{"Pr",59},{"Nd",60},
    {"Pm",61},{"Sm",62},{"Eu",63},{"Gd",64},{"Tb",65},{"Dy",66},{"Ho",67},{"Er",68},{"Tm",69},{"Yb",70},
    {"Lu",71},{"Hf",72},{"Ta",73},{"W",74},{"Re",75},{"Os",76},{"Ir",77},{"Pt",78},{"Au",79},{"Hg",80},
    {"Tl",81},{"Pb",82},{"Bi",83},{"Po",84},{"At",85},{"Rn",86},{"Fr",87},{"Ra",88},{"Ac",89},{"Th",90},
    {"Pa",91},{"U",92},{"Np",93},{"Pu",94},{"Am",95},{"Cm",96},{"Bk",97},{"Cf",98},{"Es",99},{"Fm",100}
};

unordered_map<int, string> numberToSymbol;

int n, k;
vector<string> startSymbols, targetSymbols;
vector<int> startAtoms, targetAtoms;

// Store all subsets that sum to a target value
unordered_map<int, vector<int>> targetToSubsets;

bool solve(int mask, int idx, vector<int>& selectedMasks, vector<int>& targetAtoms) {
    if (idx == targetAtoms.size()) return mask == (1 << n) - 1;

    int target = targetAtoms[idx];

    for (int subset : targetToSubsets[target]) {
        if ((mask & subset) == 0) { // Disjoint
            selectedMasks.push_back(subset);
            if (solve(mask | subset, idx + 1, selectedMasks, targetAtoms))
                return true;
            selectedMasks.pop_back();
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    for (auto& p : symbolToNumber)
        numberToSymbol[p.second] = p.first;

    cin >> n >> k;
    startSymbols.resize(n);
    targetSymbols.resize(k);
    startAtoms.resize(n);
    targetAtoms.resize(k);

    for (int i = 0; i < n; ++i) {
        cin >> startSymbols[i];
        startAtoms[i] = symbolToNumber[startSymbols[i]];
    }

    for (int i = 0; i < k; ++i) {
        cin >> targetSymbols[i];
        targetAtoms[i] = symbolToNumber[targetSymbols[i]];
    }

    if (accumulate(startAtoms.begin(), startAtoms.end(), 0) != accumulate(targetAtoms.begin(), targetAtoms.end(), 0)) {
        cout << "NO\n";
        return 0;
    }

    // Generate all subsets and their sums
    for (int mask = 1; mask < (1 << n); ++mask) {
        int sum = 0;
        for (int i = 0; i < n; ++i)
            if (mask & (1 << i))
                sum += startAtoms[i];

        // Only keep masks that match some target
        if (find(targetAtoms.begin(), targetAtoms.end(), sum) != targetAtoms.end()) {
            targetToSubsets[sum].push_back(mask);
        }
    }

    vector<int> selectedMasks;
    if (!solve(0, 0, selectedMasks, targetAtoms)) {
        cout << "NO\n";
        return 0;
    }

    cout << "YES\n";
    vector<bool> used(n, false);

    for (int i = 0; i < k; ++i) {
        int mask = selectedMasks[i];
        string equation = "";
        for (int j = 0; j < n; ++j) {
            if (mask & (1 << j)) {
                if (!equation.empty()) equation += "+";
                equation += startSymbols[j];
                used[j] = true;
            }
        }
        equation += "->" + targetSymbols[i];
        cout << equation << "\n";
    }

    return 0;
}


// // E. Nuclear Fusion
// time limit per test1.5 seconds
// memory limit per test256 megabytes
// There is the following puzzle popular among nuclear physicists.

// A reactor contains a set of n atoms of some chemical elements. We shall understand the phrase "atomic number" as the number of this atom's element in the periodic table of the chemical elements.

// You are allowed to take any two different atoms and fuse a new one from them. That results in a new atom, whose number is equal to the sum of the numbers of original atoms. The fusion operation can be performed several times.

// The aim is getting a new pregiven set of k atoms.

// The puzzle's difficulty is that it is only allowed to fuse two atoms into one, it is not allowed to split an atom into several atoms. You are suggested to try to solve the puzzle.

// Input
// The first line contains two integers n and k (1 ≤ k ≤ n ≤ 17). The second line contains space-separated symbols of elements of n atoms, which are available from the start. The third line contains space-separated symbols of elements of k atoms which need to be the result of the fusion. The symbols of the elements coincide with the symbols from the periodic table of the chemical elements. The atomic numbers do not exceed 100 (elements possessing larger numbers are highly unstable). Some atoms can have identical numbers (that is, there can be several atoms of the same element). The sum of numbers of initial atoms is equal to the sum of numbers of the atoms that need to be synthesized.

// Output
// If it is impossible to synthesize the required atoms, print "NO" without the quotes. Otherwise, print on the first line «YES», and on the next k lines print the way of synthesizing each of k atoms as equations. Each equation has the following form: "x1+x2+...+xt->yi", where xj is the symbol of the element of some atom from the original set, and yi is the symbol of the element of some atom from the resulting set. Each atom from the input data should occur in the output data exactly one time. The order of summands in the equations, as well as the output order does not matter. If there are several solutions, print any of them. For a better understanding of the output format, see the samples.

// Examples
// InputCopy
// 10 3
// Mn Co Li Mg C P F Zn Sc K
// Sn Pt Y
// OutputCopy
// YES
// Mn+C+K->Sn
// Co+Zn+Sc->Pt
// Li+Mg+P+F->Y
// InputCopy
// 2 1
// H H
// He
// OutputCopy
// YES
// H+H->He
// InputCopy
// 2 2
// Bk Fm
// Cf Es
// OutputCopy
// NO
// Note
// The reactions from the first example possess the following form (the atomic number is written below and to the left of the element):







// To find a periodic table of the chemical elements, you may use your favorite search engine.

// The pretest set contains each of the first 100 elements of the periodic table at least once. You can use that information to check for misprints.

