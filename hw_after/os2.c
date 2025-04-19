#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <limits.h>

#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)

#define container_of(ptr, type, member) ({                      \
        const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
        (type *)( (char *)__mptr - offsetof(type,member) );})

#define LIST_POISON1  ((void *) 0x00100100)
#define LIST_POISON2  ((void *) 0x00200200)

struct list_head {
    struct list_head* next, * prev;
};

#define LIST_HEAD_INIT(name) { &(name), &(name) }
#define LIST_HEAD(name) \
    struct list_head name = LIST_HEAD_INIT(name)
#define INIT_LIST_HEAD(ptr) do { \
    (ptr)->next = (ptr); (ptr)->prev = (ptr); \
} while (0)

static inline void __list_add(struct list_head* new,
    struct list_head* prev,
    struct list_head* next) {
    next->prev = new;
    new->next = next;
    new->prev = prev;
    prev->next = new;
}

static inline void list_add(struct list_head* new, struct list_head* head) {
    __list_add(new, head, head->next);
}

static inline void list_add_tail(struct list_head* new, struct list_head* head) {
    __list_add(new, head->prev, head);
}

static inline void __list_del(struct list_head* prev, struct list_head* next) {
    next->prev = prev;
    prev->next = next;
}

static inline void list_del(struct list_head* entry) {
    __list_del(entry->prev, entry->next);
    entry->next = LIST_POISON1;
    entry->prev = LIST_POISON2;
}

static inline int list_empty(const struct list_head* head) {
    return head->next == head;
}

#define list_entry(ptr, type, member) \
    container_of(ptr, type, member)

#define list_for_each(pos, head) \
  for (pos = (head)->next; pos != (head);   \
       pos = pos->next)

#define list_for_each_safe(pos, n, head) \
    for (pos = (head)->next, n = pos->next; pos != (head); \
        pos = n, n = pos->next)

#define list_for_each_entry(pos, head, member)              \
    for (pos = list_entry((head)->next, typeof(*pos), member);   \
         &pos->member != (head);                   \
         pos = list_entry(pos->member.next, typeof(*pos), member))

#define list_for_each_entry_safe(pos, n, head, member)            \
    for (pos = list_entry((head)->next, typeof(*pos), member),   \
        n = list_entry(pos->member.next, typeof(*pos), member);  \
         &pos->member != (head);                   \
         pos = n, n = list_entry(n->member.next, typeof(*n), member))

#if 0
#define debug(fmt, args...) fprintf(stderr, fmt, ##args)
#else
#define debug(fmt, args...)
#endif

typedef struct {
    unsigned char operation; //operation
    unsigned char length;   //length
} code;

typedef struct {
    int pid;                //ID
    int arrival_time;       //도착시간
    int code_bytes;         //코드길이(바이트)
    code* operations;
    struct list_head job, ready, wait;
} process;

int totalclock = 0;
int Total_Clock(int Clock, process* cur, int i) {
    totalclock = cur->operations[i].length + Clock;
    return totalclock;
}

