#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <omp.h>
#include <cstring>
using namespace std;

int num;

double wall_time()
{
#ifdef GETTIMEOFDAY
    struct timeval t;
    gettimeofday(&t, NULL);
    return 1. * t.tv_sec + 1.e-6 * t.tv_usec;
#else
    struct timespec t;
    clock_gettime(CLOCK_MONOTONIC, &t);
    return 1. * t.tv_sec + 1.e-9 * t.tv_nsec;
#endif
}

bool incre_add(int *a){
    int flag = 0;
    // continue or stop
    for(int i = 2; i <= num - 1; i++){
        if(a[i] < i - 1){
            flag = 1;
            break;
        }
    }
    if(flag){
        //add 1
        int add = 1;
        for(int i = 2; i <= num - 1; i++){
            if(add == 0) break;
            int tmp = (a[i] + add) / i;
            a[i] = (a[i] + add) % i;
            add = tmp;
        }
        return true;
    }
    return false;
}

void do_increase_base(int output){
    char s[15][15];
    int a[15][15];
    memset(a, 0, sizeof(a));
    omp_set_num_threads(num); // set the number of threads
    printf("thread numbers are %d\n", omp_get_num_threads());
    // initialize the first permutation and intermediate number of every thread
    for(int j = 0; j < num; j++){
        a[j][num] = j;
        for(int i = 1; i <= num; i++){
            s[j][i - 1] = (char)(i + '0');
        }
        for(int i = num - 1; i > num - 1 - j; i--){
            s[j][i] = s[j][i-1];
        }
        s[j][num - 1 - j] = (char)(num + '0');
        s[j][num] = 0;
    }
    // divide task into num threads to calculate
#pragma omp parallel
{
    int tid = omp_get_thread_num();
    printf("thread id is %d\n", tid);
    while(1){
        if(output) printf("%s\n", s[tid]);
        //increase base counting method
        if(!incre_add(a[tid])) break;
        int vis[15] = {0};
        // generate permutation
        for(int i = num; i >= 1; i--){
            int emptynum = 0;
            for(int j = num - 1; j >= 0; j--){
                if(vis[j] == 0){
                    if(emptynum == a[tid][i]){
                        vis[j] = 1;
                        s[tid][j] = (char)(i + '0');
                        break;
                    }
                    else{
                        emptynum++;
                    }
                }
            }
        }
    }
}
}

void test_time(){
    printf("implement increase_base with multi-threads\n");
    double start, end;
    start = wall_time();
    do_increase_base(0);
    end = wall_time();
    printf("average runtime of multi-threads increase base: %.2f ms\n", (end - start) * 1000);

}
int main(){
    num = 12;
    test_time();
    return 0;
}