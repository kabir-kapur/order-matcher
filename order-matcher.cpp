#include <iostream>
#include <string>
#include <stdio.h>
#include <queue>
#include <sstream>

using std::cin;
using std::cout;
using std::endl;
using std::queue;
using std::string;
using std::stringstream;

struct order
{
    string number;
    bool buyOrder; // true if buy, false if sell
    string instrument;
    int quantity;
    int price;
};

queue<order> buyOrders;
queue<order> sellOrders;

std::string fetchOrder()
{
    // grabs user input, returns empty std::string if no input
    string unparsedOrder;
    cout << "Enter an order: ";
    getline(cin, unparsedOrder);
    return unparsedOrder;
}

order parseOrder(string unparsedOrder)
{
    order parsedOrder;
    string token;
    stringstream stream(unparsedOrder);
    int tokenCount = 0;

    while (stream >> token)
    {
        if (tokenCount == 0)
            parsedOrder.number = token;
        else if (tokenCount == 1)
        {
            if (token == "BUY")
                parsedOrder.buyOrder = true;
            else if (token == "SELL")
                parsedOrder.buyOrder = false;
        }
        else if (tokenCount == 2)
            parsedOrder.instrument = token;
        else if (tokenCount == 3)
            parsedOrder.quantity = stoi(token);
        else if (tokenCount == 3)
            parsedOrder.price = stoi(token);

        tokenCount++;
    }

    return parsedOrder;
}

int main()
{
    order currParsedOrder;
    string currUnparsedOrder;

    while (currUnparsedOrder != "exit")
    {
        currUnparsedOrder = fetchOrder();
        currParsedOrder = parseOrder(currUnparsedOrder);
        if (currParsedOrder.buyOrder)
            buyOrders.push(currParsedOrder);
        else if (!currParsedOrder.buyOrder)
            sellOrders.push(currParsedOrder);
    }

    return 1;
}