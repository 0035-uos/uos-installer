#ifndef SINGLETON_H
#define SINGLETON_H

template <typename T>
class Singleton
{
public:
    Singleton(){}
public:
    static T* Instance() {
        static T _m;
        return &_m;
    }
};

#endif // SINGLETON_H
