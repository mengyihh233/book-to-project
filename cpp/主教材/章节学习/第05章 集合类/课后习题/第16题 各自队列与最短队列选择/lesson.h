#pragma once
#include "../../../../教学辅助/queue_trace.h"
inline std::size_t findShortestQueue(const std::vector<std::queue<QueueCustomer>>& queues) {
    if(queues.empty())throw std::invalid_argument("cashier queue vector is empty");
    std::size_t shortest=0;
    for(std::size_t i=1;i<queues.size();++i)if(queues[i].size()<queues[shortest].size())shortest=i;
    return shortest;
}
inline QueueResult simulateSeparate(const QueueTrace& trace) {
    validateQueueTrace(trace);QueueResult result;
    std::vector<std::queue<QueueCustomer>> queues(static_cast<std::size_t>(trace.cashiers));
    std::vector<int> remaining(static_cast<std::size_t>(trace.cashiers),0);
    for(std::size_t t=0;t<trace.services.size();++t) {
        if(trace.services[t]>0){queues[findShortestQueue(queues)].push({static_cast<int>(t),trace.services[t]});++result.arrived;}
        for(std::size_t i=0;i<queues.size();++i) {
            if(remaining[i]>0){--remaining[i];if(remaining[i]==0)++result.finished;}
            else if(!queues[i].empty()) {
                const auto customer=queues[i].front();queues[i].pop();
                result.totalWait+=static_cast<long long>(t)-customer.arrival;
                ++result.started;remaining[i]=customer.service;
            }
        }
        result.waiting=0;for(const auto& queue:queues)result.waiting+=static_cast<long long>(queue.size());
        result.queueArea+=result.waiting;
    }
    result.busy=std::count_if(remaining.begin(),remaining.end(),[](int seconds){return seconds>0;});
    return result;
}
