#include <iostream>
#include <fstream>
#include <unordered_set>
#include <algorithm>

using std::cout;            using std::endl;
using std::string;          using std::unordered_set;
using std::all_of;          using std::ifstream;

/*
 * Note that you have to pass in the file as a single string
 * into the findWikiLinks function!
 * So we have to turn the passed-in file into a single string...
 * does that sound familiar at all?
 * Find strings like <a href="/wiki/Stanford_University" title="Stanford University">
 */
unordered_set<string> findWikiLinks(const string& page_html) {
    // TODO: delete this return statement and implement the
    //       function!
    unordered_set<string> wikiLinks;
    string prefix = "<a href=\"/wiki/";
    string suffix = "\" title=";

    for (auto iter = page_html.begin(); iter != page_html.end(); iter++) {
        iter = std::search(iter, page_html.end(), prefix.begin(), prefix.end());
        if (iter == page_html.end())
            break;
        iter += prefix.size();
        auto endIter = std::find(iter, page_html.end(), '"');
        if (endIter == page_html.end())
            break;
        string linkItem(iter, endIter);

        auto lambda = [](char c) { return c != '#' && c != ':'; };
        if (all_of(linkItem.begin(), linkItem.end(), lambda))
            wikiLinks.insert(linkItem);
    }
    return wikiLinks;
}

int main() {
    /* Note if your file reading isn't working, please go to the
     * projects tab on the panel on the left, and in the run section,
     * uncheck the "Run in terminal" box and re-check it. This
     * should fix things.
     */

    cout << "Enter a file name: ";
    string filename;
    getline(std::cin, filename);
    string page_html;

    // TODO: Create a filestream from the filename, and convert it into
    //       a single string of data called page_html (declared above)

    // Write code here
    ifstream inputFile(filename);
    if (inputFile.is_open()) {
        page_html.assign(
            (std::istreambuf_iterator<char>(inputFile)),
            (std::istreambuf_iterator<char>())
        );
    }
    else {
        cout << "Error opening file" << endl;
        return EXIT_FAILURE;
    }

    unordered_set<string> validLinks = findWikiLinks(page_html);

    // TODO: Print out the validLinks set above.
    //       You can print it out in any format; this is just for you
    //       to be able to compare your results with the [output] results
    //       under the /res folder.

    // Write code here
    for (const auto& link : validLinks) {
        cout << link << endl;
    }
    return 0;
}
