#include "Util.hpp"

unsigned int N, M, w, x, y, z, total_visitors;
Visitor* visitors;
pthread_mutex_t output_lock;
pthread_mutex_t step_locks[NUMBER_OF_STEPS];
sem_t gallery_1;
sem_t glass_corridor;
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
    init_visitors();
    init_sync_objects();
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
    pthread_exit(NULL);
}

void* visit(void* arg) {
    Visitor* visitor = (Visitor*)arg;
    
    sleep(visitor->get_arrival_delay());
    log(visitor->get_status(get_time()));
    
    // time in hallway AB
    sleep(w);

    visitor->set_status(Status::ARRIVAL_B);
    log(visitor->get_status(get_time()));

    // steps
    visitor->set_status(Status::STEPS);
    int step;
    for(step = 0; step < NUMBER_OF_STEPS; step++) {
        if(!step) pthread_mutex_lock(&step_locks[step]);
        log(visitor->get_status(get_time(), step + 1));
        sleep(MAX_STEP_DELAY);
        if(step != NUMBER_OF_STEPS - 1) {
            pthread_mutex_lock(&step_locks[step + 1]);
            pthread_mutex_unlock(&step_locks[step]);
        }    
    }
    
    sem_wait(&gallery_1);
    pthread_mutex_unlock(&step_locks[step - 1]);
    
    // gallery 1
    visitor->set_status(Status::C_GALLERY_1_ENTRANCE);
    log(visitor->get_status(get_time()));

    // time in gallery 1
    sleep(x);
    
    // glass corridor
    sem_wait(&glass_corridor);
    sem_post(&gallery_1);
    visitor->set_status(Status::D_GALLERY_1_EXIT);
    log(visitor->get_status(get_time()));

    // time in glass corridor
    sleep(rand_range(1, MAX_GLASS_CORRIDOR_DELAY));
    sem_post(&glass_corridor);

    // gallery 2
    visitor->set_status(Status::E_GALLERY_2_ENTRANCE);
    log(visitor->get_status(get_time()));

    // time in gallery 2
    sleep(y);

    pthread_exit(NULL);
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

void init_gallery_semaphore() {
    sem_init(&gallery_1, 0, GALLERY1_MAX_OCCUPANCY);
}

void init_glass_corridor_semaphore() {
    sem_init(&glass_corridor, 0, GLASS_CORRIDOR_MAX_OCCUPANCY);
}

bool is_valid_params(int N, int M, int w, int x, int y, int z) {
    return N >= 0 && M >= 0 && w >= 0 && x >= 0 && y >= 0 && z >= 0;
}

void init_sync_objects() {
    init_output_lock();
    init_step_locks();
    init_gallery_semaphore();
    init_glass_corridor_semaphore();
    init_clock();
}

void init_visitors() {
    visitors = new Visitor[N + M];
    TicketGenerator* generator = TicketGenerator::get_instance();
    for (unsigned int i = 0; i < N; i++)
        visitors[i] = Visitor(generator->get_ticket_id(TicketTier::STANDARD), TicketTier::STANDARD, rand_range(1, MAX_ARRIVAL_DELAY), Status::ARRIVAL_A);
    for (unsigned int i = N; i < total_visitors; i++)
        visitors[i] = Visitor(generator->get_ticket_id(TicketTier::PREMIUM), TicketTier::PREMIUM, rand_range(1, MAX_ARRIVAL_DELAY), Status::ARRIVAL_A);
}
