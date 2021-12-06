#include <stdio.h>
#include <stdlib.h>
#include "q.h"
int enter(char *objname, int priority)
{
	int len, s_qid;
	struct q_entry s_entry; /* 메시지를 저장할 구조 */
							/* 이름의 길이, 우선순위 수준을 확인한다. */
	if ((len = strlen(objname)) > MAXOBN)
	{
		warn("name too long");
		return (-1);
	}
	if (priority > MAXPRIOR || priority < 0)
	{
		warn("invalid priority level");
		return (-1);
	}
	/* 필요에 따라 메시지 큐를 초기화한다. */
	if ((s_qid = init_queue()) == -1)
		return (-1);
	/* s_entry를 초기화한다. */
	s_entry.mtype = (long)priority;
	strncpy(s_entry.mtext, objname, MAXOBN);
	/* 메시지를 보내고, 필요할 경우 기다린다. */
	if (msgsnd(s_qid, &s_entry, len, 0) == -1)
	{
		perror("msgsnd failed");
		return (-1);
	}
	else
		return (0);
}
int warn(char *s)
{
	fprintf(stderr, "warning: %s\n", s);
}
/* init_queue -- 큐 식별자를 획득한다. */
#include "q.h"
int init_queue(void)
{
	int queue_id;
	/* 메시지 큐를 생성하거나 개방하려고 시도한다 */
	if ((queue_id = msgget(QKEY, IPC_CREAT | QPERM)) == -1)
		perror("msgget failed");
	return (queue_id);
}
int serve(void)
{
	int mlen, r_qid;
	struct q_entry r_entry;
	/* 필요에 따라 메시지 큐를 초기화한다. */
	if ((r_qid = init_queue()) == -1)
		return (-1);
	for (;;)
	{
		if ((mlen = msgrcv(r_qid, &r_entry, MAXOBN, (-1 * MAXPRIOR), MSG_NOERROR)) == -1)
		{
			perror("msgrcv failed");
			return (-1);
		}
		else
		{
			/* 우리가 문자열을 가지고 있는지 확인한다. */
			r_entry.mtext[mlen] = '\0';
			/* 객체 이름을 처리한다. */
			proc_obj(&r_entry);
		}
	}
}
main()
{
	pid_pid;
	switch (pid = fork())
	{
	case 0: /* 자식 */
		serve();
		break; /* 실제로는, 서버는 결코 퇴장(exit)하지
			   않음 */
	case -1:
		warn("fork to start server failed");
		break;
	default:
		printf("server process pid is %d\n", pid);
	}
	exit(pid != -1 ? 0 : 1);
}
int proc_obj(struct q_entry *msg)
{
	printf("\npriority: %ld name: %s\n", msg > mtype, msg - > mtext);
}