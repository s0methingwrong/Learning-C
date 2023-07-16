CFLAGS = -g -Wall
TARGET = main
STACK = list
PERM_SRCS = main.c menu.c
LIST_STACK_SRCS = list_stack.c node.c
VECTOR_STACK_SRCS = vector_stack.c vector.c
PERM_OBJS = $(PERM_SRCS:.c=.o)
LIST_STACK_OBJS = $(LIST_STACK_SRCS:.c=.o)
VECTOR_STACK_OBJS = $(VECTOR_STACK_SRCS:.c=.o)


ifeq ($(STACK), list)
	STACK_OBJS = $(LIST_STACK_OBJS)
else 
ifeq ($(STACK), vector)
	STACK_OBJS = $(VECTOR_STACK_OBJS)
else
	STACK_OBJS = $(LIST_STACK_OBJS)
endif
endif

.PHONY: all clean 

all: $(TARGET)

$(TARGET): $(PERM_OBJS) $(STACK_OBJS)
	$(CC) -o $(TARGET) $(PERM_OBJS) $(STACK_OBJS) $(CFLAGS)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(TARGET) $(PERM_OBJS) $(LIST_STACK_OBJS) $(VECTOR_STACK_OBJS)
