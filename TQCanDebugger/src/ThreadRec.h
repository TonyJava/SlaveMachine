#ifndef THREADREC_H
#define THREADREC_H

#include <QThread>
#include <QObject>
#include <QString>
#include "can_config.h"
#include <errno.h>
#include <getopt.h>
#include <libgen.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <stdint.h>
#include <signal.h>
#include <net/if.h>

#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/uio.h>

#include <linux/can.h>
#include <linux/can/raw.h>
#define BUF_SIZ	(255)

class ThreadRec: public QThread
{
	Q_OBJECT
public:
	ThreadRec(int argc, char** pstr);
	virtual ~ThreadRec();
	void run();
	void print_usage(char *prg);
	int add_filter(u_int32_t id, u_int32_t mask);
	int MyRecieve(int argc, char **argv);
//	bool m_bHex;
public slots:
	void stop();
	signals:
	void mesRecv(QString);
private:
	int	s;
	int	running;
	struct can_filter *filter;
	int filter_count;
	char** m_argv;
	int m_argc;
};
extern int optind, opterr, optopt;
enum {
	VERSION_OPTION = CHAR_MAX + 1,
	FILTER_OPTION,
};
typedef void (*sighandler_t)(int);
extern sighandler_t signal(int signum, sighandler_t handler);
#endif
