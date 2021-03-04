temp = func (x, y) : recursive {
    if (x == y) {
        print (-500);
    }
    else {
        recursive (x + 1, y);
    }
}

recursive (0, 100000);