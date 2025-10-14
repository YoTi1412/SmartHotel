NAME = smarthotel

CC = c++
CFLAGS = -Wall -Werror -Wextra -std=c++17 -g -fsanitize=address

SRCS_PATH = src/
UTILS_PATH = utils/
INC_PATH = include/

SRCS = main.cpp \
       Logger.cpp \
       Utils.cpp \
       BookingManager.cpp

OBJ_PATH = objs/
OBJS = $(addprefix $(OBJ_PATH), $(SRCS:.cpp=.o))

INCLUDES = -I $(INC_PATH)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $(OBJS)

$(OBJ_PATH)%.o: $(SRCS_PATH)%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_PATH)%.o: $(UTILS_PATH)%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
