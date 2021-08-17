string operator*(const string &s, int k) {
    if (k == 0)
        return "";
    string p = (s + s) * (k / 2);
    if (k % 2 == 1)
        p += s;
    return p;
}
