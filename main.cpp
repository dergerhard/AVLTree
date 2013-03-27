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
const string line80charsSharp = "################################################################################";


/*!
 * \brief getCommand parses the command line arguments and returns the right command
 * \param argc
 * \param argv
 * \return the command to be executed
 */
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
                if (strcmp(argv[i+1], "All")==0)
                    return All;
            }
        }
    }
    return Help;
}

/*!
 * \brief printHelp prints out the help file.
 */
void printHelp()
{
    cout << "Usage: AVLTree -test [FourInsertScenarios | TimeTest | TimeTestSorted | RandomTest | All]" << endl << endl;
    cout << "- FourInsertScenarios: Tests the four possible rotations" << endl;
    cout << "- TimeTest: Measures the insert time for the values in 'testvalues.txt'" << endl;
    cout << "- TimeTestSorted: Measures the insert time for the values in 'testvalues_sorted.txt'" << endl;
    cout << "- RandomTest: Performs a test of inserting 1,000,000 random numbers and deleting 10,000 randomly" << endl;
    cout << "- All: Performs all above tests" << endl;
    cout << "ATTENTION: All commands are case sensitive!" << endl;
}


/*!
 * \brief timeTest Runs a value insert test and measures the time to do it.
 * \param filename filename with the values. ATTENTION: there can only be one value per line. Duplicates are ignored.
 */
void timeTest(string filename)
{
    cout << line80charsSharp << endl;
    cout << "Running Time Test with " << filename << endl;
    cout << line80charsSharp << endl;

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

    cout << endl << endl;
}

/*!
 * \brief fourInsertScenarios tests the four rotations with predefined input and expected output.
 */
void fourInsertScenarios()
{
    cout << line80charsSharp << endl;
    cout << "Running 4 insert scenarios" << endl;
    cout << line80charsSharp << endl;

    AVLTreeTest::testLLRotation(false);
    AVLTreeTest::testLRRotation(false);
    AVLTreeTest::testRRRotation(false);
    AVLTreeTest::testRLRotation(false);

    cout << endl << endl;
}

/*!
 * \brief randomTest inserts 1,000,000 random numbers into the tree, checks its integrity, then removes 10,000 values and checks the integrity again.
 */
void randomTest()
{
    cout << line80charsSharp << endl;
    cout << "Inserting 1,000,000 random numbers and deleting 10,000 randomly" << endl;
    cout << line80charsSharp << endl;

    AVLTreeTest::randomNumbersTest(1000000);

    cout << endl << endl;
}


/*!
 * \brief testAll calls all available tests
 */
void testAll()
{
    fourInsertScenarios();
    timeTest("testvalues.txt");
    timeTest("testvalues_sorted.txt");
    randomTest();
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

    return 0;
}
