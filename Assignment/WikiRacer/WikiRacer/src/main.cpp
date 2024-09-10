#include <iostream>     // for cout, cin
#include <fstream>      // for ifstream
#include <sstream>      // for stringstream
#include <unordered_set>
#include <vector>
#include <queue>
#include <unordered_map>
#include "wikiscraper.h"

using std::cout;            using std::endl;
using std::ifstream;        using std::stringstream;
using std::string;          using std::vector;
using std::priority_queue;  using std::unordered_map;
using std::unordered_set;   using std::cin;
using std::pair;

/*
 * This is the function you will be implementing. It takes
 * two string representing the names of a start_page and
 * end_page and is supposed to return a ladder, represented
 * as a vector<string>, of links that can be followed from
 * start_page to get to the end_page.
 *
 * For the purposes of this algorithm, the "name" of a Wikipedia
 * page is what shows at the end of the URL when you visit that page
 * in your web browser. For ex. the name of the Stanford University
 * Wikipedia page is "Stanford_University" since the URL that shows
 * in your browser when you visit this page is:
 *
 *       https://en.wikipedia.org/wiki/Stanford_University
 */
vector<string> findWikiLadder(const string& start_page, const string& end_page) {
    // TODO: 1. Once your file reading is working, replace the below
    //          return statement with "return {};".
    //       2. Make sure that you've copied over your findWikiLinks method
    //          from Part A into wikiscraper.cpp.
    //       3. Finally, implement this function per Part B in the handout!
    //
    //                Best of luck!

    // Create a WikiScraper object
    WikiScraper scraper;
    const unordered_set<string>& linkSetStart = scraper.getLinkSet(start_page);
    const unordered_set<string>& linkSetEnd = scraper.getLinkSet(end_page);

    // Comparison function for the priority queue
    auto comparator = [&scraper, &linkSetEnd](const vector<string>& ladderFirst, const vector<string>& ladderSecond) {

        const string& pageFirst = ladderFirst.back();
        const string& pageSecond = ladderSecond.back();

        const unordered_set<string>& linkSetFirst = scraper.getLinkSet(pageFirst);
        const unordered_set<string>& linkSetSecond = scraper.getLinkSet(pageSecond);

        // Calculate the number of common links between linkSetFirst and linkSetEnd
        int commonLinksFirst = std::count_if(linkSetFirst.begin(), linkSetFirst.end(), [&linkSetEnd](const string& link) {
            return linkSetEnd.find(link) != linkSetEnd.end();
        });

        // Calculate the number of common links between linkSetSecond and linkSetEnd
        int commonLinksSecond = std::count_if(linkSetSecond.begin(), linkSetSecond.end(), [&linkSetEnd](const string& link) {
            return linkSetEnd.find(link) != linkSetEnd.end();
        });

        return commonLinksFirst < commonLinksSecond;
    };


    // Creates a priority_queue names ladderQueue
    priority_queue<vector<string>, vector<vector<string>>, decltype(comparator)>
        ladderQueue(comparator);

    // Create/add a ladder containing {start_page} to the queue.
    ladderQueue.push({start_page});

    // Set to keep track of visited pages
    unordered_set<string> visitedPages;
    visitedPages.insert(start_page);

    // While the ladderQueue is not empty
    while (!ladderQueue.empty()) {

        vector<string> ladder = ladderQueue.top();
        ladderQueue.pop();

        const unordered_set<string> &currentPageLinkSet = scraper.getLinkSet(ladder.back());

        if (currentPageLinkSet.find(end_page) != currentPageLinkSet.end()) {
            ladder.push_back(end_page);
            return ladder;
        }

        for (const string& link : currentPageLinkSet) {
            if (visitedPages.find(link) == visitedPages.end()) {
                visitedPages.insert(link);
                cout << "Adding " << link << " to visitedPages" << endl;
                vector<string> newLadder = ladder;
                newLadder.push_back(link);
                ladderQueue.push(std::move(newLadder));
            }
        }
    }

    // If no ladder is found, return an empty vector
    return {};
}

int main() {
    /* Container to store the found ladders in */
    vector<vector<string>> outputLadders;

    cout << "Enter a file name: ";
    string filename;
    getline(cin, filename);

    // TODO: Create a filestream from the filename.
    //       For each pair {start_page, end_page} in the input file,
    //       retrieve the result of findWikiLadder(start_page, end_page)
    //       and append that vector to outputLadders.

    // Write code here
    ifstream inputFile(filename);
    vector<pair<string, string>> inputPairs;
    string startPage, endPage;
    int numPairs = 0;

    if (!inputFile.is_open()) {
        cout << "Error opening file" << endl;
        return EXIT_FAILURE;
    }

    inputFile >> numPairs;
    for (int n = 0; n < numPairs; n++) {
        inputFile >> startPage >> endPage;
        inputPairs.push_back({startPage, endPage});
    }

    for (auto& pair : inputPairs) {
        outputLadders.push_back(findWikiLadder(pair.first, pair.second));
    }

    /*
     * Print out all ladders in outputLadders.
     * We've already implemented this for you!
     */
    for (auto& ladder : outputLadders) {
        if(ladder.empty()) {
            cout << "No ladder found!" << endl;
        } else {
            cout << "Ladder found:" << endl;
            cout << "\t" << "{";

            std::copy(ladder.begin(), ladder.end() - 1,
                      std::ostream_iterator<string>(cout, ", "));
            /*
             * The above is an alternate way to print to cout using the
             * STL algorithms library and iterators. This is equivalent to:
             *    for (size_t i = 0; i < ladder.size() - 1; ++i) {
             *        cout << ladder[i] << ", ";
             *    }
             */
            cout << ladder.back() << "}" << endl;
        }
    }
    return 0;
}




