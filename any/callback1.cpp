#include <any>
#include <iostream>
#include "event_source.hpp"

void callback1(std::any& context_any){
   auto& context = *std::any_cast<int>(&context_any);
   std::cout << "callback1: " << context++ << std::endl;
}

void attach1(EventSource& source){
    source.add_EventListener(callback1, 7); 
}
