fact = func(x) : factorial {
res = 1;
if (x > 0)
    res = factorial(x - 1)  * x;
res;
}

print (factorial (?));