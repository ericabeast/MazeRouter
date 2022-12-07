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
using namespace std;

int do_count = 0;
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

int main(int argc, char *argv[])
{
    cout << "hi" << endl;
    ifstream ifs;
    ofstream ofs;
    ifs.open(argv[1]);
    ofs.open(argv[2]);
    // ofs.open("output.txt");
    string uselessRow;
    ifs >> uselessRow;
    int howMany_Row;
    ifs >> howMany_Row;

    string uselessCol;
    ifs >> uselessCol;
    int howMany_Col;
    ifs >> howMany_Col;

    // cout << howMany_Row <<endl;
    // cout << howMany_Col <<endl;

    char **theMaze;
    theMaze = new char *[howMany_Col + 2];
    for (int i = 0; i < howMany_Col + 2; i++)
    {
        theMaze[i] = new char[howMany_Row + 2];
    }
    //

    int **maze2 = new int *[howMany_Col + 2];
    for (int i = 0; i < howMany_Col + 2; ++i)
    {
        maze2[i] = new int[howMany_Row + 2];
    }
    char **maze3 = new char *[howMany_Col + 2];
    for (int i = 0; i < howMany_Col + 2; ++i)
    {
        maze3[i] = new char[howMany_Row + 2];
    }
    int **maze4 = new int *[howMany_Col + 2];
    for (int i = 0; i < howMany_Col + 2; ++i)
    {
        maze4[i] = new int[howMany_Row + 2];
    }
    //
    for (int i = 0; i < howMany_Col + 2; i++)
    {
        for (int j = 0; j < howMany_Row + 2; j++)
        {
            theMaze[i][j] = '0';
            //
            maze2[i][j] = '0' - 48;
            maze3[i][j] = '0';
            maze4[i][j] = '0' - 48;
            //
        }
    }
    for (int i = 0; i < howMany_Row + 2; i++)
    {
        theMaze[0][i] = '2';
        theMaze[howMany_Col + 1][i] = '2';
        //
        maze2[0][i] = '2' - 48;
        maze2[howMany_Col + 1][i] = '2' - 48;
        maze3[0][i] = '2';
        maze3[howMany_Col + 1][i] = '2';
        maze4[0][i] = '2' - 48;
        maze4[howMany_Col + 1][i] = '2' - 48;
        //
    }
    for (int i = 0; i < howMany_Col + 2; i++)
    {
        theMaze[i][0] = '2';
        theMaze[i][howMany_Row + 1] = '2';
        //
        maze2[i][0] = '2' - 48;
        maze2[i][howMany_Row + 1] = '2' - 48;
        maze3[i][0] = '2';
        maze3[i][howMany_Row + 1] = '2';
        maze4[i][0] = '2' - 48;
        maze4[i][howMany_Row + 1] = '2' - 48;
        //
    }
    //
    key a;
    position temp;
    position last;
    int now;
    stack<position> path;
    stack<position> path2;
    queue<position> way;
    int number = 1;

    //
    string uselessBlk;
    ifs >> uselessBlk;
    int howMany_Blk;
    ifs >> howMany_Blk;
    for (int i = 0; i < howMany_Blk; i++)
    {
        int left_down_x, left_down_y, right_up_x, right_up_y;
        ifs >> left_down_x;
        ifs >> left_down_y;
        ifs >> right_up_x;
        ifs >> right_up_y;
        for (int j = 0; j <= right_up_x - left_down_x; j++)
        {
            for (int k = 0; k <= right_up_y - left_down_y; k++)
            {
                theMaze[left_down_x + j + 1][left_down_y + k + 1] = '2';
                maze2[left_down_x + j + 1][left_down_y + k + 1] = '2' - 48;
                maze3[left_down_x + j + 1][left_down_y + k + 1] = '2';
                maze4[left_down_x + j + 1][left_down_y + k + 1] = '2' - 48;
            }
        }
    }

    string uselessNet;
    ifs >> uselessNet;
    int howMany_Net;
    ifs >> howMany_Net;

    vector<vector<position>> theRoute(howMany_Net);
    vector<Net> theNet(howMany_Net);
    for (int i = 0; i < howMany_Net; i++)
    {
        int Source_X, Source_Y, Target_X, Target_Y;
        string netName;
        ifs >> netName;
        ifs >> Source_X;
        ifs >> Source_Y;
        ifs >> Target_X;
        ifs >> Target_Y;
        theNet[i].netName = netName;
        theNet[i].Source_X = Source_X + 1;

        theNet[i].Source_Y = Source_Y + 1;
        theNet[i].Target_X = Target_X + 1;
        theNet[i].Target_Y = Target_Y + 1;
        theMaze[Source_X + 1][Source_Y + 1] = '2';
        // a.set_start(Source_X+1,Source_Y+1);
        //
        maze2[Source_X + 1][Source_Y + 1] = 2;
        maze3[Source_X + 1][Source_Y + 1] = '2';
        maze4[Source_X + 1][Source_Y + 1] = 2;
        //
        theMaze[Target_X + 1][Target_Y + 1] = '2';
        // a.set_end(Target_X+1,Target_Y+1);
        //
        maze2[Target_X + 1][Target_Y + 1] = 2;
        maze3[Target_X + 1][Target_Y + 1] = '2';
        maze4[Target_X + 1][Target_Y + 1] = 2;
        //
        // cout << "Source x: "<<Source_X+1<<" Source y: "<<Source_Y+1 <<endl;
    }

    int round = 0;
    int totalRound = 1;
    vector<int> allPermutation;

    string aString;
    string str = "";
    while (round != howMany_Net)
    {
        totalRound = totalRound * (round + 1);
        round++;
    }
    //// permutation
    for (int i = 1; i <= howMany_Net; i++)
    {
        aString = to_string(i);
        str = str + aString;
    }
    int n = str.size();
    permute(str, 0, n - 1, allPermutation);
    ////////////////////////////////////
    // for(int i = 0 ;i<allPermutation.size();i++){
    //     cout << allPermutation[i]<<endl;
    // }

    int allround = 0;
    int current_number;

    // cout << totalRound <<endl;
    // cout << allPermutation[0]<<endl;
    int finish;
    int whetherFound = 1;
    while (allround != totalRound)
    {
        current_number = allPermutation[allround];
        finish = 0;
        string priority = to_string(current_number);
        string receiver;

        int theArray[howMany_Net];
        for (int i = 0; i < howMany_Net; i++)
        {

            // cout << receiver<<endl;
            theArray[i] = priority[i] - '0';
            // cout << theArray[i]<<endl;
        }
        // cout <<"~~~~~~~~~~~~~~~~"<<endl;
        // cout << theNet[0].Source_X<<endl;
        // cout << theNet[0].Source_Y<<endl;
        // cout << theNet[0].Target_X<<endl;
        // cout << theNet[0].Target_Y<<endl;
        // cout << theArray[0]<<endl;
        for (int i = 0; i < howMany_Net; i++)
        {
            // cout << theNet[theArray[i]-1].Target_X<<endl;
            // cout << theNet[theArray[i]-1].Target_Y <<endl;
            // cout << "theArray[i]-1: " ;
            // cout <<theArray[i]-1<<endl;

            maze3[theNet[theArray[i] - 1].Target_X][theNet[theArray[i] - 1].Target_Y] = 'E';
            maze4[theNet[theArray[i] - 1].Target_X][theNet[theArray[i] - 1].Target_Y] = -1;
            maze3[theNet[theArray[i] - 1].Source_X][theNet[theArray[i] - 1].Source_Y] = 'S';
            maze4[theNet[theArray[i] - 1].Source_X][theNet[theArray[i] - 1].Source_Y] = 3;
            a.set_start(theNet[theArray[i] - 1].Source_X, theNet[theArray[i] - 1].Source_Y);
            a.set_end(theNet[theArray[i] - 1].Target_X, theNet[theArray[i] - 1].Target_Y);
            // if(allround == 120){
            //     cout << "Line~~~Line~~Line"<<endl;
            //     cout <<theArray[i]<<endl;
            //     cout << endl;
            //     cout <<"before S E~~~~~~~~~~"<<endl;
            //     for(int i = howMany_Row+1;i >=0 ; i--){
            //         for(int j=0; j < howMany_Col+2 ; j++){
            //             cout << maze3[j][i]<< "\t";
            //         }
            //         cout << endl;
            //     }

            // }
            // cout <<"wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww"<<endl;

            // cout << "maze 4" << endl;
            // cout << "do count: "<<++do_count << endl;
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
            if (1 == goMaze(howMany_Row, howMany_Col, maze3, maze4, a, path, path2, way, theArray[i] - 1, theRoute, allround))
            {
                while (!way.empty())
                    way.pop();
                upload_Maze(maze3, maze4, maze2, howMany_Row, howMany_Col, theArray[i], allround);
                // cout <<"!! 55 !!"<<endl;
                // cout << maze3[5][5]<<endl;
                // cout << maze4[5][5]<<endl;
                finish++;
            }
            else
            {
                while (!way.empty())
                {
                    way.pop();
                }
                // cout <<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
                origin_Maze(maze3, maze4, maze2, howMany_Row, howMany_Col, theMaze);
                for (int i = 0; i < theRoute.size(); i++)
                {
                    theRoute[i].clear();
                }

                finish = 0;
            }
        }
        if (finish == howMany_Net)
        {
            // cout <<" all around:"<<allround<<endl;
            break;
        }

        allround++;
        if (allround == totalRound)
        {
            // cout << "No solution is found"<<endl;
            whetherFound = 0;
            ///////  if code enters here, it means no solution is found.
        }
    }
    allround = 0;
    vector<position> toBeDone;
    position toBe;
    // cout << "before next while loop"<<endl;
    // cout << endl;
    // for(int i = howMany_Row+1;i >=0 ; i--){
    //     for(int j=0; j < howMany_Col+2 ; j++){
    //         cout << maze3[j][i]<< "\t";
    //     }
    //     cout << endl;
    // }
    // cout << endl;

    if (whetherFound == 0)
    {
        while (allround != totalRound)
        {
            current_number = allPermutation[allround];
            finish = 0;
            string priority = to_string(current_number);
            string receiver;

            int theArray[howMany_Net];
            for (int i = 0; i < howMany_Net; i++)
            {

                // cout << receiver<<endl;
                theArray[i] = priority[i] - '0';
                // cout << theArray[i]<<endl;
            }

            origin_Maze(maze3, maze4, maze2, howMany_Row, howMany_Col, theMaze);
            for (int i = 0; i < howMany_Net; i++)
            {

                maze3[theNet[theArray[i] - 1].Target_X][theNet[theArray[i] - 1].Target_Y] = 'E';
                maze4[theNet[theArray[i] - 1].Target_X][theNet[theArray[i] - 1].Target_Y] = -1;
                maze3[theNet[theArray[i] - 1].Source_X][theNet[theArray[i] - 1].Source_Y] = 'S';
                maze4[theNet[theArray[i] - 1].Source_X][theNet[theArray[i] - 1].Source_Y] = 3;
                // cout << "Maze4 "<<endl;
                // for(int k = howMany_Row+1;k >=0 ; k--){
                //         for(int j=0; j < howMany_Col+2 ; j++){
                //             cout << maze4[j][k]<< "\t";
                //         }
                //         cout << endl;
                //     }
                a.set_start(theNet[theArray[i] - 1].Source_X, theNet[theArray[i] - 1].Source_Y);
                a.set_end(theNet[theArray[i] - 1].Target_X, theNet[theArray[i] - 1].Target_Y);
                if (i == 0)
                {
                    goMaze(howMany_Row, howMany_Col, maze3, maze4, a, path, path2, way, theArray[i] - 1, theRoute, allround);
                    while (!way.empty())
                        way.pop();
                    // for(int k = howMany_Row+1;k >=0 ; k--){
                    //     for(int j=0; j < howMany_Col+2 ; j++){
                    //         cout << maze4[j][k]<< "\t";
                    //     }
                    //     cout << endl;
                    // }

                    upload_Maze(maze3, maze4, maze2, howMany_Row, howMany_Col, theArray[i], allround);
                    for (int j = 0; j < theRoute[theArray[i] - 1].size(); j++)
                    {
                        toBe.x = theRoute[theArray[i] - 1][j].x;
                        toBe.y = theRoute[theArray[i] - 1][j].y;
                        // cout <<"tobe.x "<< toBe.x <<" tobe.y: "<<toBe.y;
                        toBeDone.push_back(toBe);
                    }
                    for (int i = 0; i < theRoute.size(); i++)
                    {
                        theRoute[i].clear();
                    }
                    maze3[theNet[theArray[i] - 1].Target_X][theNet[theArray[i] - 1].Target_Y] = 'E';
                    maze4[theNet[theArray[i] - 1].Target_X][theNet[theArray[i] - 1].Target_Y] = -1;
                    maze3[theNet[theArray[i] - 1].Source_X][theNet[theArray[i] - 1].Source_Y] = 'S';
                    maze4[theNet[theArray[i] - 1].Source_X][theNet[theArray[i] - 1].Source_Y] = 3;
                    // cout <<endl;
                    // cout << "intend to block"<<endl;
                    // for(int k = howMany_Row+1;k >=0 ; k--){
                    //     for(int j=0; j < howMany_Col+2 ; j++){
                    //         cout << maze3[j][k]<< "\t";
                    //     }
                    //     cout << endl;
                    // }
                    // cout << endl;
                    // for(int k = howMany_Row+1;k >=0 ; k--){
                    //     for(int j=0; j < howMany_Col+2 ; j++){
                    //         cout << maze4[j][k]<< "\t";
                    //     }
                    //     cout << endl;
                    // }

                    // cout << "special part 1 end" << endl;
                }

                if (1 == goMaze(howMany_Row, howMany_Col, maze3, maze4, a, path, path2, way, theArray[i] - 1, theRoute, allround))
                {
                    while (!way.empty())
                        way.pop();
                    upload_Maze(maze3, maze4, maze2, howMany_Row, howMany_Col, theArray[i], allround);
                    // if(i == 0){
                    //      cout << "find a route"<<endl;

                    // }
                    // cout <<"!! 55 !!"<<endl;
                    // cout << maze3[5][5]<<endl;
                    // cout << maze4[5][5]<<endl;
                    finish++;
                }
                else
                {
                    while (!way.empty())
                    {
                        way.pop();
                    }
                    // cout <<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
                    origin_Maze(maze3, maze4, maze2, howMany_Row, howMany_Col, theMaze);
                    for (int i = 0; i < theRoute.size(); i++)
                    {
                        theRoute[i].clear();
                    }

                    finish = 0;
                }

                // cout << "normal part  end" << endl;
                // cout <<"after ~~~~~~"<<endl;
                // for(int k = howMany_Row+1;k >=0 ; k--){
                //     for(int j=0; j < howMany_Col+2 ; j++){
                //         cout << maze3[j][k]<< "\t";
                //     }
                //     cout << endl;
                // }
                if (i == 0)
                {
                    for (int j = 0; j < toBeDone.size(); j++)
                    {
                        maze3[toBeDone[j].x][toBeDone[j].y] = '0';
                        maze4[toBeDone[j].x][toBeDone[j].y] = '0' - 48;
                    }
                    toBeDone.clear();
                    // cout << "after i = 0:"<<endl;
                }
                // cout << endl;

                //  for(int k = howMany_Row+1;k >=0 ; k--){
                //     for(int j=0; j < howMany_Col+2 ; j++){
                //         cout << maze3[j][k]<< "\t";
                //     }
                //     cout << endl;
                // }
            }
            if (finish == howMany_Net)
            {
                // cout <<" all around:"<<allround<<endl;
                break;
            }

            allround++;
            // if (allround == totalRound){
            //     cout << "No solution is found"<<endl;
            //     whetherFound = 0;
            //     ///////  if code enters here, it means no solution is found.
            // }
        }
    }

    // cout << endl;
    // for(int i = howMany_Row+1;i >=0 ; i--){
    //     for(int j=0; j < howMany_Col+2 ; j++){
    //         cout << maze3[j][i]<< "\t";
    //     }
    //     cout << endl;
    // }
    // cout << endl;

    // for(int i = 0 ;i<howMany_Net;i++){
    //     cout << "Net: "<<i+1<<endl;
    //     for(int j = 0;j<theRoute[i].size();j++){
    //         cout <<"x:" <<theRoute[i][j].x<<"  y:"<< theRoute[i][j].y<<"\t";
    //     }
    //     cout << endl;
    // }
    // for(int i = 0 ;i<howMany_Net;i++){
    //     for(int j = 0;j<theRoute[i].size();j++){
    //        maze3[theRoute[i][j].x][theRoute[i][j].y] = i+10;
    //     }
    // }
    // for (int i = 0; i < howMany_Net; i++)
    // {
    //     cout << theNet[i].netName << endl;
    //     cout << "begin" << endl;
    //     cout << theRoute[i].size() << endl;
    //     cout << theNet[i].Target_X - 1 << " " << theNet[i].Target_Y - 1 << " " << theRoute[i][0].x - 1 << " " << theRoute[i][0].y - 1 << endl;
    //     for (int j = 0; j < theRoute[i].size() - 1; j++)
    //     {
    //         cout << theRoute[i][j].x - 1 << " " << theRoute[i][j].y - 1 << " " << theRoute[i][j + 1].x - 1 << " " << theRoute[i][j + 1].y - 1 << endl;
    //     }
    //     cout << theRoute[i][theRoute[i].size() - 1].x - 1 << " " << theRoute[i][theRoute[i].size() - 1].y - 1 << " " << theNet[i].Source_X - 1 << " " << theNet[i].Source_Y - 1 << endl;
    //     cout << "end" << endl;
    //     cout << endl;
    // }
    for (int i = 0; i < howMany_Net; i++)
    {
        ofs << theNet[i].netName << endl;
        ofs << "begin" << endl;
        ofs << theRoute[i].size() << endl;
        ofs << theNet[i].Target_X - 1 << " " << theNet[i].Target_Y - 1 << " " << theRoute[i][0].x - 1 << " " << theRoute[i][0].y - 1 << endl;
        for (int j = 0; j < theRoute[i].size() - 1; j++)
        {
            ofs << theRoute[i][j].x - 1 << " " << theRoute[i][j].y - 1 << " " << theRoute[i][j + 1].x - 1 << " " << theRoute[i][j + 1].y - 1 << endl;
        }
        ofs << theRoute[i][theRoute[i].size() - 1].x - 1 << " " << theRoute[i][theRoute[i].size() - 1].y - 1 << " " << theNet[i].Source_X - 1 << " " << theNet[i].Source_Y - 1 << endl;
        ofs << "end" << endl;
        ofs << endl;
    }

    // walk maze
    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////
}