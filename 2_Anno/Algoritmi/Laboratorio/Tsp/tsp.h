#ifndef TSP_H
#define TSP_H

#ifdef __cplusplus
// C++ code

// soft limit on CPU time (in seconds)
#define TASK_TIMELIMIT 3

namespace helpers {
    long long get_elapsed_time(void);
    bool has_reached_timeout(void);

    void setup(void);
}

#ifndef GRADER_CPP
class program {

    typedef int main_t(void);

    public:
        virtual main_t main;
};

int main() {
    program p;

    helpers::setup();

    p.main();

    return 0;
}

#define main program::main

#endif // GRADER_CPP

#else
// C code

#error "Only C++ is supported"

#endif // __cplusplus

#endif // TSP_H

#pragma once