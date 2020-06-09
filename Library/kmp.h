#require N
int nxt[N];
int kmp(string& s)
{
    int i = 0, j = -1, len = s.size();
    nxt[i] = j;
    while(i < len)
    {
        if(j == -1 or s[i] == s[j])
        {
            i++;
            j++;
            nxt[i] = j;
        }
        else j = nxt[j];
    }
    return nxt[len];
}
/*
    longest palindromic suffix and prifix using KMP.
    string s = "sasmplolol";
    string t = s;
    reverse(t.begin(), t.end());
    string a = s + "#" + t;
    string b = t + "#" + s;
    string p = a.substr(0, kmp(a));
    string q = b.substr(0, kmp(b));
    if(len(p) < len(q)) 
        cout << t1 << q << t2 << endl;
    else
        cout << t1 << p << t2 << endl;
*/