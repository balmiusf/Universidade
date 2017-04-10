#define SIZE 20

typedef struct list *list;
typedef struct SingleNode *SingleNode;
typedef struct frame *frame;

struct frame
{
    char *vars[SIZE];
    int n_fa;   // last position of formal args
    int n_lc;   // last position of locals
};

struct SingleNode
{
	frame v;
	SingleNode next;
};

struct list
{
	SingleNode header;
	int size;
};

void free_list(list list);
list list_new(void);
frame getFrame(list list, int i);
void list_insert(list list, frame k);