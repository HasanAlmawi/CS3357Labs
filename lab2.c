#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdbool.h>
#include <syslog.h>

int main(int argc, char** argv)
{
        openlog("lab-2", LOG_PERROR | LOG_PID | LOG_NDELAY, LOG_USER);

        int c, i;
        static int verbose_flag = 0;
        static int debug_flag = 0;
        char* username = NULL;

        setlogmask(LOG_UPTO(LOG_WARNING));

        while(1)
        {
                static struct option long_options[] =
                {
                        {"verbose", no_argument, &verbose_flag, 1},
                        {"username", required_argument, 0, 'u'},
                        {"debug", no_argument, &debug_flag, 1},
                        {0,0,0,0}
                };

                int option_index = 0;
                c = getopt_long(argc, argv, "vdu:", long_options, &option_index);

                //If we've reached the end of the topions, stop iterating
                if(c == -1)
                        break;

                switch(c)
                {
                        case 'u':
                                username = optarg;
                                break;

                        case 'v':
                                verbose_flag = 1;
                                break;

                        case 'd':
                                debug_flag = 1;
                                break;

                        case '?':
                                exit(EXIT_FAILURE);
                                break;
                }
        }

        if(debug_flag==1)
                {
                        setlogmask(LOG_UPTO(LOG_DEBUG));
                        syslog(LOG_DEBUG, "Hello world");
                }
        else if((debug_flag==0&&verbose_flag==0)||username==NULL)
                {
                        syslog(LOG_WARNING, "No username specified");
                }
        else
                {
                        setlogmask(LOG_UPTO(LOG_INFO));
                        syslog(LOG_INFO, "Your username is: %s", username);
                }

        closelog();
        exit(EXIT_SUCCESS);

        return 0;
}

