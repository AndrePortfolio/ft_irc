NAME = ircserv
CXXFLAGS = -Wall -Wextra -Werror #-std=c++98
CXX = c++
COMPRESS = ar rcs
RM = rm -rf

OBJ_DIR = objects
SRC_DIR = sources
CMD_SRC_DIR = $(SRC_DIR)/commands
SRC_DIRS = $(SRC_DIR) $(SRC_DIR)/commands
HEADER = includes
S1 = main server client acceptClients runServer handleData utils
S2 = help #invite join kick mode nick oper part pass ping privmsg quit topic user
SRC =
SRC += $(addprefix $(SRC_DIR)/,$(addsuffix .cpp, $(S1)))
SRC += $(addprefix $(CMD_SRC_DIR)/,$(addsuffix .cpp, $(S2)))
OBJ = $(addprefix $(OBJ_DIR)/,$(notdir $(SRC:.cpp=.o)))

# Colours
GREEN = \033[1;32m
ORANGE = \033[1;33m
RED = \033[1;31m
CYAN = \033[1;36m
RESET = \033[0m

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ)
	@$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME) -I $(HEADER)
	@echo "$(CYAN)make$(RESET)   $@ $(GREEN)[OK]$(RESET)"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR) $(foreach dir, $(SRC_DIRS), $(OBJ_DIR)/$(notdir $(dir)))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@$(CXX) $(CXXFLAGS) -c $< -o $@ -I $(HEADER)

$(OBJ_DIR)/%.o: $(CMD_SRC_DIR)/%.cpp
	@$(CXX) $(CXXFLAGS) -c $< -o $@ -I $(HEADER)

clean:
	@$(RM) $(OBJ_DIR)
	@echo "$(ORANGE)$@$(RESET)  $(NAME) $(GREEN)[OK]$(RESET)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(RED)$@$(RESET) $(NAME) $(GREEN)[OK]$(RESET)"

re: fclean all

git:
	find . -type f -name '*.o' -exec rm {} +
	@git add .
	@git commit
	@git push
	@clear
	@echo "|                                                 |"
	@echo "|                                                 |"
	@echo "|      -------{ Commited and Pushed }-------      |"
	@echo "|                                                 |"
	@echo "|                                                 |"

.PHONY: all clean fclean re