int main(int argc, char* argv[]) {
    int present_pid = 0;
    int PC = 0;
    int Clock = 0;
    int Idle = 0;
    int Procs_cnt = 0;
    int procs_cnt = 0;
    int before_clk = 0;
    int switch_cnt = 0;
    int next_pid = 0;
    int total_Idle = 0;

    process* cur, * next;
    LIST_HEAD(job_q);
    LIST_HEAD(ready_q);
    LIST_HEAD(wait_q);

    cur = malloc(sizeof(*cur));
    while (fread(cur, 12, 1, stdin) == 1) {
        cur->operations = malloc((cur->code_bytes / 2) * sizeof(code));
        fread(cur->operations, ((cur->code_bytes / 2) * sizeof(code)), 1, stdin);
        //여기에 코드 작성         // job node 초기화 (과제#1)
        INIT_LIST_HEAD(&cur->job);
        INIT_LIST_HEAD(&cur->ready);
        INIT_LIST_HEAD(&cur->wait);
        //여기에 코드 작성         // job queue에 cur->job 추가 (과제#1)
        list_add_tail(&cur->job, &job_q);
        cur = malloc(sizeof(*cur));
    }

    //Idle 프로세스 추가
    cur = malloc(sizeof(*cur));
    cur->pid = 100;
    cur->arrival_time = 0;
    cur->code_bytes = 2;
    cur->operations = malloc((cur->code_bytes / 2) * sizeof(code));
    cur->operations[0].operation = 255;
    cur->operations[0].length = 0;
    //여기에 코드 작성           // job node 초기화 (과제#1)
    INIT_LIST_HEAD(&cur->job);
    INIT_LIST_HEAD(&cur->ready);
    INIT_LIST_HEAD(&cur->wait);
    //여기에 코드 작성           // job queue에 cur->job 추가 (과제#1)
    list_add_tail(&cur->job, &job_q);

    list_for_each_entry(cur, &job_q, job) {
        if (cur->pid != 100) {
            Procs_cnt++;
        }
    }

    while (Clock <= totalclock) {
        list_for_each_entry(cur, &job_q, job) {
            if (Clock == cur->arrival_time) {
                //여기에 코드 작성           
                INIT_LIST_HEAD(&cur->ready);
                INIT_LIST_HEAD(&cur->wait);
                //여기에 코드 작성           
                list_add_tail(&cur->ready, &ready_q);
                //여기에 코드 작성           //로드된 프로세스 정보 출력
                printf("%04d CPU: Loaded PID: %03d\tArrival: %03d\tCodesize: %03d\tPC: %03d\n",
                       Clock, cur->pid, cur->arrival_time, cur->code_bytes / 2, PC);
            }
        }
        if (Clock == totalclock) {
            list_for_each_entry(cur, &wait_q, wait) {
                if (present_pid == cur->pid) {
                    //여기에 코드 작성         
                    INIT_LIST_HEAD(&cur->ready);
                    list_add_tail(&cur->ready, &ready_q);
                    //여기에 코드 작성         
                    list_del(&cur->wait);
                    //여기에 코드 작성        
                    break;
                }
                break;
            }
        }
        list_for_each_entry_safe(cur, next, &ready_q, ready) {
            if (Clock == totalclock) {
                if (present_pid == -1 && cur->pid != 100) {
                    present_pid = cur->pid;
                    next_pid = next->pid;
                }
                if (present_pid == cur->pid && cur->operations[PC].length == Clock - before_clk) {
                    PC++;
                    if (PC == cur->code_bytes / 2) {
                        //여기에 코드작성                   //프로세스가 끝나면 ready_q에서 삭제
                        list_del(&cur->ready);
                        procs_cnt++;
                        if (Procs_cnt == procs_cnt) {
                            break;
                        }
                        present_pid = -1;
                        //여기에 코드작성                   // context switch 되기 때문에 Total clock 증가
                        totalclock += 10;
                        switch_cnt++;
                        PC = 0;
                    }
                }
                if (present_pid == cur->pid && cur->operations[PC].operation == 0
                    && cur->operations[PC].length != Clock - before_clk) {
                    totalclock = Total_Clock(Clock, cur, PC);
                    before_clk = Clock;
                }
                if (present_pid == cur->pid && cur->operations[PC].operation == 1
                    && cur->operations[PC].length != Clock - before_clk) {
                    totalclock = Total_Clock(Clock, cur, PC);
                    //여기에 코드 작성              //IO작업 문구 출력
                    printf("%04d CPU: OP_IO START len: %03d ends at: %04d\n",
                           Clock, cur->operations[PC].length, totalclock);
                    //여기에 코드 작성              //wait노드 초기화
                    INIT_LIST_HEAD(&cur->wait);
                    //여기에 코드 작성              //wait queue에 wait노드 추가
                    list_add_tail(&cur->wait, &wait_q);
                    //여기에 코드 작성              //ready_q에서 삭제
                    list_del(&cur->ready);
                    //여기에 코드 작성              //Idle 시간 확인
                    Idle += cur->operations[PC].length;
                    before_clk = Clock;
                }
            }
        }
        Clock++;
    }
    total_Idle = Idle + switch_cnt * 10;
    double u = ((double)(totalclock - total_Idle) / totalclock) * 100.0;
    //여기에 코드 작성           //TOTAL CLOCK 정보 출력
    printf("*** TOTAL CLOCKS: %04d IDLE: %04d UTIL: %2.2f%%\n",
           totalclock, total_Idle, u);
    return 0;
}