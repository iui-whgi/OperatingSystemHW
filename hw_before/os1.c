//https://yjg-lab.tistory.com/122
//https://m.blog.naver.com/PostView.naver?isHttpsRedirect=true&blogId=holy_joon&logNo=221583745847

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
//헤드 추가 & 초기화
struct list_head {
	struct list_head *next, *prev;
};

#define LIST_HEAD_INIT(name) { &(name), &(name) }

#define LIST_HEAD(name) \
	struct list_head name = LIST_HEAD_INIT(name)

#define INIT_LIST_HEAD(ptr) do { \
	(ptr)->next = (ptr); (ptr)->prev = (ptr); \
} while (0)

static inline void __list_add(struct list_head *new,
			      struct list_head *prev,
			      struct list_head *next) {
	next->prev = new;
	new->next = next;
	new->prev = prev;
	prev->next = new;
}

static inline void list_add(struct list_head *new, struct list_head *head) {
	__list_add(new, head, head->next);
}

static inline void list_add_tail(struct list_head *new, struct list_head *head) {
	__list_add(new, head->prev, head);
}

static inline void __list_del(struct list_head * prev, struct list_head * next) {
	next->prev = prev;
	prev->next = next;
}

static inline void list_del(struct list_head *entry) {
	__list_del(entry->prev, entry->next);
	entry->next = LIST_POISON1;
	entry->prev = LIST_POISON2;
}

static inline void list_del_init(struct list_head *entry) {
	__list_del(entry->prev, entry->next);
	INIT_LIST_HEAD(entry);
}

static inline void list_move(struct list_head *list, struct list_head *head) {
        __list_del(list->prev, list->next);
        list_add(list, head);
}

static inline void list_move_tail(struct list_head *list,
				  struct list_head *head) {
        __list_del(list->prev, list->next);
        list_add_tail(list, head);
}

static inline int list_empty(const struct list_head *head) {
	return head->next == head;
}

#define list_entry(ptr, type, member) \
	container_of(ptr, type, member)

#define list_for_each(pos, head) \
  for (pos = (head)->next; pos != (head);	\
       pos = pos->next)

#define list_for_each_prev(pos, head) \
	for (pos = (head)->prev; prefetch(pos->prev), pos != (head); \
        	pos = pos->prev)

#define list_for_each_safe(pos, n, head) \
	for (pos = (head)->next, n = pos->next; pos != (head); \
		pos = n, n = pos->next)
// 순회
#define list_for_each_entry(pos, head, member)				\
	for (pos = list_entry((head)->next, typeof(*pos), member);	\
	     &pos->member != (head);					\
	     pos = list_entry(pos->member.next, typeof(*pos), member))
// 역순회
#define list_for_each_entry_reverse(pos, head, member)			\
	for (pos = list_entry((head)->prev, typeof(*pos), member);	\
	     &pos->member != (head); 	\
	     pos = list_entry(pos->member.prev, typeof(*pos), member))
//중간에 삭제해도 안전하게 순회
#define list_for_each_entry_safe(pos, n, head, member)			\
	for (pos = list_entry((head)->next, typeof(*pos), member),	\
		n = list_entry(pos->member.next, typeof(*pos), member);	\
	     &pos->member != (head); 					\
	     pos = n, n = list_entry(n->member.next, typeof(*n), member))
//중간에 삭제해도 안전하게 역순회
#define list_for_each_entry_safe_reverse(pos, n, head, member)		\
	for (pos = list_entry((head)->prev, typeof(*pos), member),	\
		n = list_entry(pos->member.prev, typeof(*pos), member);	\
	     &pos->member != (head); 					\
	     pos = n, n = list_entry(n->member.prev, typeof(*n), member))

#if 0    //DEBUG
#define debug(fmt, args...) fprintf(stderr, fmt, ##args)
#else
#define debug(fmt, args...)
#endif


typedef struct{
    unsigned char operation; //operation
    unsigned char length;   //length
} code; //코드 구조체 


typedef struct {
    int pid; //ID
    int arrival_time; //도착시간
    int code_bytes; //코드길이(바이트)
    code *operations;
    struct list_head job, ready, wait;
} process; //프로세스 구조체


int main(int argc, char* argv[]){
    //이중 연결리스트는 각 노드가 선행 노드와 후속노드에 대한 링크를 가지는 리스트이다.
    //헤드노드: 데이터를 가지지 않고 오로지 삽입, 삭제코드를 간단하게 할 목적으로 만들어진 노드이다

    process *cur, *next; //포인터 생성

    LIST_HEAD(job_q); //job_q 헤드 생성
	LIST_HEAD(ready_q); //ready_q 헤드 생성
	LIST_HEAD(wait_q); //wait_q 헤드 생성
	// 리스트의 시작을 가리키는 head는 데이터에 포함되지 않은 단일 구조체여야 함
	// 선언과 초기화를 동시에 진행

    cur = malloc(sizeof(*cur));

    while(fread(cur,12,1,stdin) == 1){ //프로세스 구조체 크기만큼 읽어들임
        cur->operations = malloc((cur->code_bytes/2)*sizeof(code));
        fread(cur->operations,((cur->code_bytes/2)*sizeof(code)),1,stdin);
		//여기에 코드 작성         // job노드 초기화
		//여기에 코드 작성         // job queue에 job노드 추가
        
		cur = malloc(sizeof(*cur));
    }

	//반대로 출력하는 코드 작성
  



	
}
