print temp (?);

temp = func (x) : factorial {
    if (x < 1)
        return 1;
    return factorial (x - 1) * x;
}