/*
keep linked list of pages
most recently used page at front, least at rear
update list of pages every memory reference
assume pages used recently will be used again soon
can also keep counter in each page table entry
increment counter with each CPU cycle (how to sim?)
copy counter to PTE counter on reference to page
evict page with lowest counter value
*/
