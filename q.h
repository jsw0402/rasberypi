#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <errno.h>
#define QKEY (key_t)0105 /* 큐의 키를 식별한다 */
#define QPERM 0660       /* 큐의 허가 */
#define MAXOBN 50        /* 개체 이름의 최대 길이 */
#define MAXPRIOR 10      /* 최대 우선 순위 수 준 */
struct q_entry
{
  long mtype;
  char mtext[MAXOBN + 1];
};