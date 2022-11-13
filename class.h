#include <iostream>
#include <string>
using namespace std;

class Net
{
public:
    int Source_X = 0;
    int Source_Y = 0;
    int Target_X = 0;
    int Target_Y = 0;
    string netName;
};

class position
{
public:
    int x;
    int y;
    position()
    {
        x = 0;
        y = 0;
    }
    position(int i, int j)
    {
        x = i;
        y = j;
    }
    bool operator==(position a)
    {
        if ((a.x == x) && (a.y == y))
            return true;
        else
            return false;
    }
    bool operator!=(position a)
    {
        if ((a.x != x) || (a.y != y))
            return true;
        else
            return false;
    }
    position operator=(position a)
    {
        x = a.x;
        y = a.y;
        return *this;
    }
};

class key
{
private:
    position start, end;

public:
    int x, y;
    key()
    {
        x = 0;
        y = 0;
    }
    void set_start(int a, int b)
    {
        start.x = a;
        start.y = b;
    }
    void set_end(int a, int b)
    {
        end.x = a;
        end.y = b;
    }
    position get_start()
    {
        return start;
    }
    position get_end()
    {
        return end;
    }
};