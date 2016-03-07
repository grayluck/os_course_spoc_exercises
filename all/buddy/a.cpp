/*
 * Buddy System Memory Allocation Algorithm
 * By Gerald Yankai Zhang
 * 7:00 PM, March 7th, 2014
 */

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>

#define min(a, b) ((a) < (b) ? (a) : (b))

using namespace std;

typedef unsigned int uint;

const int maxn = 100001;
const int maxEntry = 20;
const int initialPageNum = 1024;

int fir[maxn], next[maxn], con = 0;

int gn;
struct Block {
    uint addr, siz;
}   g[maxn], t[maxn];

void delline(int st, int addr) {
    for(int i = fir[st], last = -1; i; last = i, i = next[i]) {
        if(t[i].addr == addr) {
            next[last] = next[i];
            if(last == -1)
                fir[st] = next[i];
            return;
        }
    }
}

void addline(int st, int addr, int siz) {
    
    // merge
    for(int i = fir[st]; i; i = next[i]) {
        if(t[i].addr + t[i].siz == addr || addr + siz == t[i].addr) {
            int minaddr = min(addr, t[i].addr);
            delline(st, t[i].addr);
            addline(st + 1, minaddr, siz * 2);
            return;
        }
    }
    
    next[++con] = fir[st], fir[st] = con;
    t[con].addr = addr;
    t[con].siz = siz;
}

void insertBlock(int addr, int siz);

uint my_malloc(uint num_bytes) {
    int ret = 0;
    for(int i = 0; i < maxEntry; ++i) {
        if(1<<i < num_bytes || !fir[i])
            continue;
        Block p = t[fir[i]];
        fir[i] = next[fir[i]];
        ret = p.addr;
        p.addr += num_bytes;
        p.siz -= num_bytes;
        if(p.siz)
            insertBlock(p.addr, p.siz);
        g[++gn].addr = ret;
        g[gn].siz = num_bytes;
        return ret;
    }
    return -1;
}

void my_free(uint p) {
    int i;
    for(i = 0; i < gn; ++i) 
        if(g[i].addr == p)
            break;
    Block tmp = g[i];
    for(; i < gn; ++i)
        g[i] = g[i+1];
    gn--;
    insertBlock(tmp.addr, tmp.siz);
}

void insertBlock(int addr, int siz) {
    while(siz) {
        for(int i = maxEntry; i >= 0; --i) {
            if(1<<i <= siz) {
                addline(i, addr, siz);
                siz -= 1<<i;
                addr += 1<<i;
                break;
            }
        }
    }
}

char buf[100];
int param;

int main() {
    insertBlock(0, initialPageNum);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    while(scanf("%s%d", buf, &param) != EOF) {
        if(buf[0] == 'm') {
            uint ret = my_malloc(param);
        }else {
            my_free(param);
        }
    }
    return 0;
}
