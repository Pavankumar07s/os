#include <bits/stdc++.h>
#include <fcntl.h>
#include <sys/stat.h>
using namespace std;

int main() {
    const char *fifo1 = "fifo1";
    const char *fifo2 = "fifo2";

    mkfifo(fifo1, 0666);
    mkfifo(fifo2, 0666);

    char buffer[200];
    int fd1 = open(fifo1, O_RDONLY);
    read(fd1, buffer, sizeof(buffer));
    close(fd1);

    string text = buffer;
    int chars = 0, words = 0, lines = 0;

    for (char c : text) {
        if (!isspace(c)) chars++;
        if (c == ' ' || c == '\n') words++;
        if (c == '\n') lines++;
    }
    if (!text.empty()) { words++; lines++; }

    ostringstream result;
    result << "Characters: " << chars << "\n";
    result << "Words: " << words << "\n";
    result << "Lines: " << lines << "\n";

// Send this string directly through the pipe
    string output = result.str();   // convert stringstream to string
    int fd2 = open(fifo2, O_WRONLY);
    write(fd2, output.c_str(), output.size() + 1);
    close(fd2);
}
