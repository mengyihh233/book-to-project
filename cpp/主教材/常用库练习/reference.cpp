#define BOOK_API_NO_MAIN
#include "参考实现/math.cpp"
#include "参考实现/characters.cpp"
#include "参考实现/strings.cpp"
#include "参考实现/stanford-strings.cpp"
#include "参考实现/streams.cpp"
#include "参考实现/containers.cpp"
#include "参考实现/algorithms.cpp"
#include "参考实现/objects.cpp"

int main() {
    mathCalls();
    characterCalls();
    stringCalls();
    stanfordStringCalls();
    streamCalls(); formatAndStateCalls();
    containerCalls();
    algorithmCalls();
    ownershipCalls();
    return 0;
}
