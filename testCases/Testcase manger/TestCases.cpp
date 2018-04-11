#include<iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;


string GetStdoutFromCommand(string);

int main(int argc, char const *argv[]) {
  string file;
  cout << "Welcome What sy file do you want to run: " << '\n';
  cin >> file;
  string ls = GetStdoutFromCommand("ls");
  system("ls");
  cout << "LS: " << ls << endl;
  return 0;
}

string GetStdoutFromCommand(string cmd) {

    string data;
    FILE * stream;
    const int max_buffer = 256;
    char buffer[max_buffer];
    cmd.append(" 2>&1");

    stream = popen(cmd.c_str(), "r");
    if (stream) {
    while (!feof(stream))
    if (fgets(buffer, max_buffer, stream) != NULL) data.append(buffer);
    pclose(stream);
    }
    return data;
}
