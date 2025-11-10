#include <bits/stdc++.h>
#include <fcntl.h>
#include <sys/stat.h>


using namespace std;

int main() {
    const char *fifo1 = "fifo1";
    const char *fifo2 = "fifo2";

    mkfifo(fifo1, 0666);
    mkfifo(fifo2, 0666);

    char input[200], output[200];

    cout << "Enter a sentence:\n";
    cin.getline(input, 200);

    int fd1 = open(fifo1, O_WRONLY);
    write(fd1, input, strlen(input) + 1);
    close(fd1);

    int fd2 = open(fifo2, O_RDONLY);
    read(fd2, output, sizeof(output));
    close(fd2);

    cout << "\n--- Result from Process 2 ---\n" << output << endl;

    unlink(fifo1);
    unlink(fifo2);
}
