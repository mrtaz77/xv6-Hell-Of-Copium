/*
	This program generates random numbers based on the Poisson distribution.

	A Poisson distribution is a probability distribution often used to model the
	number of times an event occurs within a specified interval, like the number
	of arrivals at a service point in a given time frame. It has a parameter
	lambda (λ) which represents the average rate of occurrences in the interval.

	In this code:
	- We create a Poisson distribution with lambda = 10000.234.
	- Using a random number generator, we produce a random value that fits
	this Poisson distribution.
	- The get_random_number function returns a new random number each time it
	is called, based on the specified Poisson distribution.
*/

#include "PoissonRandom.hpp"


static random_device rd;
static mt19937 generator(rd());

int rand() {
	poisson_distribution<int> pd(LAMDA);
	return pd(generator);
}

int rand_range(int min, int max) {
	return min + rand() % (max - min + 1);
}
