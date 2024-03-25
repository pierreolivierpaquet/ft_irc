# **************************************************************************** #
#                                                                              #
#                                   IRC                                        #
#                                                                              #
# **************************************************************************** #

TARGET = ircserv

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

SRCS_PATH	:=	src/
SRCS := $(SRCS_PATH)main.cpp \
		$(SRCS_PATH)ft_irc.cpp \
		$(SRCS_PATH)Clients.cpp \
		$(SRCS_PATH)Server.cpp \

INCL_PATH	:=	include/
INCL		:=	-I $(INCL_PATH)

OBJS = $(patsubst %.cpp, bin/%.o,$(SRCS))

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

run:
	@echo "MAKE RUN\t"
	./$(TARGET) "6667" "123456789"

.PHONY: all $(TARGET) clean fclean re
