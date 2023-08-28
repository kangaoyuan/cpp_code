#include <any>
#include <iostream>
#include "event_source.hpp"

void callback2(std::any& context_any){
   auto& context = *std::any_cast<double>(&context_any);
   std::cout << "callback1: " << context * 2 << std::endl;
}

void attach2(EventSource& source){
    source.add_EventListener(callback2, 77.27); 
}
    
