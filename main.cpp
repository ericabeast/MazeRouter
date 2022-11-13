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
#include "func.h"
// #include "class.h"
using namespace std;

int do_count = 0;

int main(int argc, char *argv[])
{
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