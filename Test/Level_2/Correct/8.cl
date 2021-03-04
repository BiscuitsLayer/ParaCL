temp2 = func (x) : testFunc2 {
    if (x > 0) {
        return 1;
    }
}

temp1 = func (x) : testFunc1 {
    return 3 * temp2 (1);
}

print testFunc1 (5);