#include <iostream>
#include <string>
#include <stdio.h>
#include <queue>
#include <sstream>
#include <list>

using std::cin;
using std::cout;
using std::endl;
using std::for_each;
using std::list;
using std::queue;
using std::string;
using std::stringstream;
using std::to_string;

struct order
{
    string number;     // order number
    bool buyOrder;     // true if buy, false if sell
    string instrument; // instrument in question
    int quantity;      // quantity of order
    int price;         // price preference
};

queue<order> buyOrders;
list<order> sellOrders = list<order>();
list<order>::iterator it;
list<string> completedOrders;
list<string>::iterator it2;

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

void print(string str)
{
    std::cout << str << endl;
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
            sellOrders.push_back(currParsedOrder);

        order currentBuyOrderToFill = buyOrders.front();

        for (it = sellOrders.begin(); it != sellOrders.end(); it++)
        {
            if (it->instrument == currentBuyOrderToFill.instrument)
            {
                if (it->price == currentBuyOrderToFill.price)
                { // only match same price orders
                    if (it->quantity > currentBuyOrderToFill.quantity)
                    {
                        it->quantity -= currentBuyOrderToFill.quantity;
                        buyOrders.pop();
                        completedOrders.push_back("TRADE " + it->instrument + " " + it->number + " " + currentBuyOrderToFill.number + " " + to_string(it->price) + " " + to_string(currentBuyOrderToFill.quantity));
                        // TRADE BTCUSD abe14 12345 5 10000
                        break;
                    }
                    else if (it->quantity < currentBuyOrderToFill.quantity)
                    {
                        currentBuyOrderToFill.quantity -= it->quantity;
                        completedOrders.push_back("TRADE" + it->instrument + it->number + currentBuyOrderToFill.number + to_string(it->price) + to_string(it->price));
                        sellOrders.erase(it);
                    }
                }
            }
        }
    }

    for_each(completedOrders.begin(),
             completedOrders.end(),
             print);

    return 1;
}