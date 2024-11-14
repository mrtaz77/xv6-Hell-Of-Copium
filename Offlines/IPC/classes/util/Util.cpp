#include "Util.hpp"

unsigned int N, M, w, x, y, z, total_visitors;
Visitor* visitors;
pthread_mutex_t output_lock;
pthread_mutex_t step_locks[NUMBER_OF_STEPS];
auto start_time = chrono::high_resolution_clock::now();

void input_params() {
    cin >> N >> M;
    cin >> w >> x >> y >> z;
    total_visitors = N + M;
}

void output_params() {
    cout << N << " " << M << endl;
    cout << w << " " << x << " " << y << " " << z << endl;
}

void open_museum() {
    if(N <= 0 && M <= 0) exit(0);
    visitors = new Visitor[N + M];
    TicketGenerator* generator = TicketGenerator::get_instance();
    for(unsigned int i = 0; i < N; i++) 
        visitors[i] = Visitor(generator->get_ticket_id(TicketTier::STANDARD), TicketTier::STANDARD, rand_range(1, MAX_ARRIVAL_DELAY), Status::ARRIVAL_A);
    for(unsigned int i = N; i < N + M; i++) 
        visitors[i] = Visitor(generator->get_ticket_id(TicketTier::PREMIUM), TicketTier::PREMIUM, rand_range(1, MAX_ARRIVAL_DELAY), Status::ARRIVAL_A);
    init_output_lock();
    init_step_locks();
    init_clock();
    int remaining_visitors = total_visitors;
    bool arrived[total_visitors] = {false};
    pthread_t visitor_threads[total_visitors];
    while(remaining_visitors) {
        int random_visitor = rand_range(0, N + M - 1);
        if(arrived[random_visitor]) continue;
        arrived[random_visitor] = true;
        pthread_create(&visitor_threads[random_visitor], NULL, visit, (void*)&visitors[random_visitor]);
        remaining_visitors--;
    }
    for(unsigned int i = 0; i < total_visitors; i++)
        pthread_join(visitor_threads[i], NULL);
}

void* visit(void* arg) {
    Visitor* visitor = (Visitor*)arg;
    sleep(visitor->get_arrival_delay());
    log(visitor->get_status(get_time()));
    sleep(w);
    visitor->set_status(Status::ARRIVAL_B);
    log(visitor->get_status(get_time()));
    visitor->set_status(Status::STEPS);
    
    for(int step = 0; step < NUMBER_OF_STEPS; step++) {
        if(!step) pthread_mutex_lock(&step_locks[step]);
        sleep(MAX_STEP_DELAY);
        log(visitor->get_status(get_time(), step + 1));
        if(step != NUMBER_OF_STEPS - 1) pthread_mutex_lock(&step_locks[step + 1]);
        pthread_mutex_unlock(&step_locks[step]);
    }

    visitor->set_status(Status::C_GALLERY_1_ENTRANCE);
    log(visitor->get_status(get_time()));
    return NULL;
}

void init_output_lock() {
    pthread_mutex_init(&output_lock, NULL);
}

void init_clock() {
    start_time = chrono::high_resolution_clock::now();
}

long long get_time() {
    auto end_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::seconds>(end_time - start_time);
    auto elapsed_time_in_seconds = duration.count();
    return elapsed_time_in_seconds;
}

void log(const string& message) {
    pthread_mutex_lock(&output_lock);
    cout << message << endl;
    pthread_mutex_unlock(&output_lock);
}

void init_step_locks() {
    for(unsigned int i = 0; i < NUMBER_OF_STEPS; i++)
        pthread_mutex_init(&step_locks[i], NULL);
}