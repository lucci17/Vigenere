#include <iostream>
#include <fstream>
#include <clocale>
#include <windows.h>

using namespace std;
char spec[] = {'å','ä','ö',' ',',','.','Å','Ä','Ö'};
int spe[9];
int out[3000];
char en_out[3000];
int key[16];
int k_pos = 0;
int pos = 0;

string r;

int chg(char a)
{
    int k = a - 'a';
    if(k < 26 && k >= 0)
        return k;
    if(k < -6 && k >= -32)
        return k + 32;
    for(int i = 0;i < 6;i++)
    {
        if(k == spe[i])
            return i + 26;
    }
    for(int i = 6;i < 9;i++)
    {
        if(k == spe[i])
            return i + 20;
    }
    return -1;
}

char encpt(int a,int b)
{
    int c = (a + b) % 32;
    if(c < 26 && c >= 0)
        return c + 'a';
    if(c < 32 && c >= 26)
        return spec[c-26];
    return 0;
}

int main()
{
    setlocale(LC_ALL, "swedish");
    //SetConsoleOutputCP(1252);
    for(int i = 0;i < 9;i++)
    {
        spe[i] = spec[i] - 'a';
    }
    fstream fin;
    fstream fkey;
    fstream fout;
    fstream fplain;
    fin.open("text.txt",ios::in);
    fkey.open("vig_group07.key");
    fout.open("vig_group07.crypto",ios::out);
    fplain.open("vig_group07.plain",ios::out);
    while(!fin.eof())
    {
        fin>>r;
        for(int i = 0; i < r.length();i++)
        {
            int if_w = 0;
            int k = r[i] - 'a';
            if(k < -6 && k >= -32)
            {
                char a = 'a' + k +32;
                fplain << (a);
                if_w = 1;
            }
            for(int i = 6;i < 9;i++)
            {
                if(k == spe[i])
                {
                    fplain << spec[i-6];
                    if_w = 1;
                }
            }
            int j = chg(r[i]);
            if(j != -1)
            {
                if(!if_w)
                    fplain<<r[i];
                out[pos] = j;
                pos++;
            }
        }
        fplain<<" ";
        out[pos] = 29;
        pos++;
    }
    while(!fkey.eof())
    {
        fkey>>r;
        for(int i = 0; i < r.length();i++)
        {
            int j = chg(r[i]);
            if(j != -1)
            {
                key[k_pos] = j;
                k_pos++;
            }
        }
    }
    cout << pos <<endl;
    cout << k_pos <<endl;
    for(int i = 0;i < k_pos;i++)
    {
        cout<<key[i]<<' ';
    }
    for(int i = 0;i < pos;i++)
    {
        en_out[i] = encpt(out[i],key[i % 10]);
        fout<<en_out[i];
    }
    fin.close();
    fout.close();
    fkey.close();
    cout<<spec[1]<<endl;
    return 0;
}
