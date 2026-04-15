//Eternity Calculator (Specified limit: F2147483647)
//v0.15
//slog

//V0?: ETERNITYNUM SETUP | V0.1: ADDITION | V0.2: MULTIPLICATION | V0.3: POWER
//V0.4: TETRATION (V1) | V0.5: TETRATION (V2) | V0.6: FIXNUM + BUGFIXES | V0.7: LOG10, POW10, O(1) TETRATION
//V0.8: SUBTRACTION | V0.9: DIVISION | V0.10: NATURAL LOGARITHM | V0.11: LOGARITHM
//V0.12: ISEQUAL | V0.13: ISHIGHER | V0.14: ISLOWER | V0.15: SLOG (V1)

//Upcoming: factorials

#include <iostream>
#include <sstream> //ayo, is this include sodastream??
#include <cmath>
#include <algorithm>
#include <string>
#include <iomanip>
using namespace std;

struct ENum {
    double l;
    double v;
};

//OTHER CONCEPTS
//BracketNum: A concept designed to compute numbers up to 10{1.79e308}10
//Same as the BigNum calc, it uses 16 bytes for one.
//The BracketNum, instead of using like OmegaNum (1000-slot arrays), which takes 8000 bytes (MAX) per value
//it uses the same concept for storing like OmegaNum but with 5 slots as the difference between I2H200G133F123 and I2H200G133Fe123 doesn't matter at this point
//because it's so small incremental games would definetly increase this. If there's like I1e10 i change this

//struct ONum {
//  int op;
//  double v;
//  double l[] = {0, 0, 0, 0, 0};
//  double la[] = {0, 0, 0, 0, 0}; //amount for each layer

//}

//Use for some other stuff, NOT recommended to delete.
ENum e = {0, 2.71828182846};
ENum pi = {0, 3.14159265359};

// Examples:
// {0, 1} = 1
// {0, 1e6} = 1e6
// {1, 1} = e1
// {1, 999} = e999
// {2, 308.3} = ee308.3
// {inf, v} = Omega (Broken Eternities' Infinity)
// {l, inf} = {l+1, 308} (einf or e(1.79e+308) = ee308)

//RETURN NUMBER
string returnNum(ENum definedNumber) {
    ostringstream oss;
      oss << fixed << setprecision(10) << "\033[33m~" << definedNumber.v
      << "F"
      << setprecision(0) << definedNumber.l << "\033[0m";
      return oss.str();
    //old: return "{" + to_string(definedNumber.l) + ", " + to_string(definedNumber.v) + "}";
}

//FIX NUMBER (if 1e11F11 happens for example)
ENum fixNum(ENum& n){
    while(n.v >= 1e10){
        n.v = log10(n.v);
        n.l++;
    }
    while(n.v < 1){
        n.v = pow(10, n.v);
        n.l--;
    }
    return n;
}

//ADDITION
ENum addNum(const ENum& a, const ENum& b) {
    //IF LAYERS ARE 1 AND 0 (example: {0, 9.99e9} + {1, 10} will be {1, 10})
    if (a.l == 0 && b.l == 1) {
        double av = log10(a.v);
        return addNum({1, av}, b);
    }
    if (a.l == 1 && b.l == 0) {
        double bv = log10(b.v);
        return addNum(a, {1, bv});
    }
    //IF LAYER IS BIGGER THAN ANOTHER
    if(a.l > b.l) return a;
    if(b.l > a.l) return b;
    //IF LAYER A = 0
    if(a.l==0){
        ENum result = {a.l, a.v + b.v};
        return fixNum(result);
    }
    //IF LAYER A IS 1 OR HIGHER (as layer 0 already returns)
    double dif = abs(a.v - b.v);
    if (dif > 10.0) {
        return (a.v > b.v) ? a : b;
    }
    //IF LAYER A IS 1
    if (a.l == 1) {
        double result = max(a.v, b.v) + log10((double)1 + pow((double)10, min(a.v, b.v) - max(a.v, b.v)));
        return {1, result};
    }

    //IF LAYER A IS 2 OR HIGHER (difference is almost nothing so we do not care)
    return (a.v > b.v) ? a : b;
}

