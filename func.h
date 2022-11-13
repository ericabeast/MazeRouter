#include <iostream>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <math.h>
#include <sstream>
#include <iterator>
#include <ctime>
#include <time.h>
#include <stack>
#include <queue>
#include "class.h"
using namespace std;

void permute(string a, int l, int r, vector<int> &allPermutation)
{
    // Base case
    if (l == r)
    {
        // cout<<a<<endl;
        int num = stoi(a);
        allPermutation.push_back(num);
    }
    else
    {
        // Permutations made
        for (int i = l; i <= r; i++)
        {

            // Swapping done
            swap(a[l], a[i]);

            // Recursion called
            permute(a, l + 1, r, allPermutation);

            // backtrack
            swap(a[l], a[i]);
        }
    }
}

bool goMaze(int howMany_Row, int howMany_Col, char **maze3, int **maze4, key a, stack<position> &path, stack<position> &path2, queue<position> &way, int whichNet, vector<vector<position>> &theRoute, int allround)
{
    int distance = 3;
    char in;
    position temp2;
    position onthePath;
    int dead_road;
    temp2 = a.get_start();
    // cout<<"0000:" << temp2.x <<"\t" << temp2.y<<endl;
    way.push(temp2);
    maze4[temp2.x][temp2.y] = distance;
    // cout<<"---:"<<maze4[temp2.x][temp2.y]<<endl;
    while (temp2 != a.get_end())
    {
        //  cout << "///////////////////////////////////////"<<endl;
        dead_road = 0;
        temp2 = way.front();
        way.pop();
        distance = maze4[temp2.x][temp2.y];
        distance++;
        position queue_temp;
        if (maze4[temp2.x][temp2.y + 1] == 0)
        {
            // cout << "1"<<endl;
            queue_temp = temp2;
            queue_temp.y++;
            maze4[queue_temp.x][queue_temp.y] = distance;
            way.push(queue_temp);
            dead_road = 1;
        }
        if (maze4[temp2.x][temp2.y - 1] == 0)
        {
            // cout << "2"<<endl;
            queue_temp = temp2;
            queue_temp.y--;
            maze4[queue_temp.x][queue_temp.y] = distance;
            way.push(queue_temp);
            dead_road = 1;
            // cout << "2"<<endl;
        }
        //  cout << "a"<<endl;
        if (maze4[temp2.x + 1][temp2.y] == 0)
        {
            // cout << "3"<<endl;
            queue_temp = temp2;
            queue_temp.x++;
            maze4[queue_temp.x][queue_temp.y] = distance;
            way.push(queue_temp);
            dead_road = 1;
        }
        if (maze4[temp2.x - 1][temp2.y] == 0)
        {
            // cout << "4"<<endl;
            queue_temp = temp2;
            queue_temp.x--;
            maze4[queue_temp.x][queue_temp.y] = distance;
            way.push(queue_temp);
            dead_road = 1;
        }
        //  cout << "c"<<endl;
        if (maze4[temp2.x][temp2.y + 1] == -1)
        {
            // cout << "5"<<endl;
            temp2.y++;
            maze4[temp2.x][temp2.y] = distance;
            dead_road = 1;
        }
        //  cout << "d"<<endl;
        if (maze4[temp2.x][temp2.y - 1] == -1)
        {
            // cout << "6"<<endl;
            temp2.y--;
            maze4[temp2.x][temp2.y] = distance;
            dead_road = 1;
        }
        //  cout << "e"<<endl;
        if (maze4[temp2.x + 1][temp2.y] == -1)
        {
            // cout << "7"<<endl;
            temp2.x++;
            maze4[temp2.x][temp2.y] = distance;
            dead_road = 1;
        }
        //  cout << "f"<<endl;
        if (maze4[temp2.x - 1][temp2.y] == -1)
        {
            temp2.x--;
            maze4[temp2.x][temp2.y] = distance;
            dead_road = 1;
        }
        //  cout << "current temp" << temp2.x << " " << temp2.y << endl;
        if (dead_road == 0 && way.size() == 0)
            break;
        //  if(allround==120){
        //      for(int i = howMany_Row+1;i >=0 ; i--){
        //         for(int j=0; j < howMany_Col+2 ; j++){
        //             cout << maze4[j][i]<< "\t";
        //         }
        //         cout << endl;
        //     }
        //  }
    }
    // for(int i = howMany_Row+1;i >=0 ; i--){
    //         for(int j=0; j < howMany_Col+2 ; j++){
    //             cout << maze4[j][i]<< "\t";
    //         }
    //         cout << endl;
    //     }
    // cout << endl;

    if (dead_road == 0)
    {
        cout << "No route is found." << endl;
        return 0;
    }
    else
    {
        int end = maze4[a.get_end().x][a.get_end().y];
        position ending = a.get_end();
        cout << "end found : " << ending.x << " " << ending.y << endl;
        for (int i = end - 1; i > 3; i--)
        {
            if (i == maze4[ending.x + 1][ending.y])
            {
                maze3[++ending.x][ending.y] = '1';
                onthePath.x = ending.x;
                onthePath.y = ending.y;
                theRoute[whichNet].push_back(onthePath);
                // theRoute[whichNet][i-4].x = ending.x+1;
                // theRoute[whichNet][i-4].y = ending.y;
            }

            else if (i == maze4[ending.x - 1][ending.y])
            {
                maze3[--ending.x][ending.y] = '1';
                onthePath.x = ending.x;
                onthePath.y = ending.y;
                theRoute[whichNet].push_back(onthePath);
                // theRoute[whichNet][i-4].x = ending.x-1;
                // theRoute[whichNet][i-4].y = ending.y;
            }

            else if (i == maze4[ending.x][ending.y + 1])
            {
                maze3[ending.x][++ending.y] = '1';
                onthePath.x = ending.x;
                onthePath.y = ending.y;
                theRoute[whichNet].push_back(onthePath);
                // theRoute[whichNet][i-4].x = ending.x;
                // theRoute[whichNet][i-4].y = ending.y+1;
            }

            else if (i == maze4[ending.x][ending.y - 1])
            {
                maze3[ending.x][--ending.y] = '1';
                onthePath.x = ending.x;
                onthePath.y = ending.y;
                theRoute[whichNet].push_back(onthePath);
                // theRoute[whichNet][i-4].x = ending.x;
                // theRoute[whichNet][i-4].y = ending.y-1;
            }
        }
        //    for(int i=0;i<length;i++){
        //      for(int j=0;j<width;j++){
        //      ofs1<< maze3[i][j];
        //      ofs1<<" ";
        //     }
        //      ofs1<<endl;
        //   }

        //

        // show the maze
        // for(int i = howMany_Row+1;i >=0 ; i--){
        //     for(int j=0; j < howMany_Col+2 ; j++){
        //         cout << maze4[j][i]<< "\t";
        //     }
        //     cout << endl;
        // }
        // cout << endl;
        // for(int i = howMany_Row+1;i >=0 ; i--){
        //     for(int j=0; j < howMany_Col+2 ; j++){
        //         cout << maze3[j][i]<< "\t";
        //     }
        //     cout << endl;
        // }
        // cout <<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
    }
    return 1;
}
void upload_Maze(char **maze3, int **maze4, int **maze2, int howMany_Row, int howMany_Col, int whichNet, int allround)
{
    for (int i = 0; i < howMany_Row + 2; i++)
    {
        for (int j = 0; j < howMany_Col + 2; j++)
        {
            if (maze4[j][i] != 2)
            {
                maze4[j][i] = maze2[j][i];
            }
        }
    }
    for (int i = 0; i < howMany_Row + 2; i++)
    {
        for (int j = 0; j < howMany_Col + 2; j++)
        {
            if (maze3[j][i] == '1' || maze3[j][i] == 'S' || maze3[j][i] == 'E')
            {

                maze3[j][i] = '2';
                maze4[j][i] = '2' - 48;
            }
        }
    }
    cout << "upload done!" << endl;
}
void origin_Maze(char **maze3, int **maze4, int **maze2, int howMany_Row, int howMany_Col, char **theMaze)
{
    cout << "initialized! " << endl;
    for (int i = 0; i < howMany_Row + 2; i++)
    {
        for (int j = 0; j < howMany_Col + 2; j++)
        {
            maze4[j][i] = maze2[j][i];
            maze3[j][i] = theMaze[j][i];
        }
    }
}