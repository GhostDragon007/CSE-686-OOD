In this first project we will build and test a facility for converting a C++ source code file to a web page3, with essentially the same content. Here's what it does:
<h3>Finds and Loads a file for processing:</h3>
Files will be loaded when their names match a regular expression. That might be as simple as *.h, but will often be somewhat more complex. You will spend some time getting familiar with the C++11 regex classes. Files that match can be opened with the std::iostream facilities.
vConverts file into a webpage fragment:</h3>
That entails creating a new file with the same name, but with an html extension. Contents of the source code file are copied directly to the html file.
Then all html markup characters are replaced with their exscape sequence equivalents, e.g., < is replaced by &lt, etc.
That text is prepended with "<pre>" and postpended with "</pre>". That ensures that the rendered text preserves all of the white space included in the original file.
<h3>Convert html fragment into a valid html document:</h3>
This is done by adding template text (from a template file) for a head section and the beginning of the body4. Finally a small piece of template code, read from a template file is added to the end of the html fragment text.
At this point the file is viewable in a browser.
