#include "Util.hpp"

unsigned int N, M, w, x, y, z, total_visitors;
Visitor* visitors;
pthread_mutex_t output_lock;
pthread_mutex_t step_locks[NUMBER_OF_STEPS];
sem_t gallery_1;
sem_t glass_corridor;
auto start_time = chrono::high_resolution_clock::now();

// Reader-Writer Problem
// Writer's Preference
// Reader : Standard Ticket Holder
// Writer : Premium Ticket Holder

// Priority Lock: to block standard ticket holders 
// when a premium ticket holder is present
pthread_mutex_t priority_lock;

// Exclusive Access Lock: to block incoming premium ticket holders
// when a premium ticket holder or one or more standard ticket holders is present
pthread_mutex_t exclusive_access_lock;

// Standard Ticket Counter Lock: to update the number of standard ticket holders
pthread_mutex_t standard_ticket_counter_lock;
unsigned int standard_ticket_counter = 0;

// Premium Ticket Counter Lock: to update the number of premium ticket holders
pthread_mutex_t premium_ticket_counter_lock;
unsigned int premium_ticket_counter = 0;

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
    init_locks_and_semaphores();
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
    
    // time in hallway AB
    sleep(w);

    visitor->set_status(Status::ARRIVAL_B);
    log(visitor->get_status(get_time()));

    // steps
    visitor->set_status(Status::STEPS);
    int step;
    for(step = 0; step < NUMBER_OF_STEPS; step++) {
        // acquire lock for first step
        if(!step) pthread_mutex_lock(&step_locks[step]);
        
        log(visitor->get_status(get_time(), step + 1));
        sleep(MAX_STEP_DELAY);
        
        // for all steps other than the last
        // acquire the next step and release current step
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

    visitor->set_status(Status::ENTRY_PHOTO_BOOTH);
    log(visitor->get_status(get_time()));

    // ticket tier check
    if(visitor->get_ticket_tier() == TicketTier::PREMIUM)
        premium_ticket_holder(visitor);
    else
        standard_ticket_holder(visitor);
    
    // exit
    visitor->set_status(Status::EXIT_F);
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

void init_gallery_semaphore() {
    sem_init(&gallery_1, 0, GALLERY1_MAX_OCCUPANCY);
}

void init_glass_corridor_semaphore() {
    sem_init(&glass_corridor, 0, GLASS_CORRIDOR_MAX_OCCUPANCY);
}

bool is_valid_params(int N, int M, int w, int x, int y, int z) {
    return N >= 0 && M >= 0 && w >= 0 && x >= 0 && y >= 0 && z >= 0;
}

void init_locks_and_semaphores() {
    init_output_lock();
    init_step_locks();
    init_gallery_semaphore();
    init_glass_corridor_semaphore();
    init_photo_booth_locks();
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

void standard_ticket_holder(Visitor* visitor) {
    // similar to synch
    // use before for that thread which has lower priority
    pthread_mutex_lock(&priority_lock);
    
    pthread_mutex_lock(&standard_ticket_counter_lock);
    standard_ticket_counter++;
    if(standard_ticket_counter == 1)
        pthread_mutex_lock(&exclusive_access_lock); // block incoming premium ticket holders but not standard ticket holders
    pthread_mutex_unlock(&standard_ticket_counter_lock);

    pthread_mutex_unlock(&priority_lock); // can access now

    // inside photo booth
    visitor->set_status(Status::INSIDE_PHOTO_BOOTH);
    log(visitor->get_status(get_time()));

    // time in photo booth
    sleep(z);

    pthread_mutex_lock(&standard_ticket_counter_lock);
    standard_ticket_counter--;
    if(standard_ticket_counter == 0)
        pthread_mutex_unlock(&exclusive_access_lock); // unblock incoming premium ticket holders
    pthread_mutex_unlock(&standard_ticket_counter_lock);
}

void premium_ticket_holder(Visitor* visitor) {
    pthread_mutex_lock(&premium_ticket_counter_lock);
    premium_ticket_counter++;
    if(premium_ticket_counter == 1)
        pthread_mutex_lock(&priority_lock); // block incoming standard ticket holders
    pthread_mutex_unlock(&premium_ticket_counter_lock);

    // similar to synch
    // use after for that thread which has higher priority
    pthread_mutex_lock(&exclusive_access_lock); // block incoming premium ticket holders

    // inside photo booth
    visitor->set_status(Status::INSIDE_PHOTO_BOOTH);
    log(visitor->get_status(get_time()));

    // time in photo booth
    sleep(z);

    pthread_mutex_unlock(&exclusive_access_lock); // unblock incoming premium ticket holders

    pthread_mutex_lock(&premium_ticket_counter_lock);
    premium_ticket_counter--;
    if(premium_ticket_counter == 0)
        pthread_mutex_unlock(&priority_lock); // unblock incoming standard ticket holders
    pthread_mutex_unlock(&premium_ticket_counter_lock);
}

void init_photo_booth_locks() {
    pthread_mutex_init(&standard_ticket_counter_lock, NULL);
    pthread_mutex_init(&premium_ticket_counter_lock, NULL);
    pthread_mutex_init(&priority_lock, NULL);
    pthread_mutex_init(&exclusive_access_lock, NULL);
}