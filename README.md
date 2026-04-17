# Break Eternity C++ Version
A recreation of break_eternity .js but instead of using javascript it uses C++, which supports numbers to 10^^(2^1024).

# All the credit goes to Patashu, the creator of Break Eternity JS. I used his project's name here.

# Information
Break-Eternity-CPP is a project made to compute numbers up to 10^^(2^1024), same as break_eternity.js.
The actual point here is that i remade it but in C++, so you can use C++ libraries with it.
When you reach above 10^^(2^1024) the text displayed is 'Omega', because after BreakEternity you GO past eternity and then reach Omega which is broken until 10{1000}10.

# Features
EternityNum struct, addition, subtraction, multiplication, division, exponentation, tetration, normalization (fixNum),
log10, pow10, natural logarithm (ln), logarithm (customizable base too), isEqual, isHigher, isLower, slog (slightly inaccurate)

# How to use
You start off by making a EternityNum struct with two double variables: the layer and the value.
To set a variable, you don't just set 1e+400, as this will result in an error and isn't a struct.
To actually make it 1e+400, you need to make {1, 400}. Why? The '1' is how much e's are there (or 10^'s) and
the 400 is the value, so {3, 300} will be eee300.
1. ADDITION: To add to a variable, you need to set x = addNum(y, z) where x, y and z are ENums (eternitynums). Put anything like {1, 10} and {0, 1000000000}, it will return ~{1, 10.04} or ~10.04F1.
2. SUBTRACTION: You get the point, it's the same with the addition, but it subtracts it. subNum(y, z) returns y - z.
3. MULTIPLICATION: here, {1, 10} and {1, 9} would result in {1, 19}, because 10^x * 10^y is always 10^(x+y).
4. POWER: {1, 10} and {1, 9} would be ee(a.v+b.v) (1e10^1e9 = ee19)
5. DIVISION: Inverted multiplication. {1, 10} and {1, 9} returns {1, 1} because 10^x / 10^y is always 10^(x-y).
6. TETRATION: It currently tetrates by 2 n times, it will be improved later. Once it's improved, i will add it here
7. LOG10: If the layer is 1 or higher, it subtracts it, if it's 0, it log10s the value.
8. POW10: This is the function that took like 30 seconds to make. It adds the layer by 1.
9. FACTORIAL: It will also be improved later, basically n! = n * n-1 * n-2 ... n times ... * 1.
10. NATURAL LOGARITHM: This is a logarithm with the base equal to 'e' (~2.71).
11. LOGARITHM: One of the 2 only functions with 1 line inside. Its formula is ln(a) / ln(b).
12. ISEQUAL: Input two variables, and depending on what you put there, it will return 0 or 1 (false or true)
13. ISHIGHER: Input two variables, and says if a > b is true or false. To recreate ">=", you need to use isHigher && isEqual for now.
14. ISLOWER: Input two variables, and it says the exact opposite of isHigher.
15. SLOG: The opposite of tetration, but it's sadly slightly inaccurate. Will be fixed later
16. EXP-FACTORIAL (NEW): This is exponential factorial, which instead of doing n*(n-1)*(n-2)... n times ...*1 it does n^(n-1)^(n-2)... n times ...^1
17. LAYER-ADD: Adds any value to the layer. (must be a double)
18. LAYER-MULTI: Multiplies the layer by a double.
19. LAYER-EXPO: Powers the layer by a double.
20. EPOW: literally pow(e, number)
21. SQRT: literally pow(number, 0.5)

# Stuff to fix
1. Slog inaccuracy: Results may be off, like it was once tested, it said ~2.84 where it had to be ~2.89.

# Extras
The code comes with a calculator, ready for you to test. If you can, tell me if there's any issues except for slog inaccuracy.
There's a Infinity detector which just returns Omega.
