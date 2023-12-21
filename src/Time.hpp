#include <sys/time.h>


class Time
{
private:
    struct timeval time;

public:
    Time()
    {
        gettimeofday(&time, NULL);
    }

    Time(const Time &other)
    {
        time = other.time;
    }

    Time(Time &&other)
    {
        time = other.time;
    }

    void reset()
    {
        gettimeofday(&time, NULL);
    }

    double get_ms() const
    {
        struct timeval now;
        gettimeofday(&now, NULL);
        return (now.tv_sec - time.tv_sec) * 1000.0 + (now.tv_usec - time.tv_usec) / 1000.0;
    }

    double get_s() const{
        return get_ms() / 1000;
    }

    double reset_s(){
        double time = get_s();
        reset();
        return time;
    }

    double getDiff_ms(Time &other) const
    {
        return get_ms() - other.get_ms();
    }

    bool operator<(Time &other) const
    {
        return get_ms() < other.get_ms();
    }

    Time &operator=(Time &other)
    {
        time = other.time;
        return *this;
    }

    Time &operator+=(double ms)
    {
        this->time.tv_sec += ms / 1000.0;
        this->time.tv_usec += (ms - (int)ms) * 1000.0;
        return *this;
    }

    Time operator+(double ms)
    {
        Time other = *this;
        other += ms;
        return other;
    }

    bool operator==(Time &other)
    {
        return time.tv_sec == other.time.tv_sec && time.tv_usec == other.time.tv_usec;
    }

    bool operator<(const Time &other) const
    {
        return this->get_ms() < other.get_ms();
    }

    bool operator<(const double &other) const
    {
        return this->get_ms() < other;
    }
};
