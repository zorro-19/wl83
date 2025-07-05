#include "lwip.h"
#include "lwip/sockets.h"
#include "lwip/dns.h"

void iperf_cmd(void *str)
{
    printf("iperf cmd :%s\n", str);
    char *argv[32] = {"iperf3", 0}; //p:f:i:D1VJvsc:ub:t:n:k:l:P:Rw:B:M:N46S:L:ZO:F:A:T:C:dI:hX:
    int argc = 0;
    char *cmd = str;
    char *token = strtok(cmd, " ");

    while (token != NULL) {
        if (strcmp(token, "-c") == 0) {
            token = strtok(NULL, " ");
            argv[++argc] = "-c";
            argv[++argc] = token;
        } else if (strcmp(token, "-p") == 0) {
            token = strtok(NULL, " ");
            argv[++argc] = "-p";
            argv[++argc] = token;
        } else if (strcmp(token, "-t") == 0) {
            token = strtok(NULL, " ");
            argv[++argc] = "-t";
            argv[++argc] = token;
        } else if (strcmp(token, "-b") == 0) {
            token = strtok(NULL, " ");
            argv[++argc] = "-b";
            argv[++argc] = token;
        } else if (strcmp(token, "-i") == 0) {
            token = strtok(NULL, " ");
            argv[++argc] = "-i";
            argv[++argc] = token;
        } else if (strcmp(token, "-u") == 0) {
            argv[++argc] = "-u";
        } else if (strcmp(token, "-R") == 0) {
            argv[++argc] = "-R";
        } else if (strcmp(token, "-s") == 0) {
            argv[++argc] = "-s";
            argv[++argc] = "-d";
            /* as_server = 1; */
        } else if (strcmp(token, "-d") == 0) {
            argv[++argc] = "-d";
        } else if (strcmp(token, "-S") == 0) {
            token = strtok(NULL, " ");
            argv[++argc] = "-S";
            argv[++argc] = token;
        } else if (strcmp(token, "-l") == 0) {
            token = strtok(NULL, " ");
            argv[++argc] = "-l";
            argv[++argc] = token;
        } else if (strcmp(token, "-w") == 0) {
            token = strtok(NULL, " ");
            argv[++argc] = "-w";
            argv[++argc] = token;
        } else if (strcmp(token, "-P") == 0) {
            token = strtok(NULL, " ");
            argv[++argc] = "-P";
            argv[++argc] = token;
        }

        token = strtok(NULL, " ");
    }

    iperf_main(++argc, argv);
}

//bbm一设备端作为iperf client，另一设备端作为iperf server 进行吞吐测试

//client example
void iperf_client(void)
{
    char cmd[] = "iperf3 -c 192.168.1.2 -u -p 5001 -t 1200 -b 40M -l 1200 -R";
    iperf_cmd(cmd);
}

//server example
void iperf_server(void)
{
    char cmd[] = "iperf3 -s -i 1 -p 5001 -d";
    iperf_cmd(cmd);
}

