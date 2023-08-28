#include "event_source.hpp"

int main(){
    EventSource source;
    attach1(source);    
    attach2(source);    

    source.dispatchEvent();
    source.dispatchEvent();

    return 0;
}
