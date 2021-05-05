#
#  Lecture sample programs
#

CC	= gcc
CFLAGS	= -O0 -Wall -MMD -g 
LDFLAGS	=

TARGET = \
	hello_world	\
	hello_world2	\
	a_plus_b	\
	plus		\
	multi		\
	multi_flat	\
	square		\
	get_mem		\
	get_stack	\
	get_stack2	\
	fork_mem	\
	fork_exec	\
	fork_exec2	\
	fork_exec2.1	\
	fork_exec2.2	\
	fork_exec2.3	\


SRC_DIR = src

.PHONY:	all clean


all:	$(TARGET)

clean:
	rm -f $(TARGET) *.d

-include *.d

%:	$(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $^ -o $@

