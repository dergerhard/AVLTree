#include <iostream>
#include "avltree.h"
#include "avltreetest.h"
#include <cstdlib>
#include <set>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cctype>

enum Cmd{ FourInsertScenarios, TimeTest, TimeTestSorted, RandomTest, All, Help};

Cmd getCommand(int argc, char *argv[])
{
    for (int i=0; i<argc; i++)
    {
        if (strcmp(argv[i], "--help")==0)
            return Help;
        else if (strcmp(argv[i], "-test")==0)
        {
            if ((i+1)<argc)
            {
                if (strcmp(argv[i+1], "FourInsertScenarios")==0)
                    return FourInsertScenarios;
                if (strcmp(argv[i+1], "TimeTest")==0)
                    return TimeTest;
                if (strcmp(argv[i+1], "TimeTestSorted")==0)
                    return TimeTestSorted;
                if (strcmp(argv[i+1], "RandomTest")==0)
                    return RandomTest;
                if (strcmp(argv[i+1], "All")==0
                        )
                    return All;
            }
        }
    }
    return All;
}

void printHelp()
{
    cout << "Usage: AVLTree -test [FourInsertScenarios | TimeTest | TimeTestSorted | RandomTest | All]" << endl << endl;
    cout << "   FourInsertScenarios: Tests the four possible rotations" << endl << endl;
    cout << "   TimeTest: Measures the insert time for the values in 'testvalues.txt'" << endl << endl;
    cout << "   TimeTestSorted: Measures the insert time for the values in 'testvalues_sorted.txt'" << endl << endl;
    cout << "   RandomTest: Performs a test of inserting 1,000,000 random numbers and deleting 10,000 randomly" << endl << endl;
    cout << "   All: Performs all above tests" << endl << endl;
    cout << "All commands are case sensitive!" << endl;
}


void timeTest(string filename)
{
    cout << line80chars << endl;
    cout << "Running Time Test with " << filename << endl;
    cout << line80chars << endl;

    int nextValue;
    int count=0;

    ifstream sortedFile(filename.c_str());
    set<int> *sBuf = new set<int>();
    if (sortedFile.is_open())
    {
        while ( sortedFile.good() )
        {
            sortedFile >> nextValue;
            sBuf->insert(nextValue);
            count++;
        }
        sortedFile.close();

        clock_t begin = clock();
        AVLTree<int> * t = new AVLTree<int>;
        for (set<int>::const_iterator it = sBuf->begin(); it!= sBuf->end(); it++)
        {
            t->insert(*it);
        }
        clock_t end = clock();


        cout << "Time to input " << count << " values: " << ((end-begin)/1000) << "ms" << endl;
        cout << "Values in AVLTree: " << sBuf->size() << endl; // buf->size() << endl; //t->size() << endl;
        delete t;
    }
    else cout << "Unable to open file";
}

void fourInsertScenarios()
{

}

void randomTest()
{

}

void testAll()
{

}

int main(int argc, char *argv[]) {

    Cmd cmd = getCommand(argc, argv);


    switch (cmd)
    {
    case Help: printHelp(); break;
    case TimeTest: timeTest("testvalues.txt"); break;
    case TimeTestSorted: timeTest("testvalues_sorted.txt"); break;
    case FourInsertScenarios: fourInsertScenarios(); break;
    case RandomTest: randomTest(); break;
    case All: testAll(); break;
    }


    AVLTree<int> *t = new AVLTree<int>();


    /*AVLTreeTest::testLLRotation(false);
    AVLTreeTest::testLRRotation(false);
    AVLTreeTest::testRRRotation(false);
    AVLTreeTest::testRLRotation(false);
*/


    /*
    //BENCHMARK----------------------------------------------------------------
    set<int> s;
    srand (time(NULL));

    for (int i=0; i<20000000; i++)
    {
        int r = rand()%1000000000+1;
        s.insert(r);
        //cout << "Nr. " << i << ": " << r << endl;
    }
    cout << "Random numbers ready!" << endl;

    vector<float> benchmark;
    clock_t begin;
    clock_t end;
    int c=0;
    int resolution = 100000; //all 100 elements a time measurement is taken

    begin = clock();
    for (set<int>::iterator i=s.begin(); i!=s.end(); ++i)
    {
        if (c%resolution==1)
            begin=clock();

        t->insert(*i);

        if (c%resolution==0)
        {
            //cout << "@element " << c << ". ";
            end = clock();
            //cout << "Time to insert into tree: " << ((((float)end)-((float)begin))/1000) << "ms " << endl;

            cout << c << ";" << ((((float)end)-((float)begin))/1000) << ";" << endl;
            //benchmark.push_back(((((float)end)-((float)begin))));
        }
        c++;
    }

    for (int i=0; i<benchmark.size(); i++)
    {
        cout << "Time " << i << ": " << benchmark.at(i) << endl;
    }


    cout << "Time to insert into tree: " << ((((float)end)-((float)begin))/1000) << "ms " << endl;

    cout << "set size:  " << s.size() << endl;
    cout << "tree size: " << t->size() << endl;

    //END BENCHMARK ----------------------------------------------------------------
    */



    /*
    //MANUAL INPUT TEST
    while (true)
    {
        int x=0;
        cin >> x;
        t->insert(x);
        t->print();
    }

    t->print();

    */

/*
    //Trausmuth benchmark



    //Test the tree with random numbers
    //AVLTreeTest::randomNumbersTest(20);

*/



    /*
    AVLTreeTest::randomNumbersTest(2000000);

    AVLTree<int> *tr = new AVLTree<int>;

    for (int i=20; i<=90; i+=5)
        tr->insert(i);

    tr->print();

    for (int i=20; i<=90; i+=5)
    {
        int x;
        cin >> x;

        tr->remove(x);
        tr->print();
        cout << x << " REMOVED!!, size=" << tr->size() << endl;
    }
*/


    return 0;
}
