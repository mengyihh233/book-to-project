#pragma once
#include "../../../../教学辅助/queue_trace.h"
inline QueueResult simulateShared(const QueueTrace& trace) {
    validateQueueTrace(trace);QueueResult result;std::queue<QueueCustomer> waiting;
    std::vector<int> remaining(static_cast<std::size_t>(trace.cashiers),0);
    for(std::size_t t=0;t<trace.services.size();++t) {
        if(trace.services[t]>0){waiting.push({static_cast<int>(t),trace.services[t]});++result.arrived;}
        for(auto& seconds:remaining) {
            if(seconds>0){--seconds;if(seconds==0)++result.finished;}
            else if(!waiting.empty()) {
                const auto customer=waiting.front();waiting.pop();
                result.totalWait+=static_cast<long long>(t)-customer.arrival;
                ++result.started;seconds=customer.service;
            }
        }
        result.waiting=static_cast<long long>(waiting.size());result.queueArea+=result.waiting;
    }
    result.busy=std::count_if(remaining.begin(),remaining.end(),[](int seconds){return seconds>0;});
    return result;
}
