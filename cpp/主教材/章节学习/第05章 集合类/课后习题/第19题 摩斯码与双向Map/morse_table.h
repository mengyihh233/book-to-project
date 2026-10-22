#pragma once
#include <map>
#include <string>
// 仅提供26个字母的数据，不含翻译算法；个人work可以使用。
inline const std::map<char,std::string>& morseAlphabet(){
    static const std::map<char,std::string> table={
        {'A',".-"},{'B',"-..."},{'C',"-.-."},{'D',"-.."},{'E',"."},
        {'F',"..-."},{'G',"--."},{'H',"...."},{'I',".."},{'J',".---"},
        {'K',"-.-"},{'L',".-.."},{'M',"--"},{'N',"-."},{'O',"---"},
        {'P',".--."},{'Q',"--.-"},{'R',".-."},{'S',"..."},{'T',"-"},
        {'U',"..-"},{'V',"...-"},{'W',".--"},{'X',"-..-"},{'Y',"-.--"},{'Z',"--.."}
    };
    return table;
}
