#include <iostream>
#include <chrono>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <bits/stdc++.h>

using namespace std;

int N = 3;
int iter_count = 1;
sem_t sem1;

auto start_time = chrono::high_resolution_clock::now();

long long get_time() {
    auto end_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::seconds>(end_time - start_time);
    auto elapsed_time_in_seconds = duration.count();
    return elapsed_time_in_seconds;
}

void* p(void* args) {
    int *p = (int*)args;
    N = *p;
    while(true) {
        sem_wait(&sem1);
        for(int i = 0; i < iter_count; i++) {
            cout << "p" ;
        }
        N--;
        if(N == 0) {
            cout << endl;
            iter_count++;
            N = 3;
        }
        sem_post(&sem1);
        sleep(1);
    }
    return NULL;
}

void* q(void* args) {
    int *p = (int*)args;
    N = *p;
    while(true) {
        sem_wait(&sem1);
        for(int i = 0; i < iter_count; i++) {
            cout << "q" ;
        }
        N--;
        if(N == 0) {
            cout << endl;
            iter_count++;
            N = 3;
        }
        sem_post(&sem1);
        sleep(1);
    }
    return NULL;
}

void* r(void* args) {
    int *p = (int*)args;
    N = *p;
    while(true) {
        sem_wait(&sem1);
        for(int i = 0; i < iter_count; i++) {
            cout << "r" ;
        }
        N--;
        if(N == 0) {
            cout << endl;
            iter_count++;
            N = 3;
        }
        sem_post(&sem1);
        sleep(1);
    }
    return NULL;
}

int main() {
    pthread_t t1, t2, t3;
    
    sem_init(&sem1, 0, 1);

    pthread_create(&t1, NULL, p, (void*)&N);
    pthread_create(&t2, NULL, q, (void*)&N);
    pthread_create(&t3, NULL, r, (void*)&N);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    sem_destroy(&sem1);
}