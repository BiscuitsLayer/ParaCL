a = ?;
mod = 0;
i = 1;
k = 0;

while (i <= a) {
    k = a / i;
    mod = a - k * i;
    if (mod == 0) {
        print i;
    }
    i = i + 1;
}