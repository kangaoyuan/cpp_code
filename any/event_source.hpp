#include <any>
#include <vector>
#include <utility>
#include <iostream>

class EventSource;
void attach1(EventSource&);
void attach2(EventSource&);

class EventSource {
public:
    using EventListener = void(*)(std::any&);

    // hint: std::any object must be copy constructible
    void add_EventListener(EventListener callback, std::any context){
        m_listeners.emplace_back(std::move(callback), std::move(context));
    }

    void dispatchEvent(){
        for(auto&& listener : m_listeners){
            listener.first(listener.second); 
        }
    }

private:
    std::vector<std::pair<EventListener, std::any>> m_listeners;
};
