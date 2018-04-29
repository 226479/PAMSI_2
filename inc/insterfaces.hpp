#pragma once


#include <iostream>


class IRunnable {
public:
    virtual ~IRunnable() = default;

    virtual void run(const int& start_id, const int& end_id) = 0;
};

class IPreparable {
public:
    virtual ~IPreparable() = default;

    virtual void prepare(const int& size) = 0;

    virtual void prepare() = 0;

    virtual void prepare_map() = 0;

};
