# **************************************************************************** #
#                                                                              #
#                                   IRC                                        #
#                                                                              #
# **************************************************************************** #

TARGET		:=	ircserv

CXX			:=	c++
CXXFLAGS	:=	-Wall -Wextra -Werror -std=c++98

SRCS_PATH	:=	src/
SRCS		:=	$(SRCS_PATH)main.cpp			\
				$(SRCS_PATH)ft_irc.cpp			\
				$(SRCS_PATH)Clients.cpp			\
				$(SRCS_PATH)Server.cpp			\
				$(SRCS_PATH)Channel.cpp			\
				$(SRCS_PATH)parsing.cpp			\
				$(SRCS_PATH)Commands.cpp 		\
				$(SRCS_PATH)cmd_pass.cpp		\
				$(SRCS_PATH)cmd_user.cpp		\
				$(SRCS_PATH)cmd_nick.cpp		\
				$(SRCS_PATH)cmd_invite.cpp		\
				$(SRCS_PATH)cmd_kick.cpp		\
				$(SRCS_PATH)cmd_topic.cpp		\
				$(SRCS_PATH)cmd_channel.cpp		\
				$(SRCS_PATH)cmd_privatemsg.cpp	\
				$(SRCS_PATH)cmd_part.cpp		\
				$(SRCS_PATH)cmd_mode.cpp		\

INCL_PATH	:=	include/
INCL		:=	-I $(INCL_PATH)

OBJS		:=	$(patsubst %.cpp, bin/%.o,$(SRCS))

# **************************************************************************** #

all: $(TARGET)

bin/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(INCL)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(CXXFLAGS)

clean:
	rm -rf bin

fclean: clean
	rm -f $(TARGET)

re: fclean all

ip:
	@ipconfig getifaddr en1

pdf:
	@open https://cdn.intra.42.fr/pdf/pdf/94732/fr.subject.pdf

intra:
	@open https://projects.intra.42.fr/projects/ft_irc

debug:	CXX += -g
debug:	CXX += -Wno-unused-variable -Wno-unused-function
debug:	CXX += -Wno-unused-parameter -Wno-unused-const-variable
debug:	CXX += -Wno-unused-private-field
debug:	fclean $(OBJS) $(TARGET)

PASSWORD := toto
PORT := 6667
run: $(TARGET)
	@echo "MAKE RUN\t"
	./$(TARGET) $(PORT) $(PASSWORD)

.PHONY: all $(TARGET) clean fclean re
