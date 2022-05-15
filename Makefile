
SRC_DIR = ./src
OBJ_DIR = ./bin

SRCS = $(notdir $(wildcard $(SRC_DIR)/*.c))
OBJS = $(SRCS:.c=.o)
# patsub pattern, change, target -> target값들을 patter값을 change로 바꿈
OBJECTS=$(patsubst %.o,$(OBJ_DIR)/%.o,$(OBJS))
DEBUG_OBJS=$(patsubst %.o, $(OBJ_DIR)/%.debug.o,$(OBJS))

schedule: 		$(OBJECTS)
				gcc -o schedule $^

debug:			$(DEBUG_OBJS)
				gcc -g -o  schedule_debug  $^

$(OBJ_DIR)/%.o:			$(SRC_DIR)/%.c
				gcc  -c  $< -o $@

$(OBJ_DIR)/%.debug.o:	$(SRC_DIR)/%.c
				gcc -g -c -DDEBUG $< -o $@

clear:		
				rm $(OBJ_DIR)/*.o schedule schedule_debug