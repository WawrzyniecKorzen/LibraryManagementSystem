
#include "sha256.h"

#include <bitset>
#include <iomanip>
#include <sstream>

SHA256::SHA256(QString input) : password(input.toStdString())
{

}

SHA256::~SHA256()
{
}

QString SHA256::hash()
{

    std::string tempString;
    for (auto& c : password)
    {
        tempString += std::bitset<8>(c).to_string();
    }





    tempString += "1";
    std::string padding = std::bitset<512>(password.length() * 8).to_string();
    tempString += padding.substr((password.length() * 8 % 512) + 1, 512);


    uint32_t words[64] = { 0 };
    for (int i = 0; i < tempString.length() / 32; i++)
    {

        words[i] = std::stoul(tempString.substr(i * 32, 32), nullptr, 2);
    }





    for (int i = 16; i < 64; i++)
    {

        uint32_t s1 = rotr(words[i - 2], 17) ^ rotr(words[i - 2], 19) ^ (words[i - 2] >> 10);
        uint32_t s0 = rotr(words[i - 15], 7) ^ rotr(words[i - 15], 18) ^ (words[i - 15] >> 3);


        words[i] = s0 + s1 + words[i - 7] + words[i - 16];
    }


    uint32_t tempVariables[8] = {};
    for (int j = 0; j < 8; j++)
        tempVariables[j] = workVariables[j];

    for (int i = 0; i < 64; i++)
    {


        uint32_t sig0 = rotr(tempVariables[0], 2) ^ rotr(tempVariables[0], 13) ^ rotr(tempVariables[0], 22);
        uint32_t sig1 = rotr(tempVariables[4], 6) ^ rotr(tempVariables[4], 11) ^ rotr(tempVariables[4], 25);
        uint32_t maj = (tempVariables[0] & tempVariables[1]) ^ (tempVariables[0] & tempVariables[2]) ^ (tempVariables[1] & tempVariables[2]);
        uint32_t ch = (tempVariables[4] & tempVariables[5]) ^ (~tempVariables[4] & tempVariables[6]);
        uint32_t temp1 = tempVariables[7] + sig1 + ch + K[i] + words[i];
        uint32_t temp2 = sig0 + maj;

        tempVariables[7] = tempVariables[6];
        tempVariables[6] = tempVariables[5];
        tempVariables[5] = tempVariables[4];
        tempVariables[4] = tempVariables[3] + temp1;
        tempVariables[3] = tempVariables[2];
        tempVariables[2] = tempVariables[1];
        tempVariables[1] = tempVariables[0];
        tempVariables[0] = temp1 + temp2;


    }
    for (int i = 0; i < 8; i++)
        tempVariables[i] = tempVariables[i] + workVariables[i];

    std::string result;
    for (int i = 0; i < 8; i++)
    {
        std::stringstream stream;
        stream << std::hex << tempVariables[i];
        std::string store = stream.str();

        while (store.length() < 8)
            store = "0" + store;

        result += store;
    }
    return QString::fromStdString(result);
}

uint32_t SHA256::rotr(uint32_t number, int rotation)
{
    return (number >> rotation) | (number << (32 - rotation));
}

