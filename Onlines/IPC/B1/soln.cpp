#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <iostream>

sem_t n_lock, t_lock;

int N, n;

using namespace std;

void* print_underscore(void* args) {
    int* p = (int *)args;
    int local_n = *p;
    while(local_n > N / 2) {
        sem_wait(&n_lock);
        for(int i = 0; i < local_n - 1; i++)cout << "_" ;
        n--;
        local_n = n;
        sem_post(&t_lock);
        sleep(1);
    }
    return NULL;
}

void* print_plus(void* args) {
    int* p = (int *)args;
    int local_n = *p;
    while(local_n > N / 2) {
        sem_wait(&t_lock);
        for(int i = local_n; i <= N; i++) cout << "+" ;
        cout << endl;
        local_n = n;
        sem_post(&n_lock);
        sleep(1);
    }
    return NULL;
}

int main() {
    cin >> N;
    n = N;
    pthread_t t1, t2;
    sem_init(&n_lock, 0, 1);
    sem_init(&t_lock, 0, 0);

    pthread_create(&t1, NULL, print_underscore, (void*)&N);
    pthread_create(&t2, NULL, print_plus, (void*)&N);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    sem_destroy(&n_lock);
    sem_destroy(&t_lock);
}   