ENum subNum(const ENum& a, const ENum& b){
    // if equal
    if(a.l == b.l && a.v == b.v) return {0, 0};
    if(a.l < b.l) return {0, 0};
    if(a.l == b.l && a.v < b.v) return {0, 0};
    // layer 0
    if(a.l == 0 && b.l == 0){
        ENum result = {0, a.v - b.v};
        return fixNum(result);
    }
    // layer 1 
    if(a.l == 1 && b.l == 1){
        double dif = a.v - b.v;
        if(dif > 10) return a;
        double result = a.v + log10(1.0 - pow(10.0, b.v - a.v));
        return {1, result};
    }
    // different layers
    if(a.l > b.l) return a;
    return a;
}

//MULTIPLY
ENum mulNum(const ENum& a, const ENum& b){
    //IF BOTH ARE 0 (prevent log10(0))
    if(a.l == 0 && a.v == 0) return {0, 0};
    if(b.l == 0 && b.v == 0) return {0, 0};
    //LAYER 0+0
    if(a.l==0 && b.l==0){ ENum result = {a.l, a.v * b.v};
    return fixNum(result); }
    //LAYER 0+1
    if(a.l==0 && b.l==1){
        double av = log10(a.v);
        return mulNum({1, av}, b);
    }
    //LAYER 1+0
    if (a.l == 1 && b.l == 0) {
        double bv = log10(b.v);
        return mulNum(a, {1, bv});
    }
    //LAYER 1+1
    if(a.l==1 && b.l==1){ return {a.l, a.v + b.v}; } //1, 5 * 1, 5 would return 1, 5+5 (1, 10)
    //DIFFERENT LAYERS (example: 2+1, 3+28)
    if(a.l > b.l) return a;
    if(b.l > a.l) return b;
    //LAYER 2+ and 2+
    if(a.v > b.v) return a;
    if(b.v > a.v) return b;
    return a;
}

ENum divNum(const ENum& a, const ENum& b){
    if(b.l == 0 && b.v == 0) throw runtime_error("Division by zero");
    if(a.l == 0 && b.l == 0){
        ENum result = {0, a.v / b.v};
        return fixNum(result);
    }
    if(a.l == 0 && b.l == 1) return {0, 0};
    if(a.l == 1 && b.l == 0){
        double bv = log10(b.v);
        return {1, a.v - bv};
    }
    if(a.l == 1 && b.l == 1) return {1, a.v - b.v};
    if(a.l > b.l) return a;
    if(b.l > a.l) return {0, 0};
    ENum c = {0, 0};
    return (a.v > b.v) ? a : c;
}

ENum powNum(const ENum& a, const ENum& b){
    ENum exponentPart = {0, b.v};
    ENum logPart = {0, log10(a.v)};
    ENum logR; //changed from double to ENum for higher powers
    //LAYER 0+0
    if(a.l == 0 && b.l == 0){
        logR = mulNum({0, b.v}, {0, log10(a.v)});
        if(logR.l == 0 && logR.v <= 308){
            ENum result = {0, pow(a.v, b.v)};
            return fixNum(result);
        }else{
            ENum result = {logR.l + 1, logR.v};
            return fixNum(result);
        }
    }
    //LAYER 1+0
    if(a.l == 1 && b.l == 0) return {1, a.v * b.v};
    //LAYER 0+1
    logR = mulNum({1, b.v}, {0, log10(a.v)});
    if(a.l == 0 && b.l == 1) return {logR.l + 1, logR.v};
    //LAYER 1+1
    logR = mulNum({0, a.v}, {1, b.v});
    if(a.l == 1 && b.l == 1) return {logR.l + 1, logR.v};
    //LAYER 2+ CASES
    if(a.l >= 1 && b.l >= 1){
        return {max(a.l, b.l) + 1, max(a.v, b.v)};
    }   
    //DIFFERENT LAYERS
    if(a.l > b.l) return a;
    if(b.l > a.l) return b;
    //SAME LAYERS ABOVE 2
    return (a.v > b.v) ? a : b;
}

//TETRATION (O(1))
ENum tetrateNum(const ENum& a, double b){
    if(b <= 1) return a;
    ENum result = a;
    //SMALL VALUES
    if(b < 10 && a.l == 0){
        for(int i = 1; i < (int)b; i++){
            result = powNum(a, result);
            result = fixNum(result);
        }
        return result;
    }
    //BIG VALUES
    result.l += (b - 1);
    result.v += log10((double)b);
    return result;
}

