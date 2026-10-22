#pragma once
#include "input_line.h"
#include <algorithm>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <queue>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

struct QueueTrace { int cashiers=1; std::vector<int> services; };
struct QueueCustomer { int arrival; int service; };
struct QueueResult {
    long long arrived=0,started=0,finished=0,waiting=0,busy=0,totalWait=0,queueArea=0;
};
inline void validateQueueTrace(const QueueTrace& trace) {
    if(trace.cashiers<1||trace.cashiers>32||trace.services.size()>10000)throw std::out_of_range("trace dimensions");
    for(int service:trace.services)if(service<0||service>10000)throw std::out_of_range("service duration");
}
inline QueueTrace readQueueTrace(std::istream& in) {
    std::string line;int ticks,cashiers;
    if(!book_input::logicalLine(in,line))throw std::invalid_argument("missing shape");
    std::istringstream shape(line);
    if(!(shape>>ticks>>cashiers))throw std::invalid_argument("invalid shape");
    shape>>std::ws;
    if(!shape.eof()||ticks<0||ticks>10000||cashiers<1||cashiers>32)throw std::out_of_range("trace dimensions");
    QueueTrace trace;trace.cashiers=cashiers;trace.services.reserve(static_cast<std::size_t>(ticks));
    for(int t=0;t<ticks;++t) {
        if(!book_input::logicalLine(in,line))throw std::invalid_argument("missing tick");
        std::istringstream record(line);int arrived,service=0;
        if(!(record>>arrived)||(arrived!=0&&arrived!=1))throw std::invalid_argument("arrival must be 0 or 1");
        if(arrived&&(!(record>>service)||service<1||service>10000))throw std::out_of_range("service duration");
        record>>std::ws;if(!record.eof())throw std::invalid_argument("extra tick data");
        trace.services.push_back(service);
    }
    if(book_input::logicalLine(in,line)||in.bad())throw std::invalid_argument("extra input");
    return trace;
}
inline void printQueueResult(const QueueResult& r,std::size_t ticks,std::ostream& out) {
    out<<"arrived="<<r.arrived<<" started="<<r.started<<" finished="<<r.finished<<" waiting="<<r.waiting<<" busy="<<r.busy<<'\n';
    out<<"total_wait="<<r.totalWait<<" queue_area="<<r.queueArea<<'\n';
    out<<std::fixed<<std::setprecision(6)<<"mean_wait="<<(r.started?static_cast<double>(r.totalWait)/static_cast<double>(r.started):0.0)
       <<" mean_queue="<<(ticks?static_cast<double>(r.queueArea)/static_cast<double>(ticks):0.0)<<'\n';
}
