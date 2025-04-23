#include "algorithms.h"
#include "scenarios.h"
#include "sortings.h"

namespace Scenarios {
void Task<Algorithms::COUNTING_SORT>::run() {
	Sortings::counting_sort(data);
}
void Task<Algorithms::HEAP_SORT>::run() {
	Sortings::heap_sort(data);
}
void Task<Algorithms::MERGE_SORT>::run() {
	Sortings::merge_sort(data, debug);
}
void Task<Algorithms::QUICK_SORT>::run() {
	Sortings::quick_sort(data, debug);
}
void Task<Algorithms::RADIX_SORT>::run() {
	Sortings::radix_sort_lsd(data);
}
}
