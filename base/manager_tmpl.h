#ifndef MANAGER_TMPL_H_H_H_
#define MANAGER_TMPL_H_H_H_
#include <map>
template<typename T1>
class Manager
{
    public:
        static Manager<T1> *get_instance();
        T1 *fetch(int id);
        T1 *add(int id);
        int size();
        void clear();
    private:
        Manager();
        ~Manager();
        std::map<int, T1> data_map;
};

template<typename T1>
Manager<T1> *Manager<T1>::get_instance()
{
    static Manager<T1> instance;
    return  &instance;
}

template<typename T1>
void Manager<T1>::clear()
{
    data_map.clear();
}

template<typename T1>
T1 *Manager<T1>::add(int id)
{
    T1 data;
    data_map[id] = data;
    return fetch(id);
}

template<typename T1>
int Manager<T1>::size()
{
    return data_map.size();
}
template<typename T1>
T1 *Manager<T1>::fetch(int id)
{
    return &(data_map[id]);
}

template<typename T1>
Manager<T1>::Manager()
{
}

template<typename T1>
Manager<T1>::~Manager()
{
}

#endif