ENum log10Num(const ENum& n) {
    if (n.l == 0) return {0, log10(n.v)};
    return {n.l - 1, n.v};
}

ENum pow10Num(const ENum& n){
    return {n.l+1, n.v};
}

ENum factNum(const ENum& a){
    // negative check
    if(a.v < 0) return {0, 0};
    // 0! and 1!
    if(a.l == 0 && a.v <= 1) return {0, 1};
    if(a.l == 0){
        double n = floor(a.v);

        if(n < 20){
            double result = 1;
            for(int i = 2; i <= n; i++){
                result *= i;
            }
            return {0, result};
        }

        // Stirling (log10 form)
        double logResult =
            n * log10(n / exp(1.0))
            + 0.5 * log10(2.0 * 3.14159265358979323846 * n);

        ENum problemBypass = {1, logResult};
        return fixNum(problemBypass);
    }
    ENum result = a;
    double add = log10(result.v);

    if(result.l == 1){
        result.v *= add;
    } else {
        result.v += add;
    }
    return result; //return fixNum(result);
}

ENum lnNum(const ENum& a){
    //IF A IS 0
    if(a.l == 0) return {0, log(a.v)};
    //IF A IS 1
    if(a.l == 1) return {0, a.v * log(10)};
    //IF A IS 2 OR ABOVE
    return {a.l - 1, a.v + log10(log(10))};
}

ENum logBaseNum(const ENum& a, const ENum& b){
    return divNum(lnNum(a), lnNum(b)); //a = 100 and b = 10 = div(4.60517018599 / ~2.30) = 2
}

bool isEqual(ENum a, ENum b){
    if(a.l != b.l) return false;
    if(a.v != b.v) return false;
    return true;
}

bool isHigher(ENum a, ENum b){
    if(a.l > b.l) return true;
    if(a.v > b.v && a.l == b.l) return true;
    return false;
}

bool isLower(ENum a, ENum b){
    if(a.l < b.l) return true;
    if(a.v < b.v && a.l == b.l) return true;
    return false;
}

ENum slogNum(ENum a){ //NOT ACCURATE, TESTED ON {2, 3} AND RETURNED 2.84 INSTEAD OF 2.89.
    double b = log10(log(10));
    return {0, a.l + log10(a.v) + b};
}

//space for exponential factorial (expfact) here
//space for super logarithm (slog) here
//space for user input to value (example: ee27 = {2, 27}) here

//INPUTS: 
//V = {0, V}
//eV = {1, V}, eeV = {2, V}, eeeV = {3, V}, VFL = {L, V}, VFeL = {pow10(L), V}

ENum num{2, 3}; //11^1000... huh... this is like ee1100
ENum testnum{0, 1000};
//\033[32m
int main() {
    while(1){
        int inputIDK;
        double dbl;
        cout << "1-add, 2-mul, 3-pow, 4-tetrate, 5-sub, 6-div, 7-log10, 8-pow10, 9-fact, 10-ln, 11-logbase, 12-isequal" << endl;
        cin >> inputIDK;
        cout << "Number A Value: ";
        cin >> num.v;
        cout << "Number A Layer: ";
        cin >> num.l;
        if(!(inputIDK == 9)){
            cout << "Number B Value: ";
            cin >> testnum.v;
            cout << "Number B Layer: ";
            cin >> testnum.l;
            cout << "Double value for tetration: ";
            cin >> dbl;
        }
        switch(inputIDK){
            case 1: num = addNum(num, testnum); break;
            case 2: num = mulNum(num, testnum); break;
            case 3: num = powNum(num, testnum); break;
            case 4: num = tetrateNum(num, dbl); break;
            case 5: num = subNum(num, testnum); break;
            case 6: num = divNum(num, testnum); break;
            case 7: num = log10Num(num); break;
            case 8: num = pow10Num(num); break;
            case 9: num = factNum(num); break;
            case 10: num = lnNum(num); break;
            case 11: num = logBaseNum(num, testnum); break;
            case 12: isEqual(num, testnum); break;
            default: cout<<"invalid"<<endl;
        }
        cout<<returnNum(num)<<endl;
    }
} //{1, 10} = ee11